#pragma once

#include <string>
#include <vector>

#include "iformatter.hpp"

namespace ChuspaPulse::formatters {

class FormatterPrometheus : public IFormatter {
public:
    std::string formato() const override;

    std::string contentType() const override;

    std::string formatear(
        const ChuspaPulse::core::Snapshot& snapshot) const override;

    std::string formatearHistorial(
        const std::vector<ChuspaPulse::core::Snapshot>& snapshots) const override;
};

} // namespace ChuspaPulse::formatters