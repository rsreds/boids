#include "boids/simulation.hpp"
#include "boids/boids.hpp"

Simulation::Simulation(std::shared_ptr<Parameters> param)
    : param(param), view_width_(param.get()->view_width()),
      view_height_(param.get()->view_height()), title_(param.get()->title()),
      running(true) {}

Simulation::~Simulation() { window.close(); }

int Simulation::run() {
  createWindow();
  Boids boids(param);
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
    float elapsed_time = clock.getElapsedTime().asSeconds();
    clock.restart();
    boids.update(elapsed_time);
    boids.show(window);
    window.display();
  }
  return EXIT_SUCCESS;
}

void Simulation::createWindow() {
  if (window.isOpen())
    window.close();
  window.create(sf::VideoMode(view_width_, view_height_), title_,
                sf::Style::Close);
  auto desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i(desktop.width / 2 - view_width_ / 2,
                                  desktop.height / 2 - view_height_ / 2));
}