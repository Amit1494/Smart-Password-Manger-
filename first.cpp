#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

struct User {
    string userName;
    string password;
    string accountName;
};

ostream &operator<<(ostream &out, User &Data) {
    out << "-------------------------------" << endl;
    out << "User Name    : " << Data.userName << endl;
    out << "Password     : " << Data.password << endl;
    out << "Account Name : " << Data.accountName << endl;
    return out;
}

bool isValidEmail(const string &email) {
    const regex valid(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return regex_match(email, valid);
}

string passwordStrengthChecker(const string &password) {
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    bool passwordLength = password.length() >= 8 ? 1 : 0;
    string specialChars = "!@#$%^&*()-+";
    int totalConditionsLength = 0;

    for (auto ch : password) {
        if (islower(ch)) hasLower = true;
        else if (isupper(ch)) hasUpper = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (specialChars.find(ch) != string::npos) hasSpecial = true;
    }

    totalConditionsLength = hasLower + hasUpper + hasDigit + hasSpecial + passwordLength;

    if (totalConditionsLength >= 5)
        return "Strong";
    else if (totalConditionsLength >= 3)
        return "Medium";
    else
        return "Weak";
}

class PasswordManager {
private:
    string LoginUserName;
    string LoginPassword;
    vector<User> listOfUsers;

public:
    void saveToFile();
    void loadFromFile();
    void mainMenu();
    void addUser();
    void deleteUser();
    void updateUser();
    void displayUsers();
    void searchUser();
    void logout();
    void passwordCheck(const string);
    void LoginMainMenu();
    void registerUser();
    void login();
};

void PasswordManager::saveToFile() {
    ofstream file(LoginUserName + ".txt");
    if (file.is_open()) {
        file << LoginUserName << "\n";
        file << LoginPassword << "\n";
        for (const auto &user : listOfUsers) {
            file << user.userName << "\n";
            file << user.password << "\n";
            file << user.accountName << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void PasswordManager::loadFromFile() {
    ifstream file(LoginUserName + ".txt");
    if (file.is_open()) {
        getline(file, LoginUserName);
        getline(file, LoginPassword);
        User user;
        while (getline(file, user.userName) &&
               getline(file, user.password) &&
               getline(file, user.accountName)) {
            listOfUsers.push_back(user);
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
}

void PasswordManager::addUser() {
    User newUser;
    cout << "------------------------------" << endl;
    cout << "Adding a new user..." << endl;
    cout << "Enter username : ";
    getline(cin, newUser.userName);
    cout << "Enter password : ";
    getline(cin, newUser.password);
    cout << "Enter account name : ";
    getline(cin, newUser.accountName);

    passwordCheck(newUser.password);

    for (char &ch : newUser.accountName)
        ch = tolower(ch);

    if (newUser.accountName == "gmail" || newUser.accountName == "email") {
        if (isValidEmail(newUser.userName)) {
            listOfUsers.push_back(newUser);
            cout << "User added successfully!" << endl;
        } else {
            cout << "Invalid email ID. Try again.\n";
            addUser();
        }
    } else {
        listOfUsers.push_back(newUser);
        cout << "User added successfully!" << endl;
    }
}

void PasswordManager::deleteUser() {
    string userName;
    bool found = false;
    cout << "Deleting a user..." << endl;
    cout << "Enter username to delete : ";
    getline(cin, userName);

    for (auto it = listOfUsers.begin(); it != listOfUsers.end(); ++it) {
        if (it->userName == userName) {
            listOfUsers.erase(it);
            found = true;
            cout << "User deleted successfully!" << endl;
            break;
        }
    }
    if (!found) cout << "User not found." << endl;
}

void PasswordManager::updateUser() {
    string userName;
    cout << "Updating a user..." << endl;
    cout << "Enter username to update : ";
    getline(cin, userName);
    bool found = false;

    for (auto &user : listOfUsers) {
        if (user.userName == userName) {
            found = true;
            cout << "Enter new password : ";
            getline(cin, user.password);
            cout << "User updated successfully!" << endl;
            break;
        }
    }
    if (!found) cout << "User not found." << endl;
}

void PasswordManager::displayUsers() {
    if (!listOfUsers.empty()) {
        cout << "Displaying all users..." << endl;
        for (auto &user : listOfUsers) cout << user;
    } else {
        cout << "Database is empty." << endl;
    }
}

void PasswordManager::searchUser() {
    string userName;
    bool found = false;
    cout << "Searching for a user..." << endl;
    cout << "Enter username to search : ";
    getline(cin, userName);

    for (auto &user : listOfUsers) {
        if (user.userName == userName) {
            found = true;
            cout << user;
            break;
        }
    }
    if (!found) cout << "User not found." << endl;
}

void PasswordManager::logout() {
    cout << "Logging out..." << endl;
    saveToFile();
    LoginUserName = "";
    LoginPassword = "";
    listOfUsers.clear();
    cout << "Logged out successfully!" << endl;
}

void PasswordManager::passwordCheck(const string password) {
    string strength = passwordStrengthChecker(password);
    cout << "Password strength: " << strength << endl;

    if (!any_of(password.begin(), password.end(), ::isupper))
        cout << "Password must have at least one uppercase letter.\n";
    if (!any_of(password.begin(), password.end(), ::islower))
        cout << "Password must have at least one lowercase letter.\n";
    if (!any_of(password.begin(), password.end(), ::isdigit))
        cout << "Password must have at least one digit.\n";
    if (password.find_first_of("!@#$%^&*()-+") == string::npos)
        cout << "Password must have at least one special character.\n";
    if (password.length() < 8)
        cout << "Password must be at least 8 characters long.\n";
}

void PasswordManager::LoginMainMenu() {
    int choice;
    do {
        cout << "Welcome to the Password Manager!" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option : ";
        cin >> choice;
        cin.ignore();
        

        switch (choice) {
            case 1: registerUser(); break;
            case 2: login(); break;
            case 3: cout << "Exiting the program." << endl; break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 3);
}

void PasswordManager::registerUser() {
    string inputUserName, inputPassword;
    cout << "Registering a new user..." << endl;
    cout << "Enter username : ";
    getline(cin, inputUserName);
    cout << "Enter password : ";
    getline(cin, inputPassword);

    ifstream file(inputUserName + ".txt");
    if (file.is_open()) {
        cout << "Username already exists. Please choose a different username.\n";
        file.close();
    } else {
        LoginUserName = inputUserName;
        LoginPassword = inputPassword;
        saveToFile();
        cout << "User registered successfully!\n";
    }
}

void PasswordManager::login() {
    string inputUserName, inputPassword;
    cout << "Logging in..." << endl;
    cout << "Enter username : ";
    getline(cin, inputUserName);

    ifstream file(inputUserName + ".txt");
    if (file.is_open()) {
        file.close();
        LoginUserName = inputUserName;
        loadFromFile();
        cout << "Enter password : ";
        getline(cin, inputPassword);

        if (inputPassword == LoginPassword) {
            cout << "Login successful!" << endl;
            mainMenu();
        } else {
            cout << "Incorrect password. Please try again." << endl;
        }
    } else {
        cout << "Username not found. Please register first." << endl;
    }
}

void PasswordManager::mainMenu() {
    int choice;
    do {
        cout << "--------------------------------" << endl;
        cout << "Welcome to the Password Manager!" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Update User" << endl;
        cout << "4. Display Users" << endl;
        cout << "5. Search User" << endl;
        cout << "6. Logout" << endl;
        cout << "Please select an option : ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice) {
            case 1: addUser(); break;
            case 2: deleteUser(); break;
            case 3: updateUser(); break;
            case 4: displayUsers(); break;
            case 5: searchUser(); break;
            case 6: logout(); break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 6);
}

int main() {
    PasswordManager PM;
    PM.LoginMainMenu();
    cout << endl;
    return 0;
}
