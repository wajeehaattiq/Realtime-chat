#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Struct to represent an individual message
struct Message {
    string sender;
    string content;
};

// Structure to store user details
struct User {
    string userId;  // New field for userId (either a string or integer as string)
    string password;
    string email;
    vector<Message> messages; // Updated to store Message structs
};

// Global user database
map<string, User> userTable;

// File paths for storing user data and messages
const string USER_FILE_PATH = "userData.txt";
const string MESSAGE_FILE_PATH = "messages.txt";

// Function prototypes
void mainMenu();
void registerUser();
void login();
void forgetPassword();
void displayUsers();
void searchUser();
void userMenu(const string& username);
void updateUser(const string& username);
void deleteUser(const string& username);
void sendMessage(const string& sender);
void displayMessages(const string& username);
void deleteMessage(const string& username);
void loadUserData();
void saveUserData();
void loadMessages();
void saveMessages();

// Function to load user data from file
void loadUserData() {
    ifstream inFile(USER_FILE_PATH);
    if (!inFile) {
        cout << "No existing user data found. Starting fresh.\n";
        return;
    }

    string line, username, password, email, userId;
    while (getline(inFile, line)) {
        if (!line.empty() && line.find(',') != string::npos) {
            stringstream ss(line);
            getline(ss, username, ',');  // Read username
            getline(ss, password, ','); // Read password
            getline(ss, email, ',');    // Read email
            getline(ss, userId, ',');   // Read user ID

            userTable[username] = {userId, password, email};  // Store data
        }
    }
    inFile.close();
}

// Function to save user data to file
void saveUserData() {
    ofstream outFile(USER_FILE_PATH);
    if (!outFile) {
        cout << "Error saving user data to file.\n";
        return;
    }

    for (const auto& user : userTable) {
        outFile << user.first << ","              // Username
                << user.second.password << ","    // Password
                << user.second.email << ","       // Email
                << user.second.userId << "\n";    // User ID
    }
    outFile.close();
}

// Function to load messages from file
void loadMessages() {
    ifstream inFile(MESSAGE_FILE_PATH);
    if (!inFile) {
        cout << "No existing messages found. Starting fresh.\n";
        return;
    }

    string line, recipient, sender, content;
    while (getline(inFile, line)) {
        if (!line.empty() && line.find(':') != string::npos) {
            // Parse message data
            stringstream ss(line);
            getline(ss, recipient, ':'); // Extract recipient
            getline(ss, sender, ':');    // Extract sender
            getline(ss, content);       // Extract content

            if (userTable.find(recipient) != userTable.end()) {
                userTable[recipient].messages.push_back({sender, content});
            }
        }
    }
    inFile.close();
}

// Function to save messages to file
void saveMessages() {
    ofstream outFile(MESSAGE_FILE_PATH);
    if (!outFile) {
        cout << "Error saving messages to file.\n";
        return;
    }

    for (const auto& user : userTable) {
        for (const auto& message : user.second.messages) {
            outFile << user.first << "," << message.sender << ":" << message.content << "\n";
        }
    }
    outFile.close();
}

// Main function
int main() {
    cout << "\n*********** REAL-TIME CHAT APPLICATION ***********\n";
    loadUserData(); // Load user data from file
    loadMessages(); // Load messages from file
    mainMenu();
    saveUserData(); // Save user data to file
    saveMessages(); // Save messages to file
    return 0;
}

