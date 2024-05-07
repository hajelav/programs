#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.hpp"

using namespace std;

class SavingsAccount : public Account
{

public:
    SavingsAccount(int accountNUmber, int balance, string name, int interest) {
        setAccountName(name);
        setAccountNumber(accountNUmber);
        setBalance(balance);
        this->interest = interest;
    }

    void deposit(int amount) override
    {
        int balance = getBalance();
        balance += amount;
    }

    void withdraw(int amount) override
    {
        int balance = getBalance();
        balance -= amount;
    }

    int calculateInterest() {
        return interest/100 * getBalance();
    }

private:
    int interest;
};
#endif