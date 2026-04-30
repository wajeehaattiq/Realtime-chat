# Real-Time Chat Application

## Overview
A console-based multi-user chat application built in C++ 
using Data Structures (STL map and vector). The system 
supports user registration, login, password reset, and 
one-to-one messaging with complete data persistence 
across sessions using file handling.

---

## Features
- User Registration with unique username and user ID
- Secure Login system
- Forget Password with email verification
- One-to-one messaging between users
- Display all received messages on login
- Delete messages
- Update user email and password
- Delete user account
- Search user by username or user ID
- Display all registered users
- All data saved automatically to files
- Maximum 50 users supported

---
## 
========== MAIN MENU ==========

- Register User
- Login
- Forget Password
- Display All Users
- Search User
- Exit
## 
### User Menu (After Login):

========== USER MENU ==========

- Send Message
- Update User Info
- Delete Account
- Delete Message
- Logout

---

## Data Structures Used
| Structure | Purpose |
|---|---|
| map | Fast user lookup by username |
| vector | Store messages for each user |
| struct User | Store user details |
| struct Message | Store sender and message content |

---

## Functions
| Function | Description |
|---|---|
| registerUser() | Register new users |
| login() | User login with password check |
| forgetPassword() | Reset password via email |
| sendMessage() | Send message to any user |
| displayMessages() | Show all received messages |
| deleteMessage() | Delete specific message |
| updateUser() | Update email or password |
| deleteUser() | Delete user account |
| searchUser() | Search by username or user ID |
| displayUsers() | Show all registered users |
| saveUserData() | Save users to userData.txt |
| loadUserData() | Load users from userData.txt |
| saveMessages() | Save messages to messages.txt |
| loadMessages() | Load messages from messages.txt |

---

## Data Persistence
All data is automatically saved in two files:

| File | Contains |
|---|---|
| userData.txt | All registered user details |
| messages.txt | All messages between users |

Data is loaded automatically when program starts
and saved after every change.

---

## User Registration Details
| Field | Description |
|---|---|
| Username | Unique login name |
| Password | Secure password |
| Email | For password recovery |
| User ID | Unique user identifier |

---

## Technologies Used
- **Language:** C++
- **Data Structures:** STL map, vector
- **File Handling:** fstream, sstream
- **Libraries:** iostream, map, vector,
  string, fstream, sstream, algorithm
- **IDE:** Visual Studio Code

---

## How to Run
1. Open project in Visual Studio Code
2. Compile the file:
g++ chat.cpp -o chat

3. Run the program:
./chat

4. Register users and start chatting!

---

## Limitations
- Console based — no GUI
- Maximum 50 users allowed
- One-to-one messaging only
- No real-time network connection

---

## Future Improvements
- Add GUI interface
- Add network-based real time messaging
- Add group chat feature
- Add message encryption
- Increase user limit

---

## Contact
Wajeeha Attiq  
GitHub: github.com/wajeehaattiq  
Email: wajeehaattiq7@gmail.com  
## Menu Options

### Main Menu:
