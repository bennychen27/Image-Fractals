/*
myImage.h

Author: Benny Chen
Date: 1-23-2020 updated 2-5-2020
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

	/* Constructor Method: Constructor that takes a string file as input and creates image object by calling ReadGIF function from ImageLib.h
	* Preconditions: fileName is a valid file name
	* Postconditions: a newImage object is created from the file being read
	*/
	myImage(string fileName);


	/* Constructor Method: Constructor that takes 2 int values for rows and columns and sets them to 0 by default. Creates a new image object by calling
	*  the CreateImage function from ImageLib.h
	* Preconditions: rows and columns are natural numbers (positive integers starting from 0)
	* post-conditions: a newImage object is created with a specified number of rows and columns.
	*                  The object image is blank and black
	*/
	myImage(int rows = 0, int cols = 0);


	/* Copy Constructor Method: Copy constructor that takes an image object as input and creates a new image object by calling CopyImage function from
	   ImageLib.h
	* Preconditions: image is a valid image
	* Postconditions: a newImage object is created which is a copy of the old image
	*/
	myImage(const myImage& newObject);


	/* Destructor Method: Calls DeallocateImage function from ImageLib.h to deallocate image after use
	* Preconditions: the image object cant be null
	* Postconditions: the image object is deallocated, rows and columns are set to 0 and pixels to nullptr
	*/
	~myImage();


	/* operator=: Assignment operator overloaded to call CopyImage function from LibraryLib.h to create a copy of image object passed as a parameter
	*  Preconditions: input object is valid and cant be null
	*  Postconditions: returns an deep copy image object that is equal to the 'this' object
	*/
	const myImage& operator=(const myImage& newObject);


	/* getRow: Accessor method that returns number of rows in inputObject image
	*  Preconditions: image object has valid rows
	*  Postconditions: returns an int of image object's number of rows
	*/
	int getRow() const;


	/* getCol: Accessor method that returns number of columns in inputObject image
	*  Preconditions: image object has valid columns
	*  Postconditions: returns an int of image object's number of columns
	*/
	int getCol() const;

	/* setRed: Mutator method that sets the red value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Sets the input red value with specified value input
	*/
	void setRed(int row, int col, int redValue);

	/* getRed: Accessor method that returns the red value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Returns the red value with specified value input at specified row and column
	*/
	int getRed(int row, int col) const;

	/* setGreen: Mutator method that sets the green value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Sets the input green value with specified value input
	*/
	void setGreen(int row, int col, int GreenValue);

	/* getGreen: Accessor method that returns the green value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Returns the green value with specified value input at specified row and column
	*/
	int getGreen(int row, int col) const;

	/* setBlue: Mutator method that sets the blue value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Sets the input blue value with specified value input
	*/
	void setBlue(int row, int col, int rlueValue);

	/* getBlue: Accessor method that returns the blue value of inputObject at specified row and column
	*  Preconditions: parameter value must be greater than 0 and less than 255
	*  Postconditions: Returns the blue value with specified value input at specified row and column
	*/
	int getBlue(int row, int col) const;

	/* setPixel: Mutator method that sets pixel rgb values, at the specified row and col values
	*  Preconditions: the input value must be between 0 - 255
	*  Postconditions: sets the pixel's row, col, and pixel to specified input value
	*				  if underflow < 0, set to 0
	*				  if overflow > 255, set to 255.
	*/
	void setPixel(int row, int col, int red, int green, int blue);


	/* getPixel: Accessor method that returns the image object's pixel values at specified row and column value
	*  Preconditions: row, col, and pixel are valid dimensions and not out of bounds
	*  Postconditions : returns the pixel at specified location
	*/
	const pixel& getPixel(int row, int col) const;

	/* outputToFile: Method that calls writeGIF function from ImageLib.h to write the image object to specified file
	*  Preconditions: filename is a valid filename to store the new gif image
	*  Postconditions: creates a GIF image of the object image with a specified filename
	*/
	void outputToFile(string fileName) const;


	/* operator==: Equal operator is overloaded to compare image object to another image object input at each pixel rgb value
	*  Preconditions: both image objects are valid images
	*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
	*/
	bool operator==(const myImage& otherObject) const;


	/* operator!=: Not equal operator is overloaded to call == function and returns ! of the function
	*  Preconditions: both image objects are valid images
	*  Postconditions: returns false if both image objects are the same size and pixels, otherwise true
	*/
	bool operator!=(const myImage& otherObject) const;


	/* operator<: Less than operator compares image object to another image object to see if the pixel rgb values are less than original image object
	*  Preconditions: both image objects are valid images
	*  Postconditions: returns true if right side of image object has MORE pixels than left side of image object
	*				   returns false if right side of image object has LESS pixels than left side of image object
	*/
	bool operator<(const myImage&) const;


	/* operator>: Greater than operator compares image object to another image object to see if the pixel rgb values are greater than original image object
	*  Preconditions: both image objects are valid images
	*  Postconditions: returns true if left side of image object has MORE pixels than right side of image object
	*				   returns false if left side of image object has LESS pixels than right side of image object
	*/
	bool operator>(const myImage&) const;


	/* operator<<: overloaded cout to output image object's row and col values
	*  Preconditions: input is a valid image object
	*  Postconditions: outputs to console the dimensions of image object in number of rows and columns
	*/
	friend ostream& operator<<(ostream&, const myImage& input);


	/* mirror: Creates a new image object which copies original image object and returns the flipped image of the new image object
	*  Preconditions: the image object contains a valid image
	*  Postconditions: returns an image object with a mirrored image (left side pixels and right side pixels are swapped)
	*/
	myImage mirror() const;

};