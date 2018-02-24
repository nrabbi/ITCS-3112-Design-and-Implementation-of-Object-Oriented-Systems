/*
 *  runner.cpp
 *
 *	ITCS 3112
 *	Project 4  : Image Editor
 *
 *  Created on : Oct 15, 2017
 *  Updated on : Oct 25, 2017
 *      Author : Nazmul Rabbi
 */

#include <iostream>
#include <string>
#include "header.h"
using namespace std;

int main() {
	string inFileName, outFileName; // variables to get the input and output file name from user input
	int option;
	
    // takes in the filename input from the user to define the input file name
    cout << "Note: Don't Include File Extension, only ppm files supported\nEnter the Input File Name: ";
    cin >> inFileName;
    cout << endl;

	Image img(inFileName); // this Image object creates an image using the file name input
    
    do {
        // menu to control the use the variable image effects
        cout << "\nOptions";
        cout << "\n-------";
        cout << "\n1: Flatten    Red  Effect";
        cout << "\n2: Grayscale       Effect";
        cout << "\n3: Horizontal Flip Effect";
        cout << "\n4: Negate     Blue Effect"; 
        cout << "\n5: Exit                  " << endl;
        
        // gets the user input on which effect they want to appy to the image
        cout << "\nYou Chose Option : ";
        cin >> option;
        cout << endl;
        
        if (option == 1)
            img.flattenRed();
        
        else if (option == 2) 
            img.toGrayscale();
        
        else if (option == 3)     
            img.flipHorizontal();
        
        else if (option == 4) 
            img.negateBlue();

    	if (option != 5){
        	// takes in the filename input from the user to define the output file name
            cout << "Note: Don't Include File Extension, will output as a ppm file\nEnter the Output File Name: ";
            cin >> outFileName;
        
        	img.writeImageToFile(outFileName);  // writes the output file as a ppm image
            img.revertToOriginalImage();        // reverts the image to the original processed image so one effect is not applied on top of another
    	}
    }while(option != 5);
    
	return 0;
}