/*
myImage.cpp

Author: Benny Chen
Date: 1-23-2020 updated 2-5-2020
Section: CSS342 C

This source file uses ImageLib.h and myImage.h. Provides a detailed definition of the functionalities from myImage.h file including:
Constructor using file names or specified size, copy constructor, destructor, and operator= using dynamic memory
Getters for number ofrows and columns in the image, as well as setters/getters for individual image pixels
Defines output to file, overloading == and !=, overloading <<
Contains a method that returns a mirror image of original image

*/

#pragma once

#include "myImage.h"
#include "ImageLib.h"
#include <iostream>

using namespace std;

/* Constructor Method: Constructor that takes a string file as input and creates image object by calling ReadGIF function from ImageLib.h
* Preconditions: fileName is a valid file name
* Postconditions: a newImage object is created from the file being read
*/
myImage::myImage(string fileName) {

	inputObject = ReadGIF(fileName);

}

/* Constructor Method: Constructor that takes 2 int values for rows and columns and sets them to 0 by default. Creates a new image object by calling
*  the CreateImage function from ImageLib.h
* Preconditions: rows and columns are natural numbers (positive integers starting from 0)
* post-conditions: a newImage object is created with a specified number of rows and columns.
*                  The object image is blank and black
*/
myImage::myImage(int row, int col) {

	inputObject = CreateImage(row, col);

}

/* Copy Constructor Method: Copy constructor that takes an image object as input and creates a new image object by calling CopyImage function from
   ImageLib.h
* Preconditions: image is a valid image
* Postconditions: a newImage object is created which is a copy of the old image
*/
myImage::myImage(const myImage& newObject) {

	inputObject = CopyImage(newObject.inputObject);

}

/* Destructor Method: Calls DeallocateImage function from ImageLib.h to deallocate image after use
* Preconditions: the image object cant be null
* Postconditions: the image object is deallocated, rows and columns are set to 0 and pixels to nullptr
*/
myImage::~myImage() {

	DeallocateImage(inputObject);

}

/* operator=: Assignment operator overloaded to call CopyImage function from LibraryLib.h to create a copy of image object passed as a parameter
*  Preconditions: input object is valid and cant be null
*  Postconditions: returns an deep copy image object that is equal to the 'this' object
*/
const myImage& myImage::operator=(const myImage& newObject) {

	if (this != &newObject) {

		DeallocateImage(inputObject);
		inputObject = CopyImage(newObject.inputObject);

	}

	return *this;
}

/* getRow: Accessor method that returns number of rows in inputObject image
*  Preconditions: image object has valid rows
*  Postconditions: returns an int of image object's number of rows
*/
int myImage::getRow() const{

	return inputObject.rows;

}

/* getCol: Accessor method that returns number of columns in inputObject image
*  Preconditions: image object has valid columns
*  Postconditions: returns an int of image object's number of columns
*/
int myImage::getCol() const{

	return inputObject.cols;

}

/* setRed: Mutator method that sets the red value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Sets the input red value with specified value input
*/
void myImage::setRed(int row, int col, int redValue) {

	if (redValue < 0 || redValue > getRow()) {

		throw exception("Red component in an image can only be between 0 and 255");

	}

		inputObject.pixels[row][col].red = redValue;
}

/* getRed: Accessor method that returns the red value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Returns the red value with specified value input at specified row and column
*/
int myImage::getRed(int row, int col) const {

	if (row < 0 || row > getRow() || col < 0 || col > getCol()) {

		throw exception("Red component in an image can only be between 0 and 255");

	}

	return inputObject.pixels[row][col].red;

}

/* setGreen: Mutator method that sets the green value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Sets the input green value with specified value input
*/
void myImage::setGreen(int row, int col, int greenValue) {

	if (greenValue < 0 || greenValue > getRow()) {

		throw exception("Green component in an image can only be between 0 and 255");

	}

	inputObject.pixels[row][col].green = greenValue;
}

/* getGreen: Accessor method that returns the green value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Returns the green value with specified value input at specified row and column
*/
int myImage::getGreen(int row, int col) const {

	if (row < 0 || row > getRow() || col < 0 || col > getCol()) {

		throw exception("Green component in an image can only be between 0 and 255");

	}

	return inputObject.pixels[row][col].green;

}

/* setBlue: Mutator method that sets the blue value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Sets the input blue value with specified value input
*/
void myImage::setBlue(int row, int col, int blueValue) {

	if (blueValue < 0 || blueValue > getRow()) {

		throw exception("Blue component in an image can only be between 0 and 255");

	}

	inputObject.pixels[row][col].blue = blueValue;
}

/* getBlue: Accessor method that returns the blue value of inputObject at specified row and column
*  Preconditions: parameter value must be greater than 0 and less than 255
*  Postconditions: Returns the blue value with specified value input at specified row and column
*/
int myImage::getBlue(int row, int col) const {

	if (row < 0 || row > getRow() || col < 0 || col > getCol()) {

		throw exception("Blue component in an image can only be between 0 and 255");

	}

	return inputObject.pixels[row][col].blue;

}

