#include <iostream>

int main() {
    std::cout << "Enter name: ";
    std::string input;
    std::cin >> input;
    std::cout << "Hello " + input  + " !\n" << std::endl;
}