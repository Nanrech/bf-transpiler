#include "transpiler.hpp"


bool BfTranspiler::is_opcode(const char c) {
  char op_arr[] = {
    '>',
    '<',
    '+',
    '-',
    '.',
    ',',
    '[',
    ']'
  };
  
  for (int i = 0; i <= 8; i++) {
    if (op_arr[i] == c)
      return true;
  }

  return false;
}

std::string BfTranspiler::token_trans(const bftoken t, int &i) {
  // I hear C++20 is gonna have proper string interpolation...
  std::stringstream ss;
  // Might as well add indent here. If it's a closing bracket we don't wanna have extra indent
  if (t.type != ']')
    ss << std::string(i, ' ');

  switch (t.type) {
    case '>':
      ss << "memory_ptr += " << t.amount << ";\n";

      return ss.str();
      
    case '<':
      ss << "memory_ptr -= " << t.amount << ";\n";

      return ss.str();

    case '+':
      ss << "memory[memory_ptr] += " << t.amount << ";\n";

      return ss.str();

    case '-':
      ss << "memory[memory_ptr] -= " << t.amount << ";\n";

      return ss.str();

    case '.':
      ss << "putchar(memory[memory_ptr]);\n";

      return ss.str();

    case ',':
      ss << "scanf(\" %c\", &c);\n" << std::string(i, ' ') << "memory[memory_ptr] = c;\n";

      return ss.str();

    case '[':
      ss << "while (memory[memory_ptr] != 0) {\n";
      i += 2;
      
      return ss.str(); 

    case ']':
      i -= 2;
      ss << std::string(i, ' ') << "}\n";

      return ss.str();

    default:
      break;
  }
  return "[]\n";
}

void BfTranspiler::trans(std::ifstream &in_file, std::ostream &out_file) {
  std::vector<char> characters;
  std::vector<bftoken> tokens;
  char c;

  while (in_file.get(c)) {
    if (is_opcode(c)) {
      characters.insert(characters.end(), c);
    }
  }

  for (char c : characters) {
    if (tokens.size() == 0 || c == '[' || c == ']' || c == '.' || c == ',') tokens.push_back(bftoken{c, 0});

    if (tokens.back().type == c) {
      tokens.back().amount++;
    }
    else {
      tokens.push_back(bftoken{c, 1});
    }
  }
  
  int indent = 2;
  for (auto t : tokens) {
    // std::cout << "{ '" << t.type << "', " << t.amount << " }" << std::endl;
    out_file << token_trans(t, indent);    
  }
}
