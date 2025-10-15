#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>
#include <limits>
#include <iomanip>
using namespace std;

// Global variables
long withdraw, deposit;

struct Account {
    long balance;
    int pin;
    string accountNumber;
    string mobileNumber;
    string accountType;
};

struct Transaction {
    string type;
    long amount;
    string timestamp;
    string accountType;
};

vector<Transaction> transactionHistory;
Account currentAccount;

// Function prototypes
void clearScreen();
void delay(int milliseconds);
bool verifyPIN();
void showMainMenu();
void checkBalance();
void withdrawCash();
void depositCash();
void changePIN();
void miniStatement();
void addTransaction(string type, long amount);
int getValidInput(int min, int max);

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

bool verifyPIN() {
    int attempts = 0;
    const int maxAttempts = 3;
    int enteredPin;
    
    while (attempts < maxAttempts) {
        cout << "\n\nENTER YOUR SECRET PIN: ";
        cin >> enteredPin;
        if (enteredPin == currentAccount.pin) {
            return true;
        } else {
            attempts++;
            cout << "\nINVALID PIN. Attempts remaining: " << (maxAttempts - attempts) << endl;
        }
    }
    cout << "\nTOO MANY FAILED ATTEMPTS. PLEASE CONTACT YOUR BANK." << endl;
    return false;
}

void addTransaction(string type, long amount) {
    time_t now = time(0);
    Transaction t = {type, amount, ctime(&now), currentAccount.accountType};
    // Remove newline from timestamp
    t.timestamp = t.timestamp.substr(0, t.timestamp.length()-1);
    transactionHistory.push_back(t);
}

void showMainMenu() {
    cout << "\n" << string(50, '=');
    cout << "\n           WELCOME TO ATM SYSTEM";
    cout << "\n" << string(50, '=') << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Withdraw Cash" << endl;
    cout << "3. Deposit Cash" << endl;
    cout << "4. Change PIN" << endl;
    cout << "5. Mini Statement" << endl;
    cout << "6. Exit" << endl;
    cout << string(50, '=') << endl;
    cout << "Enter Your Choice (1-6): ";
}

void checkBalance() {
    cout << "\n" << string(40, '-') << endl;
    cout << "ACCOUNT TYPE: " << currentAccount.accountType << endl;
    cout << "ACCOUNT NUMBER: " << currentAccount.accountNumber << endl;
    cout << "AVAILABLE BALANCE: ₹" << currentAccount.balance << endl;
    cout << string(40, '-') << endl;
}

void withdrawCash() {
    long withdrawAmount;
    cout << "ENTER THE AMOUNT TO WITHDRAW: ₹";
    cin >> withdrawAmount;
    
    if (withdrawAmount % 100 != 0) {
        cout << "PLEASE ENTER AMOUNT IN MULTIPLES OF 100." << endl;
    } else if (withdrawAmount > currentAccount.balance) {
        cout << "INSUFFICIENT BALANCE!" << endl;
        cout << "Your current balance: ₹" << currentAccount.balance << endl;
    } else if (withdrawAmount > 20000) {
        cout << "WITHDRAWAL LIMIT EXCEEDED (MAX: ₹20,000)" << endl;
    } else {
        currentAccount.balance -= withdrawAmount;
        addTransaction("WITHDRAW", withdrawAmount);
        
        cout << "\n" << string(40, '*') << endl;
        cout << "       PLEASE COLLECT CASH" << endl;
        cout << string(40, '*') << endl;
        cout << "AMOUNT WITHDRAWN: ₹" << withdrawAmount << endl;
        cout << "REMAINING BALANCE: ₹" << currentAccount.balance << endl;
        
        // Show denomination breakdown
        cout << "\nDENOMINATION:" << endl;
        int fiveHundredNotes = withdrawAmount / 500;
        int remaining = withdrawAmount % 500;
        int hundredNotes = remaining / 100;
        
        if (fiveHundredNotes > 0) {
            cout << "  " << fiveHundredNotes << " x ₹500 notes" << endl;
        }
        if (hundredNotes > 0) {
            cout << "  " << hundredNotes << " x ₹100 notes" << endl;
        }
    }
}

void depositCash() {
    long depositAmount;
    cout << "ENTER THE AMOUNT TO DEPOSIT: ₹";
    cin >> depositAmount;
    
    if (depositAmount <= 0) {
        cout << "INVALID AMOUNT!" << endl;
    } else if (depositAmount > 50000) {
        cout << "DEPOSIT LIMIT EXCEEDED (MAX: ₹50,000)" << endl;
    } else {
        currentAccount.balance += depositAmount;
        addTransaction("DEPOSIT", depositAmount);
        
        cout << "\n" << string(40, '*') << endl;
        cout << "       DEPOSIT SUCCESSFUL" << endl;
        cout << string(40, '*') << endl;
        cout << "AMOUNT DEPOSITED: ₹" << depositAmount << endl;
        cout << "NEW BALANCE: ₹" << currentAccount.balance << endl;
    }
}

