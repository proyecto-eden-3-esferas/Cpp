#ifndef TOKENIZER_H
#define TOKENIZER_H

/* class Tokenizer defines an interface for all tokenizers
 * It provides two variables:
   - std::string 'temp' and
   - a reference to an std::istream ('is')
   and two pure virtual functions:
   - process_string(STRING), and
   - tokenize()
 * The constructor initializes 'is'
 * The default constructor is explicitely deleted
 * Its descendants implement different approaches to tokenizing:
   (1) word by word: relies on simple statement: "is >> temp;"
       (class WordTokenizer)
   (2) character by character: the heart of its tokenize() member goes like:

         char c;
         while(true) {
           is.get(c);
           ...
         }

 * TODO
   [ ] add remove_trailing_space(STRING&) and remove_leading_space(STRING&)
       to Tokenizer as descendants might want to call it
 */


#include <iostream>
#include <string>

class Tokenizer {
public:
  std::string temp;
  std::istream & is;

  // Member functions:
  virtual void process_string(std::string & wd) = 0;
  virtual void tokenize() = 0;

  static bool has_non_space_char(const std::string & str) {
    for(char c : str) {
      if(!isspace(c))
        return true;
    }
        return false;
  };

  // Constructor(s) and destructor:
  Tokenizer(std::istream & i) : is(i) {};
  virtual ~Tokenizer() = default;
};

#endif
