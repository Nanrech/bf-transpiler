#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>

#define MAX_TAPE_SIZE 30000
#define IS_CHAR_VALID(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-' || currentChar == '.' || currentChar == ',' || currentChar == '[' || currentChar == ']')
#define IS_CHAR_MULTI(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-')

typedef struct Token {
  char type;
  size_t data; // index to matching jump instruction OR nº times command should be repeated
} Token;


int main(int argc, char* argv[]) {
  // Input & output files provided?
  if (argc < 3) {
    std::cout << "Error: No input/output files.\nUsage: " << argv[0] << " <program.bf> <out.c>" << std::endl;
    return 1;
  }

  // Input file exists?
  std::ifstream inFile(argv[1]);

  if (inFile.fail()) {
    std::cout << "Error: Couldn't read input file " << argv[1] << std::endl;
    return 1;
  }

  // Output file can be created?
  std::ofstream outFile(argv[2]);

  if (outFile.fail()) {
    std::cout << "Error: Couldn't create output file " << argv[2] << std::endl;
    return 1;
  }

  // ---- Read file ----
  // First pass, get amount of tokens
  char currentChar;
  char lastChar = '\0';

  int tokenAmount = 0;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    // Some successive characters are just stored as a single command
    // Their 'data' field represents how many times it should be executed
    if (!IS_CHAR_MULTI(currentChar) || currentChar != lastChar) {
      tokenAmount++;
    }

    lastChar = currentChar;
  }

  // ---- init command storage ----
  std::vector<Token> commands;
  commands.resize(tokenAmount);

  // Rewind file
  inFile.clear();
  inFile.seekg(0);

  // ---- Store tokens ----
  // Second pass, store tokens
  size_t i = 0;
  size_t data = 1;
  lastChar = '\0';
  std::stack<size_t> bracketStack;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    if (currentChar == '[') {
      bracketStack.push(i);
      data = 1;
    }
    else if (currentChar == ']') {
      if (bracketStack.empty()) {
        std::cout << "Error in input file at pos. " << inFile.tellg() << std::endl;
        throw std::runtime_error("Unmatched Closing Bracket");
      }
      // Assign last opening bracket's index to this one
      data = bracketStack.top();
      bracketStack.pop();
      // Assign this one's index to last bracket
      commands[data].data = i;
    }
    else {
      // Optimize
      if (IS_CHAR_MULTI(currentChar) && currentChar == lastChar) {
        commands[i - 1].data += 1;
        continue;
      }
      else {
        data = 1;
      }
    }

    lastChar = currentChar;
    commands[i++] = Token {
      .type = currentChar,
      .data = data,
    };
  }

  // Check for overflow
  if (bracketStack.size() != 0) {
    std::cout << "Error in input file" << std::endl;
    throw std::runtime_error("Unmatched Opening Bracket");
  }

  // ---- Close input file ----
  inFile.close();

  // ---- Insert template code ----
  outFile << "/* THE FOLLOWING SOURCE FILE WAS AUTOMATICALLY GENERATED USING https://github.com/Nanrech/brainfuck-transpiler */\n"
          << "#include <stdio.h>\n#include <stdlib.h>\n\n"
          << "#define TAPE_LENGTH 30000\n\n\n"
          << "int main(void) {\n  unsigned char c;\n  size_t ptr = 0;\n"
          << "  unsigned char* mem = calloc(TAPE_LENGTH, sizeof(unsigned char));\n\n"
          << "  if (mem == NULL) {\n    puts(\"ERROR ALLOCATING TAPE\");\n    return 1;\n  }\n\n";

  // ---- Generate output code ----
  int indent = 2;

  for (auto c : commands) {
    outFile << std::string(indent, ' ');

    switch (c.type) {

      case '>': {
        if (c.data == 1) {
          outFile << "ptr++;\n";
          break;
        }
        outFile << "ptr += " << c.data << ";\n";
        break;
      }
      case '<': {
        if (c.data == 1) {
          outFile << "ptr--;\n";
          break;
        }
        outFile << "ptr -= " << c.data << ";\n";
        break;
      }
      case '+': {
        if (c.data == 1) {
          outFile << "mem[ptr]++;\n";
          break;
        }
        outFile << "mem[ptr] += " << c.data << ";\n";
        break;
      }
      case '-': {
        if (c.data == 1) {
          outFile << "mem[ptr]--;\n";
          break;
        }
        outFile << "mem[ptr] -= " << c.data << ";\n";
        break;        break;
      }
      case '.': {
        outFile << "putchar(mem[ptr]);\n";
        break;
      }
      case ',': {
        outFile << "scanf(\"%c\", &c);\n" << std::string(indent, ' ') << "mem[ptr] = c;\n";
        break;
      }
      case '[': {
        outFile << "while (mem[ptr] != 0) {\n";
        indent += 2;
        break;
      }
      case ']': {
        outFile.seekp(-2, std::ios_base::cur);
        outFile << "}\n";
        indent -= 2;
        break;
      }
      default:
        break;
    }
  }

  // ---- Close output file ---
  outFile << "}\n";
  outFile.close();

  return 0;
}
