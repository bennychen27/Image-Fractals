/*
main.cpp

Author: Benny Chen
Date: 1-23-2020
Section: CSS342 C

This source file uses myImage.h and reads in a test2.gif image to process and modifies the rgb values of the image. Mirrors it vertically
so the left and right side are swapped. Outputs the new gif image to 'output.gif'. Displays in console the number of differences in pixels
between the old and new gif images 

*/

#pragma once

#include "myImage.h"
#include <iostream>

using namespace std;

//forward declarations
void modify(myImage&);
void compare(myImage& oldObject, myImage& newObject);

/* main()
*  Preconditions: test2.gif is a valid gif image input
*  Postconditions: once test2.gif has been modified and mirrored, it will be written as 'output.gif' and read back into the program as a
*                  new image object. the old and new gif image objects are compared and the differences in pixels are outputed to console
*/
int main() {
	
	myImage image("test2.gif");

	cout << image << endl; //output to console the size in rows and columns of test2.gif

	myImage mirrorObject = image.mirror();

	modify(mirrorObject);

	mirrorObject.outputToFile("output.gif"); //output the mirrored and modified gif image to specified location

	myImage newImage("output.gif"); //read in the new gif image as a new object

	compare(mirrorObject, newImage); //compare and print out the number of differences in pixels between the two old and new gif objects
}

/* modify()
* Preconditions: image object is a valid image
* Postconditions: returns an image object with the image modified by adding col mod 9 to red color and subtracting row mod 7 to blue color
*				  if underflow < 0, set to 0
*				  if overflow > 255, set to 255.
*/
void modify(myImage& inputObject){

	for (int row = 0; row < inputObject.getRow(); row++){

		for (int col = 0; col < inputObject.getCol(); col++){

			if (inputObject.getBlue(row, col) - (row % 7) < 0){

				inputObject.setBlue(row, col, 0);

			}

			else {
				inputObject.setBlue(row, col, inputObject.getBlue(row, col) - (row % 7));

			}

			if (inputObject.getRed(row, col) + (col % 9) > 255){

				inputObject.setRed(row, col, 255);

			}
			else {

				inputObject.setRed(row, col, inputObject.getRed(row, col) + (col % 9));

			}
		}
	}
}

/* compare()
* Preconditions: the two gif image objects are valid and have valid rows, columns, and pixels allocated
*			     with the same size of rows and columns
* Postconditions: outputs to console the number of differeneces in pixels between the old and new gif image objects
*/
void compare(myImage& oldObject, myImage& newObject) {

	if (oldObject == newObject) {

		cout << "There are no differences between the two images." << endl;

	}
	else {

		int count = 0;

		for (int row = 0; row < oldObject.getRow(); row++) {

			for (int col = 0; col < oldObject.getCol(); col++) {

				if (oldObject.getRed(row, col) != newObject.getRed(row, col) ||
					oldObject.getBlue(row, col) != newObject.getBlue(row, col) ||
					oldObject.getGreen(row, col) != newObject.getGreen(row, col)) {

					count++;

				}
			}
		}

		cout << "The number of differences in pixels between the old and new gif image objects is: " << count << endl;
	}
}