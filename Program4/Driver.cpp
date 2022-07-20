/*
Driver.cpp

Author: Benny Chen
Date: 2-25-2020
Section: CSS342 C

This program reads a GIF image file and uses recursion to perform image segmentation
and writes it into an output GIF image file. The image is segmented into connected groups
of pixels based on its color attribute. The linked list data structure is used to create
the connected groups. Image is segmented by iterating through the image rows and columns ,
selecting a seed pixel and recursively examining the neighboring 4 pixels (2 pixels in case
of boundary pixels) that has close enough color to the seed pixel.

*/

#include <iostream>
#include <math.h>
#include "ImageLib.h"
#include "PixelList.h"
#include "myImage.h"

using namespace std;
#pragma once

/* isValid: Method returns boolean false if pixel has no input or if this pixel object
            and other pixel object are not equal, otherwise true
* Preconditions: all parameters are valid inputs
* Postconditions: verifies that the pixel at row and col are not already in a group and not out of bounds
*/
bool isValid(myImage& input, int row, int col, const pixel& seed) {

	if (row < 0 || col < 0 || row > input.getRow() || col > input.getCol()) {

		return false;

	}

	else {

		if (input.getPixel(row, col).blue == 0 && input.getPixel(row, col).green == 0 && input.getPixel(row, col).red == 0) {

			return false;

		}

		else {

			if ((abs(seed.red - input.getPixel(row, col).red) + 
				abs(seed.green - input.getPixel(row, col).green) + 
				abs(seed.blue - input.getPixel(row, col).blue)) < 100) {

				return true;

			}

			return false;
		}
	}


}

/* recur: Method that recursively adds a pixel at row, col, sets a new default pixel
          at the neighboring top, bottom, left and right pixel positions
* Preconditions: all parameters are valid inputs
* Postconditions: recursively goes through the image and finds a group, new pixel node is added and values
                  are set to default at row and col
*/
void recur(myImage& input, myImage& output, PixelList& group, int row, int col, const  pixel& seed) {

	if (!isValid(input, row, col, seed)) {

		return;

	}

	else {

		group.addPixelNode(input.getPixel(row, col), row, col);
		input.setPixel(row, col, 0, 0, 0);

		recur(input, output, group, row - 1, col, seed);
		recur(input, output, group, row + 1, col, seed);
		recur(input, output, group, row, col - 1, seed);
		recur(input, output, group, row, col + 1, seed);

	}

}

/* recursionContainer: Method that uses recursion to fill out segments in output, and writes to output.gif file
* Preconditions: input image is a valid input
* Postconditions: calls the recur function to search for and fills out segments in the output image object and writes the output
                  to console total number of segments found, the number of pixels in merged group and the average color value for merged group
*/
void recursionContainer(myImage input) {

	myImage output = myImage(input.getRow(), input.getCol());
	PixelList merged = PixelList();
	PixelList group = PixelList();
	int segmentCounter = 0;

	for (int row = 0; row < input.getRow(); row++) {

		for (int col = 0; col < input.getCol(); col++) {

			if (input.getPixel(row, col).blue == 0 && input.getPixel(row, col).green == 0 && input.getPixel(row, col).red == 0) {

				//segment already exists

			}

			else {

				segmentCounter++;
				pixel seed = input.getPixel(row, col);
				recur(input, output, group, row, col, seed);
				int outputRow = 0;
				int outputCol = 0;
				merged.merge(group);
				pixel average = group.averagePixels();

				while (group.getTopData(outputRow , outputCol) == 0) {

					output.setPixel(outputRow , outputCol, average.red, average.green, average.blue);

				}
			}
		}
	}


	output.outputToFile("output.gif");

	int mergedRed = merged.averagePixels().red;
	int mergedGreen = merged.averagePixels().green;
	int mergedBlue = merged.averagePixels().blue;

	cout << "total number of segments found: " << segmentCounter << "\nnumber of pixels in merged group: " << 
		     merged.size() << "\naverage color of red, green, blue values in merged group: " << mergedRed << ", " << 
		     mergedGreen << ", " << mergedBlue << endl;

}

/*
main: Main method that reads the test4.gif as input image. Creates an output image
using  input image. Calls the recursionContainer method to create image segmentation.
The output image modified after segmentation is written to output.gif file.

Precondition: A valid test4.gif file exists
Postcondition: An output image file output.gif is written to file
*/
void main() {

	myImage input("test4.gif");
	recursionContainer(input);

}