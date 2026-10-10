#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <functional>
#include <string>
#include "alerta_umbral.hpp"

namespace pulso::alertas {

/**
 * @brief Gestor de múltiples alertas de umbral con callback de notificación y persistencia en SQLite.
 *
 * Permite registrar varias AlertaUmbral y evaluarlas todas contra un
 * MetricSnapshot. Cuando una alerta se dispara, ejecuta el callback
 * y guarda un registro en la base de datos si esta fue configurada.
 */
class GestorAlertas {
public:
    GestorAlertas() = default;
    explicit GestorAlertas(SQLite::Database& db) : db_(&db) {}
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
     * Ejecuta el callback y guarda la alerta disparada en la tabla `alerts`.
     *
     * @param snap Snapshot con las métricas actuales del sistema.
     */
    void evaluar(const pulso::MetricSnapshot& snap) const;

    /**
     * @brief Devuelve la cantidad de alertas registradas.
     * @return Número de alertas en el gestor.
     */
    std::size_t cantidadAlertas() const;

private:
    SQLite::Database* db_{nullptr};
    std::vector<AlertaUmbral> alertas_;
    std::function<void(const std::string&)> callback_;
};

} // namespace pulso::alertas