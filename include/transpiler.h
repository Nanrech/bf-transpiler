#include <vector>
#include <fstream>

#define IS_VALID_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')
#define IS_MULTI_OPERATOR_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-')
#define IS_IO_CHAR(c) (c == '.' || c == ',')
#define IS_BRACKET_CHAR(c) (c == '[' || c == ']')
#define TEMPLATE_CREDITS \
"/* THE FOLLOWING SOURCE FILE WAS AUTOMATICALLY GENERATED USING https://github.com/Nanrech/brainfuck-transpiler */\n\n"
#define TEMPLATE_START \
"#include <stdio.h>\n\
#include <stdlib.h>\n\n\n\
#define TAPE_LENGTH 30000 // As per https://esolangs.org/wiki/brainfuck\n\n\
int main(void) {\n\
  unsigned char c;\n\
  unsigned char* mem = calloc(TAPE_LENGTH, sizeof(unsigned char));\n\n\
  int ptr = 0;\n\
  /* BEGIN GENERATED CODE */\n\n"
#define TEMPLATE_END \
"\n  /* END GENERATED CODE */\n\
  free(mem);\n\
  return 0;\n\
}\n"


typedef struct {
  unsigned int amount;  // Number of times this instruction is repeated
  char type;            // Operator
} BfToken;

class BfTranspiler {
  private:
    size_t tokens_pointer;  // For .tokens
  public:
    std::vector<BfToken> tokens;
    void transpile(std::ofstream &out_file);
};
