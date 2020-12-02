// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>

#include <gtest/gtest.h>

#include <Cache_tester.hpp>

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
    Cache_tester first(64, 4096);
}
