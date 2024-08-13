//
// Created by Fin on 13.08.2024.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

template<typename T>
class vector {
    vector();
    vector(int size, T value);
    vector(const vector<T>& other);
    T& operator=(const vector<T>& other);
    vector(const vector<T>&& other);
    T& operator=(const vector<T>&& other);
    ~vector();



};


#endif //VECTOR_VECTOR_H
