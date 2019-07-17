/* Error helper functions
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the definitions for error helper functions. */

#ifndef ERROR_HELPER_H
#define ERROR_HELPER_H

#include <fstream>


void printError(int index, int n_len, char const filename[]);
/* Precondition: 
   'index' is the index of the error, 'n_len' is the length of the error,
   and 'filename' is the name of the file containing the error. */
/* Postcondition:
   The file contents are printed on screen, and an underline is printed
   underneath the error. */
    
void printOverlap(int value, char const filename[]);
/* Precondition: 
   'value' is the value of the repeated or idempotent mapping,
   and 'filename' is the name of the file containing the error. */
/* Postcondition: 
   The file contents are printed on screen, and an underline is printed
   underneath the errors. */
    
void printFileContents(char const filename[]);
/* Precondition: 
   'filename' is the name of the file to be printed. */
/* Postcondition: 
   The file contents are printed on screen. */
    
void printUnderline(int index, int len);
/* Precondition: 
   'index' is the index of the error, and len is the length. */
/* Postcondition: 
   An underline is printed at the index of the error to the length
   of the error. */   
    
int invalidIndex(int n, std::ifstream& input, char const filename[]);
/* Precondition: 
   'n' is the value to be tested, 'input' has opened the relevant config
   file and read in values up to n, and filename is the name of the file. */
/* Postcondition: 
   If 'n' is not a number between 0 and 25, an error message is displayed
   and the error returned. Otherwise, 0 is returned. */
    
int nonNumericChar(std::ifstream& input, char const filename[]);
/* Precondition: 
   'input' has opened the relevant config file and read in characters up
   to but not including the inputs to be tested, and filename is the name
   of the relevant file. */
/* Postcondition: 
   If the next block of characters up to the next whitespace character
   contains any non-numeric characters, an error message is displayed and
   the error returned. Otherwise, 0 is returned. */
    
int fileReadErr(char const filename[], std::ifstream& input_file);
/* Precondition: 
   'filename' is the name of the file to be opened, and input_file is the
   input file stream that attempted to open it. */
/* Postcondition:
   If the file was not successfully opened, an error message is displayed
   and the error returned. Otherwise, 0 is returned. */


#endif