// Function to display the main menu
void mainMenu() {
    while (true) {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Register User\n";
        cout << "2. Login\n";
        cout << "3. Forget Password\n";
        cout << "4. Display All Users\n";
        cout << "5. Search User\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                forgetPassword();
                break;
            case 4:
                displayUsers();
                break;
            case 5:
                searchUser();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to register a new user
void registerUser() {
    int numUsers;
    cout << "\n========== REGISTER USER ==========" << endl;
    cout << "How many users do you want to register? ";
    cin >> numUsers;

    for (int i = 0; i < numUsers; ++i) {
        if (userTable.size() >= 50) {
            cout << "\nUser registration limit of 50 reached. The program will now terminate." << endl;
            exit(0);
        }

        string username, password, email, userId;
        cout << "\nRegistering User " << i + 1 << ":\n";
        cout << "Enter username: ";
        cin >> username;

        if (userTable.find(username) != userTable.end()) {
            cout << "Username already exists. Please choose a different one." << endl;
            --i; // Retry the current iteration
            continue;
        }

        cout << "Enter password: ";
        cin >> password;

        cout << "Enter email: ";
        cin >> email;

        cout << "Enter user ID (must be unique): ";
        cin >> userId;

        // Check if the user ID is already in use
        bool isUserIdUsed = false;
        for (const auto& user : userTable) {
            if (user.second.userId == userId) {
                isUserIdUsed = true;
                break;
            }
        }

        if (isUserIdUsed) {
            cout << "User ID is already in use. Please choose a different one." << endl;
            --i; // Retry the current iteration
            continue;
        }

        // Register the user
        userTable[username] = {userId, password, email};
        cout << "User registered successfully!" << endl;

        // Check if the user wants to continue adding more users
        if (i == numUsers - 1) { // If this is the last user in the current batch
            char choice;
            cout << "\nDo you want to add more users? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cout << "How many more users do you want to add? ";
                int moreUsers;
                cin >> moreUsers;
                numUsers += moreUsers;
            } else {
                break;
            }
        }
    }

    saveUserData();
}

// Function to log in a user
void login() {
    string username, password;
    cout << "\n========== LOGIN ==========\n";
    cout << "Enter username: ";
    cin >> username;

    if (userTable.find(username) == userTable.end()) {
        cout << "User not found. Please register first.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (userTable[username].password == password) {
        cout << "Login successful! Welcome, " << username << ".\n";
        displayMessages(username);
        userMenu(username);
    } else {
        cout << "Incorrect password. Try again.\n";
    }
}

// User menu after login
void userMenu(const string& username) {
    while (true) {
        cout << "\n========== USER MENU ==========\n";
        cout << "1. Send Message\n";
        cout << "2. Update User Info\n";
        cout << "3. Delete Account\n";
        cout << "4. Delete Message\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                sendMessage(username);
                break;
            case 2:
                updateUser(username);
                break;
            case 3:
                deleteUser(username);
                return;
            case 4:
                deleteMessage(username);
                break;
            case 5:
                cout << "Logged out successfully.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to update user info
void updateUser(const string& username) {
    cout << "\n========== UPDATE USER INFO ==========\n";
    cout << "1. Update Email\n2. Update Password\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string newEmail;
        cout << "Enter new email: ";
        cin >> newEmail;
        userTable[username].email = newEmail;
        saveUserData();
        cout << "Email updated successfully!\n";
    } else if (choice == 2) {
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        userTable[username].password = newPassword;
        saveUserData();
        cout << "Password updated successfully!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Function to delete a user account
void deleteUser(const string& username) {
    cout << "Are you sure you want to delete your account? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    if (confirmation == "yes") {
        userTable.erase(username);
        saveUserData();
        saveMessages();
        cout << "Your account has been deleted successfully.\n";
    } else {
        cout << "Account deletion canceled.\n";
    }
}

// Function to send a message to a user
void sendMessage(const string& sender) {
    string recipient, message;
    cout << "\nEnter recipient's username: ";
    cin >> recipient;

    if (userTable.find(recipient) == userTable.end()) {
        cout << "Recipient not found.\n";
        return;
    }

    cout << "Enter your message: ";
    cin.ignore();
    getline(cin, message);

    userTable[recipient].messages.push_back({sender, message});
    saveMessages();
    cout << "Message sent to " << recipient << " successfully!\n";
}

// Function to display messages for a user
void displayMessages(const string& username) {
    cout << "\n========== MESSAGES ==========\n";

    if (userTable[username].messages.empty()) {
        cout << "No messages to display.\n";
    } else {
        for (size_t i = 0; i < userTable[username].messages.size(); ++i) {
            cout << i + 1 << "." << userTable[username].messages[i].sender
                 << ": " << userTable[username].messages[i].content << "\n";
        }
    }
    cout << "=============================\n";
}

// Function to delete a message
void deleteMessage(const string& username) {
    cout << "\n========== DELETE MESSAGE ==========\n";

    if (userTable[username].messages.empty()) {
        cout << "No messages to delete.\n";
        return;
    }

    cout << "Messages:\n";
    for (size_t i = 0; i < userTable[username].messages.size(); ++i) {
        cout << i + 1 << ". From " << userTable[username].messages[i].sender
             << ": " << userTable[username].messages[i].content << "\n";
    }

    cout << "Enter the message number to delete (0 to cancel): ";
    int msgNumber;
    cin >> msgNumber;

    if (msgNumber <= 0 || static_cast<size_t>(msgNumber) > userTable[username].messages.size()) {
        cout << "Invalid choice. No message deleted.\n";
        return;
    }

    userTable[username].messages.erase(userTable[username].messages.begin() + (msgNumber - 1));
    saveMessages();
    cout << "Message deleted successfully.\n";
}

// Function to reset a user's password
void forgetPassword() {
    string username, email, newPassword;
    cout << "\n========== FORGET PASSWORD ==========\n";
    cout << "Enter your username: ";
    cin >> username;

    if (userTable.find(username) == userTable.end()) {
        cout << "Username not found.\n";
        return;
    }

    cout << "Enter your registered email: ";
    cin >> email;

    if (userTable[username].email == email) {
        cout << "Enter your new password: ";
        cin >> newPassword;

        userTable[username].password = newPassword;
        saveUserData();
        cout << "Password reset successfully!\n";
    } else {
        cout << "Email does not match our records.\n";
    }
}
// Function to display all users
void displayUsers() {
    cout << "\n========== USER LIST ==========\n";
    if (userTable.empty()) {
        cout << "No users registered yet.\n";
        return;
    }

    for (const auto& user : userTable) {
        cout << "Username: " << user.first << "\n";              // Display username
        cout << "Email: " << user.second.email << "\n";         // Display email
        cout << "User ID: " << user.second.userId << "\n";      // Display user ID
        cout << "----------------------------------\n";
    }
}

// Function to search for a user by username or user ID
void searchUser() {
    cout << "\n========== SEARCH USER ==========\n";
    cout << "Search by (1) Username or (2) User ID? ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string username;
        cout << "Enter username: ";
        cin >> username;

        // Search user by username
        auto it = userTable.find(username);
        if (it != userTable.end()) {
            cout << "\nUser found:\n";
            cout << "Username: " << it->first << "\n";           // Display username
            cout << "Email: " << it->second.email << "\n";       // Display email
            cout << "User ID: " << it->second.userId << "\n";    // Display user ID
        } else {
            cout << "User not found.\n";
        }
    } else if (choice == 2) {
        string userId;
        cout << "Enter user ID: ";
        cin >> userId;

        // Search user by user ID
        bool found = false;
        for (const auto& user : userTable) {
            if (user.second.userId == userId) {
                cout << "\nUser found:\n";
                cout << "Username: " << user.first << "\n";      // Display username
                cout << "Email: " << user.second.email << "\n";  // Display email
                cout << "User ID: " << user.second.userId << "\n"; // Display user ID
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "User not found.\n";
        }
    } else {
        cout << "Invalid choice. Please select 1 or 2.\n";
    }
}
