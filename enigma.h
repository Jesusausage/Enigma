/* Enigma class header file
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the enigma class header file.
 */

#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include <fstream>


/* The 'Enigma' class consists of the plugboard and reflector mappings,
   number of rotors, and the rotors themselves. The machine parameters
   can be configured via config files, and messages can be sent in to
   be encrypted. */
class Enigma {
 public:
    Enigma(int no_of_rotors); // Constructor
    Enigma(Enigma const& enigma); // Copy constructor
    ~Enigma(); // Destructor

    void setConfig(int argc, char** argv, int& err);
    /* Precondition:
       'argc' and 'argv' are the quantity and values of the command line
       parameters respectively, and 'err' is the error code, currently
       set to 0. */
    /* Postcondition:
       If an error is encountered, the function immediately returns with the
       error code changed. Otherwise, the plugboard, reflector and rotors have
       their parameters set according to the files specified on the command
       line, and err = 0. */
    
    void encrypt(std::istream& ins, std::ostream& outs, int& err);
    /* Precondition:
       'ins' and 'outs' are input and output streams respectively, and 'err' 
       is the error code, currently set to 0. */
    /* Postcondition: 
       If an error is encountered, the function immediately returns with the
       error code changed. Otherwise, the data fed through ins is encrypted 
       and sent to outs, and err = 0. */
    
 private:
    int plugboard_[26]; // (plugboard_[x] = y) means "x is mapped to y".
    int reflector_[26]; // As above.
    Rotor* rotors_; // Array of rotors
    int no_of_rotors_;
    
    int keyPress(int key);
    /* Precondition: 
       'key' is an integer between 0 and 25, and all the mappings are set. */
    /* Postcondition: 
       The rightmost rotor is turned one tick, and all the others turn 
       accordingly. The integer returned is the ciphered letter corresponding
       to the input letter. */
    
    void turnRotors();
    /* Precondition: 
       The rotors have been declared. */
    /* Postcondition: 
       The rightmost rotor is turned one tick, and all others turn according
       to the notch positions of the rotor to their left. */
    
    void setPlugboard(char const filename[], int& err);
    /* Precondition: 
       'filename' is the name of the plugboard config file, 'err' is the
       error code currently 0. */
    /* Postcondition: 
       If an error is encountered, the function immediately returns with
       the error code changed. Otherwise, the plugboard is set according
       to the file inputs, and err = 0. */
    
    void setReflector(char const filename[], int& err);
    /* Precondition: 
       'filename' is the name of the reflector config file, 'err' is the
       error code currently 0. */
    /* Postcondition: 
       If an error is encountered, the function immediately returns with
       the error code changed. Otherwise, the reflector is set according
       to the file inputs, and err = 0. */
    
    void setRotors(int argc, char** argv, int& err);
    /* Precondition: 
       'argc' and 'argv' are the quantity and values of the command line
       parameters respectively, and 'err' is the error code currently
       set to 0. */
    /* Postcondition: 
       If an error is encountered, the function immediately returns with
       the error code changed. Otherwise, the rotor parameters are set
       according to the file inputs, and err = 0. */

    void setRemainingPlugs();
    /* Precondition:
       The plugboard mappings from config files have all been set, and the
       remaining unmapped values are currently set to -1. */
    /* Postcondition:
       The mappings that were initially -1 are mapped to themselves. */
    

    int invalidReflection
        (int pair[], int i, std::ifstream& input, char const filename[]) const;
    /* Precondition:
       'pair' is the set of values to be mapped to each other, 'i' is the index
       position in the input file, 'input' has opened the .rf file and read in
       values up to index i, and 'filename' is the name of the above file. */
    /* Postcondition: 
       If there is an error, an error message is displayed and the error code
       returned. Otherwise, 0 is returned. */
    
    int invalidPlug
        (int pair[], int i, std::ifstream& input, char const filename[]) const;
    /* Precondition: 
       'pair' is the set of values to be mapped to each other, 'i' is the index
       position in the input file, 'input' has opened the .pb file and read in
       values up to index i, and 'filename' is the name of the above file. */
    /* Postcondition:
       If there is an error, an error message is displayed and the error code
       returned. Otherwise, 0 is returned. */

    bool idempotentMapping
        (int pair[], int i, std::ifstream& input, char const filename[]) const;
    /* Precondition: 
       'pair' is the set of values to be mapped to each other, 'i' is the index
       position in the input file, 'input' has opened the .pb or .rf file and
       read in values up to index i, and 'filename' is the name of the file. */
    /* Postcondition:
       If the two values in 'pair' are the same, an error message is displayed
       and true returned. Otherwise, false is returned. */
    
    int invalidNoOfReflections
        (int no_of_reflections, char const filename[]) const;
    /* Precondition: 
       'no_of_reflections' stores the number of input loop iterations before
       eof was reached in the .rf file, and 'filename' is the name of the
       above file. */
    /* Postcondition: 
       If 'no_of_reflections' is a number other than 26, an error message is
       displayed and the error code returned. Otherwise, 0 is returned. */
    
    int invalidNoOfPlugs
        (int no_of_plugs, char const filename[]) const;
    /* Precondition: 'no_of_plugs' stores the number of input loop iterations
       before eof was reached in the .pb file, and 'filename' is the name of
       the above file. */
    /* Postcondition: 
       If 'no_of_plugs' is an odd number, an error message is displayed and
       the error code returned. Otherwise, 0 is returned. */
    
    int invalidInput(char ch) const;
    /* Precondition: 
       'ch' is one of the characters entered through an input stream. */
    /* Postcondition: 
       If 'ch' is not an upper case letter, an error message is displayed
       and the error code returned. Otherwise, 0 is returned. */
    
    int invalidParams(int argc) const;
    /* Precondition: 
       'argc' is the number of command line parameters, including 'enigma'. */
    /* Postcondition:
       If 'argc' is less than 3, an error message is displayed and the error
       code returned. Otherwise, 0 is returned. */
};


#endif
