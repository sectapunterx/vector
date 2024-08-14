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
        int size; /// Number of elements in the vector
        int capacity; /// Allocated storage capacity of the vector
        T* data; /// Pointer to the allocated storage
        std::allocator<T> allocator; /// Allocator for managing memory

      /**
       * @brief Resizes the vector to a new capacity.
       *
       * If the current capacity is exceeded, reallocates storage with the new capacity.
       *
       * @param new_capacity The new capacity of the vector.
       */
        void recap(int new_capacity);
    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the vector with size and capacity set to 0, and data set to nullptr.
         */
        vector();

        /**
         * @brief Constructor with size and value.
         *
         * Initializes the vector with a given size and fills it with the specified value.
         *
         * @param size The number of elements to initialize.
         * @param value The value to initialize each element with.
         */
        vector(int size, T value);

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
         * @brief Destructor.
         *
         * Destroys the vector and deallocates its memory.
         */
        ~vector();

        //TODO: vector<bool>, bit_reference, iterator(?)
    };

} // namespace my_vector

#endif //VECTOR_VECTOR_H