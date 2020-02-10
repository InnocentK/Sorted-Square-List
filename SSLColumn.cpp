/*****************************************
 ** File:    SSLColumn.cpp
 ** Project: CMSC 341 Project 1 - Sorted Square Lists, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    02/23/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **   This file contains implementation of the SSLColumn class.
 **   This class is used to managed the individual columns of
 **     the Sorted Square List
 ***********************************************/

#include "SSLColumn.h"
#include <stdexcept>
#include <iostream>

// Constructor, default size is 2
SSLColumn::SSLColumn(int n){

  m_data = new int[n];
  m_capacity = n;
  m_size = 0;
  m_start = 0;
  m_end = 0;
}

// Copy constructor
// Makes exact copy, including relative positions in circular buffers
SSLColumn::SSLColumn(const SSLColumn& other){

  // Copies members from other
  m_capacity = other.m_capacity;
  m_data = new int[m_capacity];
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;

  // Itterates through other's data and copies it over
  for (int i = 0; i <= m_size; i++){
    int curr_pos = (m_start + i) % m_capacity;
    m_data[curr_pos] = other.m_data[curr_pos];
  }
}

// Destructor
SSLColumn::~SSLColumn(){

  // Deallocating dynamic memory
  delete [] m_data;
  m_data = NULL;

  // Resets member variables
  m_capacity = 0;
  m_size = 0;
  m_start = 0;
  m_end = 0;
}

// overloaded assignment operator
// We can copy into differently-sized array.  Copying done in-place if
// target has sufficient capacity; else, target's internal array
// will be reallocated to a larger size.
const SSLColumn& SSLColumn::operator=(const SSLColumn& rhs){
  
  // Checks for self-assignment
  if (this == &rhs)
    return *this;

  delete [] m_data;
  m_data = NULL;
  
  // Checks if target has sufficient capacity
  // resizes target when smaller than rhs 
 if (m_capacity < rhs.m_capacity)
    m_capacity = rhs.m_capacity;
   
  // Resets members to match rhs
  m_data = new int[m_capacity];  
  m_size = rhs.m_size;
  m_start = 0;
  m_end = rhs.m_size;
  
  // Itterates through and copies data from rhs 
  for (int i = m_start; i < m_end; i++){
    m_data[i] = rhs.m_data[(rhs.m_start + i) % rhs.m_capacity];
  }
  return *this;
}

// Adds item to correct sorted order position in circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(n) time, where n is size of column
void SSLColumn::add(int data){

  // Checks if column is full
  if (m_size == m_capacity){
    throw std::overflow_error("Cannot add; column is out of room");
    return;
  }
  
  // In the case that the column is not populated
  if (m_start == m_end)
    m_data[m_start] = data;

  // Column still has room
  else{    
    int temp = data;
    
    // Itterates through column
    for (int i = 0; i <= m_size; i++){
      int curr_pos = (m_start + i) % m_capacity;
      
      // Checks if end of column has been reached
      if (i == m_size)
	m_data[curr_pos] = data;
      
      // Checks to see where data fits in the order
      // Nothing occurs if that is not the proper location for the data
      else if(data > m_data[curr_pos]){}
      
      // Keeps track of and moves data down the column after adding new data
      else{
	temp = m_data[curr_pos];
	m_data[curr_pos] = data;
	data = temp;
      }
    }
  }
  // Updates size
  m_end = (m_end + 1) % m_capacity;
  m_size++; 
}

// Adds item to top/left of circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(1) time
void SSLColumn::addFirst(int data){

  // Checks if column is full
  if (m_size == m_capacity){
    throw std::overflow_error("Cannot add to first; column is out of room");
    return;  
  }
  
  // In the case that the column is not populated
  else if( (m_start == m_end) && (m_size == 0) ){
    m_data[m_start] = data;
    m_end = (m_end + 1) % m_capacity;
  }

  // Column has elements; Moves "start" in order to make addition easier
  else{
    m_start = (m_start - 1 + m_capacity) % m_capacity;
    m_data[m_start] = data;
  }
  m_size++;
}

