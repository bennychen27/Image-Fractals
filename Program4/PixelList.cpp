/*
PixelList.cpp

Author: Benny Chen
Date: 2-25-2020 updated 3-10-2020
Section: CSS342 C

This is a container class for storing a set of image pixels and additional support
information related to the pixels such as the list size, seed pixel, count of all
pixels RGB values and is implemented as linked list
*/

#include < iostream >
#include "ImageLib.h"
#include "PixelList.h"

using namespace std;
#pragma once

/* PixelList: Default constructor that constructs a PixelList and sets pixelList object head to nullptr
* Preconditions: none
* Postconditions: a PixelList object is initialied with head set to nullptr
*/
PixelList::PixelList() {

	head = nullptr;

}

/* PixelList: Copy constructor that calls copy function to construct a PixelList object with copied data from
              other PixelList object. If head= null, set head to null, else copy first node and rest of linked list
* Preconditions: input is a valid object, not an empty list
* Postconditions: PixelList object is created with copied data members as other PixelList object
*/
PixelList::PixelList(const PixelList& other) {

	if (other.head == nullptr) {

		head = nullptr;

	}
	else {
		
		head = new Node;
		head->data = other.head->data;
		Node* current = other.head;
		Node* newCurrent = head;

		while (current->next != nullptr) {

			current = current->next;
			newCurrent->next = new Node;
			newCurrent = newCurrent->next;
			newCurrent->data = current->data;
			newCurrent->col = current->col;
			newCurrent->row = current->row;

		}

		newCurrent->next = nullptr;
	}

}

/* ~PixelList: Destructor that deallocates node to delete the linked list and head node
* Preconditions: none
* Postconditions: every node in the linked list is deleted
*/
PixelList::~PixelList() {

	while (head != nullptr) {

		Node* current = head;
		head = head->next;
		delete current;

	}

}

/* operator=: Assignment operator is overloaded to copy all nodes of other data object to this object. 
              Deletes current list, and sets head to nullptr, otherwise set head to new node
			  data and copy rest of pixel list and returns it
* Preconditions: other is a valid object and has valid values for data of object
* Postconditions: return this object if operator called on this object. 
                  set this object = to other object and copies all data values
*/
const PixelList& PixelList::operator=(const PixelList& other) {

	while (head != nullptr) {

		Node* current = head;
		head = head->next;
		delete current;

	}

	if (other.head == nullptr) {

		head = nullptr;

	}

	else {

		head = new Node;
		head->data = other.head->data;
		Node* current = other.head;
		Node* newCurrent = head;


		while (current->next != nullptr) {

			current = current->next;
			newCurrent->next = new Node;
			newCurrent = newCurrent->next;
			newCurrent->data = current->data;
			newCurrent->col = current->col;
			newCurrent->row = current->row;

		}

		newCurrent->next = nullptr;
	}

	return *this;

}

/* addPixelNode: Creates a new node pixel input at row and col from other pixel object
* Preconditions: other is a valid input and isnt null, has valid row/col values
* Postconditions: A new pixel node is created at the top of the linked list with row and col values stored
*/
void PixelList::addPixelNode(pixel other, int row, int col) {

	if (head == nullptr) {

		head = new Node;
		head->row = row;
		head->col = col;
		head->data = other;
		head->next = nullptr;

	}

	else {

		Node* newNode = new Node;
		newNode->row = row;
		newNode->col = col;
		newNode->data = other;
		newNode->next = head;
		head = newNode;

	}

}

/* merge: Merges all pixels in linked list by calling addPixelNode function and merges the other objects to this object
* Preconditions: other is a valid input and both linked lists cant be empty
* Postconditions: All the nodes from other object is added to this object
*/
void PixelList::merge(const PixelList& other) {

	if (this->head == nullptr || other.head == nullptr) {
		
		cout << "One or both of the lists are empty, merge unsuccessful" << endl;

	}

	else {

		Node* current = other.head;

		while (current != nullptr) {

			addPixelNode(current->data, current->row, current->col);
			current = current->next;

		}
	}

}

/* averagePixels: Averages the rgb values of pixels by dividing by size of pixel group in linked list and returns it
* Preconditions: size cant be zero, cant divide by zero
* Postconditions: return  the average of the rgb values for all the pixels in the list
*/
pixel PixelList::averagePixels() {

	pixel averagedPixel = pixel();

	if (head == nullptr) {

		averagedPixel.red = 0;
		averagedPixel.green = 0;
		averagedPixel.blue = 0;
		return averagedPixel;

	}

	int red = 0;
	int green = 0;
	int blue = 0;
	int counter = 0;
	Node* current = head;

	while (current != nullptr) {

		red += current->data.red;
		green += current->data.green;
		blue += current->data.blue;

		counter++;
		current = current->next;

	}

	red /= counter;
	green /= counter;
	blue /= counter;

	averagedPixel = pixel();
	averagedPixel.red = red;
	averagedPixel.green = green;
	averagedPixel.blue = blue;

	return averagedPixel;

}

/* getTopData: Removes top pixel and returns row and column value for that pixel
* Preconditions: row and col are valid inputs
* Postconditions: Removes the top node from the linked list and returns the row and col values for the removed pixel node
*/
int PixelList::getTopData(int& row, int& col) {

	if (head == nullptr) {

		return 1;

	}

	else {

		row = head->row;
		col = head->col;
		Node* current = head;
		head = head->next;
		delete current;
		current = nullptr;

		return 0;

	}

}

/* size: Returns the size of pixel linked list
* Preconditions: none
* Postconditions: returns the number of elements in linked list
*/
int PixelList::size() const {

	int size = 0;
	Node* current = head;

	while (current != nullptr) {

		size++;
		current = current->next;

	}

	return size;

}

