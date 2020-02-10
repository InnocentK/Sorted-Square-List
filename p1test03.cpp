// File: p1test03.cpp
//
// Edge case tests of SSLColumn class
//

#include <iostream>
#include "SSLColumn.h"

using namespace std ;


int main(int argc, char *argv[]) {
    int *buf, cap, size, start, end;

    int result;
    SSLColumn col;  // Test default constructor: should have 2-val column
    SSLColumn *col2p, *col3p;

    col.add(47);
    col.add(49);
    col.dump();  // {47, 49}

    cout << ">>>add() to full column: should trigger exception" << endl;
    try	{
	col.add(48);
    }
    catch (std::exception& e) {
	cerr << "exception caught: " << e.what() << '\n';
    }

    cout << ">>>addFirst() to full column: should trigger exception" << endl;
    try	{
	col.addFirst(46);
    }
    catch (std::exception& e) {
	cerr << "exception caught: " << e.what() << '\n';
    }

    cout << ">>>addLast() to full column: should trigger exception" << endl;
    try	{
	col.addLast(50);
    }
    catch (std::exception& e) {
	cerr << "exception caught: " << e.what() << '\n';
    }

    cout << ">>>findAt() on too-high index: should trigger exception" << endl;
    try	{
	col.findAt(2);
    }
    catch (std::exception& e) {
	cerr << "exception caught: " << e.what() << '\n';
    }

    cout << ">>>findAt() on < -1 index: should trigger exception" << endl;
    try	{
	col.findAt(-2);
    }
    catch (std::exception& e) {
	cerr << "exception caught: " << e.what() << '\n';
    }
    return 0;
}
