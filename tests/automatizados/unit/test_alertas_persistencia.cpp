#include <gtest/gtest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "alertas/gestor_alertas.hpp"
#include "core/MetricSnapshot.hpp"

TEST(GestorAlertasTest, GuardarYConsultarHistorial) {
    SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE alerts (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp INTEGER, metrica TEXT, umbral REAL, valor REAL, mensaje TEXT)");

    pulso::alertas::GestorAlertas gestor(db);
    pulso::alertas::AlertaUmbral alerta("cpu", 80.0, "Uso elevado de CPU");
    gestor.addAlerta(alerta);

    pulso::MetricSnapshot snap;
    snap.nombre = "cpu";
    snap.valor = 85.0;

    gestor.evaluar(snap);

    auto historial = gestor.obtenerHistorial();
    ASSERT_EQ(historial.size(), 1);
    EXPECT_EQ(historial[0].metrica, "cpu");
    EXPECT_DOUBLE_EQ(historial[0].valor, 85.0);
}