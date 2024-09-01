//
// Created by Fin on 13.08.2024.
//

#include <algorithm>
#include <stdexcept>

namespace my_vector {

    template<typename T>
    vector<T>::vector() : size_(0), capacity_(0), data_(nullptr) {
    }

    template<typename T>
    vector<T>::vector(size_t size, T value) : size_(size), capacity_(size), data_(allocator.allocate(size)){
      for (int i = 0; i < size; i++) {
        allocator.construct(&this->data_[i], value);
      }
    }

    template<typename T>
    vector<T>::vector(const vector<T>& other) : size_(other.size_), capacity_(other.capacity_), data_(allocator.allocate(other.capacity_)) {
      for (int i = 0; i < other.size_; ++i) {
        allocator.construct(&this->data_[i], other.data_[i]);
      }
    }

    template<typename T>
    vector<T>& vector<T>::operator=(const vector<T>& other) {
      if (this != &other) {
        for (int i = 0; i < size_; ++i) {
          allocator.destroy(&data_[i]);
        }
        allocator.deallocate(data_, capacity_);

        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = allocator.allocate(other.capacity_);
        for (int i = 0; i < other.size_; ++i) {
          allocator.construct(&this->data_[i], other.data_[i]);
        }
      }
      return *this;
    }

    template<typename T>
    const T& vector<T>::operator[] (size_t index) const {
      return data_[index];
    }

    template<typename T>
    vector<T>::vector(vector<T>&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
      other.size_ = 0;
      other.capacity_ = 0;
      other.data_ = nullptr;
    }

    template<typename T>
    vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
      if(this != &other){
        for(int i = 0; i < size_; ++i){
          allocator.destroy(&data_[i]);
        }
        allocator.deallocate(data_, capacity_);

        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->data_ = other.data_;
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
      }
      return *this;
    }

    template<typename T>
    vector<T>::~vector() {
      for (int i = 0; i < size_; ++i) {
        allocator.destroy(&data_[i]);
      }
      allocator.deallocate(data_, capacity_);
    }

    template<typename T>
    bool vector<T>::is_empty() noexcept {
      return size_ == 0;
    }

    template<typename T>
    void vector<T>::reserve(size_t new_capacity) {
      if(new_capacity > capacity_){
        T* new_data = allocator.allocate(new_capacity);
        for(int i = 0; i < size_; ++i){
          allocator.construct(&new_data[i], std::move(data_[i]));
          allocator.destroy(&data_[i]);
        }
        allocator.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
      }
    }

    template<typename T>
    void vector<T>::push_back(const T& value) {
      if(size_ == capacity_){
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      allocator.construct(&data_[size_++], value);
    }

    template<typename T>
    void vector<T>::push_back(T&& value) {
      if(size_ == capacity_){
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      allocator.construct(&data_[size_++], std::move(value));
    }

    template<typename T>
    void vector<T>::push_front(const T& value) {
      if(size_ == capacity_){
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      for(int i = size_; i > 0; --i){
        data_[i] = std::move(data_[i - 1]);
      }
      allocator.construct(&data_[0], value);
      size_++;
    }

    template<typename T>
    void vector<T>::push_front(T&& value) {
      if(size_ == capacity_){
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      for(int i = size_; i > 0; --i){
        data_[i] = std::move(data_[i - 1]);
      }
      allocator.construct(&data_[0], std::move(value));
      size_++;
    }

    template<typename T>
    void constexpr vector<T>::clear() noexcept {
      for(int i = 0; i < size_; ++i){
        allocator.destroy(&data_[i]);
      }
      size_ = 0;
      shrink_to_fit();
    }

    template<typename T>
    void vector<T>::swap(vector& other) noexcept {
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
      std::swap(data_, other.data_);
    }

    template<typename T>
    T& vector<T>::at(size_t index) {
      if (index >= size_) {
        throw std::out_of_range("Index out of range");
      }
      return data_[index];
    }

    template<typename T>
    const T& vector<T>::at(size_t index) const {
      if (index >= size_) {
        throw std::out_of_range("Index out of range");
      }
      return data_[index];
    }

    template<typename T>
    T& vector<T>::front() {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      return data_[0];
    }

    template<typename T>
    const T& vector<T>::front() const {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      return data_[0];
    }

    template<typename T>
    T& vector<T>::back() {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      return data_[size_ - 1];
    }

    template<typename T>
    const T& vector<T>::back() const {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      return data_[size_ - 1];
    }

    template<typename T>
    void vector<T>::pop_back() {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      allocator.destroy(&data_[--size_]);
    }

    template<typename T>
    void vector<T>::pop_front() {
      if (is_empty()) {
        throw std::out_of_range("Vector is empty");
      }
      allocator.destroy(&data_[0]);
      for (size_t i = 1; i < size_; ++i) {
        data_[i - 1] = std::move(data_[i]);
      }
      --size_;
    }

    template<typename T>
    void vector<T>::resize(size_t new_size) {
      if (new_size > capacity_) {
        reserve(new_size);
      }
      for (size_t i = size_; i < new_size; ++i) {
        allocator.construct(&data_[i]);
      }
      for (size_t i = new_size; i < size_; ++i) {
        allocator.destroy(&data_[i]);
      }
      size_ = new_size;
    }

    template<typename T>
    void vector<T>::resize(size_t new_size, const T& value) {
      if (new_size > capacity_) {
        reserve(new_size);
      }
      for (size_t i = size_; i < new_size; ++i) {
        allocator.construct(&data_[i], value);
      }
      for (size_t i = new_size; i < size_; ++i) {
        allocator.destroy(&data_[i]);
      }
      size_ = new_size;
    }

    template<typename T>
    void vector<T>::shrink_to_fit() {
      if (size_ < capacity_) {
        T* new_data = allocator.allocate(size_);
        for (size_t i = 0; i < size_; ++i) {
          allocator.construct(&new_data[i], std::move(data_[i]));
          allocator.destroy(&data_[i]);
        }
        allocator.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = size_;
      }
    }

    template<typename T>
    void vector<T>::trim_to_size() {
      if (capacity_ > size_) {
        shrink_to_fit();
      }
    }

    template<typename T>
    void vector<T>::ensure_capacity(size_t min_capacity) {
      if (capacity_ < min_capacity) {
        reserve(min_capacity);
      }
    }

    template<typename T>
    size_t vector<T>::size() const noexcept {
      return size_;
    }

    template<typename T>
    size_t vector<T>::capacity() const noexcept {
      return capacity_;
    }

    template<typename T>
    T* vector<T>::data() noexcept {
      return data_;
    }

    template<typename T>
    const T* vector<T>::data() const noexcept {
      return data_;
    }

} //namespace my_vector
