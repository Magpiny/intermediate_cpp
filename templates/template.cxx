#include <algorithm>
#include <print>
#include <string>

using namespace std;

template <class T, int N> class Array {
  T m_array[N];

public:
  int get_size() const { return N; }
};

int main() {
  Array<string, 5> array;

  println("This array is of size: {}", array.get_size());
}