void changePIN() {
    string mobile;
    long otp, newPin;
    
    cout << "ENTER YOUR REGISTERED MOBILE NUMBER: +91 ";
    cin >> mobile;
    
    if (mobile != currentAccount.mobileNumber) {
        cout << "MOBILE NUMBER NOT REGISTERED WITH THIS ACCOUNT!" << endl;
        return;
    }
    
    delay(1000);
    cout << "\nSENDING OTP TO YOUR MOBILE..." << endl;
    delay(2000);
    cout << "YOUR ONE TIME PASSWORD IS: 987654" << endl;
    cout << "ENTER OTP: ";
    cin >> otp;
    
    if (otp != 987654) {
        cout << "INVALID OTP!" << endl;
        return;
    }
    
    cout << "ENTER NEW 4-DIGIT PIN: ";
    cin >> newPin;
    
    // Validate PIN length
    if (newPin < 1000 || newPin > 9999) {
        cout << "PIN MUST BE 4 DIGITS!" << endl;
        return;
    }
    
    currentAccount.pin = newPin;
    cout << "\nPIN CHANGED SUCCESSFULLY!" << endl;
    delay(1000);
}

void miniStatement() {
    cout << "\n" << string(60, '=');
    cout << "\n                  MINI STATEMENT";
    cout << "\nACCOUNT TYPE: " << currentAccount.accountType;
    cout << "\nACCOUNT NO: " << currentAccount.accountNumber;
    cout << "\nCURRENT BALANCE: ₹" << currentAccount.balance;
    cout << "\n" << string(60, '=') << endl;
    
    cout << left << setw(15) << "TYPE" 
         << setw(15) << "AMOUNT" 
         << setw(25) << "DATE & TIME" << endl;
    cout << string(60, '-') << endl;
    
    int count = 0;
    // Show last 5 transactions for current account
    for (auto it = transactionHistory.rbegin(); it != transactionHistory.rend() && count < 5; ++it) {
        if (it->accountType == currentAccount.accountType) {
            cout << left << setw(15) << it->type 
                 << setw(15) << ("₹" + to_string(it->amount))
                 << setw(25) << it->timestamp << endl;
            count++;
        }
    }
    
    if (count == 0) {
        cout << "        No transactions found" << endl;
    }
    
    cout << string(60, '=') << endl;
}

int getValidInput(int min, int max) {
    int input;
    while (!(cin >> input) || input < min || input > max) {
        cout << "Invalid input! Please enter between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

int main() {
    // Initialize accounts
    Account saving = {5000, 1111, "SAV123456", "8630864432", "SAVINGS"};
    Account current = {8000, 2222, "CUR789012", "8630864432", "CURRENT"};
    
    clearScreen();
    
    // Welcome animation
    cout << "\n\n" << string(20, '*');
    cout << " WELCOME TO ATM ";
    cout << string(20, '*') << endl;
    delay(1000);
    
    // Account type selection
    cout << "\nSELECT ACCOUNT TYPE:\n";
    cout << "1. Savings Account\n";
    cout << "2. Current Account\n";
    cout << "Enter your choice (1-2): ";
    
    int accType = getValidInput(1, 2);
    currentAccount = (accType == 1) ? saving : current;
    
    clearScreen();
    
    // PIN verification
    if (!verifyPIN()) {
        return 0;
    }
    
    // Main transaction loop
    char continueTransaction;
    do {
        clearScreen();
        showMainMenu();
        
        int choice = getValidInput(1, 6);
        
        switch (choice) {
            case 1: 
                checkBalance(); 
                break;
            case 2: 
                withdrawCash(); 
                break;
            case 3: 
                depositCash(); 
                break;
            case 4: 
                changePIN(); 
                break;
            case 5: 
                miniStatement(); 
                break;
            case 6: 
                cout << "\nTHANK YOU FOR BANKING WITH US!" << endl;
                delay(1000);
                return 0;
        }
        
        cout << "\nPerform another transaction? (Y/N): ";
        cin >> continueTransaction;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (continueTransaction == 'Y' || continueTransaction == 'y');
    
    cout << "\nTHANK YOU FOR USING OUR ATM SERVICE!" << endl;
    cout << "HAVE A NICE DAY!" << endl;
    delay(2000);
    
    return 0;
}
