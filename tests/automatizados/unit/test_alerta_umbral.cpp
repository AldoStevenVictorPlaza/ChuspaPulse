#include <gtest/gtest.h>
#include <stdexcept>
#include "alertas/alerta_umbral.hpp"
#include "core/MetricSnapshot.hpp"

using namespace pulso::alertas;
using namespace pulso;

TEST(AlertaUmbralTest, OperadorMayorDisparaCuandoSuperaUmbral)
{
    AlertaUmbral alerta("cpu.usage_pct", 50.0f, '>');
    
    MetricSnapshot snap;
    snap.cpu = 65.5;
    
    EXPECT_TRUE(alerta.evaluar(snap));
}

TEST(AlertaUmbralTest, OperadorMayorNoDisparaSiEstaPorDebajo)
{
    AlertaUmbral alerta("cpu.usage_pct", 50.0f, '>');
    
    MetricSnapshot snap;
    snap.cpu = 30.0;
    
    EXPECT_FALSE(alerta.evaluar(snap));
}

TEST(AlertaUmbralTest, OperadorMenorDisparaCuandoEsInferiorAlUmbral)
{
    AlertaUmbral alerta("ram", 20.0f, '<');
    
    MetricSnapshot snap;
    snap.ram = 15.2;
    
    EXPECT_TRUE(alerta.evaluar(snap));
}

TEST(AlertaUmbralTest, LanzaInvalidArgumentSiElOperadorEsInvalido)
{
    EXPECT_THROW(
        AlertaUmbral("cpu.usage_pct", 50.0f, 'X'),
        std::invalid_argument
    );
}

TEST(AlertaUmbralTest, MensajeRetornaStringNoVacio)
{
    AlertaUmbral alerta("temperatura", 38.0f, '>');
    
    std::string msg = alerta.mensaje();
    EXPECT_FALSE(msg.empty());
}

TEST(AlertaUmbralTest, EvaluarLanzaInvalidArgumentSiLaMetricaNoExiste)
{
    AlertaUmbral alerta("temperatura", 38.0f, '>');

    MetricSnapshot snap;
    snap.cpu = 50.0;
    snap.ram = 40.0;

    EXPECT_THROW(alerta.evaluar(snap), std::invalid_argument);
}

TEST(AlertaUmbralTest, GettersRetornanLosDatosDeConstruccion)
{
    AlertaUmbral alerta("ram", 75.5f, '<');

    EXPECT_EQ(alerta.metrica(), "ram");
    EXPECT_FLOAT_EQ(alerta.umbral(), 75.5f);
    EXPECT_EQ(alerta.operador(), '<');
}
