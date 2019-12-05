#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "AutoGraph.hpp"

using namespace std;
using namespace testing;

class ActorGraphTest : public ::testing::Test {
  protected:
    ActorGraph actors;

  public:
    ActorGraphTest() {}
};
