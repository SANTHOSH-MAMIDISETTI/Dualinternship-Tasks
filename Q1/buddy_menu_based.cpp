#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BuddyAllocator {
public:
  BuddyAllocator(size_t size) : size_(size) 
  {
    free_list_.push_back(size_);
  }
  

  void* allocate(size_t size) 
  {
    for (auto block : free_list_) 
    {
      if (block >= size) 
      {
        if (block > size) 
        {
          free_list_.push_back(block - size);
        }
        free_list_.erase(find(free_list_.begin(), free_list_.end(), block));
        cout << "Allocating block of size " << size << endl;
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
        // Return the pointer to the allocated memory block as-is
        // return array;

      }
    }
    cout << "Not enough memory" << endl;
    return nullptr;
  }

  
  void deallocate(void* ptr) 
  {
    free_list_.push_back(reinterpret_cast<size_t>(ptr));
    cout << "Deallocating block at address " << ptr << endl;
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
private:
  size_t size_;
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
    cout << "5. Exit" << endl;
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
        return 0;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  }
}
