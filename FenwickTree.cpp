#include <iostream>
#include <sstream>
#include "FenwickTree.h"

using namespace std;

namespace ip2
{
    AlreadyZeroException::AlreadyZeroException(const string& message)
        : logic_error(message)
    {
    }

    class FenwickTree::Impl
    {
    public:
        int size;
        int* tree;
        int* values;

        Impl(int n)
        {
            size = n;
            tree = new int[n + 1]();   // 1-based, viskas = 0
            values = new int[n + 1](); // tikros reiksmes
        }

        Impl(const Impl& other)
        {
            size = other.size;

            tree = new int[size + 1];
            values = new int[size + 1];

            for (int i = 0; i <= size; i++)
            {
                tree[i] = other.tree[i];
                values[i] = other.values[i];
            }
        }

        ~Impl()
        {
            delete[] tree;
            delete[] values;
        }

        void updateTree(FenwickTree::Impl* impl, int index, int delta)
        {
            while (index <= impl->size)
            {
                impl->tree[index] += delta;
                index += index & (-index); // einam aukstyn per intervalus
            }
        }

        int queryTree(const FenwickTree::Impl* impl, int index)
        {
            int sum = 0;

            while (index > 0)
            {
                sum += impl->tree[index];
                index -= index & (-index); // einam zemyn
            }

            return sum;
        }
    };

    FenwickTree::FenwickTree(int size)
    {
        if (size <= 0)
            throw invalid_argument("Size must be positive");

        pImpl = new Impl(size);
    }

    FenwickTree::FenwickTree(const FenwickTree& other)
    {
        pImpl = new Impl(*other.pImpl); // deep copy
    }

    FenwickTree& FenwickTree::operator=(const FenwickTree& other)
    {
        if (this != &other)
        {
            delete pImpl;
            pImpl = new Impl(*other.pImpl); // deep copy
        }
        return *this;
    }

    FenwickTree::~FenwickTree()
    {
        delete pImpl;
    }

    void FenwickTree::add(int index, int delta)
    {
        if (index <= 0 || index > pImpl->size)
            throw out_of_range("Index out of range");

        pImpl->values[index] += delta;
        pImpl->updateTree(pImpl, index, delta);
    }

    int FenwickTree::get(int index) const
    {
        if (index <= 0 || index > pImpl->size)
            throw out_of_range("Index out of range");

        return pImpl->values[index];
    }

    void FenwickTree::set(int index, int value)
    {
        int current = get(index);
        int delta = value - current; // pokytis
        add(index, delta);
    }

    void FenwickTree::remove(int index)
    {
        int current = get(index);

        if (current == 0)
            throw AlreadyZeroException("Element already zero");

        set(index, 0);
    }

    int FenwickTree::prefixSum(int index) const
    {
        if (index < 0 || index > pImpl->size)
            throw out_of_range("Index out of range");

        return pImpl->queryTree(pImpl, index);
    }

    int FenwickTree::rangeSum(int left, int right) const
    {
        if (left > right)
            throw invalid_argument("Invalid range");

        return prefixSum(right) - prefixSum(left - 1);
    }

    string FenwickTree::toString() const
    {
        stringstream ss;

        ss << "Size: " << pImpl->size << " Values: ";

        for (int i = 1; i <= pImpl->size; i++)
            ss << pImpl->values[i] << " ";

        return ss.str();
    }

    FenwickTree& FenwickTree::operator+=(const Entry& e)
    {
        add(e.index, e.value);
        return *this;
    }

    FenwickTree& FenwickTree::operator-=(int index)
    {
        remove(index);
        return *this;
    }

    FenwickTree& FenwickTree::operator*=(const Entry& e)
    {
        set(e.index, e.value);
        return *this;
    }

    int FenwickTree::operator[](int index) const
    {
        return get(index);
    }

    void FenwickTree::operator!()
    {
        for (int i = 1; i <= pImpl->size; i++)
            pImpl->values[i] = 0;

        for (int i = 1; i <= pImpl->size; i++)
            pImpl->tree[i] = 0;
    }

    bool FenwickTree::operator==(const FenwickTree& other) const
    {
        if (pImpl->size != other.pImpl->size)
            return false;

        for (int i = 1; i <= pImpl->size; i++)
            if (pImpl->values[i] != other.pImpl->values[i])
                return false;

        return true;
    }

    bool FenwickTree::operator!=(const FenwickTree& other) const
    {
        return !(*this == other);
    }

    bool FenwickTree::operator<(const FenwickTree& other) const
    {
        return prefixSum(pImpl->size) < other.prefixSum(other.pImpl->size);
    }

    bool FenwickTree::operator<=(const FenwickTree& other) const
    {
        return !(*this > other);
    }

    bool FenwickTree::operator>(const FenwickTree& other) const
    {
        return prefixSum(pImpl->size) > other.prefixSum(other.pImpl->size);
    }

    bool FenwickTree::operator>=(const FenwickTree& other) const
    {
        return !(*this < other);
    }
}
