#ifndef STRING_HEADER
#define STRING_HEADER
#include <fstream>
#include <cstring>
#include "../ArrayList.hpp"

class String {
    char* str;
    int length;
    int capacity;
    void copyFrom(const String&);
    void free();
    void resize();
public:
    String(); //
    String(const char*); //
    String(const String&);
    String(int n);
    String& operator =(const String&); //
    char charAt(int) const; //
    int compareTo(const String&) const; //
    String concat(const String&) const; //
    ArrayList<String> split(const String&) const;
    String operator +(const String&); //
    void operator +=(const String&); //
    void operator +=(char c);
    friend std::ostream& operator <<(std::ostream&, const String&); //
    friend std::istream& operator >>(std::istream&, String&); //
    bool contains(const String&) const; //
    bool equals(const String&) const; //
    int indexOf(const String&) const; //
    bool endsWith(const String&) const;
    bool isEmpty() const; //
    int getLength() const; //
    bool startsWith(const String&) const; //
    String substring(int, int endIndex = -1) const;
    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    bool operator<(const String&) const;
    bool operator>(const String&) const;
    bool operator<=(const String&) const;
    bool operator>=(const String&) const;
    String toUpperCase() const; //
    String toLowerCase() const; //
    String trim() const; //
    const char* toString() const; //
    ~String();
};

#endif