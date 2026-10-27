#pragma once

#include <httplib.h>

#include "../storage/storage.hpp"
#include "../formatters/iformatter.hpp"

namespace ChuspaPulse::http {

void registrarHistory(
    httplib::Server& servidor,
    const ChuspaPulse::storage::Storage& storage,
    const ChuspaPulse::formatters::IFormatter& formatter);

} // namespace ChuspaPulse::http