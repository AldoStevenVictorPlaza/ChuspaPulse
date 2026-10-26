#include "sampler.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

namespace ChuspaPulse::sampler {

Sampler::Sampler(
    std::vector<std::shared_ptr<ChuspaPulse::collectors::ICollector>> collectors,
    ChuspaPulse::storage::Storage& storage,
    int intervaloSegundos,
    SnapshotCallback onSnapshot)
    : collectors_(std::move(collectors)),
      storage_(storage),
      intervaloSegundos_(intervaloSegundos),
      onSnapshot_(std::move(onSnapshot)) {}

Sampler::~Sampler() {
    detener();
}

void Sampler::iniciar() {
    if (corriendo_) {
        return;
    }

    corriendo_ = true;

    // Thread encargado de ejecutar la recolección periódica de métricas.
    thread_ = std::thread([this]() {
        while (corriendo_) {

            ChuspaPulse::core::Snapshot snapshot;
            snapshot.timestamp = std::time(nullptr);

            for (const auto& collector : collectors_) {
                try {

                    auto metricas = collector->recolectar();

                    snapshot.metricas.insert(
                        snapshot.metricas.end(),
                        metricas.begin(),
                        metricas.end());

                } catch (const std::exception& e) {

                    std::cerr << "Error en collector: "
                              << e.what()
                              << std::endl;
                }
            }

            try {

                storage_.save(snapshot);

            } catch (const std::exception& e) {

                std::cerr << "Error al guardar snapshot: "
                          << e.what()
                          << std::endl;
            }
            
                        if (onSnapshot_) {
                try {
                    onSnapshot_(snapshot);
                } catch (const std::exception& e) {
                    std::cerr << "Error al evaluar snapshot: "
                              << e.what()
                              << std::endl;
                }
            }

            std::unique_lock<std::mutex> lock(mutex_);

            cv_.wait_for(
                lock,
                std::chrono::seconds(intervaloSegundos_),
                [this]() {
                    return !corriendo_;
                });
        }
    });
}

void Sampler::detener() {
    if (!corriendo_) {
        return;
    }

    corriendo_ = false;

    cv_.notify_all();

    if (thread_.joinable()) {
        thread_.join();
    }
}

bool Sampler::corriendo() const {
    return corriendo_;
}

} // namespace ChuspaPulse::sampler
