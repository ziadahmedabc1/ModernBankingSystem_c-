#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Account
{
    string name;
    string accountNumber;
    double balance;
    string password;
};

// Function to display the 1st screen
void displayWelcomeScreen()
{
    cout << "\nChoose an option:\n";
    cout << "\n1. Login\n";
    cout << "2. Create an Account\n";
    cout << "3. Exit\n";
}


// Function to log in
bool login(Account &acc)
{
    string enteredPassword;

    cout << "Enter your password: ";
    cin >> enteredPassword;

    if (enteredPassword == acc.password)
    {
        return true;
    }
    else
    {
        cout << "\nIncorrect password. Please enter correct password.\n\n";
        system("pause");
        system("CLS");
        return false;
    }
}

// Function to login display the main menu
void displayMainMenu(const Account &acc)
{
    cout << "\n*************";
    cout << "\n* Main Menu *\n";
    cout << "*************\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Logout\n";
    cout << "5. Exit\n";
}

// Function to check if an account already exists
bool accountExists(const string &accountNumber)
{
    ifstream file(accountNumber + ".txt");
    return file.is_open();
}

// Function to create a new account
void createAccount()
{
    system("CLS");

    Account newAccount;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, newAccount.name);

    cout << "Enter Mobile number: ";
    cin >> newAccount.accountNumber;

    // Check if the account already exists
    if (accountExists(newAccount.accountNumber))
    {
        cout << "\nAccount with Mobile number " << newAccount.accountNumber << " already exists. Please try again.\n";
        system("pause");
        system("CLS");
        return;
    }

    cout << "Enter your initial balance: ";
    cin >> newAccount.balance;

    cout << "Set your password: ";
    cin >> newAccount.password;

    ofstream file(newAccount.accountNumber + ".txt");
    file << newAccount.name << endl;
    file << newAccount.balance << endl;
    file << newAccount.password << endl;
    file.close();

    system("CLS");
    cout << "*********************************\n";
    cout << "* Account created successfully! *\n";
    system("pause");
    system("CLS");
}

// Function to check the account balance
void checkBalance(const Account &acc)
{
    string enteredPassword;

    cout << "\nEnter your password: ";
    cin >> enteredPassword;
    system("CLS");
    if (enteredPassword == acc.password)
    {
        cout << "\nAccount Holder Name: " << acc.name;
        cout << "\nBalance: " << acc.balance << endl;
    }
    else
    {
        cout << "Incorrect password. Please enter correct password.\n\n";
    }
    system("pause");
    system("CLS");
}

// Function to deposit funds
void deposit(Account &acc)
{
    double amount;

    cout << "Enter the amount to deposit: ";
    cin >> amount;

    string enteredPassword;

    cout << "\nEnter your password: ";
    cin >> enteredPassword;

    if (enteredPassword == acc.password)
    {
        if (amount <= 0)
        {
            cout << "Insufficient amount. Please enter a positive value.\n";
            return;
        }

        acc.balance += amount;

        ofstream file(acc.accountNumber + ".txt");
        file << acc.name << endl;
        file << acc.balance << endl;
        file << acc.password << endl;
        file.close();

        system("CLS");

        cout << "\nAmount deposited successfully.\n"
             << endl;
        cout << "New balance: " << acc.balance << endl;
        system("pause");
        system("CLS");
    }
    else
    {
        system("CLS");
        cout << "Incorrect password. Unable to deposit funds.\n\n";
        system("pause");
        system("CLS");
    }
}

// Function to withdraw funds
void withdraw(Account &acc)
{
    double amount;

    cout << "\nEnter the amount to withdraw: ";
    cin >> amount;

    string enteredPassword;
    cout << "\nEnter your password: ";
    cin >> enteredPassword;
	
    if (enteredPassword == acc.password)
    {
        if (amount <= 0 || amount > acc.balance)
        {
        	system("CLS");
            cout << "\nInsufficient amount. Please enter a valid amount.\n\n";
			system("pause");
			system("CLS");
			return;
        }
        acc.balance -= amount;

        ofstream file(acc.accountNumber + ".txt");
        file << acc.name << endl;
        file << acc.balance << endl;
        file << acc.password << endl;
        file.close();
        system("CLS");
        cout << "\nAmount withdrawn successfully.";
        cout << "\nNew balance: " << acc.balance << endl;
        system("pause");
        system("CLS");
    }
    else
    {
        system("CLS");
        cout << "\nIncorrect password. Unable to withdraw funds.\n\n";
        system("pause");
        system("CLS");
    }
}

//Main Function
int main()
{
    int choice;
    Account currentUser;
    cout << "************************************************\n";
    cout << "**** Welcome to our bank management system! ****\n";
    cout << "************************************************\n";

    while (true)
    {
        displayWelcomeScreen();
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 3)
        {
            cout << "\nExiting the program. Goodbye!\n";
            break;
        }

        if (choice == 1)
        {
            cout << "\nEnter account number (Same as Mobile Number): ";
            cin >> currentUser.accountNumber;

            ifstream file(currentUser.accountNumber + ".txt");
            if (!file.is_open())
            {
            	system ("CLS");
                cout << "\nAccount not found. Please try again or create a new account.\n";
                system ("pause");
				system ("CLS");
                continue;
            }

            getline(file, currentUser.name);
            file >> currentUser.balance;
            file >> currentUser.password;
            file.close();

            if (!login(currentUser))
            {
                cout << "\nInvalid password. Please try again.\n";
                continue;
            }
            system("CLS");
        }

        else if (choice == 2)
        {
            createAccount();
            continue;
        }
        else
        {
            cout << "\nInvalid choice. Please try again.\n";
            continue;
        }

        while (true)
        {
            displayMainMenu(currentUser);
            cout << "\nEnter your choice: ";
            cin >> choice;

            if (choice == 5)
            {
                cout << "\nExiting the program. Goodbye!\n";
                return 0;
            }

            switch (choice)
            {
            case 1:
                checkBalance(currentUser);
                break;
            case 2:
                deposit(currentUser);
                break;
            case 3:
                withdraw(currentUser);
                break;
            case 4:
                cout << "\nLogged out.\n";
                system("pause");
                system("CLS");
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
            }

            if (choice == 4)
            {
                break;
            }
        }
    }
    return 0;
}