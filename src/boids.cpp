#include "boids/boids.hpp"
#include <algorithm>
#include <iostream>
#include <random>

Boids::Boids(std::shared_ptr<Parameters> param)
    : param(param), numboids_(param.get()->num_boids()), width_(param.get()->view_width()),
      height_(param.get()->view_height()) {
  boids_.reserve(numboids_);
  init_boids();
}

void Boids::init_boids() {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> dist_width(param.get()->margin(), width_ - param.get()->margin());
  std::uniform_real_distribution<float> dist_height(param.get()->margin(), height_ - param.get()->margin());
  std::uniform_real_distribution<float> dist_speed(-0.5, 0.5);
  std::uniform_int_distribution<int> dist_flocks(0, param.get()->num_flocks()-1);
  for (int i = 0; i < numboids_; ++i) {
    boids_.emplace_back(Boid{sf::Vector2f(dist_width(eng), dist_height(eng)),
                             sf::Vector2f(dist_speed(eng), dist_speed(eng)),
                             std::vector<sf::Vector2f>(), dist_flocks(eng)});
  }
}

void Boids::show(sf::RenderWindow &window) {
  for (auto &boid : boids_) {
    sf::CircleShape body(2.5);
    sf::Vertex direction[] = {
        sf::Vertex(boid.pos, getColor(boid.flock_id)),
        sf::Vertex(boid.pos + param.get()->simulation_speed()/10 * boid.spd, getColor(boid.flock_id))};
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(boid.pos);
    body.setFillColor(getColor(boid.flock_id));
    window.draw(body);
    window.draw(direction, 2, sf::Lines);
  }
}

void Boids::update(float elapsed_time) {
  sf::Clock clock;
  for (auto &boid : boids_) {
    Flock neighbors = getNeighbors(boid);
    keepWithinBounds(boid);
    flyTowardsCenter(boid, neighbors);
    avoidOthers(boid, neighbors);
    matchVelocity(boid, neighbors);
    limitSpeed(boid);
    boid.pos += boid.spd * (param.get()->simulation_speed() * elapsed_time);
  }
}

void Boids::keepWithinBounds(Boid &boid) {
  float turnfactor = 0.05;
  if (boid.pos.x < param.get()->margin())
    boid.spd.x += turnfactor;
  if (boid.pos.y < param.get()->margin())
    boid.spd.y += turnfactor;
  if (boid.pos.x > (width_ - param.get()->margin()))
    boid.spd.x -= turnfactor;
  if (boid.pos.y > (height_ - param.get()->margin()))
    boid.spd.y -= turnfactor;
}

Flock Boids::getNeighbors(Boid const &boid) {
  Flock neighbors;
  for (auto &otherboid : boids_) {
    // if (boid != otherboid)
    if (isInView(otherboid, boid, param.get()->view_range(), param.get()->view_angle()))
    // if (distance(boid, otherboid) < param.get()->view_range())
      neighbors.push_back(otherboid);
  }
  return neighbors;
}

void Boids::flyTowardsCenter(Boid &boid, Flock const &neighbors) {
  sf::Vector2f center_of_mass{0.f, 0.f};
  int num_neighbours = 0;
  for (auto &neighbor : neighbors) {
    if (boid.flock_id != neighbor.flock_id)
      continue;
    ++num_neighbours;
    center_of_mass += neighbor.pos;
  }
  center_of_mass = center_of_mass / (float)num_neighbours;
  sf::Vector2f delta_pos = center_of_mass - boid.pos;
  boid.spd += delta_pos * param.get()->cohesion();
}

void Boids::avoidOthers(Boid &boid, Flock const &neighbors) {
  sf::Vector2f dispalcement{0.f, 0.f};
  for (auto &neighbor : neighbors) {
    if (distance(boid, neighbor) < param.get()->separation()) {
      dispalcement -= (neighbor.pos - boid.pos);
    }
  }
  boid.spd += dispalcement * 0.0008f;
}

void Boids::matchVelocity(Boid &boid, Flock const &neighbors) {
  sf::Vector2f neighbors_speed{0.f, 0.f};
  int num_neighbor = 0;
  for (auto &neighbor : neighbors) {
    if (boid.flock_id != neighbor.flock_id)
      continue;
    ++num_neighbor;
    neighbors_speed += neighbor.spd;
  }
  neighbors_speed = neighbors_speed / (float)num_neighbor;
  boid.spd += (neighbors_speed - boid.spd) * param.get()->alignment();
}

void Boids::limitSpeed(Boid &boid) {
  float vlim = 1;
  if (lenght(boid.spd) > vlim) {
    boid.spd = (boid.spd / lenght(boid.spd)) * vlim;
  }
}

sf::Color getColor(int i) {
  switch (i) {
  case 0:
    return sf::Color::Green;
  case 1:
    return sf::Color::Blue;
  case 2:
    return sf::Color::Red;
  default:
    return sf::Color::Yellow;
    break;
  }
}