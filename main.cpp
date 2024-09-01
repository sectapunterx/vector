#include "vector.h"
#include <iostream>

int main() {
  my_vector::vector<int> vec;

  // Add elements to the vector
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  // Display the elements
  std::cout << "Vector elements after push_back: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  // Add elements to the front
  vec.push_front(5);
  vec.push_front(1);

  // Display the elements
  std::cout << "Vector elements after push_front: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  // Remove the last element
  vec.pop_back();

  // Display the elements
  std::cout << "Vector elements after pop_back: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  // Remove the first element
  vec.pop_front();

  // Display the elements
  std::cout << "Vector elements after pop_front: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  // Resize the vector
  vec.resize(10, 100);

  // Display the elements
  std::cout << "Vector elements after resize: ";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;

  // Shrink the vector to fit its size
  vec.shrink_to_fit();

  // Display the capacity
  std::cout << "Vector capacity after shrink_to_fit: " << vec.capacity() << std::endl;

  // Ensure the vector has at least a certain capacity
  vec.ensure_capacity(20);

  // Display the capacity
  std::cout << "Vector capacity after ensure_capacity: " << vec.capacity() << std::endl;

  // Trim the vector to its size
  vec.trim_to_size();

  // Display the capacity
  std::cout << "Vector capacity after trim_to_size: " << vec.capacity() << std::endl;

  return 0;

}