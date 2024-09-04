# Suri Banking System

Welcome to the **Suri Banking System** project. This system simulates basic banking operations such as creating an account, logging in, checking balances, transferring funds, and more. The project is implemented in C and demonstrates file handling, linked lists, and basic encryption for password management.

## Features

- **User Sign-Up:** Create a new account with a unique username and password.
- **User Login:** Log in to the system with a valid username and password.
- **Balance Management:** Add or withdraw money from your account.
- **Funds Transfer:** Transfer funds between users.
- **Transaction Logs:** View logs of all transactions associated with your account.

## File Structure

- **`main.c`**: The main driver code that contains the banking system operations.
- **`encrypt.h`**: Header file for encryption and decryption functions used for password management.
- **`user.txt`**: Stores user data including usernames, encrypted passwords, and balances.
- **`logs/`**: Directory that stores logs of all transactions for each user.

## How It Works

### Encryption and Password Management

Passwords are stored in an encrypted format using the custom `encrypt()` function. Upon login, the system decrypts the stored password and compares it with the input provided by the user.

### Transaction Logs

Every transaction (like adding balance, withdrawing funds, transferring funds) is logged into a file named after the user in the `logs/` directory. Each log entry records the type of transaction, amount, date, and the new balance after the transaction.

## Compilation and Execution

To compile the project:

```bash
gcc -o banking_system main.c encrypt.c -Wall -Wextra
```
## Note:
The program assumes that the logs/ directory exists. Ensure to create it if it doesn't exist:

```bash
mkdir logs
```
The program stores user data in a file named user.txt in the working directory