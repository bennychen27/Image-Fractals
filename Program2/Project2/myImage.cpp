/*
myImage.cpp

Author: Benny Chen
Date: 1-23-2020
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

/* Constructor Method:
* Preconditions: fileName is a valid file name
* Postconditions: a newImage object is created from the file being read
*/
myImage::myImage(string fileName) {

	inputObject = ReadGIF(fileName);

}

/* Constructor Method:
* Preconditions: rows and columns are natural numbers (positive integers starting from 0)
* post-conditions: a newImage object is created with a specified number of rows and columns.
*                  The object image is blank and black
*/
myImage::myImage(int row, int col) {

	inputObject = CreateImage(row, col);

}

/* Copy Constructor Method:
* Preconditions: image is a valid image
* Postconditions: a newImage object is created which is a copy of the old image
*/
myImage::myImage(const myImage& newObject) {

	inputObject = CopyImage(newObject.inputObject);

}

/* Destructor Method:
* Preconditions: the image object cant be null
* Postconditions: the image object is deallocated, rows and columns are set to 0 and pixels to nullptr
*/
myImage::~myImage() {

	DeallocateImage(inputObject);

}

/* Preconditions: input object is valid and cant be null
*  Postconditions: returns an deep copy image object that is equal to the 'this' object
*/
const myImage& myImage::operator=(const myImage& newObject) {

	if (this != &newObject) {

		DeallocateImage(inputObject);
		inputObject = CopyImage(newObject.inputObject);

	}

	return *this;
}

/* Preconditions: image object has valid rows
*  Postconditions: returns an int of image object's number of rows
*/
int myImage::getRow() const{

	return inputObject.rows;

}

/* Preconditions: image object has valid columns
*  Postconditions: returns an int of image object's number of columns
*/
int myImage::getCol() const{

	return inputObject.cols;

}

/* Preconditions: the input value must be between 0 - 255
*  Postconditions: sets the pixel's row, col, and pixel to specified input value
				  if underflow < 0, set to 0
				  if overflow > 255, set to 255.
*/
void myImage::setPixel(int row, int col, pixel in){

	inputObject.pixels[row][col] = in;

}

/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
*  Postconditions : returns the pixel at specified location
*/
pixel myImage::getPixel(int row, int col) const {

	return inputObject.pixels[row][col];

}

/* Preconditions: the input value must be between 0 - 255
*  Postconditions: sets the pixel's red number to specified input value
				  if underflow < 0, set to 0
				  if overflow > 255, set to 255.
*/
void myImage::setRed(int x, int y, int value){

	inputObject.pixels[x][y].red = value;

}

/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
*  Postconditions : returns the pixel's red number at specified location
*/
int myImage::getRed(int row, int col) const{

	return getPixel(row, col).red;

}

/* Preconditions: the input value must be between 0 - 255
*  Postconditions: sets the pixel's green number to specified input value
				  if underflow < 0, set to 0
				  if overflow > 255, set to 255.
*/
void myImage::setGreen(int row, int col, int value){

	inputObject.pixels[row][col].green = value;

}

/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
*  Postconditions : returns the pixel's green number at specified location
*/
int myImage::getGreen(int row, int col) const{

	return getPixel(row, col).green;

}

/* Preconditions: the input value must be between 0 - 255
*  Postconditions: sets the pixel's blue number to specified input value
				  if underflow < 0, set to 0
				  if overflow > 255, set to 255.
*/
void myImage::setBlue(int row, int col, int value){

	inputObject.pixels[row][col].blue = value;

}

/* Preconditions: row, col, and pixel are valid dimensions and not out of bounds
*  Postconditions : returns the pixel's blue number at specified location
*/
int myImage::getBlue(int row, int col) const{

	return getPixel(row, col).blue;

}

/* Preconditions: filename is a valid filename to store the new gif image
*  Postconditions: creates a GIF image of the object image with a specified filename
*/
void myImage::outputToFile(string filename) const{

	WriteGIF(filename, inputObject);

}


/* Preconditions: both image objects are valid images
*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
*/
bool myImage::operator!=(const myImage& otherObject) const {

	return !(*this == otherObject);

}

/* Preconditions: both image objects are valid images
*  Postconditions: returns true if both image objects are the same size and pixels, otherwise false
*/
bool myImage::operator==(const myImage& otherObject) const {

	if (inputObject.rows * inputObject.cols != otherObject.inputObject.rows != otherObject.inputObject.cols) {

		return false;

	}

	for (int row = 0; row < this->getRow(); row++) {

		for (int col = 0; col < this->getCol(); col++) {

			if (this->getBlue(row, col) != otherObject.getBlue(row, col) || this->getRed(row, col) != otherObject.getRed(row, col) ||
				this->getGreen(row, col) != otherObject.getGreen(row, col)) {

				return true;

			}
		}
	}

	return true;
}

/* Preconditions: both image objects are valid images
*  Postconditions: returns true if left side of image object has MORE pixels than right side of image object
				   returns false if left side of image object has LESS pixels than right side of image object
*/
bool myImage::operator>(const myImage& image) const {

	return (inputObject.rows * inputObject.cols) > (inputObject.rows * inputObject.cols);

}

/*
	/* Preconditions: both image objects are valid images
	*  Postconditions: returns true if right side of image object has MORE pixels than left side of image object
					   returns false if right side of image object has LESS pixels than left side of image object
	*/
bool myImage::operator<(const myImage& image) const {

	return (inputObject.rows * inputObject.cols) < (inputObject.rows * inputObject.cols);

}

/* Preconditions: input is a valid image object
*  Postconditions: outputs to console the dimensions of image object in number of rows and columns
*/
ostream& operator<<(ostream& output, const myImage& input) {

	output << "Number of rows: " << input.inputObject.rows << " Number of columns: " << input.inputObject.cols;

	return output;

}

/* Preconditions: the image object contains a valid image
*  Postconditions: returns an image object with a mirrored image (left side pixels and right side pixels are swapped)
*/
myImage myImage::mirror()
{
	for (int row = 0; row < getRow(); row++)
	{
		for (int col = 0; col < (getCol() / 2); col++)
		{
			pixel temp = getPixel(row, col);
			setPixel(row, col, getPixel(row, getCol() - 1 - col));
			setPixel(row, getCol() - 1 - col, temp);
		}
	}
	return *this;
}