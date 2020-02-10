// File: p1test07.cpp
//
// Additional tests of SortedSquareList class
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

    cout << "Fresh list:" << endl;
    ssl.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;

    ssl.add(45);
    ssl.add(48);
    ssl.add(46);
    cout << "After adding 45, 48, 46:" << endl;
    ssl.dump();  // {45, 46, 48}

    // Following should show size == 3 and cap == 4
    cout << ">>>Testing size() and capacity(): expecting 3, 4; got "
	 << ssl.size() << ", " << ssl.capacity() << endl;

    ssl.add(47);
    cout << "Adding 47:" << endl;
    ssl.inspect(buf, cap, size, start, end);
    cout << "orig: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl.dump();  // {45, 46, 47, 48}

    cout << ">>>Testing copy constructor on dynamic object:\n" <<
	"results should be IDENTICAL to above (except for buf addr):" << endl;
    ssl2p = new SortedSquareList(ssl);  // Test copy constructor
    ssl2p->inspect(buf, cap, size, start, end);
    cout << "copy: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl2p->dump();  // {45, 46, 47, 48}

    // Test destructor (valgrind will say at end if space reclaimed)
    cout << ">>>Calling destructor" << endl;
    delete ssl2p;

    ssl2p = new SortedSquareList();  // Again, default
    cout << ">>>Now calling overloaded operator= :" << endl;
    *ssl2p = ssl;  // Test overloaded op=
    ssl2p->dump();  // {45, 46, 47, 48}

    cout << ">>>Triggering growth: adding 49, cap should grow to 4 cols" << endl;
    ssl2p->add(49);
    ssl2p->inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl2p->dump();  // {45, 46, 47, 48, 49}

    cout << ">>>Now calling overloaded operator= to copy in-place into larger list" << endl;
    // *ssl2p is 4x4, and ssl is 2x2, result should be still 4x4, but only
    // using 2x2
    *ssl2p = ssl;  // Test overloaded op=
    ssl.inspect(buf, cap, size, start, end);
    cout << "orig: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl2p->inspect(buf, cap, size, start, end);
    cout << "copy: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl2p->dump();  // {45, 46, 47, 48}

    // First, shrink ssl2p
    cout << "Shrinking list to {45, 47}" << endl;
    ssl2p->remove(46);  // {45, 47, 48}
    ssl2p->remove(48);  // {45, 47}
    cout << ">>>Then calling overloaded operator= to copy in-place into smaller square list" << endl;
    // ssl2p is 4x4, but only 2 values, so should copy into ssl w/o realloc
    ssl = *ssl2p;
    ssl.inspect(buf, cap, size, start, end);
    cout << "orig: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;
    ssl.dump();
    delete ssl2p;

    return 0;
}
