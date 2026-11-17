#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class RingBuffer {
public:
  // One array slot is reserved to distinguish full from empty, so the
  // usable capacity is allocated capacity minus one.
  explicit RingBuffer(std::size_t capacity)
      : buffer(capacity), readIndex(0), writeIndex(0) {
    if (capacity < 2) {
      throw std::invalid_argument(
          "RingBuffer needs at least two slots with one-slot-empty tracking");
    }
  }

  // Write at writeIndex. If full, that slot is the reserved empty slot:
  // advancing both indices replaces the oldest item and keeps the buffer full.
  void enqueue(int value) {
    buffer[writeIndex] = value;
    writeIndex = (writeIndex + 1) % buffer.size();
    //advance the read index if buffer is full, read index now points to the oldest element
    if (writeIndex == readIndex) {
      readIndex = (readIndex + 1) % buffer.size();
    }
  }

  // Removes the oldest item into value. Returns false if the buffer is empty.
  bool dequeue(int &value) {
    if (empty()) {
      return false;
    }

    value = buffer[readIndex];
    readIndex = (readIndex + 1) % buffer.size();
    return true;
  }

  bool empty() const {
    return readIndex == writeIndex;
  }

  bool full() const {
    return (writeIndex + 1) % buffer.size() == readIndex;
  }

  std::size_t size() const {
    if (writeIndex >= readIndex) {
      return writeIndex - readIndex;
    }
    return buffer.size() - readIndex + writeIndex;
  }

  // Print items in queue order, starting at the oldest item.
  void print() const {
    std::cout << "Buffer (oldest to newest): ";
    for (std::size_t index = readIndex; index != writeIndex;
         index = (index + 1) % buffer.size()) {
      std::cout << buffer[index] << ' ';
    }
    std::cout << '\n';
  }

private:
  std::vector<int> buffer;
  std::size_t readIndex;
  std::size_t writeIndex;
};

int main() {
  // Four physical slots provide three usable entries.
  RingBuffer buffer(4);

  buffer.enqueue(10);
  buffer.enqueue(20);
  buffer.enqueue(30);
  std::cout << "Full: " << (buffer.full() ? "yes" : "no")
            << ", size: " << buffer.size() << '\n';
  std::cout << "Enqueue 40 (overwrites oldest if full)\n";
  buffer.enqueue(40);
  buffer.print();

  int value = 0;
  if (buffer.dequeue(value)) {
    std::cout << "Dequeued: " << value << '\n';
  }

  std::cout << "Enqueue 50 after dequeue\n";
  buffer.enqueue(50);
  buffer.print();

  while (buffer.dequeue(value)) {
    std::cout << "Dequeued: " << value << '\n';
  }

  if (!buffer.dequeue(value)) {
    std::cout << "Cannot dequeue: buffer is empty\n";
  }

  return 0;
}
