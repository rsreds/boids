#include <vector>

template <class T>
struct Point2
{
  T x;
  T y;
};

template <class T> using Vector2 = std::vector<Point2<T>>;

struct Boid
{
  Point2 <int> pos;
  Point2 <int> spd;
  Vector2<int> history;
};
