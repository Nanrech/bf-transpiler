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
/*
inline void BfTranspiler::move_right() {
  // Move .amount to the right. If the tape is too small, expand it
  unsigned int token_amount = tokens[tokens_pointer].amount;

  if ((tape_pointer + token_amount) >= tape.size()) {
    for (unsigned int _ = 0; _ < token_amount; _++) {
      tape_pointer++;
      tape.push_back(0);
    }
  }
  else {
    for (unsigned int _ = 0; _ < token_amount; _++) {
      tape_pointer++;
    }
  }
}

inline void BfTranspiler::move_left() {
  // Move .amount to the left. No negative index allowed
  unsigned int token_amount = tokens[tokens_pointer].amount;
  // "error: cOmPaRiSoN oF uNsIgNeD eXpReSsIoN iN '>= 0' iS aLwAyS tRuE" 🤓☝
  // error here bc tape_pointer and token.amount are both unsigned so they'd wrap around
  int diff = tape_pointer - token_amount;

  if (diff >= 0) {
    tape_pointer -= token_amount;
  }
  else {
    tape_pointer = 0;
  }
}

inline void BfTranspiler::increment() {
  tape[tape_pointer] += tokens[tokens_pointer].amount;
}

inline void BfTranspiler::decrement() {
  tape[tape_pointer] -= tokens[tokens_pointer].amount;
}

inline void BfTranspiler::output() {
  cout << tape[tape_pointer];
}

inline void BfTranspiler::input() {
  cin >> tape[tape_pointer];
}

inline void BfTranspiler::bracket_open() {
  if (tape[tape_pointer] == 0) {
    tokens_pointer = tokens[tokens_pointer].amount;
  }
  else {
    return;
  }
}

inline void BfTranspiler::bracket_close() {
  if (tape[tape_pointer] != 0) {
    tokens_pointer = tokens[tokens_pointer].amount;
  }
  else {
    return;
  }
}
*/