//  P2: Mountain Path
//  Nazmul Rabbi
//  ITCS 3112
//  Last Updated 9/15/17 Friday 4:24pm
// 	Structure
//  Step 1 -> Reads the file
//  Step 2 -> Extract the data from file and store it into an array
//  Step 3 -> Outputs the data from an array and outputs it to a ppm image
//  Step 4 -> The output image is then read and passed through the greedy algorithm
//  Step 5 -> The greedy algorithm calculates the shortest elevation path
//  Step 6 -> Then the shortest elevation path is drawn over the original image and is outputted to a separate file

#include <iostream>
#include <fstream>
using namespace std;

int  randNum(int min, int max); 															 	// initializes the function that generates a random number
void readData(ifstream & inFile, int myArray[], int & max);									 	// initializes the function that reads and stores the data as well as finds the max value in the dataset
void findSize(int & width, int & height, int & size, ifstream & inFile); 					   	// initializes the function that finds the width, height, size of the dataset
void outputData(ifstream & inFile, ofstream & outFile, int & max, int myArray[], int size);   	// initializes the function that output's the data after reading the original dataset
void findElevationPath(ifstream & inFile, int size, int width, int height, int myArray[]);    	// initializes the function that finds the lowest elevation path of the dataset

int main() {
    srand(time(0)); 					   	// initializes the random number
    ifstream inFile; 					    // initializes the input file stream
    ofstream outFile; 					    // initializes the output file stream
    string inFileName, outFileName; 	   	// initializes the variables that carries the name of the input & output file
    int width, height, size, max = 0; 	   	// initializes the variables that carries the width, height, size and max value of the dataset

    // takes in the filename input from the user to define the input file name
    cout << "Note: Don't Include File Extension, only dat files supported\nEnter the Input File Name: ";
    cin >> inFileName;
    cout << endl;

    // takes in the filename input from the user to define the output file name
    cout << "Note: Don't Include File Extension, will output as a ppm file\nEnter the Output File Name: ";
    cin >> outFileName;
    cout << endl;

    inFile.open(inFileName + ".dat"); 		// opens the input file as stated by the user input
    findSize(width, height, size, inFile);	// calls the findSize function to find the width, height and size of the data
    inFile.close(); 						// closes the input file

    int myArray[size];						// initializes the array to store the dataset
    inFile.open(inFileName + ".dat"); 	 	// opens the file as stated by the user input
    readData(inFile, myArray, max);		   	// reads data from file and store it into an array
    inFile.close();						  	// closes the input file

    inFile.open(inFileName + ".dat");					// opens the input file as stated by the user input
    outFile.open(outFileName + ".ppm");					// creates the output file as stated by the user input
    outputData(inFile, outFile, max, myArray, size);	// outputs data to a ppm file
    inFile.close();										// closes the input file
    outFile.close();									// closes the output file

    inFile.open(outFileName +".ppm");							// opens the input file as stated by the user input
    findElevationPath(inFile, size, width, height, myArray);	// finds the lowest elevation path
    outFile.open(outFileName +"_elevation.ppm");				// creates a separate output file to draw the lowest elevated path

    // outputs the data that draws the elevation path in a separate file
    outFile << "P3" << endl << width << " " << height << endl << max << " ";
    for(int i=1; i<size; i++){
        outFile << myArray[i] << " ";
    }

    inFile.close();		// closes the input file
    outFile.close();	// closes the output file

    cout << "Program terminated...\n";

    return 0;
}

// generates the random number
int randNum(int min, int max){
    return rand() % max + min;
}

void readData(ifstream & inFile, int myArray[], int & max){
    int readCounter = 1; // initializes the counting variable that helps to store the data from the input file to the created array

    // runs a loop to read the file until the end of line in the input file
    while (!inFile.eof()) {
        inFile >> myArray[readCounter];
        myArray[readCounter+1] = myArray[readCounter];
        myArray[readCounter+2] = myArray[readCounter];

        // finds the max value by comparing all the values in the dataset and stores the maximum into the max variable
        if (max < myArray[readCounter])
            max = myArray[readCounter];

        if (max < myArray[readCounter+1])
            max = myArray[readCounter+1];

        if (max < myArray[readCounter+2])
            max = myArray[readCounter+2];

        readCounter+=3; // counter to control the flow of the loop
    }

    myArray[0] = max; 								// assigns the max value as the first value in the data array
    cout << "Max Value: " << max << endl << endl; 	// outputs the max value to the console
}

void findSize(int & width, int & height, int & size, ifstream & inFile){
    int input = 0; // initializes the temporary variable that helps to store width and height data into a separate variable

    // checks if the filename the user entered into the console is valid
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    else {
        cout << "File was opened successfully!\n\n";
    }

    // stores the value of the width and height from the input file with the help of input temporary variable
    inFile >> input;
    width = input;
    inFile >> input;
    height = input;

    cout << "Width: " << width << "\nHeight: " << height << endl; 	// outputs the Width and Height values to console
    size = (width*height*3)+1; 										// calculates the size of the array
    cout << "Size of Array: " << size << endl; 						// outputs the size of the array into the console
}

