/*
 *  header.h
 *
 *	ITCS 3112
 *	Project 4  : Image Editor
 *
 *  Created on : Oct 15, 2017
 *  Updated on : Oct 17, 2017
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

	private:
	int width, height, max, ** img_array;
};

// constructors implementation
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

// destructor implementation
Image::~Image(){
	cout << "\nDestructor Initiated...\nImage is now being deleted...";

	for (int i = height-1; i >= 0; i--) {
		delete[] img_array[i];  // deletes each rows in the pointer array
		img_array[i]=0;         // assigns each row to zero
	}
	delete [] img_array;        // deletes the pointer array
	img_array = 0;              // assigns the pointer to zero

}

// get methods implementation
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

// set methods implementation
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

// other methods implementation
void Image::buildImageDataset(int w, int h){
	cout << "\nWidth  : " << w << "\nHeight : " << h << endl;
	img_array = new int* [h];			//create rows of board for pointer array
    for(int row = 0; row < h; row++)
    	img_array[row] = new int[w*3];	//create columns of board for pointer array
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
		
		buildImageDataset(width,height);  // builds the 2d image pointer array
			
		// assigns the data from the input file to the pointer array
    	for (int r = 0; r < height; r++){
    		for(int col = 0; col < width*3; col++)
    			inFile >> img_array[r][col];
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

#endif