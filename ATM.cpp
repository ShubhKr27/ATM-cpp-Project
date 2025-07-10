#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(x) Sleep(x * 1000)
#define CLEAR "cls"
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)
#define CLEAR "clear"
#endif

using namespace std;

class ATM {
private:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    vector<string> transactionHistory;
    bool isLocked = false;
    int pinAttempts = 0;

public:
    void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_No_a) {
        account_No = account_No_a;
        name = name_a;
        PIN = PIN_a;
        balance = balance_a;
        mobile_No = mobile_No_a;
    }

    long int getAccountNo() { return account_No; }
    string getName() { return name; }
    int getPIN() { return PIN; }
    double getBalance() { return balance; }
    string getMobileNo() { return mobile_No; }
    vector<string> getTransactionHistory() { return transactionHistory; }
    bool getLockStatus() { return isLocked; }

    void setMobile(string mob_prev, string mob_new) {
        if (mob_prev == mobile_No) {
            mobile_No = mob_new;
            cout << "\nSuccessfully Updated Mobile no.\n";
        } else {
            cout << "\nIncorrect Old Mobile no!\n";
        }
    }

    void cashWithDraw(int amount_a) {
        if (amount_a > 0 && amount_a <= balance && amount_a <= 20000) {
            balance -= amount_a;
            string transaction = "Withdrew: ₹" + to_string(amount_a);
            transactionHistory.push_back(transaction);
            cout << "\nPlease Collect Your Cash\n";
            cout << "Available Balance: ₹" << balance << endl;
        } else if (amount_a > 20000) {
            cout << "\nWithdrawal limit exceeded! You can only withdraw up to ₹20000.\n";
        } else {
            cout << "\nInvalid Input or Insufficient Balance\n";
        }
    }

    void lockAccount() {
        isLocked = true;
        cout << "\nYour account has been locked due to multiple incorrect attempts.\n";
    }

    void trackPinAttempts() {
        pinAttempts++;
        if (pinAttempts >= 3) {
            lockAccount();
        }
    }

    void resetPinAttempts() {
        pinAttempts = 0;
    }

    void unlockAccount() {
        isLocked = false;
        pinAttempts = 0;
        cout << "\nYour account has been unlocked. Please try again with correct details.\n";
    }
};

int main() {
    int choice = 0, enterPIN;
    long int enterAccountNo;

    ATM user1;
    user1.setData(987654321, "Hardik", 1234, 50000, "9370054900");

    do {
        system(CLEAR);
        cout << "\n**** Welcome to ATM ****\n";
        cout << "\nEnter Your Account No: ";
        cin >> enterAccountNo;

        cout << "Enter PIN: ";
        cin >> enterPIN;

        if (enterAccountNo == user1.getAccountNo() && enterPIN == user1.getPIN()) {
            if (user1.getLockStatus()) {
                cout << "\nAccount is currently locked. Please contact support.\n";
                break;
            }

            user1.resetPinAttempts();

            do {
                int amount = 0;
                string oldMobileNo, newMobileNo;

                system(CLEAR);
                cout << "\n**** ATM Main Menu ****\n";
                cout << "1. Check Balance\n";
                cout << "2. Cash Withdraw\n";
                cout << "3. Show User Details\n";
                cout << "4. Update Mobile No.\n";
                cout << "5. View Transaction History\n";
                cout << "6. Lock Account (for security)\n";
                cout << "7. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "\nYour Bank Balance is: ₹" << user1.getBalance() << endl;
                        break;

                    case 2:
                        cout << "\nEnter the amount to withdraw: ₹";
                        cin >> amount;
                        user1.cashWithDraw(amount);
                        break;

                    case 3:
                        cout << "\n*** User Details ***\n";
                        cout << "Account No: " << user1.getAccountNo() << endl;
                        cout << "Name      : " << user1.getName() << endl;
                        cout << "Balance   : ₹" << user1.getBalance() << endl;
                        cout << "Mobile No.: " << user1.getMobileNo() << endl;
                        break;

                    case 4:
                        cout << "\nEnter Old Mobile No.: ";
                        cin >> oldMobileNo;
                        cout << "Enter New Mobile No.: ";
                        cin >> newMobileNo;
                        user1.setMobile(oldMobileNo, newMobileNo);
                        break;

                    case 5: {
                        vector<string> transactions = user1.getTransactionHistory();
                        cout << "\n*** Transaction History ***\n";
                        if (transactions.empty()) {
                            cout << "No transactions found.\n";
                        } else {
                            for (const string& transaction : transactions) {
                                cout << transaction << endl;
                            }
                        }
                        break;
                    }

                    case 6:
                        user1.lockAccount();
                        break;

                    case 7:
                        cout << "Thank you for using the ATM.\n";
                        exit(0);

                    default:
                        cout << "\nInvalid Option. Please try again.\n";
                        break;
                }

                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();

            } while (true);

        } else {
            cout << "\nInvalid Account Number or PIN!\n";
            user1.trackPinAttempts();

            if (user1.getLockStatus()) {
                char retryChoice;
                cout << "Would you like to try again after 30 seconds? (y/n): ";
                cin >> retryChoice;
                if (retryChoice == 'y' || retryChoice == 'Y') {
                    cout << "Please wait 30 seconds before retrying...\n";
                    SLEEP(30);
                    user1.unlockAccount();
                    continue;
                } else {
                    cout << "Exiting. Please try again later.\n";
                    break;
                }
            }

            cout << "\nPress Enter to retry...";
            cin.ignore();
            cin.get();
        }

    } while (true);

    return 0;
}
