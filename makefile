CXX = g++
CXXFLAGS = -gstabs+

all: t01.out t02.out t03.out t06.out t07.out t08.out tXX.out proj1.out

t01.out: SortedSquareList.o SSLColumn.o p1test01.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test01.cpp -o t01.out

t02.out: SortedSquareList.o SSLColumn.o p1test02.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test02.cpp -o t02.out

t03.out: SortedSquareList.o SSLColumn.o p1test03.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test03.cpp -o t03.out

t06.out: SortedSquareList.o SSLColumn.o p1test06.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test06.cpp -o t06.out

t07.out: SortedSquareList.o SSLColumn.o p1test07.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test07.cpp -o t07.out

t08.out: SortedSquareList.o SSLColumn.o p1test08.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1test08.cpp -o t08.out

tXX.out: SortedSquareList.o SSLColumn.o p1testXX.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o p1testXX.cpp -o tXX.out

proj1.out: SortedSquareList.o SSLColumn.o driver.cpp
	$(CXX) $(CXXFLAGS) SortedSquareList.o SSLColumn.o driver.cpp -o proj1.out

SortedSquareList.o: SortedSquareList.cpp  SortedSquareList.h SSLColumn.o
	$(CXX) $(CXXFLAGS) -c SortedSquareList.cpp

SSLColumn.o: SSLColumn.cpp SSLColumn.h
	$(CXX) $(CXXFLAGS) -c SSLColumn.cpp

run:
	./proj1.out

test1:
	./t01.out

test2:
	./t02.out

test3:
	./t03.out

test6:
	./t06.out

test7:
	./t07.out

test8:
	./t08.out

testx:
	./tXX.out

val:
	valgrind ./proj1.out

val1:
	valgrind ./t01.out

val2:
	valgrind ./t02.out

val3:
	valgrind ./t03.out

val6:
	valgrind ./t06.out

val7:
	valgrind ./t07.out

val8:
	valgrind ./t08.out

valx:
	valgrind ./tXX.out

clean:
	rm *~

cleaner:
	rm *.o

cleanest:
	rm *~
	rm *.o