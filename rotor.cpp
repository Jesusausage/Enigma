/* Rotor class member functions
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the definitions for member functions to set configuration
 * parameters in the enigma machine's rotors.
 */

#include "rotor.h"
#include "fidelis.h"
#include <fstream>

using namespace std;


Rotor::Rotor()
{
    for (int i = 0; i < 26; i++) {
        notches_[i] = false;
    }
}


Rotor::Rotor(Rotor const& rotor)
{
    pos_ = rotor.pos_;
    
    for (int i = 0; i < 26; i++) {
        mappings_[i][0] = rotor.mappings_[i][0];
        mappings_[i][1] = rotor.mappings_[i][1];
        
        notches_[i] = rotor.notches_[i];
    }
}


void Rotor::setMappings(ifstream& rot_file, int& err, char const filename[])
{
    int mapping;
    
    for (int i = 0; i < 26; i++) { // 26 mappings to set
        rot_file >> ws;
        if ( (err = noRotorMap(i, rot_file, filename)) )
            return; // Returns err if eof before 26 maps set
        
        if ( (err = nonNumericChar(rot_file, filename)) )
            return;
        
        rot_file >> mapping;    
        if ( (err = invalidRotor(mapping, i, rot_file, filename)) )
            return;

        mappings_[i][0] = mapping; // mappings_[][0] for right-to-left,
        mappings_[mapping][1] = i; // and mappings_[][1] for left-to-right
    }
}


void Rotor::setPosition
(ifstream& pos_file, int& err, char const filename[],
 int rotor_no, int no_of_rotors)
{
    int position;

    pos_file >> ws;
    if ( (err = noStartingPos(rotor_no, no_of_rotors, pos_file, filename)) )
        return; // Returns err if eof before all rotor starting pos are set
    
    if ( (err = nonNumericChar(pos_file, filename)) )
        return;
    
    pos_file >> position;    
    if ( (err = invalidIndex(position, pos_file, filename)) )
        return;
    
    pos_ = position;
}   


void Rotor::setNotches(ifstream& rot_file, int& err, char const filename[])
{
    int notch_position;

    rot_file >> ws;
    while (!rot_file.eof()) {
        if ( (err = nonNumericChar(rot_file, filename)) )
            return;

        rot_file >> notch_position;
        if ( (err = invalidIndex(notch_position, rot_file, filename)) )
            return;
        
        notches_[notch_position] = true;
        rot_file >> ws;
    }
}


bool Rotor::turn()
{
    pos_ = (pos_ + 1) % 26;

    if (notches_[pos_])
        return true;

    return false;
}


int Rotor::inputRtoL(int letter)
{
    letter = (letter + pos_) % 26;
    letter = mappings_[letter][0]; //.mappings_[][0] for going right to left
    letter = (letter - pos_ + 26) % 26; // "+ 26" in case of negative output

    return letter;
}


int Rotor::inputLtoR(int letter)
{ 
    letter = (letter + pos_) % 26;
    letter = mappings_[letter][1]; //.mappings_[][0] for going left to right
    letter = (letter - pos_ + 26) % 26; // "+ 26" in case of negative output

    return letter;
}
