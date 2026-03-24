#ifndef CHAR_XML_TOKENIZER_H
#define CHAR_XML_TOKENIZER_H

#ifndef CHAR_XML_TOKENIZER_H
#include "CharXMLTokenizer.h"
#endif

#include <map>
#include <stack>

/* class CharEntXMLTokenizer is a child of CharEntXMLTokenizer
 * This class additionally parses DOCTYPE declarations with entity declarations like:
   by overriding member check_gt_bang(CHAR)
<!DOCTYPE book [
  <!ENTITY nwalsh "Norman Walsh">
  <!ENTITY chap1 SYSTEM "json.txt">
]>
 * WARNING New versions of code is selected by asserting macro NEW
 * TODO:
 [ ] parse entity uses, like &chap1;
 */

class CharEntXMLTokenizer : public CharXMLTokenizer {
public:
  using Tokenizer::is;

  bool check_lt_bang(char c) override;
  // Constructor(s) and destructor:
  CharEntXMLTokenizer(std::istream & i) : CharXMLTokenizer(i) {};
  ~CharEntXMLTokenizer() = default;
};

bool CharEntXMLTokenizer::check_lt_bang(char c) {
  if(c== '<') {
    if( is.peek() == '!' ) {
      is >> std::ws; // just in case
      std::string word;
      // read word and make it lowercase:
      is >> word;
      Tokenizer::tolower(word);
      if(word.compare("doctype")) {
        std::cout << "READ: <!" << word << " instead of <!DOCTYPE\n";
        return false;
      }
      else {
        is >> std::ws; // eat space
      /*
         - peek() to find if next char is alphanumeric
         - read SYSTEM and its value (like SYSTEM "http://www.dtds-r-us.com/generic.dtd")
         - consume space
         - peek() to find if next char is '['
         - process entity declarations
         - eat closing ']'
         - eat closing '>'
      */

      }

    }
    else
      return false;
  }
  else
    return false;
};

#ifndef SEPARATE_COMPILATION
#include "CharEntXMLTokenizer.cpp"
#endif

#endif
