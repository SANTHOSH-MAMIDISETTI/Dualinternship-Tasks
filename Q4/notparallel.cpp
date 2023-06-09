/* 
  * This program computes the sum of the elements of an array.
  * The array is initialized with consecutive integers starting with 0.
  * The array size is 1,000,000.
  * The program uses a for loop to compute the sum.
  * The program uses the chrono library to measure the execution time.
  * The program does not use parallelism.
  * 
  * Compile & Run : g++ notparallel.cpp -o notparallel
  *
*/
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
  vector<int> array(1000000);
  for (int i = 0; i < array.size(); i++) {
    array[i] = i;
  }

  // Measure start time
  auto start = high_resolution_clock::now();

  int sum = 0;
  for (int i = 0; i < array.size(); i++) {
    sum += array[i];
  }

  // Measure end time
  auto end = high_resolution_clock::now();

  // Compute the duration in milliseconds
  auto duration = duration_cast<milliseconds>(end - start).count();

  // Print the sum
  std::cout << "The sum is " << sum << std::endl;

  // Print the vector elements
  // std::cout << "The elements of the vector are: ";
  // for (int i = 0; i < array.size(); i++) {
  //   std::cout << array[i] << " ";
  // }
  // std::cout << std::endl;

  // Print the execution time
  std::cout << "Execution time: " << duration << " milliseconds" << std::endl;

  return 0;
}
