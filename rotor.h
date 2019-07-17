/* Rotor class header file
 * 
 * Author: Philip Cai 
 * Last modified: 16/11/2018
 * 
 * This file contains the header file for the rotor class. 
 */

#ifndef ROTOR_H
#define ROTOR_H

#include <fstream>


/* The 'Rotor' class consists of the rotor's mappings, notch positions, and
   its rotation position. The rotor can be turned, set from config files,
   and values can be sent in to be encrypted. */
class Rotor {
 public:
    Rotor(); // Constructor
    Rotor(Rotor const& rotor); // Copy constructor
    
    bool turn();
    /* Precondition:
       'pos_' is currently an integer between 0 and 25. */
    /* Postcondition:
       'pos_' is incremented by 1 (mod 26). If the rotor moves into a position
       where a notch exists, true is returned. Otherwise, false is returned. */
    
    int inputRtoL(int letter);
    /* Precondition:
       'letter' is the integer to be mapped, passing through right to left. */
    /* Postcondition:
       The mapped output integer is returned. */
    
    int inputLtoR(int letter);
    /* Precondition:
       'letter' is the integer to be mapped, passing through left to right. */
    /* Postcondition:
       The mapped output integer is returned. */

    void setPosition
        (std::ifstream& pos_file, int& err, char const filename[],
         int i, int no_of_rotors);
    /* Precondition: 
       'pos_file' has opened the file containing rotor positions, 'err' is
       the error code currently set to 0, 'filename' is the name of the above
       file, 'i' is index of the current rotor being set, and 'no_of_rotors'
       is the total number of rotors in the machine. */
    /* Postcondition: 
       If an error is encountered, the function immediately returns with the
       error code changed. If not, 'pos_file' reads in one number, the rotor's
       position is set, and err = 0. */
    
    void setNotches
        (std::ifstream& rot_file, int& err, char const filename[]);
    /* Precondition:
       'rot_file' has opened the file containing rotor mappings and read in
       exactly 26 numbers, 'err' is the error code currently set to 0, and
       'filename' is the name of the above file. */
    /* Postcondition:
       If an error is encountered, the function immediately returns with the
       error code changed. If not, 'rot_file' reads in every number until eof,
       the relevant notches are set, and err = 0. */

    void setMappings
        (std::ifstream& rot_file, int& err, char const filename[]);
    /* Precondition:
       'rot_file' has opened the file containing rotor mappings, 'err' is the
       error code currently set to 0, and 'filename' is the name of the
       above file. */
    /* Postcondition:
       If an error is encountered, the function immediately returns with the
       error code changed. If not, 'rot_file' reads in exactly 26 numbers, the
       rotor mappings are set, and err = 0. */
    
 private:  
    int mappings_[26][2]; // [0] is right to left, [1] is left to right
    int pos_; // Increments by 1 every time the rotor rotates once
    bool notches_[26]; // notches_[x] true <=> there is a notch at pos x
    
    int invalidRotor
        (int n, int i, std::ifstream& input, char const filename[]) const;
    /* Precondition:
       'n' is the value read in from config files, 'i' is the current map
       index being set, 'input' has opened the .rot file and read up to exactly
       the current value (n), and 'filename' is the name of the .rot file. */
    /* Postcondition:
       If there is an error, an error message is displayed and the error code
       returned. Otherwise, 0 is returned. */
    
    int noRotorMap
        (int i, std::ifstream& input, char const filename[]) const;
    /* Precondition:
       'i' is the index of the last rotor map read, 'input' has opened
       the .rot file and read up to exactly the current index (i), and
       'filename' is the name of the .rot file. */
    /* Postcondition:
       If eof is reached, an error message is displayed and the error code
       returned. Otherwise, 0 is returned. */
    
    int noStartingPos
        (int i, int no_of_rotors, std::ifstream& input,
         char const filename[]) const;
    /* Precondition:
       'i' is the index of the last rotor pos read, 'no_of_rotors' is the
       total number of rotors in the machine, 'input' has opened
       the .pos file and read up to exactly the current index (i), and
       'filename' is the name of the .rot file. */
    /* Postcondition:
       If eof is reached, an error message is displayed and the error
       code returned. Otherwise, 0 is returned. */
};


#endif
