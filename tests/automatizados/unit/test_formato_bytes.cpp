
#include <gtest/gtest.h>

#include "utils/formato_bytes.hpp"

TEST(FormatoBytesHumanosTest, BytesMenoresA1024) {
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(800), "800.0 B");
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(1), "1.0 B");
}

TEST(FormatoBytesHumanosTest, PotenciasDe1024) {
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(1024), "1.0 KB");
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(1048576), "1.0 MB");
}

TEST(FormatoBytesHumanosTest, ValoresIntermedios) {
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(1536), "1.5 KB");
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(2621440), "2.5 MB");
}

TEST(FormatoBytesHumanosTest, ValoresNegativos) {
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(-1536), "-1.5 KB");
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(-800), "-800.0 B");
}

TEST(FormatoBytesHumanosTest, ValorCero) {
    EXPECT_EQ(pulso::utils::formatearBytesHumanos(0), "0.0 B");
}
