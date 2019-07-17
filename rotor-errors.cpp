/* Enigma class error functions
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the definitions for member functions to check for errors
 * in the rotor config files. */

#include "errors.h"
#include "rotor.h"
#include "fidelis.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Rotor::invalidRotor
(int n, int i, ifstream& input, char const filename[]) const
{
    if (invalidIndex(n, input, filename))
        return INVALID_INDEX;
    
    for (int j = 0; j < i; j++) {
        if (mappings_[j][0] == n) {
            // Error if input matches any existing map
            cerr << "\nOverlapping rotor mapping '" << n;
            cerr << "' given in file\n'" << filename;
            cerr << "', index " << input.tellg() << ":\n";
            // Current stream pos gives error index
            
            printOverlap(n, filename);
            return INVALID_ROTOR_MAPPING;
        }
    }
    
    return NO_ERROR;
}


int Rotor::noRotorMap
(int i, ifstream& input, char const filename[]) const
{
    if (input.eof()) {
        cerr << "\nInsufficient rotor mappings given in file\n'" << filename;
        cerr << "'; " << i << " given, must contain at least 26.\n";
        return INVALID_ROTOR_MAPPING;
    }

    return NO_ERROR;
}


int Rotor::noStartingPos
(int i, int no_of_rotors, ifstream& input, char const filename[]) const
{
    if (input.eof()) {
        cerr << "\nInsufficient rotor starting positions given in file\n'";
        cerr << filename << "'; " << i << " given, must contain ";
        cerr << no_of_rotors << ".\n";
        return NO_ROTOR_STARTING_POSITION;
    }

    return NO_ERROR;
}
