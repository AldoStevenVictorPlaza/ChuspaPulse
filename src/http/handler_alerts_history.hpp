#pragma once

#include <string>

namespace pulso {
    class MetricsSnapshot;
    class GestorAlertas;
}

namespace pulso::http {

/**
 * @brief Genera una respuesta JSON para el endpoint GET /alerts con las alertas activas.
 */
std::string handleAlerts(const pulso::GestorAlertas& gestor, const pulso::MetricsSnapshot& snap);

} // namespace pulso::http