#include "OperationClock.h"

auto main() -> int
{
  MiningSimulation::OperationClock op_clock;
  while (op_clock.not_expired()) {
    ++op_clock;
  }
  return 0;
}
