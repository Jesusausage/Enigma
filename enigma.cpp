/* Enigma class member functions
 * 
 * Author: Philip Cai 
 * Last modified: 19/11/2018
 * 
 * This file contains the definitions for member functions to set configuration
 * parameters in the enigma machine, and to encrypt input.
 */

#include "enigma.h"
#include "fidelis.h"
#include <fstream>

using namespace std;


Enigma::Enigma(int no_of_rotors)
{
    for (int i = 0; i < 26; i++) {
        plugboard_[i] = -1;
        reflector_[i] = -1;
    }
    // Default set to -1 to prevent overlapping maps during setConfig
    
    no_of_rotors_ = no_of_rotors;
    
    if (no_of_rotors > 0)
        rotors_ = new Rotor[no_of_rotors];
    else
        rotors_ = nullptr;
}


Enigma::Enigma(Enigma const& enigma)
{
    for (int i = 0; i < 26; i++) {
        plugboard_[i] = enigma.plugboard_[i];
        reflector_[i] = enigma.reflector_[i];
    }

    no_of_rotors_ = enigma.no_of_rotors_;
    
    if (no_of_rotors_ > 0) {
        rotors_ = new Rotor[no_of_rotors_];     
        for (int i = 0; i < no_of_rotors_; i++)
            rotors_[i] = enigma.rotors_[i];
    } else
        rotors_ = nullptr;
}


Enigma::~Enigma()
{
    if (no_of_rotors_ > 0)
        delete [] rotors_;
}


void Enigma::setRotors(int argc, char** argv, int& err)
{
    ifstream rot_file;
    ifstream pos_file(argv[argc-1]);
    if ( (err = fileReadErr(argv[argc-1], pos_file)) )
        return;

    for (int rotor_no = 0; rotor_no < no_of_rotors_; rotor_no++) {
        rotors_[rotor_no].setPosition
            (pos_file, err, argv[argc-1], rotor_no, no_of_rotors_);
        if (err)
            return;
        
        // rotor files start at fourth command line param
        rot_file.open(argv[rotor_no+3]);
        if ( (err = fileReadErr(argv[rotor_no+3], rot_file)) )
            return;        
        rotors_[rotor_no].setMappings(rot_file, err, argv[rotor_no+3]);
        if (err) 
            return;        
        rotors_[rotor_no].setNotches(rot_file, err, argv[rotor_no+3]);
        if (err)
            return;     
        rot_file.close();
    }
}


void Enigma::setReflector(char const filename[], int& err)
{    
    int i;
    int pair[2]; // Stores the pair of values to be mapped to each other
    ifstream rf_file(filename);
    if ( (err = fileReadErr(filename, rf_file)) )
        return;

    rf_file >> ws;
    for (i = 0; !rf_file.eof(); i++) {    
        if ( (err = nonNumericChar(rf_file, filename)) )
            return;
        
        rf_file >> pair[i % 2];
        // Use loop index 'i' to determine which half of pair to store
        if ( (err = invalidReflection(pair, i, rf_file, filename)) )
            return;

        if (i % 2) { // Only set rf mappings every second loop iteration
            reflector_[pair[0]] = pair[1];
            reflector_[pair[1]] = pair[0];
        }
        rf_file >> ws;
    }
    
    if ( (err = invalidNoOfReflections(i, filename)) )
        return; // Uses loop index to check
}


void Enigma::setPlugboard(char const filename[], int& err)
{
    int i;
    int pair[2]; // Stores the pair of values to be mapped to each other
    ifstream pb_file(filename);
    if ( (err = fileReadErr(filename, pb_file)) )
        return;

    pb_file >> ws;    
    for (i = 0; !pb_file.eof(); i++) {
        if ( (err = nonNumericChar(pb_file, filename)) )
            return;
        
        pb_file >> pair[i % 2];
        // Use loop index 'i' to determine which half of pair to store
        if ( (err = invalidPlug(pair, i, pb_file, filename)) )
            return;
                
        if (i % 2) { // Only set pb mappings every second loop iteration
            plugboard_[pair[0]] = pair[1];
            plugboard_[pair[1]] = pair[0];
        }
        pb_file >> ws;
    }
    
    if ( (err = invalidNoOfPlugs(i, filename)) )
        return; // Uses loop index to check
    
    setRemainingPlugs();
}    


void Enigma::setRemainingPlugs()
{
    for (int i = 0; i < 26; i++) {
        if (plugboard_[i] == -1)
            plugboard_[i] = i;
    }
}    


int Enigma::keyPress(int key)
{    
    turnRotors();    
    
    key = plugboard_[key];
    
    for (int i = (no_of_rotors_ - 1); i >= 0; i--)
        key = rotors_[i].inputRtoL(key);
    
    key = reflector_[key];
    
    for (int i = 0; i <= (no_of_rotors_ - 1); i++)
        key = rotors_[i].inputLtoR(key);
    
    key = plugboard_[key];

    return key;
}


void Enigma::turnRotors()
{
    int i = no_of_rotors_ - 1;

    while (i >= 0 && rotors_[i].turn()) 
        i--;
    // (i >= 0) checked first, since rotors_[i] may not exist
}
    

void Enigma::encrypt(istream& ins, ostream& outs, int& err)
{
    char ch, output;
    
    outs << "Please enter plaintext (terminate with '.'): \n";
    ins >> ws >> ch;
    outs << "Generating ciphertext: ";
    
    while (ch != '.' && !ins.eof()) {
        if ( (err = invalidInput(ch)) )
            return;
        
        output = keyPress(ch - 'A') + 'A';
        outs << output;
   
        ins >> ws >> ch;
    }
}


void Enigma::setConfig(int argc, char** argv, int& err)
{
    if ( (err = invalidParams(argc)) )
        return;
    
    setReflector(argv[2], err);
    if (err)
        return;
    
    setPlugboard(argv[1], err);
    if (err)
        return;
    
    if (argc > 3) {
        setRotors(argc, argv, err);
        if (err)
            return;
    }
}
