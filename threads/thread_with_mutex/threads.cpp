#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <time.h>

using namespace std;
pthread_mutex_t mutex;

class Account {

    public:
        Account(int accNum, int bal, string name) : m_acc_number(accNum), m_balance(bal), m_name(name) {}
        ~Account() {}

        int get_account_number() {
            return m_acc_number;
        }
        int get_balance() {
            return m_balance; 
        }
        void deposit(int num) {
            m_balance += num;
        }
        void withdraw(int num) {
            if(m_balance >= num) {
                m_balance -= num;
            } else {
                cout << "cannot withdraw" << endl;
            }
        }
    private:
        int m_acc_number;
        int m_balance;
        string m_name;
};


void* thread_function(void *arg) {

    //int thread_num = *((int *)arg);
    int thread_num = 0;
    printf("Hello from thread %d!\n", thread_num);
    pthread_exit(NULL);
}

//producer thread function
void* consumer(void* data) {
    srand(time(NULL));
    //int random_number = rand()%100;
    int random_number = 100;
    pthread_mutex_lock(&mutex);
    Account *account = static_cast<Account*>(data);
    account->withdraw(random_number);
    cout << "Withdraw:" << random_number << " Balance:" << account->get_balance() << endl;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

//producer thread function
void* producer(void* data) {
    srand(time(NULL));
    //int random_number = rand()%100;
    int random_number = 100;
    pthread_mutex_lock(&mutex);
    Account *account = static_cast<Account*>(data);
    account->deposit(random_number);
    cout << "Deposit:" << random_number << " Balance:" << account->get_balance() << endl;
    pthread_mutex_unlock(&mutex);
     pthread_exit(NULL);
}

int main() {

    //create a vector or producers
    int num_threads = 5;
    vector<pthread_t> producers(num_threads);
    vector<pthread_t> consumers(num_threads);
    pthread_mutex_init(&mutex, NULL);

    //create a bank account 
    Account* account = new Account(1234, 1000, "BofA");
    //create 5 producers/consumer threads
    for(int i=0; i<num_threads; i++) {
        pthread_create(&producers[i], NULL, producer, (void*)account);
        pthread_create(&consumers[i], NULL, consumer, (void*)account);
    }
    

   for(int i=0; i<num_threads; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
   }
    pthread_mutex_destroy(&mutex);
    return 0;
}
