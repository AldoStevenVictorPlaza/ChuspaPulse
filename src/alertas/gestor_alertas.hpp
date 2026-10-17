#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <functional>
#include <string>
#include <cstdint>
#include "alerta_umbral.hpp"

namespace pulso::alertas {

struct RegistroAlerta {
    int id{0};
    int64_t timestamp{0};
    std::string metrica;
    double umbral{0.0};
    double valor{0.0};
    std::string mensaje;
};

class GestorAlertas {
public:
    GestorAlertas() = default;
    explicit GestorAlertas(SQLite::Database& db);
    ~GestorAlertas() = default;

    void addAlerta(const AlertaUmbral& alerta);
    void setCallback(std::function<void(const std::string&)> callback);
    void evaluar(const pulso::MetricSnapshot& snap) const;
    std::size_t cantidadAlertas() const;

    // Método que requiere la API para GET /alerts/history
    std::vector<RegistroAlerta> obtenerHistorial(std::size_t limite = 100, std::size_t offset = 0) const;

private:
    SQLite::Database* db_{nullptr};
    std::vector<AlertaUmbral> alertas_;
    std::function<void(const std::string&)> callback_;
};

} // namespace pulso::alertas