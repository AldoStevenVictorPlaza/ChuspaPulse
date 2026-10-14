#pragma once
#ifndef METRIC_SNAPSHOT_HPP
#define METRIC_SNAPSHOT_HPP

#include <string>
#include <chrono>

namespace pulso {

struct MetricSnapshot {
    std::string nombre;
    double valor;
    double cpu;
    double ram;
    double disk;
    double rx_bytes;
    double tx_bytes;
    std::chrono::system_clock::time_point timestamp;

    // Constructor por defecto
    MetricSnapshot()
        : nombre("")
        , valor(0.0)
        , cpu(0.0)
        , ram(0.0)
        , disk(0.0)
        , rx_bytes(0.0)
        , tx_bytes(0.0)
        , timestamp(std::chrono::system_clock::now()) {}

    // Constructor completo con nombre y valor
    MetricSnapshot(const std::string& nom, double val, double cpu_val = 0.0, 
                   double ram_val = 0.0, double disk_val = 0.0,
                   double rx_val = 0.0, double tx_val = 0.0)
        : nombre(nom)
        , valor(val)
        , cpu(cpu_val)
        , ram(ram_val)
        , disk(disk_val)
        , rx_bytes(rx_val)
        , tx_bytes(tx_val)
        , timestamp(std::chrono::system_clock::now()) {}

    // Verifica que las métricas principales sean válidas
    bool isValid() const {
        return !nombre.empty() && valor >= 0.0;
    }
};

} // namespace pulso
#endif