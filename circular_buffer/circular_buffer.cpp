/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class RingBuffer
{

  public:int capacity;
  int currSize;
  bool full;
  bool empty;
    vector < int >buf;
  int start;
  int end;

    RingBuffer (int size)
  {
	capacity = size;
	currSize = 0;
	full = false;
	empty = false;
	end = -1; start = 0;
	for (int i = 0; i < size; i++)
	  buf.push_back (0);
  }


  void enqueue (int num)
  {

	 
    end = (end+1)%capacity;
	buf[end] = num;
 	
	if(currSize < capacity) {
	    currSize++;
	} else {
	    start = (end+1)%capacity;
	}

  }

  int dequeue ()
  {
   int val;
   if(currSize == 0)
        return -1;
    
    if(currSize < capacity) {
        val = buf[start];
        start = (start+1)%capacity;
    }  else {
        start = (end+1)%capacity;
        val = buf[start];
        start = (start+1)%capacity;
    }
    currSize--;

  }
  
  int size() {
      return currSize;
  }
  
  int front() {
      return buf[start];
  }
   int back() {
       return buf[end];
   }


};

void testEnqueue() {
    // Create a ring buffer with a capacity of 5 elements
    RingBuffer buffer(5);

    // Test enqueuing elements
    buffer.enqueue(1);
    assert(buffer.size() == 1);
    assert(buffer.front() == 1);
    assert(buffer.back() == 1);

    buffer.enqueue(2);
    assert(buffer.size() == 2);
    assert(buffer.front() == 1);
    assert(buffer.back() == 2);

    buffer.enqueue(3);
    assert(buffer.size() == 3);
    assert(buffer.front() == 1);
    assert(buffer.back() == 3);

    buffer.enqueue(4);
    assert(buffer.size() == 4);
    assert(buffer.front() == 1);
    assert(buffer.back() == 4);

    buffer.enqueue(5);
    assert(buffer.size() == 5);
    assert(buffer.front() == 1);
    assert(buffer.back() == 5);

    // Test enqueuing when the buffer wraps around
    buffer.dequeue(); // Remove the first element (1)
    buffer.enqueue(6); // Enqueue at the end, wrapping around
    buffer.enqueue(7);
    buffer.enqueue(8);
    assert(buffer.size() == 5);
    assert(buffer.front() == 4); // After wrapping around, 2 is the new front
    assert(buffer.back() == 8);
    
    std::cout << "All enqueue tests passed successfully!" << std::endl;
}

int main() {
    testEnqueue();
    return 0;
}

