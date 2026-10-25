#include "handler_version.hpp"
#include "../core/version.hpp"

namespace ChuspaPulse {
namespace http {

    std::string handleVersion() {
        return "{\"version\": \"" + ChuspaPulse::APP_VERSION + "\"}";
    }

} // namespace http
} // namespace ChuspaPulse