/* setPixel: Mutator method that sets pixel rgb values, at the specified row and col values
*  Preconditions: the input value must be between 0 - 255
*  Postconditions: sets the pixel's row, col, and pixel to specified input value
*				   Throws exception if row or column values are out of bounds
*				  
*/
void myImage::setPixel(int row, int col, int red, int green, int blue){

	if (row >= inputObject.rows || row < 0 || col >= inputObject.cols || col < 0) {

		throw exception("Parameters to set pixel out of bounds");

	}

	inputObject.pixels[row][col].red = red;
	inputObject.pixels[row][col].green = green;
	inputObject.pixels[row][col].blue = blue;

}

/* getPixel: Accessor method that returns the image object's pixel values at specified row and column value
*  Preconditions: row, col, and pixel are valid dimensions and not out of bounds
*  Postconditions : if row or column values are out of bounds, return a default pixel (set to black) otherwise, returns the pixel at specified location
*/
const pixel& myImage::getPixel(int row, int col) const{

	if (row >= inputObject.rows || row < 0 || col >= inputObject.cols || col < 0) {


		myImage e = myImage(1, 1);
		e.setPixel(0, 0, 0, 0, 0);
		return e.getPixel(0, 0);

	}

		return inputObject.pixels[row][col];

}

/* outputToFile: Method that calls writeGIF function from ImageLib.h to write the image object to specified file
*  Preconditions: filename is a valid filename to store the new gif image
*  Postconditions: creates a GIF image of the object image with a specified filename
*/
void myImage::outputToFile(string fileName) const{

	WriteGIF(fileName, inputObject);

}

/* operator!=: Not equal operator is overloaded to call == function and returns ! of the function
*  Preconditions: both image objects are valid images
*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
*/
bool myImage::operator!=(const myImage& otherObject) const {

	return !(*this == otherObject);

}

/* operator==: Equal operator is overloaded to compare image object to another image object input at each pixel rgb value
*  Preconditions: both image objects are valid images
*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
*/
bool myImage::operator==(const myImage& otherObject) const {

	if (inputObject.rows != otherObject.inputObject.rows || inputObject.cols != otherObject.inputObject.cols) {

		return false;

	}

	for (int row = 0; row < inputObject.rows; row++) {

		for (int col = 0; col < inputObject.cols; col++) {

			if (inputObject.pixels[row][col].red != otherObject.inputObject.pixels[row][col].red ||
				inputObject.pixels[row][col].green != otherObject.inputObject.pixels[row][col].green ||
				inputObject.pixels[row][col].blue != otherObject.inputObject.pixels[row][col].blue) {

				return false;

			}
		}
	}

	return true;
}

/* operator>: Greater than operator compares image object to another image object to see if the pixel rgb values are greater than original image object
*  Preconditions: both image objects are valid images
*  Postconditions: returns true if left side of image object has MORE pixels than right side of image object
*				   returns false if left side of image object has LESS pixels than right side of image object
*/
bool myImage::operator>(const myImage& image) const {

	return (inputObject.rows * inputObject.cols) > (inputObject.rows * inputObject.cols);

}

/* operator<: Less than operator compares image object to another image object to see if the pixel rgb values are less than original image object
*  Preconditions: both image objects are valid images
*  Postconditions: returns true if right side of image object has MORE pixels than left side of image object
*				   returns false if right side of image object has LESS pixels than left side of image object
*/
bool myImage::operator<(const myImage& image) const {

	return (inputObject.rows * inputObject.cols) < (inputObject.rows * inputObject.cols);

}

/* operator<<: overloaded cout to output image object's row and col values
*  Preconditions: input is a valid image object
*  Postconditions: outputs to console the dimensions of image object in number of rows and columns
*/
ostream& operator<<(ostream& output, const myImage& input) {

	output << "Number of rows: " << input.inputObject.rows << " Number of columns: " << input.inputObject.cols << endl;;

	return output;

}

/* mirror: Creates a new image object which copies original image object and returns the flipped image of the new image object
*  Preconditions: the image object contains a valid image
*  Postconditions: returns an image object with a mirrored image (left side pixels and right side pixels are swapped)
*/
myImage myImage::mirror() const {

	myImage mirror = *this;

	for (int row = 0; row < mirror.inputObject.rows; row++)
	{
		for (int col = 0; col < (mirror.inputObject.cols / 2); col++)
		{
			pixel temp = mirror.inputObject.pixels[row][col];
			mirror.inputObject.pixels[row][col] = mirror.inputObject.pixels[row][mirror.inputObject.cols - 1 - col];
			mirror.inputObject.pixels[row][mirror.inputObject.cols - 1 - col] = temp;
		}
	}
	return mirror;
}