#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define TEMPLATE_CREDITS \
"/* THE FOLLOWING SOURCE FILE WAS AUTOMATICALLY GENERATED USING https://github.com/Nanrech/brainfuck-transpiler */\n\n"

#define TEMPLATE_A \
"#include <stdio.h>\n\
#include <stdlib.h>\n\n\n\
#define TAPE_LENGTH 30000 // As per https://esolangs.org/wiki/brainfuck\n\n\
int main(void) {\n\
  unsigned char c;\n\
  unsigned char* mem = calloc(TAPE_LENGTH, sizeof(unsigned char));\n\n\
  int ptr = 0;\n\
  /* BEGIN GENERATED CODE */\n\n"

#define TEMPLATE_B \
"\n  /* END GENERATED CODE */\n\
  free(mem);\n\
  return 0;\n\
}\n"

using namespace std;


enum {
  BFT_MOVR = '>',
  BFT_MOVL = '<',
  BFT_INC = '+',
  BFT_DEC = '-' ,
  BFT_OUT = '.',
  BFT_INP = ',',
  BFT_BRO = '[',
  BFT_BRC = ']'
};

typedef struct {
  // Number of repeat instructions OR 0
  unsigned int amount;
  // BfTokenType
  char type;
} BfToken;

class BfTranspiler {
  public:
    bool is_opcode(const char c);
    std::string token_trans(const BfToken token, int &indent);
    void trans(std::ifstream &in_file, std::ostream &out_file);
};
