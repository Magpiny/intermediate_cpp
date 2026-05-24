#include <map>
#include <print>
#include <string>
#include <tuple>
#include <utility>

// C++17 Bindings; ausome source
struct Point {
  int x;
  int y;
  int z;
};

std::map<std::string, int> students_ages;

int main() {
  Point coordinates{12, 13, 5};
  students_ages = {
      {"Wangeci", 17}, {"Otieno", 16}, {"Fatuma", 18}, {"Naipei", 15}};

  auto [x, y, z] = coordinates;
  std::println("Coords: {}, {}, {}", x, y, z);

  std::pair<std::string, int> book = {"The Wanj", 2026};
  auto [title, year] = book;
  std::println("{} was released in {}", title, year);

  std::tuple<std::string, int, float> data{"Nairobi", 47, 3.89};
  auto [county, code, population] = data;
  std::println("{}, county number 0{} has {}million residents", county, code,
               population);

  // Mostly shines in iteration
  for (const auto &[name, age] : students_ages) {
    std::println("{} is {}yrs old", name, age);
  }
  return 0;
}
