
#include <iostream>
#include "Account.hpp"
#include "SavingsAccount.hpp"
#include <memory>
int main() {

    shared_ptr<Account> a1 = make_shared<SavingsAccount>(1, 1000, "Savings Account", 10);
    a1->deposit(1000);
    cout << a1->getBalance() << endl;
    a1->deposit(100);
    cout << a1->getBalance() << endl;
}