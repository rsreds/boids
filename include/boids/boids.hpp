#if !defined(BOIDS)
#define BOIDS

#include "boids/boid.hpp"
#include "boids/param.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

using Flock = std::vector<Boid>;

class Boids {
private:
  std::shared_ptr<Parameters> param;
  int const numboids_;
  int width_;
  int height_;
  Flock boids_;
  void init_boids();

public:
  Boids(std::shared_ptr<Parameters> param);
  Boids(int numboids, int height, int width);
  Flock getNeighbors(Boid const &boid);
  void show(sf::RenderWindow &window);
  void update(float elapsed_time);
  void keepWithinBounds(Boid &boid);
  void avoidOthers(Boid &boid, Flock const &neighbors);
  void flyTowardsCenter(Boid &boid, Flock const &neighbors);
  void matchVelocity(Boid &boid, Flock const &neighbors);
  void limitSpeed(Boid &boid);
};

sf::Color getColor(int i);

#endif // BOIDS
