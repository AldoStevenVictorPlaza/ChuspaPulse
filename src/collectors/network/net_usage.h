#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "../icollector.hpp"

typedef struct {
    uint64_t rx_bytes;
    uint64_t tx_bytes;
} NetInfo;

NetInfo getNetUsage();

namespace ChuspaPulse::collectors::network {

class NetworkCollector : public ChuspaPulse::collectors::ICollector {
public:
    std::string nombre() const override;
    std::vector<ChuspaPulse::core::Metrica> recolectar() override;
};

}  // namespace ChuspaPulse::collectors::network
