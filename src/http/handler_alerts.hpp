#pragma once

#include <string>

namespace ChuspaPulse {
    struct MetricSnapshot;
    namespace alertas { class GestorAlertas; }
}

namespace ChuspaPulse::http {

/**
 * @brief Genera el JSON de GET /alerts con las alertas activas para el snapshot dado.
 */
std::string handleAlerts(const ChuspaPulse::alertas::GestorAlertas& gestor,
                         const ChuspaPulse::MetricSnapshot& snap);

} // namespace ChuspaPulse::http