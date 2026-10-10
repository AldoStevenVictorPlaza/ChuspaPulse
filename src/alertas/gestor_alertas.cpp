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

} // namespace pulso::alertas