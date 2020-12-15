#include <iostream>

class Cuboid {
  public:
    Cuboid (double length, double width, double height) {
      volume = length * width * height;
      surface_area = 2 * length * width + 2 * length * height + 2 * width * height;
      edge_length = 4 * length + 4 * width + 4 * height;
    }

    double get_volume () {
      return volume;
    }

    double get_surface_area () {
      return surface_area;
    }

    double get_edge_length () {
      return edge_length;
    }

  private:
    double volume;
    double surface_area;
    double edge_length;
};

int main () {
  std::cout << "Cuboid dimensions (length, width, height): ";
  double l, w, h;
  std::cin >> l >> w >> h;
  Cuboid cuboid (l, w, h);
  std::cout << "Volume: " << cuboid.get_volume() << std::endl;
  std::cout << "Surface Area: " << cuboid.get_surface_area() << std::endl;
  std::cout << "Edge Length: " << cuboid.get_edge_length() << std::endl;
  return 0;
}