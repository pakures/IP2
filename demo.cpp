#include <iostream>
#include "FenwickTree.h"

using namespace std;
using namespace ip2;

int main()
{
    try
    {
        FenwickTree t(5);

        cout << "Initial: " << t.toString() << endl;

        // add
        t.add(1, 5);
        t.add(2, 3);
        t.add(3, 7);

        cout << "After add: " << t.toString() << endl;

        // get
        cout << "Value at 2: " << t.get(2) << endl;

        // set
        t.set(2, 10);
        cout << "After set: " << t.toString() << endl;

        // prefix sum
        cout << "Prefix sum (3): " << t.prefixSum(3) << endl;

        // range sum
        cout << "Range sum (1,3): " << t.rangeSum(1,3) << endl;

        // operator +=
        t += {4, 6};
        cout << "After += : " << t.toString() << endl;

        // operator *= (set)
        t *= {1, 20};
        cout << "After *= : " << t.toString() << endl;

        // operator []
        cout << "t[1] = " << t[1] << endl;

        // copy constructor
        FenwickTree t2 = t;

        // comparison
        cout << "t == t2: " << (t == t2) << endl;

        // remove
        t -= 1;
        cout << "After remove: " << t.toString() << endl;

        // comparison
        cout << "t != t2: " << (t != t2) << endl;

        // operator !
        !t;
        cout << "After clear: " << t.toString() << endl;
    }
    catch (exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
