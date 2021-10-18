#if !defined(MACRO)
#define MACRO

#include <SFML/System.hpp>
#include <cmath>
#include <vector>

struct Boid {
  sf::Vector2f pos;
  sf::Vector2f spd;
  std::vector<sf::Vector2f> history;
  int flock_id;
};

template <class T> inline T lenght(sf::Vector2<T> const &v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}

template <class T>
inline T distance(sf::Vector2<T> const &a, sf::Vector2<T> const &b) {
  return lenght<T>(a - b);
}

inline float distance(Boid const &a, Boid const &b) {
  return distance<float>(a.pos, b.pos);
}

inline bool isInView(Boid const &boid, Boid const &watcher, float view_range, float view_angle) {
  float radius = distance(watcher, boid);
  if (radius > view_range) return false;
  float atan = std::atan2(boid.pos.y - watcher.pos.y, boid.pos.x - watcher.pos.x);
  float watcher_angle = std::atan2(watcher.spd.y, watcher.spd.x);
  float start_angle = watcher_angle - view_angle*0.5;
  float end_angle = watcher_angle + view_angle*0.5;
  if (start_angle < end_angle && start_angle < atan && atan < end_angle) return true;
  if (start_angle >= end_angle && (atan >= start_angle || atan < end_angle)) return true;
  return false;
}
#endif // MACRO
