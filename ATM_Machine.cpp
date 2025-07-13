#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class ATM {
private:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    bool isLocked = false;

public:
    ATM() {}

    void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_No_a, bool isLocked_a) {
        account_No = account_No_a;
        name = name_a;
        PIN = PIN_a;
        balance = balance_a;
        mobile_No = mobile_No_a;
        isLocked = isLocked_a;
    }

    long int getAccountNo() const { return account_No; }
    string getName() const { return name; }
    int getPIN() const { return PIN; }
    double getBalance() const { return balance; }
    string getMobileNo() const { return mobile_No; }
    bool getLockStatus() const { return isLocked; }

    void cashWithDraw(int amount) {
        if (amount > 0 && amount <= balance && amount <= 20000) {
            balance -= amount;
            cout << "\nPlease Collect Your Cash" << endl;
            cout << "Remaining Balance: \u20B9" << balance << endl;
            // For actual transaction history, we could log here
        } else if (amount > 20000) {
            cout << "\nWithdrawal limit exceeded (Max: \u20B920000)." << endl;
        } else {
            cout << "\nInvalid amount or insufficient balance." << endl;
        }
    }

    void setMobile(string oldMobile, string newMobile) {
        if (oldMobile == mobile_No) {
            mobile_No = newMobile;
            cout << "\nMobile number updated successfully." << endl;
        } else {
            cout << "\nIncorrect old mobile number." << endl;
        }
    }

    void lockAccount() {
        isLocked = true;
        cout << "\nAccount has been locked." << endl;
    }

    void unlockAccount() {
        isLocked = false;
        cout << "\nAccount has been unlocked." << endl;
    }

    string toCSV() const {
        return to_string(account_No) + "," + name + "," + to_string(PIN) + "," +
               to_string(balance) + "," + mobile_No + "," + to_string(isLocked);
    }

    bool fromCSV(const string& line) {
        stringstream ss(line);
        string token;

        try {
            getline(ss, token, ','); if (token.empty()) return false;
            account_No = stol(token);

            getline(ss, name, ','); if (name.empty()) return false;

            getline(ss, token, ','); if (token.empty()) return false;
            PIN = stoi(token);

            getline(ss, token, ','); if (token.empty()) return false;
            balance = stod(token);

            getline(ss, mobile_No, ','); if (mobile_No.empty()) return false;

            getline(ss, token, ','); if (token.empty()) return false;
            isLocked = stoi(token);

            return true;
        } catch (...) {
            return false; // Invalid line format
        }
    }
};

// ---- Utility Functions ----

vector<ATM> loadUsersFromFile(const string& filename) {
    vector<ATM> users;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        ATM user;
        if (user.fromCSV(line)) {
            users.push_back(user);
        } else {
            cout << "Skipped invalid line in file: " << line << endl;
        }
    }
    return users;
}

void saveUsersToFile(const string& filename, const vector<ATM>& users) {
    ofstream file(filename);
    for (const ATM& user : users) {
        file << user.toCSV() << endl;
    }
}

// ---- Main ----

int main() {
    vector<ATM> users = loadUsersFromFile("users.txt");

    long int enteredAcc;
    int enteredPin;

    cout << "Enter Account Number: ";
    cin >> enteredAcc;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    bool found = false;
    for (ATM& user : users) {
        if (user.getAccountNo() == enteredAcc && user.getPIN() == enteredPin) {
            if (user.getLockStatus()) {
                cout << "\nAccount is locked. Contact bank to unlock." << endl;
                return 0;
            }

            int choice;
            do {
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
                        cout << "\nAvailable Balance: \u20B9" << user.getBalance() << endl;
                        break;

                    case 2: {
                        int amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        user.cashWithDraw(amount);
                        break;
                    }

                    case 3:
                        cout << "\n--- User Details ---" << endl;
                        cout << "Account Number: " << user.getAccountNo() << endl;
                        cout << "Name: " << user.getName() << endl;
                        cout << "Mobile Number: " << user.getMobileNo() << endl;
                        // cout << "Available Balance: \$" << user.getBalance() << endl;
                        cout << "\nAvailable Balance: ₹" << user.getBalance() << endl;
                        cout << "Account Status: " << (user.getLockStatus() ? "Locked" : "Active") << endl;
                        break;

                    case 4: {
                        string oldMob, newMob;
                        cout << "Enter old mobile number: ";
                        cin >> oldMob;
                        cout << "Enter new mobile number: ";
                        cin >> newMob;
                        user.setMobile(oldMob, newMob);
                        break;
                    }

                    case 5:
                        cout << "\nTransaction history feature not yet implemented.\n";
                        break;

                    case 6:
                        user.lockAccount();
                        break;

                    case 7:
                        cout << "Exiting ATM..." << endl;
                        break;

                    default:
                        cout << "Invalid choice." << endl;
                }

                saveUsersToFile("users.txt", users);

            } while (choice != 7);

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nInvalid account number or PIN." << endl;
    }

    return 0;
}
