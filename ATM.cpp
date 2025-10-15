#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

long amount = 5000, deposit, withdraw;
int choice, pin, k, c;
char transaction = 'Y';

// Function to clear screen (platform-specific)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to simulate delay
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

int main() {
    clearScreen();
    
    // Card insertion message
    {
        clearScreen();
        string str = " PLEASE INSERT YOUR CARD ";
        char pwd[50];
        int j;
        
        // Simulate loading animation
        for (int j = 1; j < 10; j++) {
            delay(20);
            cout << "*";
        }
        
        for (size_t j = 0; j < str.length(); j++) {
            delay(20);
            cout << str[j];
        }
        
        for (int j = 1; j < 10; j++) {
            delay(20);
            cout << "*";
        }
    }
    
    cin.get(); // Wait for key press
    
    // Card reading simulation
    {
        cout << "\n\n";
        delay(1000);
        cout << "CARD READING" << endl;
        delay(500);
        cout << "CARD MATCH" << endl;
        delay(500);
        cout << "Press Enter To Continue";
        cin.get();
    }
    
    clearScreen();
    
    // PIN verification
    while (pin != 1111) {
        cout << "\n\nENTER YOUR SECRET PIN: ";
        cin >> pin;
        if (pin != 1111)
            cout << "\nPLEASE ENTER VALID PASSWORD." << endl;
    }
    
    do {
        delay(100);
        cout << "\n1. Saving Account" << "\n2. Current Account\n3. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> c;
        clearScreen();
        
        switch (c) {
            case 3:
                return 0;
                break;
                
            case 1:
            case 2:
                delay(100);
                cout << "\n*****************************";
                cout << "\n****WELCOME TO ATM SYSTEM****" << endl;
                cout << "1. Check Balance" << endl << "2. Withdraw Cash" << endl;
                cout << "3. Deposit Cash" << endl << "4. Change Pin" << "\n5. Exit" << endl;
                cout << "*******************************" << endl;
                cout << "Enter Your Choice: ";
                cin >> choice;
                
                switch (choice) {
                    case 1:
                        cout << "YOUR BALANCE IN RUPEES: " << amount;
                        break;
                        
                    case 2:
                        cout << "ENTER THE AMOUNT TO WITHDRAW: ";
                        cin >> withdraw;
                        if (withdraw % 100 != 0) {
                            cout << "ENTER THE AMOUNT IN MULTIPLES OF HUNDRED." << endl;
                        } else if (withdraw > (amount - 100)) {
                            cout << "INSUFFICIENT BALANCE";
                        } else if (withdraw % 500 == 0) {
                            amount = amount - withdraw;
                            cout << endl << "\n****PLEASE COLLECT CASH****" << endl;
                            withdraw = withdraw / 500;
                            delay(500);
                            cout << "       " << withdraw << " X 500 NOTES";
                            delay(500);
                            cout << "\n\nYOUR REMAINING BALANCE IS: " << amount;
                        } else if (withdraw % 500 != 0 && withdraw > 400) {
                            int z = withdraw % 500;
                            int w = withdraw - z;
                            int v = w / 500;
                            int y = z / 100;
                            cout << endl << "\n****PLEASE COLLECT CASH****" << endl;
                            delay(500);
                            cout << "       " << v << " X 500 NOTES" << "\n" << "       " << y << " X 100 NOTES";
                            amount = amount - withdraw;
                            delay(500);
                            cout << "\n\nYOUR REMAINING BALANCE IS: " << amount;
                        } else {
                            withdraw = withdraw / 100;
                            cout << endl << "\n****PLEASE COLLECT CASH****" << endl;
                            delay(500);
                            cout << "       " << withdraw << " X 100 NOTES";
                            amount = amount - (100 * withdraw);
                            delay(500);
                            cout << "\n\nYOUR REMAINING BALANCE IS: " << amount;
                        }
                        break;
                        
                    case 3:
                        cout << "ENTER THE AMOUNT TO DEPOSIT: ";
                        cin >> deposit;
                        delay(500);
                        cout << " " << amount << " + " << deposit;
                        amount = amount + deposit;
                        cout << " = " << amount;
                        delay(500);
                        cout << "\nYOUR BALANCE IS: " << amount;
                        break;
                        
                    case 4:
                        long m, n, l;
                        cout << "ENTER YOUR MOBILE NUMBER: +91 ";
                        cin >> n;
                        if (n != 8630864432) {
                            cout << "THIS NUMBER IS NOT REGISTERED WITH THIS ACCOUNT!!";
                        } else {
                            delay(1000);
                            cout << "\nYOUR ONE TIME PASSWORD IS: 987654" << "\nENTER YOUR ONE TIME PASSWORD: ";
                            cin >> m;
                            if (m != 987654) {
                                delay(500);
                                cout << "\nINVALID OTP!!";
                            } else {
                                cout << "\nENTER NEW PIN: ";
                                cin >> l;
                                pin = l;
                                delay(500);
                                cout << "\nYOU HAVE SUCCESSFULLY CHANGED YOUR PIN.";
                                delay(300);
                                cout << "\nYOUR NEW PIN: " << pin;
                            }
                        }
                        break;
                        
                    case 5:
                        cout << "\nTHANK YOU FOR USING ATM SERVICE..." << endl;
                        break;
                        
                    default:
                        cout << "INVALID CHOICE";
                }
                break;
        }
        
        cout << "\nPress Enter to continue";
        cin.ignore(); // Clear input buffer
        cin.get();
        
        delay(1000);
        cout << "\n\n\n\n\n\nDO YOU WISH TO HAVE ANOTHER TRANSACTION (Y/N): ";
        cin >> transaction;
        
        if (transaction == 'n' || transaction == 'N')
            k = 1;
            
    } while (!k);
    
    delay(200);
    cout << "\n\n\nTHANKS FOR USING OUR ATM SERVICE";
    cin.ignore();
    cin.get();
    
    return 0;
}
