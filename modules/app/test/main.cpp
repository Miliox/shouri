#include <gtest/gtest.h>

TEST (SampleTest, Success) { 
    EXPECT_EQ (1, 1);
}

TEST (SampleTest, Failure) { 
    EXPECT_EQ (1, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}