#pragma once

#include <httplib.h>
#include "storage/storage.hpp"

namespace ChuspaPulse::http {

/// Registra el handler de /metrics/prometheus en el servidor httplib.
void registrarPrometheus(
    httplib::Server& servidor,
    const ChuspaPulse::storage::Storage& storage);

} // namespace ChuspaPulse::http