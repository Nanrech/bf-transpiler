#include "transpiler.h"

using namespace std;


bool BfTranspiler::is_opcode(const char c) {
  for (char i : {'>', '<', '+', '-', '.', '[', ']'}) {
    if (i == c) {
      return true;
    }
  }
  return false;
}

string BfTranspiler::token_trans(const BfToken token, int &indent) {
  // I hear C++20 is gonna have proper string interpolation...
  stringstream ss;
  // Might as well add indent here. If it's a closing bracket we don't wanna have extra indent
  if (token.type != BRC)
    ss << string(indent, ' ');

  switch (token.type) {
    case MOVR:
      if (token.amount != 1) {
        ss << "ptr += " << token.amount << ";\n";
      }
      else {
        ss << "ptr++;\n";
      }

      return ss.str();
      
    case MOVL:
      if (token.amount != 1) {
        ss << "ptr -= " << token.amount << ";\n";
      }
      else {
        ss << "ptr--;\n";
      }

      return ss.str();

    case INC:
      if (token.amount != 1) {
        ss << "mem[ptr] += " << token.amount << ";\n";
      }
      else {
        ss << "mem[ptr]++;\n";
      }

      return ss.str();

    case DEC:
      if (token.amount != 1) {
        ss << "mem[ptr] -= " << token.amount << ";\n";
      }
      else {
        ss << "mem[ptr]--;\n";
      }

      return ss.str();

    case OUT:
      ss << "putchar(mem[ptr]);\n";

      return ss.str();

    case INP:
      ss << "scanf(\" %c\", &c);\n" << string(indent, ' ') << "mem[ptr] = c;\n";

      return ss.str();

    case BRO:
      ss << "while (mem[ptr] != 0) {\n";
      indent += 2;
      
      return ss.str(); 

    case BRC:
      indent -= 2;
      ss << string(indent, ' ') << "}\n";

      return ss.str();

    default:
      break;
  }
  return "[]\n";
}

void BfTranspiler::trans(ifstream &in_file, ostream &out_file) {
  vector<char> characters;
  vector<BfToken> tokens;
  char c;

  while (in_file.get(c)) {
    if (is_opcode(c)) {
      characters.insert(characters.end(), c);
    }
  }

  for (char c : characters) {
    if (tokens.size() == 0 || c == '[' || c == ']' || c == '.' || c == ',') tokens.push_back(BfToken{0, c});

    if (tokens.back().type == c) {
      tokens.back().amount++;
    }
    else {
      tokens.push_back(BfToken{1, c});
    }
  }
  
  int indent = 2;
  for (auto t : tokens) {
    // cout << "{ '" << t.type << "', " << t.amount << " }" << endl;
    out_file << token_trans(t, indent);    
  }
}
