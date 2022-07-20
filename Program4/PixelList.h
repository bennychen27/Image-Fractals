/*
PixelList.h

Author: Benny Chen
Date: 2-25-2020 updated 3-10-2020
Section: CSS342 C

This is a container class for storing a set of image pixels and additional support 
information related to the pixels such as the list size, seed pixel, count of all 
pixels RGB values and is implemented as linked list.
*/

#include < iostream >
#include "ImageLib.h"

using namespace std;
#pragma once

class PixelList {

// constructor, copy constructor, operator=, destructor, addPixel, and merge (see below.) 
// You can implement other member functions (including size and averageColor), if desired.
private:

	struct Node {

		pixel data;
		Node* next;
		int row;
		int col;

	};

	Node* head;

public:

	/* PixelList: Default constructor that constructs a PixelList and sets pixelList object head to nullptr
	* Preconditions: none
	* Postconditions: a PixelList object is initialied with head set to nullptr
	*/
	PixelList();

	/* PixelList: Copy constructor that calls copy function to construct a PixelList object with copied data from
				  other PixelList object. If head= null, set head to null, else copy first node and rest of linked list
	* Preconditions: input is a valid object, not an empty list
	* Postconditions: PixelList object is created with copied data members as other PixelList object
	*/
	PixelList(const PixelList& input);

	/* operator=: Assignment operator is overloaded to copy all nodes of other data object to this object.
				  Deletes current list, and sets head to nullptr, otherwise set head to new node
				  data and copy rest of pixel list and returns it
	* Preconditions: other is a valid object and has valid values for data of object
	* Postconditions: return this object if operator called on this object.
					  set this object = to other object and copies all data values
	*/
	const PixelList& operator=(const PixelList& input);

	/* ~PixelList: Destructor that deallocates node to delete the linked list and head node
	* Preconditions: none
	* Postconditions: every node in the linked list is deleted
	*/
	~PixelList();

	/* addPixelNode: Creates a new node pixel input at row and col from other pixel object
	* Preconditions: other is a valid input and isnt null, has valid row/col values
	* Postconditions: A new pixel node is created at the top of the linked list with row and col values stored
	*/
	void addPixelNode(pixel input, int row, int col);

	/* merge: Merges all pixels in linked list by calling addPixelNode function and merges the other objects to this object
	* Preconditions: other is a valid input and both linked lists cant be empty
	* Postconditions: All the nodes from other object is added to this object
	*/
	void merge(const PixelList& input);

	/* averagePixels: Averages the rgb values of pixels by dividing by size of pixel group in linked list and returns it
	* Preconditions: size cant be zero, cant divide by zero
	* Postconditions: return  the average of the rgb values for all the pixels in the list
	*/
	pixel averagePixels();

	/* getTopData: Removes top pixel and returns row and column value for that pixel
	* Preconditions: row and col are valid inputs
	* Postconditions: Removes the top node from the linked list and returns the row and col values for the removed pixel node
	*/
	int getTopData(int& r, int& c);

	/* size: Returns the size of pixel linked list
	* Preconditions: none
	* Postconditions: returns the number of elements in linked list
	*/
	int size() const;
};
