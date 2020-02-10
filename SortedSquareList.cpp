/*****************************************
 ** File:    SortedSquareColumn.cpp
 ** Project: CMSC 341 Project 1 - Sorted Square Lists, Spring 2018
 ** Author:  Innocent Kironji
 ** Date:    02/23/18
 ** Section: 03
 ** E-mail:  wambugu1@umbc.edu
 **
 **  This file contains implementation for a Sorted Square List
 **  This is a 2D circular buffer of SSLColumn objects that is
 **    capable of sorting itself and managing it's own squareness 
 ***********************************************/

#include "SortedSquareList.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

// default constructor
SortedSquareList::SortedSquareList(){

  const int DEFAULT_SIZE = 2;

  // Creating the Square Buffer
  m_cols = new SSLColumn*[DEFAULT_SIZE];
  m_cols[0] = new SSLColumn();
  m_cols[1] = new SSLColumn();
  m_colInfo = new int[DEFAULT_SIZE];
  m_colInfo[0] = 0;
  m_colInfo[1] = DEFAULT_SIZE;

  // Setting other members
  m_capacity = (*m_cols)->capacity();
  m_size = (*m_cols)->size();
  m_start = 0;
  m_end = m_size;
  m_total_size = m_size;
}

// copy constructor
SortedSquareList::SortedSquareList(const SortedSquareList& other){

  // Copying members from other
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
  m_total_size = other.m_total_size;

  // Allocating enough space for new Square List
  m_colInfo = new int[m_capacity];
  m_cols = new SSLColumn*[m_capacity];
  for (int i = 0; i < m_capacity; i++)
    m_cols[i] = new SSLColumn();

  // Copying data from other's columns
  for (int i = 0; i < m_size; i++){
    int curr_col = (m_start + i) % m_capacity;
    *m_cols[curr_col] = *other.m_cols[curr_col];
    m_colInfo[curr_col] = other.m_colInfo[curr_col];
  }
}

// destructor
SortedSquareList::~SortedSquareList(){

  // Deallocating dynamic memory
  for (int i = 0; i < m_capacity; i++){
    delete m_cols[i];
    m_cols[i] = NULL;
  }
  delete [] m_cols;
  m_cols = NULL;
  delete [] m_colInfo;
  m_colInfo = NULL;

  // Resetting memebers
  m_capacity = 0;
  m_size = 0;
  m_start = 0;
  m_end = 0;
  m_total_size = 0;
}

// overloaded assignment operator
// We can copy into differently-sized square list, as long as it is large
// enough to hold all of the actual stored data.
const SortedSquareList& SortedSquareList::operator=(const SortedSquareList& rhs){

  // Checks for self-assignment
  if (this == &rhs)
    return *this;

  // Deallocating dynamic memory for target
  for (int i = 0; i < m_capacity; i++){
    delete m_cols[i]; 
    m_cols[i] = NULL;
  }
  delete [] m_cols;
  m_cols = NULL;
  delete [] m_colInfo;
  m_colInfo = NULL;

  // Checks if target is large enough and resizes accordingly
  if (m_capacity < rhs.m_capacity)
    m_capacity = rhs.m_capacity;

  // Resetting members for target
  m_size = rhs.m_size;
  m_start = 0;
  m_end = m_size;
  m_total_size = rhs.m_total_size;

  // Allocating enough space for new Square List
  m_colInfo = new int[m_capacity];
  m_cols = new SSLColumn*[m_capacity];
  for (int i = 0; i < m_capacity; i++)
    m_cols[i] = new SSLColumn();

  // Copying data from other's columns
  for (int i = m_start; i < m_end; i++){
    *m_cols[i] = *rhs.m_cols[(rhs.m_start + i) % rhs.m_capacity];
    m_colInfo[i] = rhs.m_colInfo[(rhs.m_start + i) % rhs.m_capacity];
  }

  return *this;
}

