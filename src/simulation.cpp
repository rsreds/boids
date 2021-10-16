#include "simulation.hpp"

Simulation::Simulation(int width, int height,std::string title)
    : width_(width), height_(height), title_(title), running(true) {}

Simulation::~Simulation() { window.close(); }

int Simulation::run() {
  createWindow();

  // Boids boids;
  // boids.start()
  while (running) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return EXIT_SUCCESS;
      }
    }
    window.clear();
    // boids.update();
    // boids.show(window);
    window.display();
  }
  return EXIT_SUCCESS;
}

void Simulation::createWindow() {
  if (window.isOpen())
    window.close();
  window.create(sf::VideoMode(width_, height_), title_,
                sf::Style::Close);
  auto desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i(desktop.width / 2 - width_ / 2,
                                  desktop.height / 2 - height_ / 2));
}