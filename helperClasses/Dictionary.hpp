#ifndef DICT_H
#define DICT_H
#include <iostream>
#include "String/String.h"

template<typename K, typename V>
struct Pair {
    K first;
    V second;
};

template <typename K, typename V>
class Dictionary {
    Pair<K, V>* data;
    int size;
    int capacity;
    void resize();
    void free() {
        delete[] data;
    }
    void copyFrom(const Dictionary<K, V>& other);
public:
    Dictionary();
    Dictionary(const Dictionary<K, V>& other);
    Dictionary<K, V>& operator=(const Dictionary<K, V>& other);
    void add(const K& key, const V& value);
    bool remove(const K& key);
    const V& find(const K& key) const;
    const Pair<K, V>* getPairs() const;
    bool hasKey(const K& key) const;
    bool setValue(const K& key, const V& value);
    void print() const;
    int getSize() const;
    void clear();
    ~Dictionary();
};
template <typename K, typename V>
void Dictionary<K, V>::clear() {
    free();
    capacity = 4;
    data = new Pair<K, V>[capacity];
    size = 0;
}
template <typename K, typename V>
int Dictionary<K, V>::getSize() const {
    return size;
}
template <typename K, typename V>
bool Dictionary<K, V>::hasKey(const K& key) const {
    for(int i = 0; i < size; i++) {
        if(key == data[i].first)
            return true;
    }
    return false;
}
template <typename K, typename V>
bool Dictionary<K, V>::setValue(const K& key, const V& value) {
    for(int i = 0; i < size; i++) {
        if(key == data[i].first) {
            data[i].second = value;
            return true;
        }
    }
    add(key, value);
    return true;
}
template <typename K, typename V>
const Pair<K, V>* Dictionary<K, V>::getPairs() const {
    return data;
}
template <typename K, typename V>
Dictionary<K, V>::Dictionary() {
    capacity = 4;
    size = 0;
    data = new Pair<K, V>[capacity];
}
template <typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary<K, V>& other) {
    copyFrom(other);
}
template <typename K, typename V>
Dictionary<K, V>::~Dictionary() {
        free();
}
template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary<K, V>& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
}
template <typename K, typename V>
bool Dictionary<K, V>::remove(const K& key) {
    int removeIndex = -1;
    for(int i = 0; i < size; i++)
        if(key == data[i].first) {
            removeIndex = i;
            break;
        }
    if(removeIndex == -1) return false;
    for(int i = removeIndex; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}
template <typename K, typename V>
void Dictionary<K, V>::resize() {
    capacity *= 2;
    Pair<K, V>* ptr = new Pair<K, V>[capacity];
    for(int i = 0; i < size; i++)
        ptr[i] = data[i];
    free();
    data = ptr;
}
template <typename K, typename V>
void Dictionary<K, V>::copyFrom(const Dictionary<K, V>& other) {
    size = other.size;
    capacity = other.capacity;
    data = new Pair<K, V>[capacity];
    for(int i = 0; i < size; i++)
        data[i] = other.data[i];
}

template <typename K, typename V>
void Dictionary<K, V>::add(const K& key, const V& value) {
    if(hasKey(key))
        throw String("Key is already added in collection!");
    if(size == capacity)
        resize();
    int insertIndex = size;
    for(int i = 0; i < size; i++) {
        if(key < data[i].first) {
            insertIndex = i;
            break;
        }
    }
    for(int i = size; i > insertIndex; i--) {
        data[i] = data[i - 1];
    }
    data[insertIndex] = {key, value};
    size++;
}
template <typename K, typename V>
const V& Dictionary<K, V>::find(const K& key) const {
    for(int i = 0; i < size; i++)
        if(data[i].first == key)
            return data[i].second;
    throw String("No such key in dictionary!");
}
template <typename K, typename V>
void Dictionary<K, V>::print() const {
    for(int i = 0; i < size; i++) {
        std::cout << data[i].first << " " << data[i].second
        << std::endl;
    }
} 

#endif