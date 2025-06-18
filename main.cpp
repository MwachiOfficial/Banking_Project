#include <iostream>
#include <fstream>
using namespace std;
int normal_user(){

}
int admin(){
    string username;
    string admin_password;
    cout<<"Welcome to the registration and deposit page\n";
    cout<<"Enter administrator username and person.\n";
    ifstream fin;
    ifstream fout;
    fin.open("admin.txt");
    cout<<"Enter username:\t";
    fin<<admin_username"\n";
    fout<<"Enter password: \t"
    fin<<admin_password"\n";
    fin.close();
    welcome_admin();

}
int welcome_admin(){
    int option;
    cout<<"1. Deposit money for client \n";
    cout<<"2. Deposit money for client \n";
    cout<<"3. Deposit money for client \n";
    cin<<option;
    

}
int main(){
    int option
    cout<<"Welcome to xxx E_CASH SERVICES ********\n";
    cout<<"Choose option;\n"
    cout<<"Option 1: Normal user login\n";
    cout<<"Option 2: Administrator login\n";
    cin<< option;
    if (option=1){
        admin();
    }
    else if(
        normal_user();
    )
}