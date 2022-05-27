#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

template <typename T>
class Deque {
    T** data;
    int size;
    int capacity;
    int get;
    int put;
    void free();
    void copyFrom(const Deque&);
    void resize();
public:
    Deque();
    Deque(const Deque<T>&);
    Deque<T>& operator=(const Deque<T>&);
    bool add(const T&);
    T pop_front();
    T pop_back();
    T peek_front() const;
    T peek_back() const;
    bool isEmpty() const;
    ~Deque();
};

template <typename T>
void Deque<T>::free() {
    for(int i = get; i % capacity != put; i++) 
        delete data[i];
    delete[] data;
}
template <typename T>
void Deque<T>::copyFrom(const Deque<T>& deque) {
    data = new T*[deque.capacity];
    capacity = deque.capacity;
    size = deque.size;
    get = deque.get;
    put = deque.put;
    for(int i = get; i % capacity !=  put; i++) {
        data[i % capacity] = new T(deque.data[i % capacity]);
    }
}
template <typename T>
void Deque<T>::resize() {
    T** tmp = new T*[capacity * 2];
    for(int i = 0; i < size; i++) {
        tmp[i] = new T(*data[(get + i) % capacity]);
    }
    capacity *= 2;
    free();
    data = tmp;
    get = 0;
    put = size;
}
template <typename T>
Deque<T>::Deque() {
    capacity = 4;
    data = new T*[capacity];
    size = 0;
    put = 0;
    get = 0;
}
template <typename T>
Deque<T>::Deque(const Deque<T>& deque) {
    copyFrom(deque);
}
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& deque) {
    if(this != &deque) {
        free();
        copyFrom(deque);
    }
    return *this;
}
template <typename T>
bool Deque<T>::add(const T& el) {
    if(capacity == size)
        resize();
    data[put] = new T(el);
    put++;
    put %= capacity;
    size++;
    return true;
}
template <typename T>
T Deque<T>::pop_front() {
    if(isEmpty()) throw 404;
    T result = *data[get];
    get++;
    get %= capacity;
    size--;
    return result;
}
template <typename T>
T Deque<T>::pop_back() {
    if(isEmpty()) throw 404;
    T result = *data[(put - 1 + capacity) % capacity];
    (--put += capacity) %= capacity;
    size--;
    return result;
}
template <typename T>
T Deque<T>::peek_front() const {
    return *data[get];
}
template <typename T>
T Deque<T>::peek_back() const {
    if(isEmpty()) throw 404;
    return *data[(put - 1 + capacity) % capacity];
}
template <typename T>
bool Deque<T>::isEmpty() const {
    return size == 0;
}
template <typename T>
Deque<T>::~Deque() {
    free();
}
#endif