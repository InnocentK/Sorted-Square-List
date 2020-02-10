// File: p1test08.cpp
//
// Additional shifting tests of SortedSquareList class
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
    SortedSquareList *ssl1p, *ssl2p, *ssl3p;


    for (int i = 10; i <= 90; i += 10) {
	cout << "Adding " << i << ":" << endl;
	ssl.add(i);
	ssl.dump();
    }

    ssl.add(25);
    cout << "Adding 25:" << endl;
    ssl.dump();

    ssl.add(85);
    cout << "Adding 85:" << endl;
    ssl.dump();

    ssl.add(75);
    cout << "Adding 75:" << endl;
    ssl.dump();

    ssl.add(55);
    cout << "Adding 55:" << endl;
    ssl.dump();

    return 0;
}