void outputData(ifstream & inFile, ofstream & outFile, int & max, int myArray[], int size){
    int input = 0; // initializes the temporary variable that helps to output width and height data into the output file

    outFile << "P3" << endl;                // writes the header into the output file
    inFile >> input;						// grabs the width of the dataset from input file
    outFile << input << " ";				// writes the width value of the dataset into the output file
    inFile >> input;						// grabs the height of the dataset from input file
    outFile << input << endl << max << " ";	// writes the height and the max value of the dataset into the output file

    // here input variable is making sure garbage data is not being written into the output file by holding on the un-needed data
    inFile >> input;
    inFile >> input;
    inFile >> input;
    inFile >> input;
    inFile >> input;
    inFile >> input;

    // the loop that writes the main RGB dataset into the output file
    for (int j=7; j<size+6; j+=3){
        outFile << myArray[j] << " " << myArray[j+1] << " " << myArray[j+2] << " ";
    }
}

void findElevationPath(ifstream & inFile, int size, int width, int height, int myArray[]){
    string temp;                                              					// initializes temporary variable that holds un-needed data
    int counter = 0, index, row , coin_toss = randNum(1, 2), edge[height];;  	// initializes counter, index, row, coin_toss and edge array variable that assists in finding the lowest elevation path
    bool terminate = false;

    // takes in the user input on which row they want to start out their path calculation
    cout << "Note: Row Starts at 1 (not 0) and ends at " << height << "\nEnter the Row: ";
    cin >> row;

    // here temp variable is making sure garbage data is not being used as part of the dataset to find lowest elevation path
    inFile >> temp;
    inFile >> temp;
    inFile >> temp;

    // reads the dataset until the end of line and when counter is not less than size
    while (!inFile.eof() && counter<size) {
        inFile >> myArray[counter];
        counter++;
    }

    // calculates the index of the inputted row position by the user
    if (row>1)
        index = width*(row-1)*3+1;
    else if (row==1)
        index = 1;

    cout << endl;
	counter = 0; 	   // counter is reset to zero
    width = width * 3; // multiplies the width by 3 times so that it equals to the number of RGB values needed

    // makes sure the last two rgb values of the starting row is 0
    myArray[index+1]=0;
    myArray[index+2]=0;

    // this loop calculates the index position of the rightmost edge position of each row so that we can figure out when the elevation path has ended
    for (int i=1; i<=height; i++){
        edge[i]= (width*i)-2;
    }

    do {
        // calculates the base (current postion, up, down and side) values as well as their difference (Projected Positon-Current Position) in the current index position
        int up = myArray[index-(width-3)];    // the value that is on the next upward movement posiion
        int side = myArray[index+3];          // the value that is on the next sideways movement posiion
        int down = myArray[index+(width+3)];  // the value that is on the next downward movement posiion
        int base = myArray[index];            // Base is current position
        int up_diff = abs(up-base);           // Difference of Up - Current Position
        int side_diff = abs(side-base);       // Difference of Side - Current Position
        int down_diff = abs(down-base);       // Difference of Down - Current Position

        // sideways movement logic
        if (((side_diff<up_diff) && (side_diff<down_diff)) || ((side_diff==up_diff) || (side_diff==down_diff))){
            myArray[index+4] =  0;
            myArray[index+5] =  0;
            index+=3;
        }

        // checks if the end of path has been reached after the sideways movement
        for (int i=1; i<=height; i++){
            if (edge[i]==index)
                terminate = true;
        }

        // updating the values so it can calculate the values for the newly updated position if previously moved
        up = myArray[index-(width-3)];
        side = myArray[index+3];
        down = myArray[index+(width+3)];
        base = myArray[index];
        up_diff = abs(up-base);
        side_diff = abs(side-base);
        down_diff = abs(down-base);

        // upwards movement logic
        if (((up_diff<side_diff) && (up_diff<down_diff)) || ((up_diff==down_diff) && (up_diff<side_diff) && (coin_toss==1))){
            myArray[index-(width-4)] = 0;
            myArray[index-(width-5)] = 0;
            index-=(width-3);
        }

        // checks if the end of path has been reached after the upwards movement
        for (int i=1; i<=height; i++){
            if (edge[i]==index)
                terminate = true;
        }

        // updating the values so it can calculate the values for the newly updated position if previously moved
        up = myArray[index-(width-3)];
        side = myArray[index+3];
        down = myArray[index+(width+3)];
        base = myArray[index];
        up_diff = abs(up-base);
        side_diff = abs(side-base);
        down_diff = abs(down-base);

        // downwards movement logic
        if (((down_diff<side_diff) && (down_diff<up_diff)) || ((up_diff==down_diff) && (down_diff<side_diff) && (coin_toss==2))){
            myArray[index+(width+4)] = 0;
            myArray[index+(width+5)] = 0;
            index+=(width+3);
        }

        // checks if the end of path has been reached after the upwards movement
        for (int i=1; i<=height; i++){
            if (edge[i]==index)
                terminate = true;
        }
    }while(terminate==false);
    // this loop runs until terminate boolean is not false
}
