/*
 *  runner.cpp
 *
 *	ITCS 3112
 *	Project 4  : Image Editor
 *
 *  Created on : Oct 15, 2017
 *  Updated on : Oct 17, 2017
 *      Author : Nazmul Rabbi
 */

#include <iostream>
#include <string>
#include "header.h"
using namespace std;

int main() {
	string inFileName, outFileName; // variables to get the input and output file name from user input
	int rowInput, pixelLength;       // variables to get the row and length of the red band to be drawn on the image

    // takes in the filename input from the user to define the input file name
    cout << "Note: Don't Include File Extension, only ppm files supported\nEnter the Input File Name: ";
    cin >> inFileName;
    cout << endl;

	Image img(inFileName); // this Image object creates an image using the file name input
	
    // gets user input to where they want to draw the red band in the image
    cout << "\nDrawing Red Band\n----------------\nNote: Row starts at 0 and ends at " << img.getHeight()-1 << "\nEnter Row Value : ";
    cin >> rowInput;
    
    // gets user input on the length of the red band
    cout << "Enter the length of the Red Band : ";
    cin >> pixelLength;
    
    img.drawRedBand(rowInput, pixelLength); // draws the red band across the image
    
	// takes in the filename input from the user to define the output file name
    cout << "\nNote: Don't Include File Extension, will output as a ppm file\nEnter the Output File Name: ";
    cin >> outFileName;

	img.writeImageToFile(outFileName); // writes the output file as a ppm image

	return 0;
}