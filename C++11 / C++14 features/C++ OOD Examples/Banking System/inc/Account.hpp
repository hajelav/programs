#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;
class Account {
public:
    Account() = default;
    ~Account() = default;
    int getAccountNumber() {
        return accountNUmber;
    }
    int getBalance() {
        return balance;
    }
    string getAccountName() {
        return name;
    }

    void setAccountNumber(int accountNumber) {
        this->accountNUmber = accountNUmber;
    }
    void setBalance(int balance) {
        this->balance = balance;
    }
    void setAccountName(string name) {
        this->name = name;
    }

    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;

    

private:
    int accountNUmber;
    int balance;
    string name;


};

#endif // !ACCOUNT_H