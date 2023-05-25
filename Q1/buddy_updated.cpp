#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BuddyAllocator {
public:
  BuddyAllocator(size_t size) : size_(size), max_block_size_(size) 
  {
    free_list_.push_back(size_);
  }
  

  void* allocate(size_t size) 
  {
    if (size > size_)
    {
      cout << "Requested size is larger than the available memory." << endl;
      return nullptr;
    }
      
    for (auto block : free_list_) 
    {
      if (block >= size) 
      {
        if (block > size) 
        {
          free_list_.push_back(block - size);
          max_block_size_ = max(max_block_size_, block - size);
        }
        free_list_.erase(find(free_list_.begin(), free_list_.end(), block));
        cout << "Allocating block of size " << size << " from address " << block << endl;
        int* array = new int[size / sizeof(int)];
        int sum = 0;
        for (int i = 0; i < size / sizeof(int); i++) 
        {
          array[i] = i + 1;
          sum += array[i];
        }
        cout << "Numbers in the allocated array: ";
        for (int i = 0; i < size / sizeof(int); i++) 
        {
          cout << array[i] << " ";
        }
        cout << endl;
        cout << "Sum of numbers in the allocated array: " << sum << endl;
        return reinterpret_cast<void*>(array);
      }
    }
    cout << "Not enough memory" << endl;
    return nullptr;
  }

  
  void deallocate(void* ptr) 
  {
    size_t block_address = reinterpret_cast<size_t>(ptr);
    free_list_.push_back(block_address);
    cout << "Deallocating block at address " << block_address << endl;
    int* array = reinterpret_cast<int*>(ptr);
    delete[] array;
  }
  
  void printFreeList() 
  {
    cout << "Free List: ";
    for (auto block : free_list_) 
    {
      cout << block << " ";
    }
    cout << endl;
  }
  
  size_t getMaxBlockSize() const 
  {
    return max_block_size_;
  }

private:
  size_t size_;
  size_t max_block_size_;
  vector<size_t> free_list_;
};


int main() 
{
  BuddyAllocator allocator(1024);
  int choice;
  size_t size;
  void* ptr = nullptr;
  while (true) 
  {
    cout << "--------------------------------" << endl;
    cout << "1. Allocate memory" << endl;
    cout << "2. Deallocate memory" << endl;
    cout << "3. Allocate and Deallocate memory" << endl;
    cout << "4. Print Free List" << endl;
    cout << "5. Query Maximum Block Size" << endl;
    cout << "6. Exit" << endl;
    cout << "--------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) 
    {
      case 1:
        if (ptr != nullptr) 
        {
          cout << "Memory is already allocated. Deallocate it first." << endl;
          break;
        }
        cout << "Enter the size of the block to allocate: ";
        cin >> size;
        ptr = allocator.allocate(size);
        if (ptr != nullptr) 
        {
          cout << "Block allocated successfully." << endl;
        }
        break;
      case 2:
        if (ptr != nullptr) 
        {
          allocator.deallocate(ptr);
          ptr = nullptr;
          cout << "Block deallocated successfully." << endl;
        } 
        else 
        {
          cout << "No block is currently allocated." << endl;
        }
        break;
      case 3:
        if (ptr != nullptr) 
        {
          allocator.deallocate(ptr);
          cout << "Block deallocated successfully." << endl;
          ptr = nullptr;
        }
        cout << "Enter the size of the block to allocate: ";
        cin >> size;
        ptr = allocator.allocate(size);
        if (ptr != nullptr) 
        {
          cout << "Block allocated successfully." << endl;
        }
        break;
      case 4:
        allocator.printFreeList();
        break;
      case 5:
        cout << "Maximum block size that can be allocated: " << allocator.getMaxBlockSize() << endl;
        break;
      case 6:
        return 0;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  }
}
