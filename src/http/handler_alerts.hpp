#pragma once

#include <string>

namespace pulso {
    struct MetricSnapshot;
    namespace alertas { class GestorAlertas; }
}

namespace pulso::http {

/**
 * @brief Genera el JSON de GET /alerts con las alertas activas para el snapshot dado.
 */
std::string handleAlerts(const pulso::alertas::GestorAlertas& gestor,
                         const pulso::MetricSnapshot& snap);

} // namespace pulso::http