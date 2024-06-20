#include <vector>
#include <string_view>
#include <fstream>

#define IS_VALID_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']')
#define IS_MULTI_OPERATOR_CHAR(c) (c == '>' || c == '<' || c == '+' || c == '-')
#define IS_IO_CHAR(c) (c == '.' || c == ',')
#define IS_BRACKET_CHAR(c) (c == '[' || c == ']')


namespace BFC_TEMPLATE {
  constexpr std::string_view credits{"/* THE FOLLOWING SOURCE FILE WAS AUTOMATICALLY GENERATED USING https://github.com/Nanrech/brainfuck-transpiler */\n"};
  constexpr std::string_view includes{"#include <stdio.h>\n#include <stdlib.h>\n\n"};
  constexpr std::string_view tape_length{"#define TAPE_LENGTH 30000\n\n\n"};
  constexpr std::string_view main_start{"int main(void) {\n  unsigned char c;\n  size_t ptr = 0;\n"};
  constexpr std::string_view main_tape{"  unsigned char* mem = calloc(TAPE_LENGTH, sizeof(unsigned char));\n\n  if (mem == NULL) {\n    puts(\"ERROR ALLOCATING TAPE\");\n    return 1;\n  }"};
  constexpr std::string_view generated_begin{"\n\n  /* BEGIN GENERATED CODE */\n\n"};
  constexpr std::string_view generated_end{"\n  /* END GENERATED CODE */\n\n  free(mem);\n  return 0;\n}\n"};
}

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
