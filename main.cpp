#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int welcome_user(){
    cout<<"Welcome User\n";
    int option;
    cout << "1. Withdraw cash\n";
    cout << "2. Check balance\n";
    cout << "3. Reset password\n";
    cout << "Enter option to proceed: ";
    cin >> option;
    return 0;

}
//My main user function
int normal_user() {
    string user_username;
    string user_password;

    cout << "Welcome to the Normal User login page\n";

    cout << "Enter username:\t";
    cin >> user_username;

    cout << "Enter password:\t";
    cin >> user_password;

    ofstream fout("user.txt", ios::app);

    if (!fout) {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    fout << user_username << "\n" << user_password << "\n";
    fout.close();

    welcome_user();

    return 0;
}


int welcome_admin() {
    int option;
    cout << "1. Deposit money for client\n";
    cout << "2. Withdraw money for client\n";
    cout << "3. Check client balance\n";
    cout << "Enter your choice: ";
    cin >> option;
    return 0;
}
//My main admin function
int admin() {
    string admin_username;
    string admin_password;

    cout << "Welcome to the registration and deposit page\n";
    cout << "Enter administrator username and password.\n";

    cout << "Enter username:\t";
    cin >> admin_username;

    cout << "Enter password:\t";
    cin >> admin_password;

    ofstream fout("admin.txt",ios::app);
    if (!fout) {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    fout << admin_username << "\n" << admin_password << "\n";
    fout.close();

    welcome_admin();
    return 0;
}

int main() { 
    int option;

    cout << "Welcome to xxx E_CASH SERVICES ********\n";
    cout << "Choose option:\n";
    cout << "Option 1: Normal user login\n";
    cout << "Option 2: Administrator login\n";
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

