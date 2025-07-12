#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Struct to represent a user in the system
struct User {
    int id;             // Unique user ID
    std::string username;
    std::string role;   // User role (e.g., admin, analyst)
};

// Struct to represent a device in the system
struct Device {
    int id;             // Unique device ID
    std::string name;   // Device name
    std::string ip;     // Device IP address
    std::string status; // Device status (active/inactive)
};

// Main Cyber Management System class
class CyberManagementSystem {
private:
    std::vector<User> users;      // List of users
    std::vector<Device> devices;  // List of devices

    int userIdCounter = 1;        // Tracks next user ID to assign
    int deviceIdCounter = 1;      // Tracks next device ID to assign

    // File names for saving/loading data
    const std::string usersFile = "users.txt";
    const std::string devicesFile = "devices.txt";

public:
    // Constructor loads users and devices from files
    CyberManagementSystem() {
        loadUsers();
        loadDevices();
    }

    // Destructor saves users and devices back to files when program ends
    ~CyberManagementSystem() {
        saveUsers();
        saveDevices();
    }

    // Adds a new user with given username and role
    void addUser(const std::string& username, const std::string& role) {
        users.push_back({userIdCounter++, username, role});
        std::cout << "User added successfully.\n";
    }

    // Displays all users in the system
    void listUsers() {
        std::cout << "\nUsers:\n";
        for (const auto& user : users) {
            std::cout << "ID: " << user.id 
                      << ", Username: " << user.username 
                      << ", Role: " << user.role << '\n';
        }
        if(users.empty()) std::cout << "No users available.\n";
    }

    // Adds a new device with given name, IP, and status
    void addDevice(const std::string& name, const std::string& ip, const std::string& status) {
        devices.push_back({deviceIdCounter++, name, ip, status});
        std::cout << "Device added successfully.\n";
    }

    // Displays all devices in the system
    void listDevices() {
        std::cout << "\nDevices:\n";
        for (const auto& device : devices) {
            std::cout << "ID: " << device.id 
                      << ", Name: " << device.name 
                      << ", IP: " << device.ip 
                      << ", Status: " << device.status << '\n';
        }
        if(devices.empty()) std::cout << "No devices available.\n";
    }

private:
    // Save the users vector to the users.txt file
    void saveUsers() {
        std::ofstream file(usersFile);
        for (const auto& user : users) {
            file << user.id << "," << user.username << "," << user.role << "\n";
        }
    }

    // Save the devices vector to the devices.txt file
    void saveDevices() {
        std::ofstream file(devicesFile);
        for (const auto& device : devices) {
            file << device.id << "," << device.name << "," << device.ip << "," << device.status << "\n";
        }
    }

    // Load users from users.txt file, if it exists
    void loadUsers() {
        std::ifstream file(usersFile);
        if (!file.is_open()) return; // No file yet, skip loading

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, username, role;

            // Parse line of format: id,username,role
            if (getline(ss, idStr, ',') && getline(ss, username, ',') && getline(ss, role)) {
                int id = std::stoi(idStr);
                users.push_back({id, username, role});
                // Keep userIdCounter updated so no ID conflicts
                if (id >= userIdCounter) userIdCounter = id + 1;
            }
        }
    }

    // Load devices from devices.txt file, if it exists
    void loadDevices() {
        std::ifstream file(devicesFile);
        if (!file.is_open()) return; // No file yet, skip loading

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, ip, status;

            // Parse line of format: id,name,ip,status
            if (getline(ss, idStr, ',') && getline(ss, name, ',') && getline(ss, ip, ',') && getline(ss, status)) {
                int id = std::stoi(idStr);
                devices.push_back({id, name, ip, status});
                // Keep deviceIdCounter updated so no ID conflicts
                if (id >= deviceIdCounter) deviceIdCounter = id + 1;
            }
        }
    }

public:
    // Main menu for user interaction
    void menu() {
        while (true) {
            // Display options
            std::cout << "\n=== Cyber Management System Menu ===\n";
            std::cout << "1. Add User\n";
            std::cout << "2. List Users\n";
            std::cout << "3. Add Device\n";
            std::cout << "4. List Devices\n";
            std::cout << "5. Exit\n";
            std::cout << "Choose an option: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // discard newline left in input buffer

            // Handle user choice
            if (choice == 1) {
                // Add User option
                std::string username, role;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter role: ";
                std::getline(std::cin, role);
                addUser(username, role);
            } else if (choice == 2) {
                // List Users option
                listUsers();
            } else if (choice == 3) {
                // Add Device option
                std::string name, ip, status;
                std::cout << "Enter device name: ";
                std::getline(std::cin, name);
                std::cout << "Enter IP address: ";
                std::getline(std::cin, ip);
                std::cout << "Enter status (active/inactive): ";
                std::getline(std::cin, status);
                addDevice(name, ip, status);
            } else if (choice == 4) {
                // List Devices option
                listDevices();
            } else if (choice == 5) {
                // Exit program
                std::cout << "Exiting system...\n";
                break;
            } else {
                // Invalid input
                std::cout << "Invalid option, try again.\n";
            }
        }
    }
};

// Main function - entry point of program
int main() {
    CyberManagementSystem cms; // Create system instance
    cms.menu();               // Start interactive menu
    return 0;
}
