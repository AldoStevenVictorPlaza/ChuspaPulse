#include "gestor_alertas.hpp"
#include <chrono>

namespace pulso::alertas {

GestorAlertas::GestorAlertas(SQLite::Database& db) : db_(&db) {}

void GestorAlertas::addAlerta(const AlertaUmbral& alerta) {
    alertas_.push_back(alerta);
}

void GestorAlertas::setCallback(std::function<void(const std::string&)> callback) {
    callback_ = callback;
}

void GestorAlertas::evaluar(const pulso::MetricSnapshot& snap) const {
    if (alertas_.empty()) {
        return;
    }

    for (const auto& alerta : alertas_) {
        if (alerta.evaluar(snap)) {
            // 1. Ejecutar callback si existe
            if (callback_) {
                callback_(alerta.mensaje());
            }

            // 2. Persistir alerta en SQLite si la BD está configurada
            if (db_) {
                auto now = std::chrono::system_clock::now();
                auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                    now.time_since_epoch()
                ).count();

                SQLite::Statement query(*db_, 
                    "INSERT INTO alerts (timestamp, metrica, umbral, valor, mensaje) "
                    "VALUES (?, ?, ?, ?, ?)"
                );

                query.bind(1, static_cast<long long>(timestamp));
                query.bind(2, snap.nombre);
                query.bind(3, alerta.umbral());
                query.bind(4, snap.valor);
                query.bind(5, alerta.mensaje());

                query.exec();
            }
        }
    }
}

std::size_t GestorAlertas::cantidadAlertas() const {
    return alertas_.size();
}


std::vector<RegistroAlerta> GestorAlertas::obtenerHistorial() const {
    std::vector<RegistroAlerta> historial;
    if (!db_) return historial;

    try {
        SQLite::Statement query(*db_, 
            "SELECT id, timestamp, metrica, umbral, valor, mensaje FROM alerts ORDER BY id DESC"
        );

        while (query.executeStep()) {
            RegistroAlerta reg;
            reg.id = query.getColumn(0).getInt();
            reg.timestamp = query.getColumn(1).getInt64();
            reg.metrica = query.getColumn(2).getText();
            reg.umbral = query.getColumn(3).getDouble();
            reg.valor = query.getColumn(4).getDouble();
            reg.mensaje = query.getColumn(5).getText();
            historial.push_back(reg);
        }
    } catch (const std::exception& e) {
        // En caso de que la tabla aún no exista
    }

    return historial;
}
} // namespace pulso::alertas

