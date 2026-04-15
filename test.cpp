#include <iostream>
#include <fstream>
#include "FenwickTree.h"

using namespace std;
using namespace ip2;

void printResult(bool cond, const string& name, ostream& out)
{
    if (cond)
        out << "PASS " << name << endl;
    else
        out << "FAIL " << name << endl;
}

int main()
{
    ofstream log("log.txt");

    try
    {
        FenwickTree t(5);

        printResult(t.get(1) == 0, "initial value", cout);
        printResult(t.get(1) == 0, "initial value", log);

        t.add(1, 5);
        t.add(2, 3);

        printResult(t.get(1) == 5, "add test", cout);
        printResult(t.get(1) == 5, "add test", log);

        t.set(2, 10);

        printResult(t.get(2) == 10, "set test", cout);
        printResult(t.get(2) == 10, "set test", log);

        printResult(t.prefixSum(2) == 15, "prefix sum", cout);
        printResult(t.prefixSum(2) == 15, "prefix sum", log);

        printResult(t.rangeSum(1,2) == 15, "range sum", cout);
        printResult(t.rangeSum(1,2) == 15, "range sum", log);

        t -= 1;
        printResult(t.get(1) == 0, "remove", cout);
        printResult(t.get(1) == 0, "remove", log);

        t += {3, 7};
        printResult(t.get(3) == 7, "operator +=", cout);
        printResult(t.get(3) == 7, "operator +=", log);

        t *= {3, 20};
        printResult(t.get(3) == 20, "operator *=", cout);
        printResult(t.get(3) == 20, "operator *=", log);

        FenwickTree t2 = t;
        printResult(t == t2, "copy + ==", cout);
        printResult(t == t2, "copy + ==", log);

        !t;
        printResult(t.prefixSum(5) == 0, "clear operator !", cout);
        printResult(t.prefixSum(5) == 0, "clear operator !", log);

        // exception test
        try
        {
            t.remove(1);
            printResult(false, "exception test", cout);
            printResult(false, "exception test", log);
        }
        catch (...)
        {
            printResult(true, "exception test", cout);
            printResult(true, "exception test", log);
        }

    }
    catch (...)
    {
        cout << "Unexpected error" << endl;
        log << "Unexpected error" << endl;
    }

    log.close();
    return 0;
}
