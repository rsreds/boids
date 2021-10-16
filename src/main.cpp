#include "boids/simulation.hpp"

int main() {
  Simulation simulation(640, 480, "Boids");
  simulation.run();
  return EXIT_SUCCESS;
}
