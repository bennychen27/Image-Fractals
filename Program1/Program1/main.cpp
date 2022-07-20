/*
main.cpp

Author: Benny Chen
Date: 1-11-2020
Section: CSS342 C

This source file uses ImageLib.h, ImageLib.lib, and reads in a test1.gif image to process and saves to folder
after being modified. Creates a copy image of image and mirrors it, and saves the new image to a file. The image
is then read back into a new image variable, and the two images are compared to see the number of differences
in pixel rgb values.

*/

#pragma once

#include <string>
#include <iostream>
#include "ImageLib.h"
using namespace std;

// forward declarations
void invert(image in);
void mirror(image in);
int compare(image in, image in2);

// main()
// Preconditions: test1.gif exists and is a valid GIF image to be read
// Postcondtions: test1output.gif and output.gif will be written which will contain both a modified image and
//                a mirror image, respectively. Will also compare the mirror image and a read-in of the mirror
//				  image and output to console the differences in pixel rgb values
int main() {

	// Read test1 image from file
	image input = ReadGIF("test1.gif");

	if (input.rows == 0) {

		cout << "Unable to open file: test1.gif" << endl;
		return -1;

	}

	// Modifies the image's pixel rgb values
	invert(input);

	// Create new image variable and copy image of input
	image newInput = CopyImage(input);

	// Creates a mirror-image (left side and ride side reversed)
	mirror(newInput);

	// Outputs the dimensions in rows and columns of image
	cout << "The dimensions of the image are: " << input.rows << 
		    " rows by " << input.cols << " columns." << endl; 
	WriteGIF("test1output.gif", input);
	WriteGIF("output.gif", newInput);

	// Creates new image variable of the mirror image and outputs the differences between the two images rgb values
	image mirrorInput = ReadGIF("output.gif");
	cout << "There are " << compare(newInput, mirrorInput) << " differences between the mirror image and"
		 << " the read-in mirror image" << endl;
	
	// Wait for user input before exiting
	system("PAUSE");
	DeallocateImage(input);
	DeallocateImage(newInput);
	return 0;

}

// invert: modifies the input image's pixel rgb values based on rows and columns
// Preconditions: the input image (in) has in.rows * in.cols pixels allocated
// Postconditions: the input image is modified such that the blue and red pixel colors are modified. Green is unchanged
//                 Accounts for overflow with red and underflow with blue
void invert(image in){

	for (int row = 0; row < in.rows; row++) {

		for (int col = 0; col < in.cols; col++) {

			if (in.pixels[row][col].blue - (row % 7) < 0) {

				in.pixels[row][col].blue = 0;

			}
			else if (in.pixels[row][col].red + (col % 9) > 255) {

				in.pixels[row][col].red = 255;

			}
			else {

				in.pixels[row][col].blue -= row % 7;
				in.pixels[row][col].red += col % 9;
				in.pixels[row][col].green;

			}
		}
	}
}

// mirror: mirrors the image of test1.gif where left side and right side are reversed
// Preconditions: the newInput image (in) has in.rows * in.cols pixels allocated and has the same number of rows and 
//                columns as input image
// Postconditions: Each input pixel has been swapped using a temp pixel variable and each pixel is reversed
void mirror(image in) {

	for (int row = 0; row < in.rows; row++) {

		for (int col = 0; col < in.cols / 2; col++) {

			int swapCol = in.cols - col - 1;

			pixel temp = in.pixels[row][col];
			in.pixels[row][col] = in.pixels[row][swapCol];
			in.pixels[row][swapCol] = temp;

		}
	}

}

// compare: Takes two image inputs and compares their pixel color values to see if there are differences. A single
//          color value difference increments the counter by 1
// Preconditions: in and in2 must have the same number of rows and columns to be compared
// Postconditions: Returns a counter of the differences between rgb values after comparing every pixel in both images
int compare(image in, image in2) {

	int count = 0;

	if (in.rows == in2.rows && in.cols == in2.cols) {

		for (int row = 0; row < in.rows; row++) {

			for (int col = 0; col < in.cols; col++) {

				if (in.pixels[row][col].red != in2.pixels[row][col].red) {

					count++;

				}

				else if (in.pixels[row][col].green != in2.pixels[row][col].green) {

					count++;

				}

				else if (in.pixels[row][col].blue != in2.pixels[row][col].blue) {

					count++;

				}

				else {

					continue;

				}
			}
		}
	}
	return count;
}