// Adds item to bottom/right of circular buffer.
// Throws exception if out of room.
// REQUIREMENT: must execute in O(1) time
void SSLColumn::addLast(int data){

  // Checks if column is full
  if (m_size == m_capacity){
    throw std::overflow_error("Cannot add to last; column is out of room");
    return;  
  }
  
  // Does not matter if column is empty or not
  else{
    m_data[m_end] = data;
    m_end = (m_end + 1) % m_capacity;
    m_size++;
  }
}

// returns position of item in column, -1 if not found.
// REQUIREMENT: must execute in O(log(n)) time, where n is size of column
int SSLColumn::find(int data){

  int pos = -1;

  // Variables used to halve the search list
  int lower = 0;
  int upper = m_size - 1;
  int mid = (lower + upper) / 2;
  int true_mid = (mid + m_start) % m_capacity;

  // Splits the column in half continuously until value is found
  do{

    // When current position is the value
    if (m_data[true_mid] == data)
      return mid;

    // When data is in the upper half of current range
    else if (m_data[true_mid] < data)
      lower = mid + 1;

    // When data is in the lower half
    else
      upper = mid - 1;

    // Updating mid
    mid = (lower + upper) / 2;
    true_mid = (mid + m_start) % m_capacity;

  }while (lower <= upper);

  // Only called when data is not found
  return pos;
}

// Retrieves value at index pos in circular buffer, based on sort order.
// If pos == -1, retrieves last value in list, a la Python
// Throws exception if pos >= size.
// REQUIREMENT: must execute in O(1) time.
int SSLColumn::findAt(int pos){

  // Checks if valid position was given
  if (pos >= m_size){
    throw std::overflow_error("Cannot find position; not in column");
  }
  else{
    int data_pos = (m_start + pos) % m_capacity;
    return m_data[data_pos];
  }
}

// Removes item from column, returning original position of item,
// -1 if not found.
// REQUIREMENT: must execute in O(n) time, where n is size of column
int SSLColumn::remove(int data){

  int removed_pos = -1;
  const int SIZE = m_size;

  // Itterates through column
  for (int i = 0; i < SIZE; i++){
    int curr_pos = (m_start + i) % m_capacity;
    int next_pos = (curr_pos + 1) % m_capacity;

    // Checks for position to remove 
    if (m_data[curr_pos] == data)
      removed_pos = i;

    // Shifts items up the column to keep proper dimensions 
    if( (removed_pos > -1) && (next_pos != m_end) )
      m_data[curr_pos] = m_data[next_pos];   
  }

  // Updates the size and end if an item was removed
  if (removed_pos > -1){
    m_size--;
    m_end = (m_end - 1 + m_capacity) % m_capacity;
  }

  return removed_pos;
}

// Removes top/left item from circular buffer and returns it.
// Throws exception if empty.
// REQUIREMENT: must execute in O(1) time
int SSLColumn::removeFirst(void){

  // Checks if column is empty
  if (m_size == 0){
    throw std::overflow_error("Cannot remove first; column is empty");
  }

  // Calculates the actual position to remove
  else{
    int removed_pos = m_start;
    m_start = (m_start + 1) % m_capacity;
    m_size--;
    return m_data[removed_pos];
  }
}

// Removes bottom/right item from circular buffer and returns it.
// Throws exception if empty.
// REQUIREMENT: must execute in O(1) time
int SSLColumn::removeLast(void){

  // Checks if column is empty
  if (m_size == 0){
    throw std::overflow_error("Cannot remove last; column is empty");
  }

  // Column has at least one element to remove
  else{
    m_end = (m_end - 1 + m_capacity) % m_capacity;
    m_size--;
    return m_data[m_end];
  }
}

// return maximum number of items this buffer can hold
int SSLColumn::capacity(){

  return m_capacity;
}

// return number of items currently held in the buffer
int SSLColumn::size(){

  return m_size;
}

// debugging function. Prints out contents.
void SSLColumn::dump(){

  // Checks for empty
  if (m_size == 0){
    std::cout << "Nothing to print" << std::endl;
    return;
  }

  // Itterates through column and prints data
  for (int i = 0; i < m_size; i++){
    int curr_pos = (m_start + i) % m_capacity;
    std::cout << " " << m_data[curr_pos] << " |";
  }
}
