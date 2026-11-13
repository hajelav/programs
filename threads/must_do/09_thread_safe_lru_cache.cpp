
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <unoredered_map>

using namespace std;

typedef struct node {
  int key;
  int val;
  struct node *prev;
  struct node *next;
  node(int key, int val)
      : val(val), key(key), prev(nullptr), next(nullptr) {}
} NODE;

class LRUCache {
public:
  LRUCache(int size)
      : capacity(size), currSize(0) {

    HEAD = new NODE(-1);
    TAIL = new NODE(-1);
    HEAD->next = TAIL;
    TAIL->prev = HEAD;
  }

  int get(int key) {
  }

  bool put(int key, int val) {
  }

private:
  NODE *HEAD,
      *TAIL;
  int capacity;
  int currSize;
  unordered_map<int, NODE *> valNodeMap;
};

int main() {

  retrurn 0;
}