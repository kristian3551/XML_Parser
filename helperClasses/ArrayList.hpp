#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <iostream>

const int INITIAL_CAPACITY = 4;

template <typename T>
class ArrayList {
protected:
    T** data;
    int size;
    size_t capacity;
    void resize();
    void copyFrom(const ArrayList<T>&);
    void free();
public:
    ArrayList();
    ArrayList(const ArrayList<T>&);
    ArrayList<T>& operator=(const ArrayList<T>&);
    bool push(const T&);
    bool push(T&&);
    bool remove(const T&);
    bool removeByIndex(int);
    bool find(const T&) const;
    int indexOf(const T&) const;
    T& operator[](int);
    const T& operator[](int) const;
    ArrayList<T>& operator+=(const ArrayList<T>&);
    ArrayList<T>& operator+=(const T& el);
    int getSize() const;
    bool isEmpty() const;
    void clear();
    ~ArrayList();
};

template <typename T>
void ArrayList<T>::resize() {
    capacity *= 2;
    T** ptr = new T*[capacity];
    for(int i = 0; i < size; i++) {
        ptr[i] = new T(*data[i]);
    }
    free();
    data = ptr;
}
template <typename T>
void ArrayList<T>::copyFrom(const ArrayList<T>& other) {
    capacity = other.capacity;
    size = other.size;
    data = new T*[capacity];
    for(int i = 0; i < size; i++) {
        data[i] = new T(*(other.data[i]));
    }
}
template <typename T>
void ArrayList<T>::free() {
    for(int i = 0; i < size; i++)
        delete data[i];
    delete[] data;
}
template <typename T>
ArrayList<T>::ArrayList() {
    capacity = INITIAL_CAPACITY;
    data = new T*[capacity];
    size = 0;
}
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    copyFrom(other);
}
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
template <typename T>
bool ArrayList<T>::push(const T& el) {
    if(size == capacity)
        resize();
    data[size++] = new T(el);
    return true;
}
template <typename T>
bool ArrayList<T>::push(T&& el) {
    if(size == capacity)
        resize();
    data[size++] = new T(el);
    return true;
}
template <typename T>
bool ArrayList<T>::remove(const T& el) {
    int elIndex = indexOf(el);
    if(elIndex == -1) return false;
    for(int i = elIndex; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return true;
}
template <typename T>
bool ArrayList<T>::removeByIndex(int index) {
    if(index < 0 || index >= size)
        return false;
    for(int i = index; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return true;
}
template <typename T>
int ArrayList<T>::indexOf(const T& el) const {
    for(int i = 0; i < size; i++)
        if(el == *data[i]) 
            return i;
    return -1;
}
template <typename T>
bool ArrayList<T>::find(const T& el) const {
    return indexOf(el) != -1;
}
template <typename T>
T& ArrayList<T>::operator[](int index) {
    if(index < 0 || index >= size)
        throw 0;
    return *data[index];
}
template <typename T>
const T& ArrayList<T>::operator[](int index) const {
    if(index < 0 || index >= size)
        throw 0;
    return *data[index];
}
template <typename T>
ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T>& other) {
    for(int i = 0; i < other.size; i++) {
        push(*other.data[i]);
    }
    return *this;
}
template <typename T>
ArrayList<T>& ArrayList<T>::operator+=(const T& el) {
    push(el);
    return *this;
}
template <typename T>
int ArrayList<T>::getSize() const {
    return size;
}
template <typename T>
bool ArrayList<T>::isEmpty() const {
    return size == 0;
}
template <typename T>
void ArrayList<T>::clear() {
    free();
    capacity = INITIAL_CAPACITY;
    data = new T*[capacity];
    size = 0;
}
template <typename T>
ArrayList<T>::~ArrayList() {
    free();
}

#endif