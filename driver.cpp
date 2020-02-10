#include "SortedSquareList.h"
#include "SSLColumn.h"
#include <iostream>
using namespace std;

int main(){
 
  SortedSquareList *test = new SortedSquareList();
  test->dump();
  test->add(0);
  test->add(1);
  test->add(2);
  test->add(3);
  test->add(4);
  test->add(5);
  test->add(6);
  test->add(7);
  test->add(8);
  test->add(9);
  test->add(10);
  test->add(11);
  test->add(12);
  test->add(13);
  test->add(14);
  test->add(15);

  test->remove(10);
  test->add(16);

  test->dump();
  delete test;
  test = NULL;

  return 0;
}
