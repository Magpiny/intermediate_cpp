#include <print>
#include <string>

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  string mname;
  vector<int> b = {2, 3, 5, 6, 8, 9};

  int cn = 3;
  for_each(b.begin(), b.end(), [=](int x) mutable {
    println("The cube of {} is {}", x, pow(x, cn));
  });
}
