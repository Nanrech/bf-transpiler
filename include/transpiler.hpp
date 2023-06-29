#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define TEMPLATE_CREDITS \
"/* THE FOLLOWING SOURCE FILE WAS AUTOMATICALLY GENERATED USING https://github.com/Nanrech/brainfuck-transpiler */\n"

#define TEMPLATE_A \
"#include <stdio.h>\n\
#include <stdlib.h>\n\n\n\
#define TAPE_LENGTH 30000\n\n\
int main(void) {\n\
  // uchar alias\n\
  typedef unsigned char uchar;\n\
  // Mandatory input char\n\
  uchar c;\n\
  // Pointer\n\
  int memory_ptr = 0;\n\
  // Tape\n\
  uchar* memory = calloc(TAPE_LENGTH, sizeof(uchar));\n\n\
  /* BEGIN GENERATED CODE */\n\n"

#define TEMPLATE_B \
"\n  /* END GENERATED CODE */\n\
  free(memory);\n\
  return 0;\n\
}\n"

typedef struct {
  char type;
  int amount;
} bftoken;

class BfTranspiler {
  public:
    bool is_opcode(const char c);
    std::string token_trans(const bftoken t, int &i);
    void trans(std::ifstream &in_file, std::ostream &out_file);
};
