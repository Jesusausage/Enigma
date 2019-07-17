/* Enigma class error functions
 * 
 * Author: Philip Cai 
 * Last modified: 16/11/2018
 * 
 * This file contains the definitions for member functions to check for errors
 * in the enigma machine config files. */

#include "errors.h"
#include "enigma.h"
#include "fidelis.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Enigma::invalidNoOfReflections
(int no_of_reflections, char const filename[]) const
{
    if (no_of_reflections != 26) { // 26 mappings required
        cerr << "\nIncorrect number of reflector mappings given in file\n'";
        cerr << filename << "'; " << no_of_reflections;
        cerr << " mappings given, must contain 26.\n";
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    return NO_ERROR;
}


int Enigma::invalidNoOfPlugs
(int no_of_plugs, char const filename[]) const
{
    if (no_of_plugs % 2) { // must be even
        cerr << "\nIncorrect number of plugboard mappings given in file\n'";
        cerr << filename << "'; " << no_of_plugs;
        cerr << " mappings given, must contain an even number\n";
        cerr << "less than or equal to 26.\n";
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    return NO_ERROR;
}


bool Enigma::idempotentMapping
(int pair[], int i, ifstream& input, char const filename[]) const
{
    if (i % 2) {
        if (pair[0] == pair[1]) {
            cerr << "\nIdempotent mapping '" << pair[i % 2];
            cerr << "' given in file\n'" << filename;
            cerr << "', index " << input.tellg() << ":\n";
            // Current stream pos gives error index
            
            printOverlap(pair[i % 2], filename);
            return true;
        }
    }

    return false;
}  


int Enigma::invalidReflection
(int pair[], int i, ifstream& input, char const filename[]) const
{
    if (i >= 26) // First checks if loop index out of bounds
        return invalidNoOfReflections(i+1, filename);
    // "i+1" because index starts at 0
    
    if (invalidIndex(pair[i % 2], input, filename))
        return INVALID_INDEX;
    
    for (int j = 0; j < 26; j++) {
        if (reflector_[j] == pair[i % 2]) {
            // Error if any existing map matches the input value
            cerr << "\nOverlapping reflector mapping '" << pair[i % 2];
            cerr << "' given in file\n'" << filename;
            cerr << "', index " << input.tellg() << ":\n";
            // Current stream pos gives error index
            
            printOverlap(pair[i % 2], filename);
            return INVALID_REFLECTOR_MAPPING;
        }
    }

    if (idempotentMapping(pair, i, input, filename))
        return INVALID_REFLECTOR_MAPPING;

    return NO_ERROR;
}


int Enigma::invalidPlug
(int pair[], int i, ifstream& input, char const filename[]) const
{
    if (i >= 26) // First check if loop index out of bounds
        return invalidNoOfPlugs(i+1, filename);
    
    if (invalidIndex(pair[i % 2], input, filename))
        return INVALID_INDEX;
    
    for (int j = 0; j < 26; j++) {
        if (plugboard_[j] == pair[i % 2]) {
            // Error if any existing map matches the input value
            cerr << "\nOverlapping plugboard mapping '" << pair[i % 2];
            cerr << "' given in file\n'" << filename;
            cerr << "', index " << input.tellg() << ":\n";
            // Current stream pos gives error index
            
            printOverlap(pair[i % 2], filename);
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
    }

    if (idempotentMapping(pair, i, input, filename))
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

    return NO_ERROR;
}


int Enigma::invalidInput(char ch) const
{
    if (ch < 'A' || ch > 'Z') {
        cerr << "\n'" << ch << "' is not a valid input character.\n";
        cerr << "You may only enter characters from A - Z.\n";
        return INVALID_INPUT_CHARACTER;
    }

    return NO_ERROR;
}


int Enigma::invalidParams(int argc) const
{
    if (argc < 3) {
        cerr << "Too few command line parameters given.\n";
        cerr << "At least a plugboard and reflector config file must be ";
        cerr << "given on the command line:\n";
        cerr << "'./enigma <plugboard> <reflector> <rotorI> ";
        cerr << "<rotorII>...<rotorx> <rotor pos>'\n\n";
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

    return NO_ERROR;
}
