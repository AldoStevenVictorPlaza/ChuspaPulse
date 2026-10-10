#include "schema.hpp"

namespace pulso::storage {
/**
 * @brief Inicializa el esquema de la base de datos SQLite.
 *
 * Crea la tabla `snapshots` para métricas y la tabla `alerts`
 * para almacenar el historial de alertas disparadas.
 *
 * @param db Referencia a la base de datos SQLite ya abierta.
 * @throws SQLite::Exception si la ejecución del SQL falla.
 */
void inicializarEsquema(SQLite::Database& db) {

    db.exec(
        "CREATE TABLE IF NOT EXISTS snapshots ("
        "   timestamp INTEGER NOT NULL,"
        "   nombre    TEXT    NOT NULL,"
        "   valor     REAL    NOT NULL,"
        "   unidad    TEXT    NOT NULL"
        ");"
    );

    db.exec(
        "CREATE INDEX IF NOT EXISTS idx_snapshots_timestamp "
        "ON snapshots(timestamp);"
    );

    db.exec(
        "CREATE TABLE IF NOT EXISTS alerts ("
        "   id        INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   timestamp INTEGER NOT NULL,"
        "   metrica   TEXT    NOT NULL,"
        "   umbral    REAL    NOT NULL,"
        "   valor     REAL    NOT NULL,"
        "   mensaje   TEXT    NOT NULL"
        ");"
    );

    db.exec(
        "CREATE INDEX IF NOT EXISTS idx_alerts_timestamp "
        "ON alerts(timestamp);"
    );
}

} // namespace pulso::storage