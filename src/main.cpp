#include <iostream>
#include <fstream>
#include <stack>
#include "transpiler.h"


// This, obviously, reuses much of the code from my interpreter.
int main(int argc, char* argv[]) {
  // Don't look here, it's ugly
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <program.bf>\nMissing bf file." << std::endl;
    return 1;
  }

  // Standard error checking
  std::ifstream in_file(argv[1]);
  if (in_file.fail()) {
    std::cout << "Error reading " << argv[1] << std::endl;
    return 1;
  }

  std::ofstream out_file;
  if (argc > 2) {
    out_file.open(argv[2]);
    if (out_file.fail()) {
      std::cout << "Error opening/creating" << argv[2] << std::endl;
      return 1;
    }
  }
  else {
    out_file.open("out.c");
    if (out_file.fail()) {
      std::cout << "Error opening/creating fallback out.c file. Check the program's permissions and open file handles and try again." << std::endl;
      return 1;
    }
  }

  // ---- Parser happens below this point ----

  BfTranspiler transpiler;

  std::stack<unsigned int> bracket_stack;  // Keeps track of previous brackets
  char c;                             // char of holding
  unsigned int total_tokens = 0;

  while (!in_file.get(c).eof()) {
    char buffer_c = c;
    unsigned int amount = 1;

    if (IS_IO_CHAR(c)) {
      transpiler.tokens.push_back(BfToken {.amount = amount, .type = buffer_c});
      total_tokens++;
    }
    else if (IS_MULTI_OPERATOR_CHAR(c)) {
      while (!in_file.get(c).eof()) {
        if (!IS_VALID_CHAR(c)) {
          // Text, whitespace, whatever. Don't need it. Skip.
          continue;
        }
        else {
          if (c == buffer_c) {
            // Minor optimization. The parser merges consecutive equal tokens into one
            // So ++++++++ would be one {'+', 8} token instead of 8 '+' tokens
            amount++;
            continue;
          }
          else {
            // Put it back where it came from
            in_file.putback(c);
            // And insert what we must
            transpiler.tokens.push_back(BfToken {.amount = amount, .type = buffer_c});
            total_tokens++;
            break;
          }
        }
      }
      if (in_file.eof()) {
        transpiler.tokens.push_back(BfToken {.amount = amount, .type = buffer_c});
        total_tokens++;
      }
    }
    else if (IS_BRACKET_CHAR(c)) {
      if (c == '[') {
        BfToken new_token = {
          .amount = 0,
          .type = buffer_c
        };
        transpiler.tokens.push_back(new_token);
        bracket_stack.push(total_tokens);
        total_tokens++;
      }
      else {
        if (bracket_stack.empty()) {
          std::cout << "Invalid syntax (bracket mismatch)" << std::endl;
          exit(-1);
        }
        BfToken new_token = {
          .amount = 0,
          .type = c
        };
        transpiler.tokens.push_back(new_token);
        bracket_stack.pop();
        total_tokens++;
      }
    }
  }
  in_file.close();

  // We're done with the in_file. Now we hand out_file over to the transpiler
  out_file << TEMPLATE_CREDITS;
  out_file << TEMPLATE_START;
  transpiler.transpile(out_file);
  out_file << TEMPLATE_END;

  // Done!
  out_file.close();

  return 0;
}
