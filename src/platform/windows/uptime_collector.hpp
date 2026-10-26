#pragma once

#include "../../collectors/uptime/uptime_collector.hpp"

#ifdef _WIN32

namespace ChuspaPulse::platform::windows {

UptimeInfo getUptimeWindows();

}

#endif
