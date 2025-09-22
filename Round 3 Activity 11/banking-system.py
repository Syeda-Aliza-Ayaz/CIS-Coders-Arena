import sys
import os
from colorama import Fore, Back, Style, init
init(autoreset=True)
import pyfiglet

def main():
    banner = pyfiglet.figlet_format("Offline Banking System", font = 'big', width = 150)
    print(Fore.CYAN + banner)
    # set files
    with open('./data/accounts.txt', 'r') as r_f, open('./data/accounts.txt', 'a') as w_f:
        accounts = r_f.readlines()
        if not accounts:
            w_f.write("username|password|balance\n")  # Ensure header exists

    with open('./data/transactions.txt', 'r') as r_f, open('./data/transactions.txt', 'a') as w_f:
        transaction = r_f.readlines()
        if not transaction:
            w_f.write("username|activity|balance deposited/withdrawn|balance remaining\n")  # Ensure header exists

    while True:
        print(Fore.YELLOW + "Welcome to the Offline Banking System!")
        print("1. Register an account")
        print("2. Login to your account")
        print("9. Exit")

        choice = input(Fore.GREEN + "Please select an option (1, 2, 9): ")

        if choice == '1':
            create_account()
        elif choice == '2':
            login()
        elif choice == '9':
            sys.exit(Fore.CYAN + "Thank you for using the Offline Banking System. Goodbye!")
        else:
            print(Fore.RED + "Invalid choice, please try again.")
    
#save data to files
def save_data(filename, data):
    with open(filename, 'a') as f:
        f.write(data + '\n')

# register
def create_account():
    print()
    username = input("Enter a username: ").strip()
    if not username:
        print(Fore.RED + "Username cannot be empty.")
        return
    if len(username) < 3:
        print(Fore.RED + "Username must be at least 3 characters long.")
        return
    with open('./data/accounts.txt', 'r') as f:
        accounts = f.readlines()
        if any(username == accounts.split('|')[0] for accounts in accounts[1:]):
            print(Fore.RED + "Username already exists. Please choose a different username.\n")
            return
    password = input("Enter a password: ").strip()
    if not password:
        print(Fore.RED + "Password cannot be empty.\n")
        return
    if len(password) < 6:
        print(Fore.RED + "Password must be at least 6 characters long.\n")
        return
    balance = 0.0
    save_data('./data/accounts.txt', f"{username}|{password}|{balance:.2f}")
    print(Fore.GREEN + Style.BRIGHT + "☑️ Account created successfully!\n")

# login
def login():
    print()
    with open('./data/accounts.txt', 'r') as f:
        accounts = f.readlines()
        if len(accounts) >= 2:
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            for account in accounts[1:]:
                acc_username, acc_password, balance = account.strip().split('|')
                if acc_username == username and acc_password == password:
                    print(Fore.MAGENTA + Style.BRIGHT + f"👋🏻 Login successful! Welcome {username}.")
                    print(Fore.MAGENTA + f"Your current balance is: {float(balance):.2f}\n")
                    login_onwards_functionality(username, float(balance))
                    return
            print(Fore.RED + "Invalid username or password. Please try again.\n")
            return
        else:
            print(Fore.RED + "No accounts found. Please register an account first.")
            return

#after login functionality
def login_onwards_functionality(username, balance):
    while True:
        print(Fore.YELLOW + f"Welcome {username}! What would you like to do?")
        print("3. Deposit Money")
        print("4. Withdraw Money")
        print("5. View Balance")
        print("6. View Transaction History")
        print("7. Transfer money")
        print("8. Logout")
        print("9. Exit")

        choice = input(Fore.GREEN + "Please select an option (3-9): ")

        if choice == '3':
            balance = deposit_money(username, balance)
            input("Press Enter to continue...")
        elif choice == '4':
            balance = withdraw_money(username, balance)
            input("Press Enter to continue...")
        elif choice == '5':
            view_balance(username, balance)
            input("Press Enter to continue...")
        elif choice == '6':
            view_transaction_history(username)
            input("Press Enter to continue...")
        elif choice == '7':
            balance = transfer_money(username, balance)
            input("Press Enter to continue...")
        elif choice == '8':
            print(Fore.CYAN + "Logging out...")
            return balance
        elif choice == '9':
            sys.exit(Fore.CYAN + "Thank you for using the Offline Banking System. Goodbye!")
            return balance
        else:
            print(Fore.RED + "Invalid choice, please try again.")

