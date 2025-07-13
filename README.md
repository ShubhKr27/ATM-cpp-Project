# Simple ATM Management System (C++)

This is a console-based ATM (Automated Teller Machine) management system implemented in C++. It simulates basic ATM functionalities such as checking balance, cash withdrawal, updating mobile numbers, and viewing user details. User data is persisted in a CSV file (`users.txt`).

## Features

  * **User Authentication:** Secure login using account number and PIN.
  * **Account Lockout:** Accounts can be locked for security reasons.
  * **Balance Inquiry:** Check the current account balance.
  * **Cash Withdrawal:** Withdraw cash with limits and balance checks.
  * **Mobile Number Update:** Change the registered mobile number after verification.
  * **User Details Display:** View personal and account information.
  * **Data Persistence:** User data is loaded from and saved to a `users.txt` file, ensuring data is not lost between sessions.
  * **Error Handling:** Basic error handling for invalid input and file operations.

## How to Compile and Run

### Prerequisites

  * A C++ compiler (e.g., g++).

### Compilation

1.  Save the provided code as `atm_system.cpp`.

2.  Open a terminal or command prompt.

3.  Navigate to the directory where you saved the file.

4.  Compile the code using a C++ compiler:

    ```bash
    g++ atm_system.cpp -o atm_system
    ```

### Running the Application

1.  After successful compilation, an executable file named `atm_system` (or `atm_system.exe` on Windows) will be created.

2.  Run the executable from your terminal:

    ```bash
    ./atm_system
    ```

### `users.txt` File Format

The system uses a `users.txt` file to store user data. Each line in the file represents a user and should follow this comma-separated value (CSV) format:

```
account_No,name,PIN,balance,mobile_No,isLocked
```

**Example `users.txt`:**

```
1234567890,John Doe,1234,15000.50,9876543210,0
9876543210,Jane Smith,5678,2500.75,8765432109,1
```

  * `account_No`: Long integer
  * `name`: String (no commas allowed within the name)
  * `PIN`: Integer
  * `balance`: Double
  * `mobile_No`: String
  * `isLocked`: Integer (0 for unlocked, 1 for locked)

**Important:** Ensure you have a `users.txt` file in the same directory as your executable before running the application. If the file doesn't exist or is empty, the application will start with no users.

## Usage

When you run the application, you'll be prompted to enter your account number and PIN.

```
Enter Account Number: 1234567890
Enter PIN: 1234
```

If the credentials are correct and the account isn't locked, you'll see the main menu:

```
**** ATM Main Menu ****
1. Check Balance
2. Cash Withdraw
3. Show User Details
4. Update Mobile No.
5. View Transaction History
6. Lock Account (for security)
7. Exit
Enter choice:
```

Follow the on-screen prompts to perform desired operations.

## Code Structure

  * **`ATM` Class:** Represents an ATM user account with properties like account number, name, PIN, balance, mobile number, and lock status. It includes methods for data manipulation and serialization/deserialization to CSV.
  * **`loadUsersFromFile(const string& filename)`:** Utility function to read user data from the specified CSV file into a `std::vector<ATM>`.
  * **`saveUsersToFile(const string& filename, const vector<ATM>& users)`:** Utility function to write the current user data from a `std::vector<ATM>` back to the CSV file.
  * **`main()` function:** The entry point of the program, handling user interaction, authentication, and calling appropriate `ATM` class methods.

## Future Enhancements

  * **Transaction History:** Implement a robust system to log and display transaction history for each account.
  * **Admin Features:** Add an administrator mode for managing user accounts (e.g., creating new accounts, unlocking accounts).
  * **Improved PIN Management:** Features like changing PIN, forgotten PIN recovery.
  * **Deposit Functionality:** Allow users to deposit money into their accounts.
  * **More Robust Error Handling:** Comprehensive input validation and error messages.
  * **GUI:** Develop a graphical user interface for a more user-friendly experience.
  * **Security Improvements:** Hashing PINs instead of storing them in plain text.

-----
