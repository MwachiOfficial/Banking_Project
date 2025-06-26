#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int withdraw_cash(string *client_pass_ptr, string client_username);
int check_balance();
int reset_password(string *client_pass_ptr, string client_username);
int welcome_user();
int normal_user();
int admin();
int welcome_admin();
int deposit_cash();
int register_client(string *adminPtr, string admin_username);
int reset_admin_password(string *adminPtr, string admin_username);

int welcome_user(string *client_pass_ptr, string client_username){
    cout<<"Welcome User\n";
    int option;
    cout << "1. Withdraw cash\n";
    cout << "2. Check balance\n";
    cout << "3. Reset password\n";
    cout << "Enter option to proceed: ";
    cin >> option;

    if (option == 1) {
        withdraw_cash(client_pass_ptr, client_username);
    } else if (option == 2) {
        check_balance();
    } else if (option == 3) {
        reset_password(client_pass_ptr, client_username);
    } else {
        cout << "Invalid option selected.\n";
    }

    return 0;

}

int withdraw_cash(string *client_pass_ptr, string client_username){
    double cash_withdrawal;
    double amount = 10000.00;
    int balance ;

    cout << " Current balance :"<< amount << endl;
    cout << "enter an amount to withdraw: ";
    cin >> cash_withdrawal;

        if(cash_withdrawal <= 0)
        cout << "incorrect withdrawal amount.Please enter again.\n";
        else if (cash_withdrawal > amount)
        cout << "insufficient funds. Please try again.\n";
        else
        balance = amount - cash_withdrawal;
        cout << "withdrwal successful.New balance:" << balance << endl;

    welcome_user(client_pass_ptr, client_username);
    return 0;
}
int check_balance(){
    double amount = 10000.00;
    cout << "Your current balance is: " << amount << endl;
    cout << "Thank you for using our service.\n";
    return 0;
}

int reset_password(string *client_pass_ptr, string client_username){
    string new_password;

    cout << "Enter new password: ";
    cin >> new_password;

    ifstream fin("user.txt");
    ofstream fout("temp.txt");

    if(!fin || !fout){
        cout << "Error opening files \n";
        return 1;
    }

    string username, password;
    bool updated = false;
    while(fin >> username >> password){
        if(username == client_username){
            fout << username << " " << new_password <<endl;
            *client_pass_ptr = new_password;
            updated = true;
        } else{
            fout << username << " " << password <<endl;
        }
    }

    cout << "Updated password: " << *client_pass_ptr << endl;
    fin.close();
    fout.close();

    remove("user.txt");
    rename("temp.txt", "user.txt");

      if (updated)
        cout << "Password updated successfully\n";
      else
        cout << "Username not found\n";


    welcome_user(client_pass_ptr, client_username);
    return 0;
}

int normal_user() {
    string client_username, client_password;

    cout << "Welcome to the Normal User login page\n";

    cout << "Enter username:\t";
    cin >> client_username;

    cout << "Enter password:\t";
    cin >> client_password;

    ifstream fin("user.txt");

    string username, password;

    if (!fin) {
        cout << "Error opening file for reading.\n";
        return 1;
    }
     bool login_success = false;
    while(fin >> username >> password ){
        if(username == client_username && password == client_password){
            string *client_pass_ptr = &client_password;
            welcome_user(client_pass_ptr, client_username);
            login_success = true;
        } else{
            cout << "Invalid username\n";
            main();
        }

    }

    fin.close();
    return 0;
}


int welcome_admin(string *adminPtr, string admin_username) {
    int option;
    cout << "1. Deposit money for client\n";
    cout << "2. Register a new client\n";
    cout << "3. Reset Password\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        deposit_cash();
    } else if (option == 2) {
        register_client(adminPtr, admin_username);
    } else if(option == 3){
        reset_admin_password(adminPtr, admin_username);
    }
    else {
        cout << "Invalid option selected.\n";
    }
    return 0;
}

int deposit_cash(){
    double deposit_amount;
    double balance;
    cout << "Welcome to the deposit page.\n";

    ifstream fin("user_balance.txt");
    if (!(fin >> balance)) {
        cout << "No balance record found. Setting default to Ksh 10,000.\n";
        balance = 10000.00;
    }
    fin.close();


    cout << "Enter amount to deposit for the client: ";
    cin >> deposit_amount;

    if (deposit_amount <= 0) {
        cout << "Invalid deposit amount. Please enter a positive number.\n";
        return -1;
    }

    balance += deposit_amount;
    ofstream fout("user_balance.txt");
    if (!fout) {
        cout << "Error saving balance.\n";
        return 1;
    }
    fout << balance;
    fout.close();

    cout << "Deposit successful! New client balance: Ksh " << balance << endl;
    return 0;
}

int register_client(string *adminPtr, string admin_username){
    string client_username;
    string *client_pass_ptr;
    string client_password;

    cout << "Register new client\n";

    cout << "Enter username:\t";
    cin >> client_username;

    cout << "Enter password:\t";
    cin >> client_password;

    ofstream fout("user.txt", ios::app);

    if (!fout) {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    fout << client_username << " " << client_password << "\n";

    client_pass_ptr = &client_password;


    fout.close();

    welcome_admin(adminPtr, admin_username);

    return 0;
}

int reset_admin_password(string *adminPtr, string admin_username){
    string new_admin_pass;

    cout << "Enter new password: ";
    cin >> new_admin_pass;

    ifstream fin("admin.txt");
    ofstream fout("temporary.txt");

    if(!fin || !fout){
        cout << "Error loading pages \n";
        return 1;
    }

    string username, password;
    bool updated = false;

    while(fin >> username >> password){
        if(username == admin_username){
            fout << username << " " << new_admin_pass <<endl;
            *adminPtr = new_admin_pass;
            updated = true;
        } else {
            fout << username << " " << password <<endl;
        }
    }


    cout << "Updated Password: " << *adminPtr << endl;
    fin.close();
    fout.close();

    remove("admin.txt");
    rename("temporary.txt", "admin.txt");

    if(updated)
      cout << "Password updated successfully \n";
    else
      cout << "Username not found \n";

    welcome_admin(adminPtr, admin_username);

    return 0;
}
//My main admin function
int admin() {
    string admin_username;
    string admin_password;
    string *adminPtr;

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

    fout << admin_username << " " << admin_password << "\n";

    adminPtr = &admin_password;
    fout.close();

    welcome_admin(adminPtr, admin_username);
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