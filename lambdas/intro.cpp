#include <print>
#include <string>

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  string mname;
  vector<int> a = {2, 3, 5, 6, 8, 9};

  for_each(a.begin(), a.end(),
           [](int x) { println("The square of {} is {}", x, pow(x, 2)); });
}
