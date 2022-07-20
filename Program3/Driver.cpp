/*
Driver.cpp

Author: Benny Chen
Date: 2-5-2020
Section: CSS342 C

This source file uses the image class and Rectangle class to create an image fractal object using recursion methods. Reads in an image gif and outputs the file
after being modified. Has functions to decrease size, mirror, and to create fractal images of the decreased image size and mirrored image sizes. The image is 
divided into 4 partitions, top left, top right, bottom left, and bottom right. The top left partition is a decreased size of original image, the top right
partition is a fractal of the decreased image size using the top left partition as input. The bottom left is a fractal of the decreased image size using the
top left partition as input. The bottom right partition is a decreased size of the original image, but flipped both vertically and horizontally as well.

*/

#include "Rectangle.h"
#include "myImage.h"
#include <iostream>

using namespace std;

/* fractalRecursion: Creates a fractal image with recursion by separating original image into 4 rectangular partitions
*  Preconditions: input image must exist, output retains the same image object as original image object, rectObject has same dimension values
                 as the original rectangle object
*  Postconditions: The fractal recursive image is output to 'output.gif' file
*/
void fractalRecursion(myImage& input, myImage& output, Rectangle rectObject) {

	// midpoints are used to determine the top left, top right, bottom left, and bottom right partitions of the rectangle object
	int colMidpoint = (rectObject.getBottomRowIndex() - rectObject.getTopRowIndex()) / 2;
	int rowMidpoint = (rectObject.getBottomColIndex() - rectObject.getTopColIndex()) / 2;

	//base case
	if (rectObject.getBottomRowIndex() - rectObject.getTopRowIndex() <= 1 && 
		rectObject.getBottomColIndex() - rectObject.getTopColIndex() <= 1) {

		return;

	}

	//original image divided into 4 partitions
	Rectangle topLeftPartition = Rectangle();
	Rectangle topRightPartition = Rectangle();
	Rectangle bottomLeftPartition = Rectangle();
	Rectangle bottomRightPartition = Rectangle();

	topLeftPartition.setTopRowIndex(rectObject.getTopRowIndex());
	topLeftPartition.setTopColIndex(rectObject.getTopColIndex());
	topLeftPartition.setBottomRowIndex(rectObject.getTopRowIndex() + colMidpoint);
	topLeftPartition.setBottomColIndex(rectObject.getTopColIndex() + rowMidpoint);

	topRightPartition.setTopRowIndex(rectObject.getTopRowIndex() + colMidpoint);
	topRightPartition.setTopColIndex(rectObject.getTopColIndex());
	topRightPartition.setBottomRowIndex(rectObject.getBottomRowIndex());
	topRightPartition.setBottomColIndex(rectObject.getBottomColIndex() - rowMidpoint);

	bottomLeftPartition.setTopRowIndex(rectObject.getTopRowIndex());
	bottomLeftPartition.setTopColIndex(rectObject.getTopColIndex() + rowMidpoint);
	bottomLeftPartition.setBottomRowIndex(rectObject.getBottomRowIndex() - colMidpoint);
	bottomLeftPartition.setBottomColIndex(rectObject.getBottomColIndex());

	bottomRightPartition.setTopRowIndex(rectObject.getTopRowIndex() + colMidpoint);
	bottomRightPartition.setTopColIndex(rectObject.getTopColIndex() + rowMidpoint);
	bottomRightPartition.setBottomRowIndex(rectObject.getBottomRowIndex());
	bottomRightPartition.setBottomColIndex(rectObject.getBottomColIndex());

	//Creates small fractal images of the decreased size image
	for (int row = topLeftPartition.getTopRowIndex(); row < topLeftPartition.getBottomRowIndex(); row++) {

		for (int col = topLeftPartition.getTopColIndex(); col < topLeftPartition.getBottomColIndex(); col++) {

			pixel pixel1 = output.getPixel(2 * (row - topLeftPartition.getTopRowIndex()), 2 * (col - topLeftPartition.getTopColIndex()));
			pixel pixel2 = output.getPixel(2 * (row - topLeftPartition.getTopRowIndex()) + 1, 2 * (col - topLeftPartition.getTopColIndex()));
			pixel pixel3 = output.getPixel(2 * (row - topLeftPartition.getTopRowIndex()), 2 * (col - topLeftPartition.getTopColIndex()) + 1);
			pixel pixel4 = output.getPixel(2 * (row - topLeftPartition.getTopRowIndex()) + 1, 2 * (col - topLeftPartition.getTopColIndex()) + 1);

			input.setRed(row, col, (pixel1.red + pixel2.red + pixel3.red + pixel4.red) / 4);
			input.setGreen(row, col, (pixel1.green + pixel2.green + pixel3.green + pixel4.green) / 4);
			input.setBlue(row, col, (pixel1.blue + pixel2.blue + pixel3.blue + pixel4.blue) / 4);
			
		}
	}

	//Uses the decreased size image and flips the pixel values at specified row and col
	for (int row = topLeftPartition.getTopRowIndex(); row < topLeftPartition.getBottomRowIndex(); row++) {

		for (int col = topLeftPartition.getTopColIndex(); col < topLeftPartition.getBottomColIndex(); col++) {

			pixel pixel1 = input.getPixel(row, col);
			input.setPixel(bottomRightPartition.getBottomRowIndex() - 1 - row + topLeftPartition.getTopRowIndex(),
				           bottomRightPartition.getBottomColIndex() - 1 - col + topLeftPartition.getTopColIndex(), pixel1);

		}
	}

	//Creates smaller images of original image
	myImage newOutput = myImage(output);

	for (int row = 0; row < (rectObject.getBottomRowIndex() - rectObject.getTopRowIndex() + 1) / 2; row++) {

		for (int col = 0; col < (rectObject.getBottomColIndex() - rectObject.getTopColIndex() + 1) / 2; col++) {

			pixel pixel1 = newOutput.getPixel(2 * row, 2 * col);
			pixel pixel2 = newOutput.getPixel(2 * row + 1, 2 * col);
			pixel pixel3 = newOutput.getPixel(2 * row, 2 * col + 1);
			pixel pixel4 = newOutput.getPixel(2 * row + 1, 2 * col + 1);

			newOutput.setRed(row, col, (pixel1.red + pixel2.red + pixel3.red + pixel4.red) / 4);
			newOutput.setGreen(row, col, (pixel1.green + pixel2.green + pixel3.green + pixel4.green) / 4);
			newOutput.setBlue(row, col, (pixel1.blue + pixel2.blue + pixel3.blue + pixel4.blue) / 4);
			
		}
	}

	fractalRecursion(input, newOutput, bottomLeftPartition);
	fractalRecursion(input, newOutput, topRightPartition);

}

/* main: Reads "test3.gif" from file to create an image object. Initializes a rectangle oject and calls the fractalRecursion function to 
         create 4 partitions of a reduced or inverted version of the original image
* Preconditions: "test3.gif" exists and is a valid image file
* Postconditions: "output.gif" is output and written to file 
*/
int main() {
	myImage input = myImage("test3.gif");

	Rectangle rectangle = Rectangle();
	rectangle.setTopRowIndex(0);
	rectangle.setTopColIndex(0);
	rectangle.setBottomRowIndex(input.getRow());
	rectangle.setBottomColIndex(input.getCol());

	myImage temp = myImage(input);
	fractalRecursion(input, temp, rectangle);

	input.outputToFile("output.gif");

}