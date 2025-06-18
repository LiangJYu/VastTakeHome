#include <iostream>
#include <string>

#include "OperationClock.h"

auto main() -> int
{
  MiningSimulation::OperationClock op_clock;
  while (op_clock.expired()) {
    ++op_clock;
  }
  return 0;
}
