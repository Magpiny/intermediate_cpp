#include <iostream>

class Rectangle
{
public:
  int height;
  int width;
};

int
main()
{
  Rectangle rec;
  int height = rec.height;
  int width = rec.width;
  height = 34;
  width = 51;
  int area = height * width;
  std::cout << "Area of the rectangle is " << area << std::endl;
}
