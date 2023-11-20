//
// Created by Tobias De Gasperis on 12.05.22.
//
//
// Basisdatei zum Erstellen von Tests
//

#include "gtest/gtest.h"
#include "dummy.h"

TEST(DummyTest, addsuccess){
    Dummy d = Dummy(1);
    EXPECT_EQ(d.add(2), 3);
}

TEST(DummyTest, addfail){
    Dummy d = Dummy(2);
    EXPECT_EQ(d.add(2), 3);
}