#if !defined(SIMULATION)
#define SIMULATION

#include <string>
#include <SFML/Graphics.hpp>

class Simulation
{
private:
  int width_;
  int height_;
  std::string title_;
  sf::RenderWindow window;
  bool running;
  void createWindow();
public:
  Simulation(int width, int height, std::string title);
  ~Simulation();
  int run();
  void stop();
};

#endif // SIMULATION
