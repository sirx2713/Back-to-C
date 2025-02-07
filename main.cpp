#include <iostream>

int main() {
    std::string input;
    std::cout << "Enter name: ";
    std::cin >> input;
    std::cout << "Hello " + input  + " !\n" << std::endl;
}