#deposit money
def deposit_money(username, balance):
    money = input(Fore.GREEN + "Enter the amount to deposit: ")
    if not money.isdigit() or float(money) <= 0:
        print(Fore.RED + "Invalid amount. Please enter a positive number.")
        return
    money = float(money)
    balance += money
    with open('./data/accounts.txt', 'r') as r_f:
        accounts = r_f.readlines()

    with open('./data/accounts.txt', 'w') as f_w:
        for i, account in enumerate(accounts):
            if i == 0:
                f_w.write(account)  # write header as-is
                continue
            acc_username, acc_password, acc_balance = account.strip().split("|")
            if acc_username == username:
                acc_balance = float(acc_balance) + money
            f_w.write(f"{acc_username}|{acc_password}|{float(acc_balance):.2f}\n")
    save_data('./data/transactions.txt', f"{username}|Deposit|{money}|{balance:.2f}")
    print(Fore.GREEN + Style.BRIGHT + f"✅ Successfully deposited {money}. Your new balance is {balance:.2f}.\n")
    return balance

#withdraw money
def withdraw_money(username, balance):
    money = input(Fore.GREEN + "Enter the amount to withdraw: ")
    if not money.isdigit() or float(money) <= 0:
        print(Fore.RED + "Invalid amount. Please enter a positive number.")
        return
    money = float(money)
    if money > balance:
        print(Fore.RED + "Insufficient balance. Please enter a valid amount.")
        return
    balance -= money
    with open('./data/accounts.txt', 'r') as r_f:
        accounts = r_f.readlines()
    
    with open('./data/accounts.txt', 'w') as f_w:
        for i, account in enumerate(accounts):
            if i == 0:
                f_w.write(account)  # write header as-is
                continue
            acc_username, acc_password, acc_balance = account.strip().split("|")
            if acc_username == username:
                acc_balance = float(acc_balance) - money
            f_w.write(f"{acc_username}|{acc_password}|{float(acc_balance):.2f}\n")
    save_data('./data/transactions.txt', f"{username}|Withdraw|{money}|{balance:.2f}")
    print(Fore.GREEN + Style.BRIGHT + f"✅ Successfully withdrew {money}. Your new balance is {balance:.2f}.\n")
    return balance

#view balance
def view_balance(username, balance):
    print(Fore.MAGENTA + Style.BRIGHT + f"Dear {username}, your current balance is: {balance:.2f}\n")

#view transaction history
def view_transaction_history(username):
    print(Fore.YELLOW + "Transaction History:")
    with open('./data/transactions.txt', 'r') as f:
        transactions = f.readlines()
        flag = False # to check if any transactions exist
        print("------------------------------------------")
        for history in transactions[1:]:
            acc_username, activity, amount, remaining_bal = history.strip().split("|")
            if acc_username == username:
                print(f"Activity: {activity}, Amount: {amount}, Remaining Balance: {remaining_bal}")
                flag = True
        if not flag:
            print(Fore.RED + "No transactions found for this account.")
        print("------------------------------------------")
        return

#transfer money
def transfer_money(username, balance):
    to = input(Fore.GREEN + "Enter the username to transfer money to: ").strip()
    if not to:
        print(Fore.RED + "Username cannot be empty.")
        return
    if to == username:
        print(Fore.RED + "You cannot transfer money to yourself.")
        return
    to_bal = None
    with open('./data/accounts.txt', 'r') as f:
        accounts = f.readlines()
        if not any(to == account.strip().split('|')[0] for account in accounts[1:]):
            print(Fore.RED + "Username does not exist.")
            return
    money = input(Fore.GREEN + "Enter the amount to transfer: ")
    if not money.isdigit() or float(money) <= 0:
        print(Fore.RED + "Invalid amount. Please enter a positive number.")
        return
    money = float(money)
    if money > balance:
        print(Fore.RED + "Insufficient balance. Please enter a valid amount.")
        return
    balance -= money
    with open('./data/accounts.txt', 'r') as r_f:
        accounts = r_f.readlines()

    with open('./data/accounts.txt', 'w') as f_w:
        for i, account in enumerate(accounts):
            if i == 0:
                f_w.write(account)  # write header as-is
                continue
            acc_username, acc_password, acc_balance = account.strip().split("|")
            if acc_username == username:
                acc_balance = str(float(acc_balance) - money)
            elif acc_username == to:
                acc_balance = str(float(acc_balance) + money)
                to_bal = acc_balance
            f_w.write(f"{acc_username}|{acc_password}|{float(acc_balance):.2f}\n")
    if to_bal is None:
        print(Fore.RED + "Transfer failed. Please try again.")
        return balance
    save_data('./data/transactions.txt', f"{username}|Transfer to {to}|{money}|{balance:.2f}")
    save_data('./data/transactions.txt', f"{to}|Received from {username}|{money}|{float(to_bal):.2f}")
    print(Fore.GREEN + Style.BRIGHT + f"✅ Successfully transferred {money} to {to}. Your new balance is {balance:.2f}.\n")
    return balance


if __name__ == "__main__":
    main()