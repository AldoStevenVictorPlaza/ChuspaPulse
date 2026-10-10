#include "handler_alerts.hpp"
#include "pulso/alertas/alerta_umbral.hpp"
#include "pulso/core/metrics.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <sstream>
#include <vector>

namespace pulso::http {

static double obtenerValorMetrica(const std::string& metrica, const pulso::MetricsSnapshot& snap) {
    if (metrica == "cpu" || metrica == "cpu.usage_pct") return snap.cpu;
    if (metrica == "ram") return snap.ram;
    if (metrica == "disk") return snap.disk;
    if (metrica == "rx_bytes") return snap.rx_bytes;
    if (metrica == "tx_bytes") return snap.tx_bytes;
    return 0.0;
}

std::string handleAlerts(const pulso::GestorAlertas& gestor, const pulso::MetricsSnapshot& snap) {
    std::ostringstream json;
    json << "{\n  \"alerts\": [";

    bool primera = true;
    
    for (const auto& alerta : gestor.getAlertas()) {
        if (alerta.evaluar(snap)) {
            if (!primera) {
                json << ",";
            }
            primera = false;

            double valor_actual = obtenerValorMetrica(alerta.metrica(), snap);

            json << "\n    {\n"
                 << "      \"metrica\": \"" << alerta.metrica() << "\",\n"
                 << "      \"umbral\": " << alerta.umbral() << ",\n"
                 << "      \"operador\": \"" << alerta.operador() << "\",\n"
                 << "      \"valor_actual\": " << valor_actual << ",\n"
                 << "      \"mensaje\": \"" << alerta.mensaje() << "\"\n"
                 << "    }";
        }
    }

    if (!primera) {
        json << "\n  ";
    }
    json << "]\n}";

    return json.str();
}

std::string handleAlertsHistory(SQLite::Database& db, int limit, int offset) {
    std::ostringstream json;
    json << "{\n  \"history\": [";

    try {
        SQLite::Statement query(db,
            "SELECT timestamp, metrica, umbral, valor, mensaje "
            "FROM alerts ORDER BY timestamp DESC LIMIT ? OFFSET ?"
        );

        query.bind(1, limit);
        query.bind(2, offset);

        bool primera = true;
        while (query.executeStep()) {
            if (!primera) {
                json << ",";
            }
            primera = false;

            long long timestamp = query.getColumn(0).getInt64();
            std::string metrica = query.getColumn(1).getText();
            double umbral = query.getColumn(2).getDouble();
            double valor = query.getColumn(3).getDouble();
            std::string mensaje = query.getColumn(4).getText();

            json << "\n    {\n"
                 << "      \"timestamp\": " << timestamp << ",\n"
                 << "      \"metrica\": \"" << metrica << "\",\n"
                 << "      \"umbral\": " << umbral << ",\n"
                 << "      \"valor\": " << valor << ",\n"
                 << "      \"mensaje\": \"" << mensaje << "\"\n"
                 << "    }";
        }

        if (!primera) {
            json << "\n  ";
        }
    } catch (const std::exception& e) {
        // En caso de error de base de datos, devuelve una lista vacía o maneja la excepción
    }

    json << "]\n}";
    return json.str();
}

} // namespace pulso::http