/*
 *  header.h
 *
 *	ITCS 3112
 *	Project 4  : Image Editor
 *
 *  Created on : Oct 15, 2017
 *  Updated on : Oct 25, 2017
 *      Author : Nazmul Rabbi
 */

#ifndef HEADER_H
#define HEADER_H
#include <fstream>
#include <string>
using namespace std;

class Image {
	public:
	/**
	 	*  Constructor initializes an empty Image
	 	*  @param none
	*/
	Image(void);
	
	/**
	 	*  Constructor initializes the input file of the Image<br>
	 	*  Constructor Allocates Image Data based on input file
	 	*  @param input_file
	*/
	Image(string input_file);
	
	/**
	 	*  Constructor initializes width and height of the Image<br>
	 	*  Constructor Allocates Image Data based on width and height
	 	*  @param w
	 	*  @param h
	*/
	Image(int w, int h);

	/**
	 	*  Destructor deallocates the Image data 
	 	*  @param none
	*/
	~Image(void);

	/**
		 *	gets the width of the Image
		 *  @param none
	  	 *	@return width
	*/
	int getWidth(void);
	
	/**
		 *	gets the height of the Image
		 *  @param none
	  	 *	@return height
	*/
	int getHeight(void);
	
	/**
		 *	gets the max value of the Image
		 *  @param none
	  	 *	@return max
	*/
	int getMax(void);
	
	/**
		 *	gets the pixel of the Image
		 *  @param col
		 *  @param row
	  	 *	@return img_array[row][col]
	*/
	int getImagePixel(int col, int row);

	/**
		 *	sets the width of the Image
		 *  @param w
	  	 *	@return none
	*/
	void setWidth(int w);
	
	/**
		 *	sets the height of the Image
		 *  @param h
	  	 *	@return none
	*/
	void setHeight(int h);
	
	/**
		 *	sets the max value of the Image
		 *  @param m
	  	 *	@return none
	*/
	void setMax(int m);
	
	/**
		 *	sets the pixel of the Image 
		 *  @param col
		 *  @param row
		 *  @param pixel
	  	 *	@return none
	*/
	void setImagePixel(int col, int row, int pixel);

	/**
		 *	Builds the Image Dataset<br>
		 *  Creates the 2D pointer array based on the given width and height value
		 *  @param w
		 *  @param h
	  	 *	@return none
	*/
	void buildImageDataset(int w, int h);
	
	/**
		 *	Builds the Image from input file<br>
		 *  Reads the file and stores the width, height, max value and individual pixels of the Image
		 *  @param in_file
	  	 *	@return none
	*/
	void buildImageFromFile(string in_file);
	
	/**
		 *	Draws a red band across the Image
		 *  @param row
		 *  @param length
	  	 *	@return none
	*/
	void drawRedBand(int row, int length);
	
	/**
		 *	Writes a ppm Image output file 
		 *  @param out_file
	  	 *	@return none
	*/
	void writeImageToFile(string out_file);
	
	/**
		 *	Applies a Grayscale Effect across the Image
		 *  @param none
	  	 *	@return none
	*/
	void toGrayscale(void);
	
	/**
		 *	Reverses the Image Horizontally
		 *  @param none
	  	 *	@return none
	*/
	void flipHorizontal(void);
	
	/**
		 *	Applies a Negate Blue Effect across the Image
		 *  @param none
	  	 *	@return none
	*/
	void negateBlue(void);
	
	/**
		 *	Applies a Flatten Red Effect across the Image
		 *  @param none
	  	 *	@return none
	*/
	void flattenRed(void);
	
	/**
		 *	Reverts the modified image back to the original processed image
		 *  @param none
	  	 *	@return none
	*/
	void revertToOriginalImage(void);
	
	private:
	int width, height, max, ** img_array, ** img_backup;
};

// constructors
Image::Image(void){
	cout << "An Empty Image is being initialized";
}

