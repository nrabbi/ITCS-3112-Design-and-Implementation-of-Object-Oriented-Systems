//  P3: Mountain Path With Pointers
//  Nazmul Rabbi
//  ITCS 3112
//  Last Updated 9/26/17 Wednesday 1:52am
//  Structure
//  Step 1 -> Reads the file and finds the number of rows, columns and the max value in the dataset
//  Step 2 -> Reads the file and stores the data into a pointer array
//  Step 3 -> Outputs a ppm image that is created from the original data read from the file
//  Step 4 -> Calculates the lowest elevation path
//  Step 5 -> Outputs a ppm image with the lowest elevation path drawn
//  Step 6 -> Converts the ppm image to png image for better compatibility

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int  randNum(int min, int max);
void findSize(ifstream & inFile, int & width, int & height, int & max);
void readData(ifstream & inFile, int ** & board, int rows, int columns);
void outputData(ofstream & outFile, int ** p, int r, int c, int max, int ** q);
void findElevationPath(int ** & board, int rows, int columns);
void deAllocate(int ** p, int r);

int main() {
    srand(time(0));                                                 // initializes the random number
    ifstream inFile;                                                // initializes the input file stream
    ofstream outFile;                                               // initializes the output file stream
    string inFileName, outFileName, userChoice;                     // initializes the variables that carries the name of the input ,output file and the user choice
    int **board, **originalBoard, columns = 0, rows = 0, max = 0;   // initializes the variables that carries the rows, columns, max value and the pointer array to store the original + new dataset

    // takes in the filename input from the user to define the input file name
    cout << "Note: Don't Include File Extension, only dat files supported\nEnter the Input File Name: ";
    cin >> inFileName;
    cout << endl;

    inFile.open(inFileName + ".dat");           // opens the input file as stated by the user input
    findSize(inFile, columns, rows, max);       // calls the findSize function to find the column, rows and max value of the dataset
    inFile.close();                             // closes the input file

    inFile.open(inFileName + ".dat");                   // opens the input file as stated by the user input
    readData(inFile, originalBoard, rows, columns);     // reads data from file and stores it into a pointer array -> Original Unchanged Array
    inFile.close();                                     // closes the input file

    inFile.open(inFileName + ".dat");           // opens the input file as stated by the user input
    readData(inFile, board, rows, columns);     // reads data from file and stores it into a pointer array -> array that will be modified to find the elevation path
    inFile.close();                             // closes the input file            

    // takes in the filename input from the user to define the output file name
    cout << "Note: Don't Include File Extension, will output as a ppm file\nEnter the Output File Name: ";
    cin >> outFileName;
    cout << endl;

    // outputs the original image
    outFile.open(outFileName + ".ppm");                             // creates the output file as stated by the user input
    outputData(outFile, board, rows, columns, max, originalBoard);  // outputs data to a ppm file
    outFile.close();                                                // closes the output file

    // creates the output file as stated by the user input for the elevated path
    outFile.open(outFileName + "_elevated_path.ppm");

    // asks the user if they want to find another elevation path? if true then the loop repeats finds the lowest elevation path, loop stops until the user tells it to stop
    do {
        findElevationPath(board, rows, columns);                            // finds the lowest elevation path
        cout << "\nWould you like to draw another elevation path?(y/n)\n";
        cin >> userChoice;
        cout << endl;
    }while(userChoice == "y" || userChoice == "Y");

    outputData(outFile, board, rows, columns, max, originalBoard);  // outputs the elevation data to a ppm file
    outFile.close();                                                // closes the output file

    deAllocate(board, rows);            // the pointer array is deallocated at the end of the program to save memory
    deAllocate(originalBoard, rows);    // the pointer array is deallocated at the end of the program to save memory

    // converts the elevated path ppm file to PNG (needs Imagamagick instlled to work)
    system(("convert " + outFileName + "_elevated_path.ppm " + outFileName + "_elevated_path_image.png").c_str());

    cout << "Program Terminated...";

    return 0;
}

// generates the random number
int randNum(int min, int max){
    return rand() % max + min;
}

void findSize(ifstream & inFile, int & column, int & row, int & max){
    int temp; // initializes the temporary variable that helps to find the max value

    // checks if the filename the user entered into the console is valid
    if (!inFile) {
        cout << "Unable to open file\n";
        exit(1);
    }
    else {
        cout << "File was opened successfully!\n\n";
    }

    // stores the value of the column and row
    inFile >> column;
    inFile >> row;

    // outputs the column and rows values to console
    cout << "Columns: " << column << "\nRows: " << row << endl;     

    // runs a loop to read the input file, until the end to find the max value of the dataset
    while (!inFile.eof()) {
        inFile >> temp;     // assigns the value from the input file to temporary variable

        // if the value of the temporary varible is bigger than max variable then this value is assigned to max variable
        if (max < temp)
            max = temp;
    }

    // outputs the max value to the console
    cout << "Max Value: " << max << endl << endl;           
}

void readData(ifstream & inFile, int ** & board, int rows, int columns){
    int garbage; // initializes the temporary variable that helps to make sure un-needed data is not passed into the data array

    board = new int* [rows]; //create rows of board for pointer array
    for(int row = 0; row < rows; row++)
        board[row] = new int[columns]; //create columns of board for pointer array

    // grabs the un-needed data and separates it from the data set that is to be manipulated
    inFile >> garbage;
    inFile >> garbage;

    // assigns the value from the input file to the pointer array until the end of input file
    while (!inFile.eof()){
        for (int r = 0; r < rows; r++){
            for(int col = 0; col < columns; col++)
                inFile >> board[r][col];
        }
    }
}

