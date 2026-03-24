#ifndef WORD_TOKENIZER_H
#define WORD_TOKENIZER_H

/* Class WordTokenizer is an oversimple tokenizer
   that relies on extractor (operator>>) into a string
 * It does little more than chunking text up into manageable strings.
   enough to make a good tokenizer of text
   but for the fact that punctuation gets appended (as in "lemon.")
 * Member functions are declared virtual
   in case another programmer wants to derive from WordTokenizer
 */

#ifndef TOKENIZER_H
#include "Tokenizer.h"
#endif

#include <iostream>
#include <string>

class WordTokenizer : public Tokenizer {
public:
  using Tokenizer::temp;
  using Tokenizer::is;

  // Member functions:

  void process_string(std::string & wd) override {
    std::cout << "PROCESS WORD: \"" << wd << "\"\n";
  };

  void tokenize() override {
    while(true) {
      is >> temp;
      if(is)
        process_string(temp);
      else
        break;
    }
  };

  // Constructor:
  WordTokenizer(std::istream & i) : Tokenizer(i) {};
  virtual ~WordTokenizer() = default;

};

#endif
