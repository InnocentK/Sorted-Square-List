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
    string cmd;
    int arg, val, pos;
    bool result;
    SortedSquareList ssl;  // Test default constructor: should make 2x2
    SortedSquareList *ssl1p, *ssl2p, *ssl3p;


    while (!cin.eof()) {
	cout << "<cmd arg>: ";
	cin >> cmd >> arg;
	if (cmd == "a") {
	    ssl.add(arg);
	    ssl.dump();
	}
	else if (cmd == "r") {
	    result = ssl.remove(arg);
	    cout << "remove() returned " << result << endl;
	    ssl.dump();
	}
	else if (cmd == "f") {
	    pos = ssl.find(arg);
	    cout << "find(" << arg << ") returned " << pos << endl;
	}
	else if (cmd == "fa") {
	    val = ssl.findAt(arg);
	    cout << "findAt(" << arg << ") returned " << val << endl;
	}
	else if (cmd == "s") {
	    val = ssl.size();
	    cout << "size() returned " << val << endl;
	}
	else if (cmd == "c") {
	    val = ssl.capacity();
	    cout << "capacity() returned " << val << endl;
	}
	else if (cmd == "d") {
	    ssl.dump();
	}
	else if (cmd == "x") {
	    break;
	}
    }


    return 0;
}
