#include <print>
#include <string>

using namespace std;

template <typename T> void Print(T value) {
  println("Printing out: {}", value);
};

int main() {
  string mname;

  Print("Magpiny");
  Print<string>("October 2024");
  Print(true);
  Print<int>(46);
  return 0;
}
