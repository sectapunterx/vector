//
// Created by Fin on 13.08.2024.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <memory>

namespace my_vector {

/**
 * @brief A templated vector class.
 *
 * This class provides a dynamic array implementation using templates.
 *
 * @tparam T The type of elements stored in the vector.
 */
    template<typename T>
    class vector {

        class iterator {
            T* ptr;
        public:
            explicit iterator(T* ptr) : ptr(ptr) {}
            iterator& operator++() { ++ptr; return *this; }
            iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }
            T& operator*() { return *ptr; }
            T* operator->() { return ptr; }
            bool operator==(const iterator& other) const { return ptr == other.ptr; }
            bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        };

        iterator begin() { return iterator(data_); }
        iterator end() { return iterator(data_ + size_); }
        iterator cbegin() const { return iterator(data_); }
        iterator cend() const { return iterator(data_ + size_); }

        size_t size_; /// Number of elements in the vector
        size_t capacity_; /// Allocated storage capacity_ of the vector
        T* data_; /// Pointer to the allocated storage
        std::allocator<T> allocator; /// Allocator for managing memory

      /**
       * @brief Resizes the vector to a new capacity_.
       *
       * If the current capacity_ is exceeded, reallocates storage with the new capacity_.
       *
       * @param new_capacity The new capacity_ of the vector.
       */
        void reserve(size_t new_capacity);

      /**
       * @brief Checks if the vector is empty.
       *
       * @return True if the vector is empty, false otherwise.
       */
        bool is_empty() noexcept;
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the vector with size_ and capacity_ set to 0, and data_ set to nullptr.
         */
        vector();

        /**
         * @brief Constructor with size_ and value.
         *
         * Initializes the vector with a given size_ and fills it with the specified value.
         *
         * @param size The number of elements to initialize.
         * @param value The value to initialize each element with.
         */
        vector(size_t size, T value);

        /**
         * @brief Copy constructor.
         *
         * Creates a copy of the given vector.
         *
         * @param other The vector to copy from.
         */
        vector(const vector<T>& other);

        /**
         * @brief Copy assignment operator.
         *
         * Assigns the contents of one vector to another.
         *
         * @param other The vector to copy from.
         * @return A reference to the assigned vector.
         */
        vector<T>& operator=(const vector<T>& other);

        /**
         * @brief Move constructor.
         *
         * Moves the contents of the given vector to a new vector.
         *
         * @param other The vector to move from.
         */
        vector(vector<T>&& other) noexcept;

        /**
         * @brief Move assignment operator.
         *
         * Moves the contents of one vector to another.
         *
         * @param other The vector to move from.
         * @return A reference to the assigned vector.
         */
        vector<T>& operator=(vector<T>&& other) noexcept;

        /**
         * @brief Accesses the element at the specified position.
         *
         * @param index The position of the element to access.
         * @return A reference to the element at the specified position.
         */
        constexpr T& operator[] (size_t index) const;

        /**
         * @brief Destructor.
         *
         * Destroys the vector and deallocates its memory.
         */
        ~vector();

        /**
         * @brief Adds an element to the end of the vector.
         *
         * @param value The value to add.
         */
        void push_back(const T& value);

        /**
         * @brief Adds an element to the end of the vector using move semantics.
         *
         * @param value The value to add.
         */
        void push_back(T&& value);

        /**
         * @brief Adds an element to the front of the vector.
         *
         * @param value The value to add.
         */
        void push_front(const T& value);

        /**
         * @brief Adds an element to the front of the vector using move semantics.
         *
         * @param value The value to add.
         */
        void push_front(T&& value);

        /**
         * @brief Clears the contents of the vector.
         *
         * Sets the size_ to 0 but does not deallocate the memory.
         */
        void constexpr clear() noexcept;

        /**
         * @brief Swaps the contents of this vector with another vector.
         *
         * @param other The vector to swap with.
         */
        void swap(vector& other) noexcept;

        /**
         * @brief Returns the number of elements in the vector.
         *
         * @return The number of elements in the vector.
         */
        size_t size() const noexcept;

        /**
         * @brief Returns the capacity_ of the vector.
         *
         * @return The capacity_ of the vector.
         */
        size_t capacity() const noexcept;

        /**
         * @brief Accesses the element at the specified position.
         *
         * @param index The position of the element to access.
         * @return A reference to the element at the specified position.
         * @throws std::out_of_range if the index is out of range.
         */
        T& at(size_t index);

        /**
         * @brief Accesses the element at the specified position (const version).
         *
         * @param index The position of the element to access.
         * @return A const reference to the element at the specified position.
         * @throws std::out_of_range if the index is out of range.
         */
        const T& at(size_t index) const;

        /**
         * @brief Accesses the first element.
         *
         * @return A reference to the first element.
         * @throws std::out_of_range if the vector is empty.
         */
        T& front();

        /**
         * @brief Accesses the first element (const version).
         *
         * @return A const reference to the first element.
         * @throws std::out_of_range if the vector is empty.
         */
        const T& front() const;

        /**
         * @brief Accesses the last element.
         *
         * @return A reference to the last element.
         * @throws std::out_of_range if the vector is empty.
         */
        T& back();

        /**
         * @brief Accesses the last element (const version).
         *
         * @return A const reference to the last element.
         * @throws std::out_of_range if the vector is empty.
         */
        const T& back() const;

        /**
         * @brief Removes the last element of the vector.
         *
         * @throws std::out_of_range if the vector is empty.
         */
        void pop_back();

        /**
         * @brief Removes the first element of the vector.
         *
         * @throws std::out_of_range if the vector is empty.
         */
        void pop_front();

        /**
         * @brief Resizes the vector to contain the specified number of elements.
         *
         * If the new size_ is greater than the current size_, new elements are default-initialized.
         * If the new size_ is less than the current size_, elements are destroyed.
         *
         * @param new_size The new size_ of the vector.
         */
        void resize(size_t new_size);

        /**
         * @brief Resizes the vector to contain the specified number of elements, initializing new elements with the specified value.
         *
         * If the new size_ is greater than the current size_, new elements are initialized with the specified value.
         * If the new size_ is less than the current size_, elements are destroyed.
         *
         * @param new_size The new size_ of the vector.
         * @param value The value to initialize new elements with.
         */
        void resize(size_t new_size, const T& value);

        /**
         * @brief Shrinks the capacity_ of the vector to fit its size_.
         */
        void shrink_to_fit();

        /**
         * @brief Returns a pointer to the underlying array.
         *
         * @return A pointer to the underlying array.
         */
        T* data() noexcept;

        /**
         * @brief Returns a const pointer to the underlying array.
         *
         * @return A const pointer to the underlying array.
         */
        const T* data() const noexcept;



        //TODO: vector<bool>, bit_reference, iterator(?)
    };

} // namespace my_vector

#endif //VECTOR_VECTOR_H