// Adds item to correct position in square list, based on sort order.
// Must grow dynamically allocated structures if we run out of room;
// REQUIREMENT: must execute in O(sqrt(n)) time, where n is
// number of items currently stored.
void SortedSquareList::add(int data){

  const int INCREMENT = 2;
  bool data_added, col_added, shifted = false;

  // Checks if the square list is empty
  if (m_size == 0){
    m_size++;
    m_total_size++;
    m_end = (m_end + 1) % m_capacity;
    m_cols[m_start]->addFirst(data);
    return;
  }

  // When Square List is full, allocate larger square list 
  if (m_capacity == m_size){

    // Initializing new square list
    int temp_capacity = m_capacity * INCREMENT;
    SSLColumn **temp_cols = new SSLColumn*[temp_capacity];
    int *temp_info = new int[temp_capacity];
    for (int i = 0; i < temp_capacity; i++)
      temp_cols[i] = new SSLColumn(temp_capacity);
    
    // Copying over columns from current square list to larger list
    for (int i = 0; i < m_size; i++){
      int curr_col = (m_start + i) % m_capacity;
      *temp_cols[i] = *m_cols[curr_col];
      temp_info[i] = m_colInfo[i];
    }
    
    // Deallocating old, smaller list
    for (int i = 0; i < m_capacity; i++){
     delete m_cols[i];
     m_cols[i] = NULL;
    }
    delete [] m_cols;
    m_cols = temp_cols;
    delete [] m_colInfo;
    m_colInfo = temp_info;

    // Updating members to match updated capacity of square list
    m_start = 0;
    m_end = m_size;
    m_capacity = temp_capacity;
  }
  
  // Itterating through square list to find proper position for data
  for (int i = 0; i < m_size; i++){
    int curr_col = (m_start + i) % m_capacity;
    int next_col = (curr_col + 1) % m_capacity;
    int prev_col = (curr_col - 1 + m_capacity) % m_capacity;
    
    // Necessary for checking if data should go within column
    int col_size = col_size = m_cols[curr_col]->size();
    int next_col_size, prev_col_size, col_low, col_high, removed = -1;

    // Because next column does not exist at end
    if (next_col != m_end)
      next_col_size = m_cols[next_col]->size();

    // Because previous column is does not exist at start
    if (curr_col != m_start)
      prev_col_size = m_cols[prev_col]->size();

    // Column size can only be 0 at the last column
    //  (when increasing columns to get perfect squareness)
    if (col_size > 0){
      col_low = m_cols[curr_col]->findAt(0);
      col_high = m_cols[curr_col]->findAt(col_size - 1);
    }

    // Handles Squareness
    // Inititally shifts left
    if( (col_size < m_size) && (next_col != m_end) && (next_col_size > 0) ){

	removed = m_cols[next_col]->removeFirst();
	m_cols[curr_col]->addLast(removed);
	col_high = removed;
	shifted = true;
    }
    // Shifts extra elements to the right
    else if( (col_size > m_size) && (next_col != m_end) && 
	     (next_col_size < m_size) ){

      removed = m_cols[curr_col]->removeLast();
      m_cols[next_col]->addFirst(removed);
    }
    
    // When at the end of initialised data
    if (next_col == m_end){
      
      // Column is empty 
      if (col_size == 0)
	m_cols[curr_col]->addFirst(data);
	
	// Column has reached largest size possible to keep squareness
      else if (col_size == m_size){

	// Adds a new column when last one is full
	if ( (i > 0) && (data > col_high) ){
	     m_cols[next_col]->addFirst(data);
	     m_size++;
	     m_end = (m_end + 1) % m_capacity;
	     return;
	}
	
	// Adds new column but uses largest data
	else if( (i > 0) && (m_size < m_capacity) ){
	  removed = m_cols[curr_col]->removeLast();
	  m_cols[next_col]->addFirst(removed);
	}

	// Fix column to match new size before adding new item
	else if (i > 0){
	  removed = m_cols[curr_col]->removeFirst();
	  m_cols[prev_col]->addLast(removed);	  
	}

	// Updating members and adding data
	m_size++;
	m_end = (m_end + 1) % m_capacity;
	m_cols[curr_col]->add(data);
	m_total_size++;
	return;
      }

      // Column is within acceptable limits and not empty
      else
	m_cols[curr_col]->add(data);      
    }

    else if( (i > 0) && (col_low > data) ){
      // Column has reached largest size possible to keep squareness
      if (col_size >= m_size){	
	removed = m_cols[curr_col]->removeLast();
	m_cols[curr_col]->add(data);
	data_added = true;

	// data is updated to the removed item so that it is easier to add
	data = removed;
      }	
      
      // Column is within acceptable limits and not empty
      else
	m_cols[curr_col]->add(data);
    }

    // When current position is likely where to add data 
    else if( (col_low <= data) && (col_high >= data) ){
      
      // Column has reached largest size possible to keep squareness
      if (col_size >= m_size){	
	removed = m_cols[curr_col]->removeLast();
	m_cols[curr_col]->add(data);
	data_added = true;

	// data is updated to the removed item so that it is easier to add
	data = removed;
      }	
      
      // Column is within acceptable limits and not empty
      else
	m_cols[curr_col]->add(data);

      // If the last column was already shifted for squareness then add ends
      if( (shifted) && (i > 0) ){
	removed = m_cols[curr_col]->removeFirst();
	m_cols[prev_col]->addLast(removed);
	m_total_size++;
	return;
      }
    }
    
    // When data is to be added to first position of column
    // Common at first position or when data has been removed
    else if( (col_low > data) && (!data_added) ){
      
      // Column has reached largest size possible to keep squareness
      if (col_size >= m_size){	
	removed = m_cols[curr_col]->removeLast();
	m_cols[curr_col]->addFirst(data);
	data = removed;
      }
      
      // Column is within acceptable limits and not empty
      else
	m_cols[curr_col]->addFirst(data);     
    }

    // Special Case to assist with squareness
    if( ( (next_col + 1) % m_capacity  == m_end) && (next_col_size == 0) 
	&& (data <= col_high) ){

      // Checks if last removed element had been added to the square list
      if (removed >= data)
	m_cols[next_col]->addFirst(removed);

      m_total_size++;
      return;
    }
  } //End of Loop
  
  // More Changes
  m_total_size++;
  
  // Itterates through column info, making updates
  for (int i = 1; i < m_size; i++)
    m_colInfo[i] = (i - 1) * m_size;
}

