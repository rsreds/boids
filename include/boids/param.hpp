#if !defined(PARAMETERS)
#define PARAMETERS

#include <string>

class Parameters {
private:
  std::string title_ = "Boids!";
  int view_width_ = 640;
  int view_height_ = 480;
  float simulation_speed_ = 200;
  int num_boids_ = 200;
  float view_range_ = 40;
  float view_angle_ = 90;
  float separation_ = 20;
  float cohesion_ = 0.1/simulation_speed_;
  float alignment_ = 2/simulation_speed_;
  int margin_ = 20;
  int num_flocks_ = 2;

public:
  void title(std::string &title) { title_ = title; }
  void view_width(int const &view_width) { view_width_ = view_width; }
  void view_height(int const &view_height) { view_height_ = view_height; }
  void num_boids(int const &num_boids) { num_boids_ = num_boids; }
  void simulation_speed(float const &simulation_speed) {
    simulation_speed_ = simulation_speed;
  }
  void view_range(float const &view_range) { view_range_ = view_range; }
  void view_angle(float const &view_angle) { view_angle_ = view_angle; }
  void separation(float const &separation) { separation_ = separation; }
  void cohesion(float const &cohesion) { cohesion_ = cohesion; }
  void alignment(float const &alignment) { alignment_ = alignment; }
  void margin(int const &margin) { margin_ = margin; }
  void num_flocks(int const &num_flocks) { num_flocks_ = num_flocks; }

  std::string title() const { return title_; }
  int view_width() const { return view_width_; }
  int view_height() const { return view_height_; }
  float simulation_speed() const {return simulation_speed_;}
  int num_boids() const { return num_boids_; }
  float view_range() const { return view_range_; }
  float view_angle() const { return view_angle_; }
  float separation() const { return separation_; }
  float cohesion() const { return cohesion_; }
  float alignment() const { return alignment_; }
  int margin() const { return margin_; }
  int num_flocks() const { return num_flocks_; }
};

#endif // MACRO