Image::Image(string input_file){
	cout << input_file << ".ppm is being initialized\n";
	buildImageFromFile(input_file);
}

Image::Image(int w, int h){
	cout << "A new Image is being initialized\n";
	width = w;
	height = h;
	buildImageDataset(w,h);
}

// destructor
Image::~Image(){
	cout << "Destructor Initiated...\nImage is now being deleted...";

	for (int i = height-1; i >= 0; i--) {
		// deletes each rows in the pointer array
		delete[] img_array[i];  
		delete[] img_backup[i];
		
		// assigns each row to zero
		img_array[i]=0;         
		img_backup[i]=0;
	}
	// deletes the pointer array
	delete [] img_array;        
	delete [] img_backup;
	
	// assigns the pointer to zero
	img_array = 0;              
	img_backup = 0;
}

// get methods
int Image::getWidth(void){
	return width;
}

int Image::getHeight(void){
	return height;
}

int Image::getMax(void){
	return max;
}

int Image::getImagePixel(int col, int row){
	return img_array[row][col];
}

// set methods
void Image::setWidth(int w){
	width = w;
}

void Image::setHeight(int h){
	height = h;
}

void Image::setMax(int m){
	max = m;
}

void Image::setImagePixel(int col, int row, int pixel){
	img_array[row][col] = pixel;
}

// other methods
void Image::buildImageDataset(int w, int h){
	cout << "\nWidth  : " << w << "\nHeight : " << h << endl;
	
	//create rows of board for pointer array
	img_array = new int* [h];			
    img_backup = new int* [h];
    
    //create columns of board for pointer array
    for(int row = 0; row < h; row++){
    	img_array[row] = new int[w*3];	
		img_backup[row] = new int[w*3];
    }
}

void Image::buildImageFromFile(string in_file){
	string garbage; 	// creates a temporary variable to hold un-needed data
	ifstream inFile;	// creates a input file stream variable to read the ppm file
	
	inFile.open(in_file + ".ppm"); // opens the input file
	
	// checks if the file that is specified is valid 
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    else {
        cout << in_file << ".ppm was read successfully\n";
        
        inFile >> garbage;	// grabs un-needed data from the input file and sets it aside
		inFile >> width;	// reads the width of the image from the input file
		inFile >> height;	// reads the height of the image from the input file
		inFile >> max;  	// reads the max value of the image from the input file
		
		buildImageDataset(width, height);  // builds the 2d image pointer array
			
		// assigns the data from the input file to the pointer array
    	for (int r = 0; r < height; r++){
    		for(int col = 0; col < width*3; col++){
    			inFile >> img_array[r][col];
    			img_backup[r][col] = img_array[r][col];
    		}
    	}
    	inFile.close(); // closes the input file stream
    }
}

void Image::drawRedBand(int row, int length){
	int position_counter = 0;	// this variable makes sure red pixels are not drawn out of the dataset bounds
	int counter = 0;			// this variable makes sure that the amount of red pixels drawn on the image is at least equal to the given length
	
	while (counter < length && position_counter < width*3){
		setImagePixel(position_counter+1, row, 0); // setting the G values from RGB triplets to 0
		setImagePixel(position_counter+2, row, 0); // setting the B values from RGB triplets to 0
		
		position_counter+=3;	// moves three positions forward due to the RGB triplet structure
		counter++;				// keeps track of the amount of red pixels drawn in the image
	}
}

void Image::writeImageToFile(string out_file){
	ofstream outFile;					// creates a output file stream variable to output the ppm image file
	outFile.open(out_file + ".ppm");	// creates the output file

    outFile << "P3" << endl;                	// writes the header into the output file
    outFile << width << " ";                    // writes the width value of the dataset into the output file
    outFile << height << endl << max << " ";    // writes the height and the max value of the dataset

    // outputs the data of array to the output file
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width*3; col++){
            outFile << img_array[row][col] << " ";
        }
    }

    outFile.close(); // closes the output file stream
}

