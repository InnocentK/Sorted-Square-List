// File: p1test01.cpp
//
// Simple test of SSLColumn class
//

#include <iostream>
#include "SSLColumn.h"

using namespace std ;


// grading function used to examine private data members.
bool SSLColumn::inspect(int* &buf, int &cap, int &size, int &start, int &end) {
    buf = m_data;
    cap = m_capacity;
    size = m_size;
    start = m_start;
    end = m_end;
    return true;
}

int main(int argc, char *argv[]) {
    int *buf, cap, size, start, end;

    int result;
    SSLColumn col(8);

    col.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;

    col.add(45);
    col.dump();  // {45}
    col.add(46);
    col.dump();  // {45, 46}
    col.add(48);
    col.add(49);
    col.add(50);
    col.dump();  // {45, 46, 48, 49, 50}
    col.add(47);
    col.dump();  // Should see, starting at [0]: {45, 46, 47, 48, 49, 50}

    // Remove first two values; should not have to shift (but ok if it does)
    result = col.remove(45);
    result = col.remove(46);
    col.dump(); // Should see, starting at [2] (but [0] okay):
		// {47, 48, 49, 50}

    // Remove value from middle of column
    result = col.remove(48);
    col.dump(); // Should remove the 48, causing shift up of lower half,
		// leaving: starting at [2] or [0]: {47, 49, 50}

    // Add value to middle
    col.add(48);
    col.dump();  // Should see, starting at [2] or [0]: {47, 48, 49, 50}

    // Add value at head
    col.add(45);
    col.dump();  // Should see, starting at [1] or [0]: {45, 47, 48, 49, 50}

    // Add values at tail up to capacity
    col.add(51);
    col.add(52);
    col.add(53);
    col.dump();  // Should see, starting at [1] or [0]:
    // {45, 47, 48, 49, 50 .. 53}

    cout << "find(52): returned " << col.find(52) << endl;  // Should see "6"
    cout << "findAt(1): returned " << col.findAt(1) << endl;// Should see "47"

    return 0;
}
