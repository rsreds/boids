#include "boids/param.hpp"
#include "boids/simulation.hpp"
#include <memory>

int main() {
  auto param = std::make_shared<Parameters>();
  Simulation simulation(param);
  simulation.run();
  return EXIT_SUCCESS;
}
