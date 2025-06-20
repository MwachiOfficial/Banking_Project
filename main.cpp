#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Function prototypes
bool validateAdmin(const string& username, const string& password);
bool validateUser(const string& username, const string& password);
void welcome_admin(const string& username);
void welcome_user(const string& username);
void depositToUser();
void withdrawFromUser();
void checkUserBalance();
void registerNewUser();
void changeAdminPassword(const string& username);
void withdrawSelf(const string& username);
void checkSelfBalance(const string& username);
void resetUserPassword(const string& username);
void updateUserRecord(const string& username, const string& newPass, double balance);
string getUserRecord(const string& username);

// Normal user main login function
int normal_user() {
    string user_username, user_password;
    cout << "Welcome to the Normal User login page\n";
    cout << "Enter username:\t";
    cin >> user_username;
    cout << "Enter password:\t";
    cin >> user_password;

    if (validateUser(user_username, user_password)) {
        welcome_user(user_username);
    } else {
        cout << "Invalid username or password.\n";
    }

    return 0;
}

// Admin main login function
int admin() {
    string admin_username, admin_password;
    cout << "Welcome to the administrator login page\n";
    cout << "Enter username:\t";
    cin >> admin_username;
    cout << "Enter password:\t";
    cin >> admin_password;

    if (validateAdmin(admin_username, admin_password)) {
        welcome_admin(admin_username);
    } else {
        cout << "Invalid administrator credentials.\n";
    }

    return 0;
}

// Welcome screen for user
void welcome_user(const string& username) {
    cout << "\n--- Welcome User ---\n";
    int option;
    cout << "1. Withdraw cash\n";
    cout << "2. Check balance\n";
    cout << "3. Reset password\n";
    cout << "Enter option to proceed: ";
    cin >> option;

    switch (option) {
        case 1: withdrawSelf(username); break;
        case 2: checkSelfBalance(username); break;
        case 3: resetUserPassword(username); break;
        default: cout << "Invalid option.\n";
    }
}

// Welcome screen for admin
void welcome_admin(const string& username) {
    cout << "\n--- Welcome Admin ---\n";
    int option;
    cout << "1. Deposit money for client\n";
    cout << "2. Withdraw money for client\n";
    cout << "3. Check client balance\n";
    cout << "4. Register new client\n";
    cout << "5. Change your admin password\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: depositToUser(); break;
        case 2: withdrawFromUser(); break;
        case 3: checkUserBalance(); break;
        case 4: registerNewUser(); break;
        case 5: changeAdminPassword(username); break;
        default: cout << "Invalid option.\n";
    }
}

bool validateAdmin(const string& username, const string& password) {
    ifstream fin("admin.txt");
    string u, p;
    while (fin >> u >> p) {
        if (u == username && p == password) return true;
    }
    return false;
}

bool validateUser(const string& username, const string& password) {
    ifstream fin("usersDB.txt");
    string u, p;
    double b;
    while (fin >> u >> p >> b) {
        if (u == username && p == password) return true;
    }
    return false;
}

string getUserRecord(const string& username) {
    ifstream fin("usersDB.txt");
    string line;
    while (getline(fin, line)) {
        if (line.find(username + " ") == 0) return line;
    }
    return "";
}

void updateUserRecord(const string& username, const string& newPass, double balance) {
    ifstream fin("usersDB.txt");
    ofstream fout("temp.txt");
    string u, p;
    double b;
    while (fin >> u >> p >> b) {
        if (u == username) fout << u << " " << newPass << " " << balance << "\n";
        else fout << u << " " << p << " " << b << "\n";
    }
    fin.close(); fout.close();
    remove("usersDB.txt");
    rename("temp.txt", "usersDB.txt");
}

void depositToUser() {
    string username;
    double amount;
    cout << "Enter client's username: ";
    cin >> username;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    string record = getUserRecord(username);
    if (record.empty()) {
        cout << "User not found.\n"; return;
    }

    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;
    b += amount;
    updateUserRecord(username, p, b);
    cout << "Deposit successful.\n";
}

void withdrawFromUser() {
    string username;
    double amount;
    cout << "Enter client's username: ";
    cin >> username;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    string record = getUserRecord(username);
    if (record.empty()) {
        cout << "User not found.\n"; return;
    }

    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;
    if (amount > b) {
        cout << "Insufficient balance.\n";
    } else {
        b -= amount;
        updateUserRecord(username, p, b);
        cout << "Withdrawal successful.\n";
    }
}

void checkUserBalance() {
    string username;
    cout << "Enter client's username: ";
    cin >> username;

    string record = getUserRecord(username);
    if (record.empty()) {
        cout << "User not found.\n"; return;
    }

    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;
    cout << "Balance: " << b << "\n";
}

void registerNewUser() {
    string username, password;
    double deposit;
    cout << "Enter new client's username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Initial deposit amount: ";
    cin >> deposit;

    if (!getUserRecord(username).empty()) {
        cout << "Username already exists.\n";
        return;
    }

    ofstream fout("usersDB.txt", ios::app);
    fout << username << " " << password << " " << deposit << "\n";
    fout.close();
    cout << "Client registered successfully.\n";
}

void changeAdminPassword(const string& username) {
    string oldPass, newPass;
    ifstream fin("admin.txt");
    ofstream fout("temp_admin.txt");
    string u, p;

    cout << "Enter old password: ";
    cin >> oldPass;

    bool updated = false;
    while (fin >> u >> p) {
        if (u == username && p == oldPass) {
            cout << "Enter new password: ";
            cin >> newPass;
            fout << u << " " << newPass << "\n";
            updated = true;
        } else {
            fout << u << " " << p << "\n";
        }
    }
    fin.close(); fout.close();
    remove("admin.txt");
    rename("temp_admin.txt", "admin.txt");

    if (updated) cout << "Password updated successfully.\n";
    else cout << "Incorrect old password.\n";
}

void withdrawSelf(const string& username) {
    double amount;
    string record = getUserRecord(username);
    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount > b) cout << "Insufficient balance.\n";
    else {
        b -= amount;
        updateUserRecord(username, p, b);
        cout << "Withdrawal successful.\n";
    }
}

void checkSelfBalance(const string& username) {
    string record = getUserRecord(username);
    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;
    cout << "Your current balance: " << b << "\n";
}

void resetUserPassword(const string& username) {
    string oldPass, newPass;
    string record = getUserRecord(username);
    stringstream ss(record);
    string u, p; double b;
    ss >> u >> p >> b;

    cout << "Enter old password: ";
    cin >> oldPass;
    if (oldPass != p) {
        cout << "Incorrect old password.\n"; return;
    }

    cout << "Enter new password: ";
    cin >> newPass;
    updateUserRecord(username, newPass, b);
    cout << "Password changed successfully.\n";
}

int main() {
    int option;
    cout << "Welcome to xxx E_CASH SERVICES ********\n";
    cout << "Choose option:\n";
    cout << "1: Normal user login\n";
    cout << "2: Administrator login\n";
    cout << "Enter your option: ";
    cin >> option;

    if (option == 1) {
        normal_user();
    } else if (option == 2) {
        admin();
    } else {
        cout << "Invalid option selected.\n";
    }

    return 0;
}
