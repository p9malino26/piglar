#include <iostream>

class Pig {
    static const std::string name = "Matilda";
public:
    static void printName() {
        std::cout << name << std::endl;
    }
};

int main() {
    Pig::printName();
}