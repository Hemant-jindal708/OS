#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

class Bank {
private:
    int accountNumber;
    double balance;
    mutable mutex mtx;

public:
    Bank(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

    void Deposit(double amount) {
        lock_guard<mutex> lock(mtx);
        balance += amount;
        cout << "Account " << accountNumber << " Deposit: " << amount 
             << ", New Balance: " << balance << endl;
    }

    void Withdraw(double amount) {
        lock_guard<mutex> lock(mtx);
        if (balance > amount) {
            balance -= amount;
            cout << "Account " << accountNumber << " Withdraw: " << amount 
                 << ", New Balance: " << balance << endl;
        } else {
            cout << "Account " << accountNumber << " Withdrawal Failed: Not enough money\n";
        }
    }

    double getBalance() {
        lock_guard<mutex> lock(mtx);
        return balance;
    }

    int getAccountNumber()  {
        return accountNumber;
    }
};

void simulateDeposits(Bank& account, int numOfDeposits, double amount) {
    for (int i = 0; i < numOfDeposits; i++) {
        account.Deposit(amount);
    }
}

void simulateWithdrawl(Bank& account, int numOfWithdrawls, double amount) {
    for (int i = 0; i < numOfWithdrawls; i++) {
        account.Withdraw(amount);
    }
}

int main() {
    // Store pointers to Bank objects in the vector
    vector<Bank*> accounts = {
        new Bank(1, 1000),
        new Bank(2, 1050),
        new Bank(3, 3000),
    };

    vector<thread> threads;

    for (auto& account : accounts) {
        threads.emplace_back(simulateDeposits, std::ref(*account), 7, 400);  // Dereference to pass by reference
        threads.emplace_back(simulateWithdrawl, std::ref(*account), 8, 750); // Dereference to pass by reference
    }

    for (auto& th : threads) {
        th.join();
    }

    cout << "\nFinal Balances:\n";
    for (auto& account : accounts) {
        cout << "Account " << account->getAccountNumber() << " Balance: " << account->getBalance() << endl;
        delete account; // Free the dynamically allocated memory
    }

    return 0;
}