// returns position of item in list, -1 if not found.
// REQUIREMENT: must execute in O(log(n)) time
int SortedSquareList::find(int data){

  int pos = -1;

  // Variables used to halve the search list
  int lower = 0;
  int upper = m_size - 1;
  int mid = (lower + upper) / 2;
  int true_mid = (mid + m_start) % m_capacity;

  // Splits the buffer in half continuously until value is found
  do{

    // Necessary for checking if data is within certain columns
    int col_size = m_cols[true_mid]->size();
    int col_low = m_cols[true_mid]->findAt(0);
    int col_high = m_cols[true_mid]->findAt(col_size - 1);

    // When current position is likely within current column 
    if( (col_low <= data) && (col_high >= data) )
      return m_cols[true_mid]->find(data) + (mid * m_size);

    // When data is in the lower half of current range of columns
    else if (col_low < data)
      lower = mid + 1;

    // When data is in the upper half of columns
    else
      upper = mid - 1;

    // Updating mid
    mid = (lower + upper) / 2;
    true_mid = (mid + m_start) % m_capacity;

  }while (lower <= upper);

  // Only called when data is not found
  return pos;
}

// Retrieves value at index pos in square list, based on total sort order.
// Throws exception if pos beyond end
// REQUIREMENT: must execute in O(log(n)) time
int SortedSquareList::findAt(int pos){

  // Checks if valid position was given
  if (pos >= m_total_size)
    throw std::overflow_error("Cannot find position; not in list");

  // If well squared (with preference to fill the left columns first) 
  //  positions can be attained with m_size
  else{
    int data_column = (pos / m_size) + m_start;
    int data_pos = pos % m_size;
    return m_cols[data_column]->findAt(data_pos);
  }
}

// Finds and removes item from square list.
// Returns true if data found, false otherwise.
// REQUIREMENT: must execute in O(sqrt(n)) time
bool SortedSquareList::remove(int data){

  bool data_removed, remove_col = false;
  const int SIZE = m_size;

  // Checks if the square list is empty
  if (m_size == 0)
    return data_removed;

  // Itterates through buffer
  for (int i = 0; i < m_size; i++){
    int curr_col = (m_start + i) % m_capacity;
    int next_col = (curr_col + 1) % m_capacity;
    int prev_col = (curr_col - 1 + m_capacity) % m_capacity;

    // Necessary for checking if data is within certain columns
    int col_size = m_cols[curr_col]->size();
    int temp_data, col_low, col_high, removed = -1; 
    int next_col_size, prev_col_size = -1;

    // Necessary to determine how size will be affected by a column removal
    if(curr_col != m_start)
      prev_col_size = m_cols[prev_col]->size();
    
    // Column contains data to remove
    if (col_size > 0){
      col_low = m_cols[curr_col]->findAt(0);
      col_high = m_cols[curr_col]->findAt(col_size - 1);
      
      // When current position is likely where to remove data
      if( (col_low <= data) && (col_high >= data) ){
	
	  removed = m_cols[curr_col]->remove(data);
	  data_removed = true;
	  m_total_size--;
	  col_size = m_cols[curr_col]->size();
      }

      // Handles Squareness during search for removal
      if( (col_size < m_size) && (next_col != m_end) ){	
	next_col_size = m_cols[next_col]->size();

	if (next_col_size > 0){
	  removed = m_cols[next_col]->removeFirst();
	  m_cols[curr_col]->addLast(removed);
	}
      }
    }
    // When end column becomes size 0 (empty) and previous column
    //  has enough room for an additional item
    else if (next_col == m_end){

      // This will make m_end = m_start and m_size to be 0
      // m_Start does not have a previous column
      if (curr_col == m_start){
	m_end = (m_end - 1 + m_capacity) % m_capacity;
	m_size--;
      }

      // Behaves similarly as the start but
      //  later columns are dependent on previous column's size
      else if (prev_col_size < m_size){
	m_end = (m_end - 1 + m_capacity) % m_capacity;
	m_size--;
      }
    }
  } //End of Loop

  // Itterates through column info, making updates
  for (int i = 1; i <= m_size; i++)
    m_colInfo[i] = (i - 1) * m_size;
  
  return data_removed;
}

// return maximum number of active items this square list can hold with
// current allocation
int SortedSquareList::capacity(){

  const int SQUARED = 2;
  return std::pow(m_capacity, SQUARED);
}

// Total number of items in the square list as a whole, across all columns
int SortedSquareList::size(){

  return m_total_size;
}

// debugging function, prints out contents of data structure
void SortedSquareList::dump(){

  if (m_size == 0){
    std::cout << "The Square List is empty" << std::endl;
    return;
  }

  // Utilisez dump() function of SSLColumn
  for (int i = 0; i < m_size; i++){
    int curr_col = (m_start + i) % m_capacity;
    int col_size = m_cols[curr_col]->size();

    // Checks that no empty columns are printed
    if (col_size != 0){
      std::cout << "Column " << curr_col << ":";
      m_cols[curr_col]->dump();
      std::cout << std::endl;
    }
  }
}
