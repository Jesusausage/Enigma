/* Error helper member functions
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the definitions for helper functions to handle errors 
 * in the enigma machine config files. */

#include "errors.h"
#include "fidelis.h"
#include <fstream>
#include <iostream>

using namespace std;


void printError(int index, int n_len, char const filename[])
{
    printFileContents(filename);
    cerr << endl;
    printUnderline(index, n_len);
    cerr << endl;
}


void printOverlap(int value, char const filename[])
{
    int in_data = 0, index1 = 0, index2 = 0;
    // 'index1', 'index2' to store location of invalid inputs in file
    int value_len = to_string(value).length();
    // Get length by converting to string first
    ifstream input_file(filename);
    
    input_file >> ws >> in_data;
    while (!index1) {
        if (in_data == value)
            // Read file data until first occurrence of invalid input
            index1 = input_file.tellg();
        input_file >> ws >> in_data;
    }
    while (!index2) {
        if (in_data == value)
            // Read file data until second occurrence of invalid input
            index2 = input_file.tellg();
        input_file >> ws >> in_data;
    }
        
    printFileContents(filename);
    cerr << endl;
    printUnderline(index1, value_len);
    printUnderline(index2 - index1, value_len);
    //index2-index1 used for start pos, as cursor starts at index1
    cerr << endl;
}


void printFileContents(char const filename[])
{
    char ch;
    ifstream input_file(filename);
    
    input_file.get(ch);
    while (!input_file.eof()) {
        if (isspace(ch))
            // White space converted to ' ' to display underline more easily
            cerr << " ";
        else
            cerr << ch;
        input_file.get(ch);
    }
}


void printUnderline(int index, int len)
{
    for (int i = (index-len + 1); i > 1; i--)
        cerr << " "; // Pads new line with spaces until index position reached
    for (; len > 0; len--)
        cerr << "~";
}


int nonNumericChar(ifstream& input, char const filename[])
{
    int stream_pos = input.tellg(); // Save current stream position
    char ch;
    
    input.get(ch);
    while (!input.eof() && !isspace(ch)) {
        // Reads characters until white space or eof
        if (!isdigit(ch)) {
            cerr << "\nNon-numeric character '" << ch;
            cerr << "' given in file\n'" << filename;
            cerr << "', index " << input.tellg() << ":\n";
            // Current stream pos gives error index
            
            printError(input.tellg(), 1, filename);
            return NON_NUMERIC_CHARACTER;
        }

        input.get(ch);
    }

    input.seekg(stream_pos); // Returns to original stream position
    return NO_ERROR;
}


int invalidIndex(int n, ifstream& input, char const filename[])
{
    if (n < 0 || n > 25) {
        int pos = input.tellg();
        // Current stream pos gives error index
        
        cerr << "\nOut of bounds input '" << n;
        cerr << "' given in file\n'" << filename;
        cerr << "', index " << pos << ":\n";
        
        int n_len = to_string(n).length();
        // Get length by converting to string first
        printError(pos, n_len, filename);
        
        return INVALID_INDEX;
    }

    return NO_ERROR;
}


int fileReadErr(char const filename[], ifstream& input_file)
{
    if (input_file.fail()) {
        cerr << "Error opening '" << filename << "'.\n";
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    cout << "File '" << filename << "' successfully opened.\n";
    return NO_ERROR;
}
