#include "handler_alerts.hpp"
#include "pulso/alertas/alerta_umbral.hpp"
#include "pulso/core/metrics.hpp"
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

} // namespace pulso::http