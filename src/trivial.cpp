#include <iostream>

struct MyVector
{
    constexpr MyVector(int _x, int _y)
        :x(_x), y(_y)
    {}

    int x, y;
};

class Camera
{
public:
    static constexpr MyVector pos = MyVector(1,2);
};

int main()
{
    std::cout << Camera::pos.x << ' ' << Camera::pos.y << std::endl;
    return 0;
}