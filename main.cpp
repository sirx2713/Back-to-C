#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Structure to hold user data.
struct User {
    std::string username;
    std::string password;
};

// Loads user records from a file.
std::vector<User> loadUsers(const std::string &filename) {
    std::vector<User> users;
    std::ifstream infile(filename);
    if (!infile) {
        // File may not exist on first run; that's normal.
        return users;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        User user;
        if (iss >> user.username >> user.password) {
            users.push_back(user);
        }
    }
    return users;
}

// Appends a new user record to the file.
void saveUser(const User &user, const std::string &filename) {
    std::ofstream outfile(filename, std::ios::app);
    if (outfile) {
        outfile << user.username << " " << user.password << "\n";
    }
}

// Authenticates non-admin users using the loaded users.
bool authenticateUser(const std::string &username, const std::string &password, const std::vector<User> &users) {
    for (const auto &user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Displays the admin menu with advanced admin capabilities.
void adminMenu(const std::vector<User> &users) {
    int choice = 0;
    do {
        std::cout << "\n=== Administrator Menu ===\n";
        std::cout << "1. View registered users\n";
        std::cout << "2. Perform admin task (placeholder)\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // discard the newline

        if (choice == 1) {
            std::cout << "\nRegistered Users:\n";
            if (users.empty()) {
                std::cout << "No users registered.\n";
            } else {
                for (const auto &user : users) {
                    std::cout << "Username: " << user.username << "\n";
                }
            }
        } else if (choice == 2) {
            std::cout << "Performing an advanced admin task...\n";
            // Insert additional admin functionality here.
        } else if (choice == 3) {
            std::cout << "Logging out from admin menu.\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);
}

// Displays the user menu with advanced capabilities for general users.
void userMenu(const std::string &username) {
    int choice = 0;
    do {
        std::cout << "\n=== User Menu for " << username << " ===\n";
        std::cout << "1. View welcome message\n";
        std::cout << "2. Change password (placeholder)\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // remove newline

        if (choice == 1) {
            std::cout << "Welcome " << username << " to © iSAD!\n";
        } else if (choice == 2) {
            std::cout << "Password change functionality coming soon...\n";
            // Advanced functionality can be expanded here.
        } else if (choice == 3) {
            std::cout << "Logging out.\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);
}

// Handles the registration of a new user.
void registerNewUser(const std::string &filename, std::vector<User> &users) {
    std::string username, password, confirmPassword;
    std::cout << "\n--- User Registration ---\n";
    std::cout << "Enter a new username (max 50 characters): ";
    std::getline(std::cin, username);
    if (username.length() > 50) {
        username = username.substr(0, 50);
        std::cout << "Username trimmed to 50 characters: " << username << "\n";
    }

    // Ensure username is not already taken.
    for (const auto &user : users) {
        if (user.username == username) {
            std::cout << "Username already exists. Registration aborted.\n";
            return;
        }
    }

    bool validPassword = false;
    while (!validPassword) {
        std::cout << "Enter a password (at least 6 characters): ";
        std::getline(std::cin, password);
        std::cout << "Confirm password: ";
        std::getline(std::cin, confirmPassword);

        if (password != confirmPassword) {
            std::cout << "Passwords do not match. Try again.\n";
        } else if (password.length() < 6) {
            std::cout << "Password is too short. Try again.\n";
        } else {
            validPassword = true;
        }
    }

    User newUser = {username, password};
    saveUser(newUser, filename);
    users.push_back(newUser);
    std::cout << "Registration successful. You can now log in.\n";
}

// Handles the login process.
void login(const std::string &filename, const std::vector<User> &users) {
    std::string username, password;
    std::cout << "\n--- Login ---\n";
    std::cout << "Enter username: ";
    std::getline(std::cin, username);

    // Check for administrator login.
    if (username == "admin") {
        std::cout << "Enter admin password: ";
        std::getline(std::cin, password);
        // Hard-coded admin password; in a real app, this should be securely stored.
        if (password == "adminpass") {
            std::cout << "Administrator access granted.\n";
            adminMenu(users);
        } else {
            std::cout << "Incorrect admin password. Access denied.\n";
        }
    } else {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        if (authenticateUser(username, password, users)) {
            std::cout << "Login successful. Welcome, " << username << "!\n";
            userMenu(username);
        } else {
            std::cout << "Invalid username or password.\n";
        }
    }
}

int main() {
    const std::string filename = "users.txt";
    std::vector<User> users = loadUsers(filename);

    int choice = 0;
    do {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Discard newline

        if (choice == 1) {
            login(filename, users);
            // Reload users in case of any new registration during the session.
            users = loadUsers(filename);
        } else if (choice == 2) {
            registerNewUser(filename, users);
        } else if (choice == 3) {
            std::cout << "Exiting application.\n";
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