void Image::toGrayscale(void){
	for (int r = 0; r < height; r++){
    	for(int col = 0; col < width*3; col+=3){
    		float rValue = getImagePixel(col,r);	// gets the value of the R pixel value at a given pixel
    		float gValue = getImagePixel(col+1,r);	// gets the value of the G pixel value at a given pixel
    		float bValue = getImagePixel(col+2,r);	// gets the value of the B pixel value at a given pixel
    		
    		// calcuates the new pixel value with the current RGB values
    		float calculation = (rValue * 0.299) + (gValue * 0.587) + (0.114 * bValue);
    		
    		setImagePixel(col, r, calculation);		// sets the new value of the R pixel at a given pixel
    		setImagePixel(col+1, r, calculation);	// sets the new value of the G pixel at a given pixel
    		setImagePixel(col+2, r, calculation);	// sets the new value of the B pixel at a given pixel
    	}
    }	
}

void Image::flipHorizontal(void){
	for (int r = 0; r < height; r++){
		int leftCounterR = 0, rightCounterR = (width*3)-3;	// sets/resets the start and end positions of the R pixel at a given image
		int leftCounterG = 1, rightCounterG = (width*3)-2;	// sets/resets the start and end positions of the G pixel at a given image
		int leftCounterB = 2, rightCounterB = (width*3)-1;	// sets/resets the start and end positions of the B pixel at a given image

    	while(leftCounterR < rightCounterR){
    		// gets the R value at a given pixel
			int leftValueR = getImagePixel(leftCounterR, r);
			int rightValueR = getImagePixel(rightCounterR, r);
			
			// sets the R value at a given pixel
			setImagePixel(leftCounterR, r, rightValueR);
			setImagePixel(rightCounterR, r, leftValueR);
			
			// moves to the next/previous R value
			leftCounterR+=3; 
			rightCounterR-=3;
    	}
    	
    	while(leftCounterG < rightCounterG){
    		// gets the G value at a given pixel
			int leftValueG = getImagePixel(leftCounterG, r);
			int rightValueG = getImagePixel(rightCounterG, r);
			
			// sets the G value at a given pixel
			setImagePixel(leftCounterG, r, rightValueG);
			setImagePixel(rightCounterG, r, leftValueG);
			
			// moves to the next/previous G value
			leftCounterG+=3; 
			rightCounterG-=3;
    	}
    	
    	while(leftCounterB < rightCounterB){
			// gets the B value at a given pixel
			int leftValueB = getImagePixel(leftCounterB, r);
			int rightValueB = getImagePixel(rightCounterB, r);
			
			// sets the B value at a given pixel
			setImagePixel(leftCounterB, r, rightValueB);
			setImagePixel(rightCounterB, r, leftValueB);
			
			// moves to the next/previous B value
			leftCounterB+=3; 
			rightCounterB-=3;
    	}
    }
}

void Image::negateBlue(void){
	int calculation; // initializes this variable to store the calculation data
	
	// loops through the array and modifies the previous pixel values with the new updated values
	for (int r = 0; r < height; r++){
    	for(int col = 2; col < width*3; col+=3){
    		calculation = abs(255 - getImagePixel(col,r));
    		setImagePixel(col, r, calculation);
    	}
    }	
}

void Image::flattenRed(void){
	// loops through the array and modifies the previous pixel values with the new updated values
	for (int r = 0; r < height; r++){
	for (int r = 0; r < height; r++){
    	for(int col = 0; col < width*3; col+=3)
    		setImagePixel(col, r, 0);
    }	
}

void Image::revertToOriginalImage(void){
	// loops through the array and modifies the already modified pixel values with original pixel values
	for (int r = 0; r < height; r++){
	for (int r = 0; r < height; r++){
    	for(int col = 0; col < width*3; col++)
    		setImagePixel(col, r, img_backup[r][col]);
    }
}

#endif