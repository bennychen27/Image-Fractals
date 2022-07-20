/*
myImage.h

Author: Benny Chen
Date: 1-23-2020
Section: CSS342 C

This source file is the header class for myImage class. Uses ImageLib.h to define all data members and methods that include:
Constructor using file names or specified size, copy constructor, destructor, and operator= using dynamic memory
Getters for number ofrows and columns in the image, as well as setters/getters for individual image pixels
Defines output to file, overloading == and !=, overloading <<
Contains a method that returns a mirror image of original image

*/

#pragma once

#include <iostream>
#include "ImageLib.h"

using namespace std;

class myImage {

private:

	image inputObject;

public:

	/* Constructor Method:
	* Preconditions: fileName is a valid file name
	* Postconditions: a newImage object is created from the file being read
	*/
	myImage(string fileName);


	/* Constructor Method:
	* Preconditions: rows and columns are natural numbers (positive integers starting from 0)
	* post-conditions: a newImage object is created with a specified number of rows and columns.
	*                  The object image is blank and black
	*/
	myImage(int rows, int cols);


	/* Copy Constructor Method:
	* Preconditions: image is a valid image
	* Postconditions: a newImage object is created which is a copy of the old image
	*/
	myImage(const myImage& newObject);


	/* Destructor Method:
	* Preconditions: the image object cant be null
	* Postconditions: the image object is deallocated, rows and columns are set to 0 and pixels to nullptr
	*/
	~myImage();


	/* Preconditions: input object is valid and cant be null
	*  Postconditions: returns an deep copy image object that is equal to the 'this' object
	*/
	const myImage& operator=(const myImage& newObject);


	/* Preconditions: image object has valid rows
	*  Postconditions: returns an int of image object's number of rows
	*/
	int getRow() const;


	/* Preconditions: image object has valid columns
	*  Postconditions: returns an int of image object's number of columns
	*/
	int getCol() const;


	/* Preconditions: the input value must be between 0 - 255
	*  Postconditions: sets the pixel's row, col, and pixel to specified input value
					  if underflow < 0, set to 0
					  if overflow > 255, set to 255.
	*/
	void setPixel(int row, int col, pixel in);


	/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
	*  Postconditions : returns the pixel at specified location
	*/
	pixel getPixel(int row, int col) const;


	/* Preconditions: the input value must be between 0 - 255
	*  Postconditions: sets the pixel's red number to specified input value
					  if underflow < 0, set to 0
					  if overflow > 255, set to 255.
	*/
	void setRed(int row, int col, int value);


	/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
	*  Postconditions : returns the pixel's red number at specified location
	*/
	int getRed(int row, int col) const;


	/* Preconditions: the input value must be between 0 - 255
	*  Postconditions: sets the pixel's green number to specified input value
					  if underflow < 0, set to 0
					  if overflow > 255, set to 255.
	*/
	void setGreen(int row, int col, int value);


	/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
	*  Postconditions : returns the pixel's green number at specified location
	*/
	int getGreen(int row, int col) const;


	/* Preconditions: the input value must be between 0 - 255
	*  Postconditions: sets the pixel's blue number to specified input value
					  if underflow < 0, set to 0
					  if overflow > 255, set to 255.
	*/
	void setBlue(int row, int col, int value);


	/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
	*  Postconditions : returns the pixel's blue number at specified location
	*/
	int getBlue(int row, int col) const;


	/* Preconditions: filename is a valid filename to store the new gif image
	*  Postconditions: creates a GIF image of the object image with a specified filename
	*/
	void outputToFile(string) const;


	/* Preconditions: both image objects are valid images
	*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
	*/
	bool operator==(const myImage& otherObject) const;


	/* Preconditions: both image objects are valid images
	*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
	*/
	bool operator!=(const myImage& otherObject) const;


	/* Preconditions: both image objects are valid images
	*  Postconditions: returns true if right side of image object has MORE pixels than left side of image object
					   returns false if right side of image object has LESS pixels than left side of image object
	*/
	bool operator<(const myImage&) const;


	/* Preconditions: both image objects are valid images
	*  Postconditions: returns true if left side of image object has MORE pixels than right side of image object
					   returns false if left side of image object has LESS pixels than right side of image object
	*/
	bool operator>(const myImage&) const;


	/* Preconditions: input is a valid image object
	*  Postconditions: outputs to console the dimensions of image object in number of rows and columns
	*/
	friend ostream& operator<<(ostream&, const myImage& input);


	/* Preconditions: the image object contains a valid image
	*  Postconditions: returns an image object with a mirrored image (left side pixels and right side pixels are swapped)
	*/
	myImage mirror();

};