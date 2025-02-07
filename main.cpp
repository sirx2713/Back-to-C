#include <iostream>

int main() {
    std::string username;
    int password;
    std::cout << "Enter username (max 50 characters): ";
    std::cin >> username;
    if (username == "admin") {
        std::cout << "You are a administrator." << std::endl;
    }
    else {
        std::cout << "You are not a administrator." << std::endl;
        std::cout << "Please enter a password for username: ";
        std::cin >> password;
        while (password > 5) {
            std::cout << "Password is too short." << std::endl;
            std::cout << "Please enter a password for username: ";
            std::cin >> password;
        }
         if (password <= 5) {
            std::cout << "Welcome " + username + " to © iSAD!" << std::endl;
        }
    }
}