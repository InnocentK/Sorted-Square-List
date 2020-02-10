// File: p1test02.cpp
//
// Additional tests of SSLColumn class
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
    SSLColumn col;  // Test default constructor: should have 2-val column
    SSLColumn *col2p, *col3p;

    cout << ">>>Results of default constructor:" << endl;
    col.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;

    cout << ">>>Adding 47, then 46:" << endl;
    col.add(47);
    col.add(46);
    col.dump();  // {46, 47}
    cout << ">>>Testing size() and capacity(): returned "
	 << col.size() << " and " << col.capacity() << endl;

    cout << ">>>Testing copy constructor on dynamic object: results should be IDENTICAL:\n  (except for buf addr)" << endl;
    col2p = new SSLColumn(col);  // Test copy constructor
    col.inspect(buf, cap, size, start, end);
    cout << "orig: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    col2p->inspect(buf, cap, size, start, end);
    cout << "copy: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    col2p->dump();  // {45, 46}

    // Test destructor (valgrind will say at end if space reclaimed)
    cout << ">>>Calling destructor" << endl;
    delete col2p;

    cout << ">>>Testing default constructor on dynamic object" << endl;
    col2p = new SSLColumn();  // Again, default
    col2p->dump();  // Should be empty
    
    cout << ">>>Now calling overloaded operator=" << endl;
    *col2p = col;  // Test overloaded op=
    col2p->inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    col2p->dump();  // Should now be {45, 46}

    cout << ">>>Dynamically creating col3 w/size==8" << endl;
    col3p = new SSLColumn(8);  // Again, default
    col3p->inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    
    cout << ">>>Now calling overloaded operator= to copy in-place into larger column" << endl;
    *col3p = col;  // Test overloaded op=
    col3p->inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    col3p->dump();  // Should now be {45, 46}

    cout << ">>>Testing addFirst() and addLast()" << endl;
    col3p->addFirst(1);
    col3p->addLast(99);
    col3p->dump();  // Should now be {1, 45, 46, 99}
    
    cout << ">>>Now calling overloaded operator= to copy in-place into smaller column" << endl;
    col2p->inspect(buf, cap, size, start, end);
    cout << "col2 before: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    *col2p = *col3p;  // Test overloaded op=
    col2p->inspect(buf, cap, size, start, end);
    cout << "col2 after: buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start =" << start << ", end = " << end << endl;
    col2p->dump();  // Should now be {45, 46}

    cout << ">>>Testing removeFirst() and removeLast()" << endl;
    col3p->removeFirst();
    col3p->removeLast();
    col3p->dump();  // Should now be {45, 46}

    delete col2p;
    delete col3p;
    return 0;
}
