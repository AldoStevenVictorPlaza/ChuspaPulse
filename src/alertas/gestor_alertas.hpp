#pragma once

#include <vector>
#include <functional>
#include <string>
#include "alerta_umbral.hpp"

namespace pulso::alertas {

/**
 * @brief Gestor de múltiples alertas de umbral con callback de notificación.
 *
 * Permite registrar varias AlertaUmbral y evaluarlas todas contra un
 * MetricSnapshot. Cuando una alerta se dispara, ejecuta un callback
 * con el mensaje descriptivo de la alerta.
 */
class GestorAlertas {
public:
    GestorAlertas() = default;
    ~GestorAlertas() = default;

    /**
     * @brief Registra una nueva alerta en el gestor.
     * @param alerta Instancia de AlertaUmbral a agregar.
     */
    void addAlerta(const AlertaUmbral& alerta);

    /**
     * @brief Establece el callback de notificación.
     * @param callback Función que recibe el mensaje de la alerta disparada.
     */
    void setCallback(std::function<void(const std::string&)> callback);

    /**
     * @brief Evalúa todas las alertas registradas contra el snapshot.
     *
     * Solo llama el callback para las alertas que se disparan.
     * Si no hay callback registrado, no hace nada.
     * Si no hay alertas registradas, no hace nada.
     *
     * @param snap Snapshot con las métricas actuales del sistema.
     */
    void evaluar(const pulso::MetricSnapshot& snap) const;

    /**
     * @brief Devuelve la cantidad de alertas registradas.
     * @return Número de alertas en el gestor.
     */
    std::size_t cantidadAlertas() const;

    /**
     * @brief Devuelve las alertas registradas.
     */
    const std::vector<AlertaUmbral>& getAlertas() const;

private:
    std::vector<AlertaUmbral> alertas_;
    std::function<void(const std::string&)> callback_;
};

} // namespace pulso::alertas
