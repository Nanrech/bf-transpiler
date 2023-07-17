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
