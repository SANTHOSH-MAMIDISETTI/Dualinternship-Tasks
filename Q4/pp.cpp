/* 
  The following code computes the sum of the elements of a vector in parallel using threads .
  The array is initialized with consecutive integers starting with 0.
  The array size is 1,000,000.
  The program uses multiple threads to compute the sum.
  The program uses the chrono library to measure the execution time.
  The program uses a mutex to protect the shared sum.
  The program uses parallelism.

  Compile & Run : g++ pp.cpp -o pp
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
  int n_cores = std::thread::hardware_concurrency();
  cout << "n_cores: " << n_cores << endl;

  vector<int> array(1000000);
  for (int i = 0; i < array.size(); i++) {
    array[i] = i;
  }

  int sum = 0;
  std::vector<std::thread> threads;
  std::mutex sum_mutex;  // Create a mutex

  // Measure start time
  auto start = high_resolution_clock::now();

  for (int i = 0; i < n_cores; i++) {
    threads.push_back(std::thread([&]() {
      int partial_sum = 0;  // Partial sum for each thread
      for (int j = i; j < array.size(); j += n_cores) {
        partial_sum += array[j];
      }

      std::lock_guard<std::mutex> lock(sum_mutex);  // Lock the mutex
      sum += partial_sum;  // Update the shared sum
      
      // Print partial sum calculated by each thread
      std::cout << "Thread " << std::this_thread::get_id() << " calculated partial sum "<< endl;
    }));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  // Measure end time
  auto end = high_resolution_clock::now();

  // Compute the duration in milliseconds
  auto duration = duration_cast<milliseconds>(end - start).count();

  // Print the sum
  cout << "The sum is " << sum << endl;

  // Print the vector elements
//   std::cout << "The elements of the vector are: ";
//   for (int i = 0; i < array.size(); i++) {
//     std::cout << array[i] << " ";
//   }
  cout << endl;

  // Print the execution time
  cout << "Execution time: " << duration << " milliseconds" << std::endl;

  return 0;
}