void outputData(ofstream & outFile, int ** p, int r, int c, int max, int ** q){
    outFile << "P3" << endl;                // writes the header into the output file
    outFile << c << " ";                    // writes the column value of the dataset into the output file
    outFile << r << endl << max << " ";     // writes the rows and the max value of the dataset

    // outputs the data of array to the output file
    for(int row = 0; row < r; row++){
        for(int col = 0; col < c; col++){
            outFile << q[row][col] << " ";  // as we want to color the path red, the original value from the original dataset has to be in the first rgb triplets position
            outFile << p[row][col] << " ";  // as we dont want to color the path green and make sure its red, the modified value from the elevated path dataset has to be in this position of the rgb triplets
            outFile << p[row][col] << " ";  // as we dont want to color the path blue and make sure its red, the modified value from the elevated path dataset has to be in this position of the rgb triplets
        }
    }
}

void findElevationPath(int ** & board, int rows, int columns){
    int index = 0, row = 0, col= 0; // initializes the variables that is needed/used to find the elevation path

    // takes in the user input on which row they want to start out their path calculation
    cout << "Note: Row Starts at 0 and ends at " << rows-1 << "\nEnter the Row: ";
    cin >> row;

    // this loop calculates the elevation path from a given user inputted row position
    do {
        // initializes the variables that is needed to calculate the elevation path
        int top, side, base, down, top_diff, side_diff, down_diff, coin_toss; 

        // checks if the row position is 0
        if (row == 0){
            // refreshes the values
            side = board[row][col+1];       // gets the value that is sideways from the current position
            base = board[row][col];         // gets the value of the current position
            down = board[row+1][col+1];     // gets the value that is bottom from the current position
            side_diff = abs(side-base);     // calculates the difference between the sideways value and the value of the current position
            down_diff = abs(down-base);     // calculates the difference between the bottom value and the value of the current position

            // sideways movement logic
            if ((side_diff == down_diff) || (side_diff<down_diff)){
                board[row][col] = 0;    // assigns the value of current position to 0
                col++;                  // changes the current position
            }
            // downward movement logic
            else if (down_diff<side_diff){
                board[row][col] = 0;    // assigns the value of current position to 0
                // changes the current position
                col++;
                row++;
            }
        }

        // checks if the row position is not (zero or the max/bottom row position)
        if (row > 0 && row < rows-1){  
            // refreshes the values 
            top = board[row-1][col+1];      // gets the value that is top from the current position
            side = board[row][col+1];       // gets the value that is sideways from the current position
            base = board[row][col];         // gets the value of the current position
            down = board[row+1][col+1];     // gets the value that is bottom from the current position
            top_diff = abs(top-base);       // calculates the difference between the top value and the value of the current position
            side_diff = abs(side-base);     // calculates the difference between the sideways value and the value of the current position
            down_diff = abs(down-base);     // calculates the difference between the bottom value and the value of the current position
            coin_toss = randNum(1, 2);      // randomly generates a random value between 1 or 2 and assigns it to the coin_toss variable

            // upwards movement logic
            if ((top_diff<side_diff && top_diff<down_diff) || (top_diff==down_diff && side_diff>top_diff && coin_toss == 1)){
                board[row][col] = 0;    // assigns the value of current position to 0
                // changes the current position
                col++;
                row--;
            } 
            // side movement logic
            else if ((side_diff<top_diff && side_diff<down_diff) || (down_diff == side_diff && side_diff < top_diff) || (side_diff == top_diff && top_diff < down_diff) || (side_diff == down_diff && down_diff < top_diff) || (side_diff==top_diff && top_diff==down_diff)){
                board[row][col] = 0;    // assigns the value of current position to 0
                // changes the current position
                col++;
            }
            // downwards movement logic
            else if ((down_diff<side_diff && down_diff<top_diff) || (top_diff==down_diff && side_diff>top_diff && coin_toss == 2)){
                board[row][col] = 0;    // assigns the value of current position to 0
                // changes the current position
                col++;
                row++;
            }
        }

        // checks if max/bottom is equal to row position
        if (row == rows-1){
            // refreshes the values
            top = board[row-1][col+1];      // gets the value that is top from the current position
            side = board[row][col+1];       // gets the value that is sideways from the current position
            base = board[row][col];         // gets the value of the current position
            top_diff = abs(top-base);       // calculates the difference between the top value and the value of the current position
            side_diff = abs(side-base);     // calculates the difference between the sideways value and the value of the current position

            // upward movement logic
            if (top_diff<side_diff){
                board[row][col] = 0;    // assigns the value of current position to 0
                // changes the current position
                col++;
                row--;
            }
            // sideways movement logic
            else if ((side_diff == top_diff) || (side_diff<top_diff)){
                board[row][col] = 0;    // assigns the value of current position to 0
                col++;                  // changes the current position
            }
        }

        // checks if the loop has reached the end of the column
        if (col == columns-1){
            board[row][col] = 0;    // assigns the value of current position to 0
            index = columns;        // assigns the value of column to the index so the loop doesnt continue after this
        } 
        else
            index++;   
    }while(index < columns);    // loop runs until it reaches the end of the column

}

void deAllocate(int ** p, int r){
    for (int i = r-1; i >= 0; i--) {
        delete[] p[i];  // deletes each rows in the pointer array 
        p[i]=0;         // assigns each row to zero
    }
    delete [] p;        // deletes the pointer array 
    p = 0;              // assigns the pointer to zero
}