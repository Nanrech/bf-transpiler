#include <iostream>
#include <vector>
#include "transpiler.h"

#define OUTFILE "out.c"

using namespace std;


int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Usage: '.\\bft.exe <program.bf>'. Missing bf file." << endl;
    return EXIT_FAILURE;
  }

  BfTranspiler Transpiler;

  ifstream in_file(argv[1]);
  ofstream out_file(OUTFILE);
  
  if (in_file.fail() || out_file.fail()) {
    if (in_file.fail()) {
      cout << "Could not read from " << argv[1] << endl;
    }
    if (out_file.fail()) {
      cout << "Could not create/open output file " << OUTFILE << endl;
    }
    
    in_file.close();
    out_file.close();
    
    return EXIT_FAILURE; 
  }


  out_file << TEMPLATE_CREDITS;
  out_file << TEMPLATE_A;
  Transpiler.trans(in_file, out_file);
  out_file << TEMPLATE_B;

  // Clean up
  out_file.close();
  in_file.close();

  return EXIT_SUCCESS;
}