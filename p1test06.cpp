// File: p1test06.cpp
//
// Simple test of SortedSquareList class
//

#include <iostream>
#include "SSLColumn.h"
#include "SortedSquareList.h"

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

bool SortedSquareList::inspect(SSLColumn** &buf, int &cap, int &size, int &start, int &end) {
    buf = m_cols;
    cap = m_capacity;
    size = m_size;
    start = m_start;
    end = m_end;
    return true;
}

int main(int argc, char *argv[]) {
    SSLColumn **buf;
    int cap, size, start, end;

    int result;
    SortedSquareList ssl;  // Test default constructor: should make 2x2

    ssl.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;

    ssl.add(45);
    ssl.dump();  // {45}
    ssl.add(46);
    ssl.dump();  // {45, 46}
    ssl.add(48);
    ssl.add(47);
    ssl.dump();  // {45, 46, 47, 48}

    // Remove first two values; should not have to shift (but ok if it does)
    result = ssl.remove(46);
    result = ssl.remove(48);
    ssl.dump(); // {45, 47}

    // Add value to end
    ssl.add(48);
    ssl.dump();  // {45, 47, 48}

    // Add value at middle
    ssl.add(46);
    ssl.dump();  // {45, 46, 47, 48}

    cout << "find(47): returned " << ssl.find(47) << endl;  // Should see "2"
    cout << "findAt(1): returned " << ssl.findAt(1) << endl;// Should see "46"

    return 0;
}
