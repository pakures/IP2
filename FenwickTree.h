/*
FenwickTree - Binary Indexed Tree

Supports:
- add(index, delta)
- set(index, value)
- get(index)
- remove(index)
- prefixSum(index)
- rangeSum(l, r)

Operators:
+= insert
-= remove
*= update
[] access
! clear

Comparison operators:
== != < <= > >=

Implementation:
- uses dynamic memory (RAII)
- deep copy supported
- Pimpl idiom used

Exceptions:
- out_of_range
- invalid_argument
- AlreadyZeroException
*/

#ifndef FENWICKTREE_H
#define FENWICKTREE_H

#include <string>
#include <stdexcept>

namespace ip2
{
    struct Entry
    {
        int index;
        int value;
    };

    // Custom exception
    class AlreadyZeroException : public std::logic_error
    {
    public:
        AlreadyZeroException(const std::string& message);
    };

    class FenwickTree
    {
    private:
        class Impl;      // forward declaration
        Impl* pImpl;     // pointer į implementaciją

    public:
        // Constructor
        FenwickTree(int size);

        // Copy constructor (deep copy)
        FenwickTree(const FenwickTree& other);

        // Assignment operator (deep copy)
        FenwickTree& operator=(const FenwickTree& other);

        // Destructor
        ~FenwickTree();

        // CRUD
        void add(int index, int delta);
        int get(int index) const;
        void set(int index, int value);
        void remove(int index);

        // Fenwick funkcijos
        int prefixSum(int index) const;
        int rangeSum(int left, int right) const;

        // Output
        std::string toString() const;

        // Operatoriai
        FenwickTree& operator+=(const Entry& e); // add
        FenwickTree& operator-=(int index);      // delete
        FenwickTree& operator*=(const Entry& e); // update

        int operator[](int index) const; // read

        void operator!(); // clear

        // Comparison
        bool operator==(const FenwickTree& other) const;
        bool operator!=(const FenwickTree& other) const;
        bool operator<(const FenwickTree& other) const;
        bool operator<=(const FenwickTree& other) const;
        bool operator>(const FenwickTree& other) const;
        bool operator>=(const FenwickTree& other) const;
    };
}

#endif
