#if !defined(SIMULATION)
#define SIMULATION

#include "boids/param.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Simulation {
private:
  std::shared_ptr<Parameters> param;
  int view_width_;
  int view_height_;
  std::string title_;
  sf::RenderWindow window;
  bool running;
  void createWindow();
  sf::Clock clock;

public:
  Simulation(std::shared_ptr<Parameters> param);
  ~Simulation();
  int run();
  void stop();
};

#endif // SIMULATION
