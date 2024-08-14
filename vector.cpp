//
// Created by Fin on 13.08.2024.
//

#include "vector.h"
#include <algorithm>

namespace my_vector {

    template<typename T>
    vector<T>::vector() : size(0), capacity(0), data(nullptr) {
    }

    template<typename T>
    vector<T>::vector(int size, T value) : size(size), capacity(size), data(allocator.allocate(size)){
      for (int i = 0; i < size; i++) {
        allocator.construct(&this->data[i], value);
      }
    }

    template<typename T>
    vector<T>::vector(const vector<T>& other) : size(other.size), capacity(other.capacity), data(allocator.allocate(other.capacity)) {
      for (int i = 0; i < other.size; ++i) {
        allocator.construct(&this->data[i], other.data[i]);
      }
    }

    template<typename T>
    vector<T>& vector<T>::operator=(const vector<T>& other) {
      if (this != &other) {
        for (int i = 0; i < size; ++i) {
          allocator.destroy(&data[i]);
        }
        allocator.deallocate(data, capacity);

        this->size = other.size;
        this->capacity = other.capacity;
        this->data = allocator.allocate(other.capacity);
        for (int i = 0; i < other.size; ++i) {
          allocator.construct(&this->data[i], other.data[i]);
        }
      }
      return *this;
    }

    template<typename T>
    vector<T>::vector(vector<T>&& other) noexcept : size(other.size), capacity(other.capacity), data(other.data) {
      other.size = 0;
      other.capacity = 0;
      other.data = nullptr;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
      if(this != &other){
        for(int i = 0; i < size; ++i){
          allocator.destroy(&data[i]);
        }
        allocator.deallocate(data, capacity);

        this->size = other.size;
        this->capacity = other.capacity;
        this->data = other.data;
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
      }
      return *this;
    }

    template<typename T>
    vector<T>::~vector() {
      for (int i = 0; i < size; ++i) {
        allocator.destroy(&data[i]);
      }
      allocator.deallocate(data, capacity);
    }

    template<typename T>
    void vector<T>::recap(int new_capacity) {
      if(new_capacity > capacity){
        T* new_data = allocator.allocate(new_capacity);
        for(int i = 0; i < size; ++i){
          allocator.construct(&new_data[i], std::move(data[i]));
          allocator.deallocate(&data[i]);
        }
        allocator.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
      }
    }

} //namespace my_vector
