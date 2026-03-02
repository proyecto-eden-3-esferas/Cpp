#ifndef WORD_TOKENIZER_H
#define WORD_TOKENIZER_H

/* Class WordTokenizer is an oversimple tokenizer
   that relies on extractor (operator>>) into a string
 * It does little more than chunking text up into manageable strings.
   enough to make a good tokenizer of text
   but for the fact that punctuation gets appended (as in "lemon.")
 * Member functions are declared virtual
   in case someone wants to derive from WordTokenizer
 * No constructor taking a filename even though you are meant to tokenize a text file,
   which would get neatly closed in the destructor.
 * A template version could be defined like:
     template <CHAR=char>
     class WordTokenizer {
       typedef std::basic_string<CHAR> string_t;
       ...
     };
 */

#include <iostream>
#include <string>

class WordTokenizer {
public:
  std::string temp;
  std::istream & is;

  // Member functions:

  virtual void process_string(std::string & wd) {
    std::cout << "PROCESS WORD: \"" << wd << "\"\n";
  };

  virtual void tokenize() {
    while(true) {
      is >> temp;
      if(is)
        process_string(temp);
      else
        break;
    }
  };

  // Constructor:

  WordTokenizer(std::istream & i) : is(i) {};
  ~WordTokenizer() = default;

};

#endif
