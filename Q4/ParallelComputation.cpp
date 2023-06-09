// #include <iostream>
// #include <thread>
// #include <vector>

// using namespace std;

// int main() {
//   // Get the number of cores available on the system.
//   int n_cores = std::thread::hardware_concurrency();
// cout << "n_cores: " << n_cores << endl;
//   // Create a vector to store the array elements.
//   vector<int> array(1000000);

//   // Initialize the array elements.
//   for (int i = 0; i < array.size(); i++) {
//     array[i] = i;
//   }

//   // Compute the sum of the array elements in parallel.
//   int sum = 0;
//   std::vector<std::thread> threads;
//   for (int i = 0; i < n_cores; i++) {
//     threads.push_back(std::thread([&]() {
//       for (int j = i; j < array.size(); j += n_cores) {
//         sum += array[j];
//       }
//     }));
//   }

//   for (auto& thread : threads) {
//     thread.join();
//   }

//   // Print the sum.
//   std::cout << "The sum is " << sum << std::endl;

//   return 0;
// }

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

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

  for (int i = 0; i < n_cores; i++) {
    threads.push_back(std::thread([&]() {
      int partial_sum = 0;  // Partial sum for each thread
      for (int j = i; j < array.size(); j += n_cores) {
        partial_sum += array[j];
      }

      std::lock_guard<std::mutex> lock(sum_mutex);  // Lock the mutex
      sum += partial_sum;  // Update the shared sum
    }));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  std::cout << "The sum is " << sum << std::endl;

  return 0;
}
