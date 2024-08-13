//
// Created by Fin on 13.08.2024.
//

#include "vector.h"


template<typename T>
vector<T>::vector() {
    size = 0;
    capacity = 0;
    data = nullptr;
}


template<typename T>
vector<T>::vector(int size, T value) {
  this->size = size;
  this->capacity = size;
  this->data = allocator.allocate(size);
  for (int i = 0; i < size; i++) {
    allocator.construct(&this->data[i], value);
  }
}


template<typename T>
vector<T>::vector(const vector<T>& other) {
  this->size = other.size;
  this->capacity = other.capacity;
  this->data = allocator.allocate(other.capacity);
  for(int i = 0; i < other.size; ++i){
    allocator.construct(&this->data[i], other.data[i]);
  }
}
