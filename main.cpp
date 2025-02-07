#include <iostream>
#include <string>

int main() {
    std::string username;
    std::string password;

    std::cout << "Enter username (max 50 characters): ";
    std::getline(std::cin, username);

    // Trim username if longer than 50 characters
    if (username.length() > 50) {
        username = username.substr(0, 50);
        std::cout << "Username trimmed to 50 characters: " << username << std::endl;
    }

    // Administrator check
    if (username == "admin") {
        std::cout << "You are an administrator." << std::endl;
        // Additional admin-specific functionality can be added here.
    } else {
        std::cout << "You are not an administrator." << std::endl;

        // Prompt for password until a valid one is entered
        bool validPassword = false;
        while (!validPassword) {
            std::cout << "Enter a password (at least 6 characters): ";
            std::getline(std::cin, password);

            if (password.length() < 6) {
                std::cout << "Password is too short. Please try again." << std::endl;
            } else {
                validPassword = true;
            }
        }

        std::cout << "Welcome " << username << " to © iSAD!" << std::endl;
    }

    return 0;
}
