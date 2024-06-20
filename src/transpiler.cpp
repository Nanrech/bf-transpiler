#include "transpiler.h"


void BfTranspiler::transpile(std::ofstream &out_file) {
  // 2 space indentation by default
  int indent = 2;

  for (tokens_pointer = 0; tokens_pointer <= tokens.size() - 1; tokens_pointer++) {
    BfToken current_token = tokens[tokens_pointer];
    out_file << std::string(indent, ' ');

    switch (current_token.type) {
      case '>':
        if (current_token.amount == 1) {
          out_file << "ptr++;" << std::endl;
          break;
        }
        out_file << "ptr += " << current_token.amount << ";" << std::endl;
        break;

      case '<':
        // This compiler does not report coding errors
        if (current_token.amount == 1) {
          out_file << "ptr--;" << std::endl;
          break;
        }
        out_file << "ptr -= " << current_token.amount << ";" << std::endl;
        break;

      case '+':
        if (current_token.amount == 1) {
          out_file << "mem[ptr]++;" << std::endl;
          break;
        }
        out_file << "mem[ptr] += " << current_token.amount << ";" << std::endl;
        break;

      case '-':
        if (current_token.amount == 1) {
          out_file << "mem[ptr]--;" << std::endl;
          break;
        }
        out_file << "mem[ptr] -= " << current_token.amount << ";" << std::endl;
        break;

      case '.':
        out_file << "putchar(mem[ptr]);" << std::endl;
        break;

      case ',':
        out_file << "scanf(\"%c\", &c);" << std::endl << std::string(indent, ' ') << "mem[ptr] = c;" << std::endl;
        break;

      case '[':
        out_file << "while (mem[ptr] != 0) {" << std::endl;
        indent += 2;
        break;

      case ']':
        out_file.seekp(-2, std::ios_base::cur);
        out_file << "}" << std::endl;
        indent -= 2;
        break;

      default:
        break;
    }
  }
}
