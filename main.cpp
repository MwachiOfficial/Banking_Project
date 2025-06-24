#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int withdraw_cash();
int check_balance();
int reset_password(string *pass_ptr);
int welcome_user();
int normal_user();
int admin();
int welcome_admin();
int deposit_cash();
int withdraw_balance();
int check_client_balance();
int reset_client_password(string *adminPtr);

int welcome_user(string *pass_ptr){
    cout<<"Welcome User\n";
    int option;
    cout << "1. Withdraw cash\n";
    cout << "2. Check balance\n";
    cout << "3. Reset password\n";
    cout << "Enter option to proceed: ";
    cin >> option;

    if (option == 1) {
        withdraw_cash();
    } else if (option == 2) {
        check_balance();
    } else if (option == 3) {
        reset_password(pass_ptr);
    } else {
        cout << "Invalid option selected.\n";
    }

    return 0;

}

int withdraw_cash(){
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
    
       
       cout << endl;
    return 0;
}
int check_balance(){
    return 0;
}

int reset_password(string *pass_ptr){
    string new_password;

    cout << "Enter new password: ";
    cin >> new_password;
    *pass_ptr = new_password;

    ofstream fout("user.txt", ios::app);
     if (!fout) {
        cout << "Error opening file for writing.\n";
        return 1;
    }

    fout << new_password << endl;
    cout << "Updated password: " << *pass_ptr << endl;
    fout.close();

    welcome_user(pass_ptr);
    return 0;
}

//My main user function
int normal_user() {
    string user_username;
    string *pass_ptr;
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

    pass_ptr = &user_password;


    fout.close();

    welcome_user(pass_ptr);

    return 0;
}


int welcome_admin(string *adminPtr) {
    int option;
    cout << "1. Deposit money for client\n";
    cout << "2. Withdraw money for client\n";
    cout << "3. Check client balance\n";
    cout << "4. Reset Password\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        deposit_cash();
    } else if (option == 2) {
        withdraw_balance();
    } else if (option == 3) {
        check_client_balance();
    } else if(option == 4){
        reset_client_password(adminPtr);
    }
    else {
        cout << "Invalid option selected.\n";
    }
    return 0;
}

int deposit_cash(){
    return 0;
}

int withdraw_balance(){
    return 0;
}

int check_client_balance(){
    return 0;
}

int reset_client_password(string *adminPtr){
    string new_client_pass;

    cout << "Enter new password: ";
    cin >> new_client_pass;

    ofstream fout("admin.txt", ios::app);
    if(!fout){
        cout << "Error opening file for writing. \n";
        return 1;
    }
    fout << new_client_pass <<endl;
    cout << "Updated Password: " << new_client_pass << endl;
    *adminPtr = new_client_pass;
    fout.close();

    welcome_admin(adminPtr);

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

    fout << admin_username << "\n" << admin_password << "\n";

    adminPtr = &admin_password;
    fout.close();

    welcome_admin(adminPtr);
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