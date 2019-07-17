/* Main program
 * 
 * Author: Philip Cai 
 * Last modified: 16/11/2018
 * 
 * This file contains the main program. */

#include "errors.h"
#include "enigma.h"
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{   
    Enigma enigma(argc - 4);
    int err = NO_ERROR;

    enigma.setConfig(argc, argv, err);
    if (err) {
        cerr << "Error code " << err << ". Exiting...\n";
        return err;
    }

    enigma.encrypt(cin, cout, err);
    if (err) {
        cerr << "Error code " << err << ". Exiting...\n";
        return err;
    }

    cerr << "\nNo error. Program terminating...\n";
    return NO_ERROR;
}
