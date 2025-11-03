Smart Password Manager

The Smart Password Manager is a console-based C++ application designed to help users securely store and manage their passwords. It provides features like password encryption, authentication, and credential management through a simple and efficient command-line interface.

Features

User registration and login authentication

Add, view, edit, and delete saved credentials

Secure password storage using encryption

Password strength validation

Random password generator

Simple console interface for easy navigation

Tech Stack

Language: C++

Concepts Used: File Handling, Encryption, Data Structures, String Manipulation

Tools: Any C++ compiler (e.g., GCC, MinGW, Turbo C++, or IDEs like Code::Blocks / Visual Studio / IntelliJ with C++ plugin)

Installation and Setup

Clone this repository

git clone https://github.com/your-username/Smart-Password-Manager.git


Navigate to the project folder

cd Smart-Password-Manager


Compile the program

g++ password_manager.cpp -o password_manager


Run the executable

./password_manager

Usage

Register as a new user

Log in with your credentials

Add new account details (website, username, password)

View or delete saved passwords securely

Log out when finished

Example:

=== Smart Password Manager ===
1. Register
2. Login
3. Exit
Enter your choice: 1

Security

Passwords are stored in encrypted format using custom encryption logic.

User login ensures that data is isolated per user.

The system uses basic file handling to save credentials locally.

Future Enhancements

GUI-based version using Qt or Python Tkinter

Stronger AES encryption

Integration with cloud storage

Auto-fill capability for web logins

Author

Amit HMH
amithmh14@gmail.com
Passionate about C++ development and cybersecurity
