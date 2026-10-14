#include "alertas/gestor_alertas.hpp"
#include "core/MetricSnapshot.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <cassert>
#include <iostream>

int main() {
    // 1. Base de datos en memoria para el test
    SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE alerts (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp INTEGER, metrica TEXT, umbral REAL, valor REAL, mensaje TEXT)");

    // 2. Instanciar gestor y agregar alerta de prueba
    pulso::alertas::GestorAlertas gestor(db);
    pulso::alertas::AlertaUmbral alerta("cpu", 80.0, "Uso elevado de CPU");
    gestor.addAlerta(alerta);

    // 3. Crear snapshot y evaluar
    pulso::MetricSnapshot snap;
    snap.nombre = "cpu";
    snap.valor = 85.0;

    gestor.evaluar(snap);

    // 4. Verificar que se persistió correctamente en el historial
    auto historial = gestor.obtenerHistorial();
    assert(historial.size() == 1);
    assert(historial[0].metrica == "cpu");
    assert(historial[0].valor == 85.0);

    std::cout << "Test de persistencia de alertas completado con exito!" << std::endl;
    return 0;
}