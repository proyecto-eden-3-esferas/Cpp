#ifndef CHAR_TOKENIZER_H
#define CHAR_TOKENIZER_H

/*
 * Class CharTokenizer processes an in-stream character by character
 * It (1) overrides pure virtual Tokenizer::tokenize()
 * which , unlike (sibling) WordTokenizer::tokenize(), works char by char
 * and (2) defines check(CHAR c), which (a) acts on c and (b) returns true if c is "special"
   and thus shouldn't be appended to string Tokenizer::temp
   NOTE: descendants just override check()
   NOTE: check() is only called within tokenize()
   NOTE: parent Tokenizer is only used
         (1) as an interface, specifically tokenize()
         (2) to inherit variables (string) temp and (istream &) is;
   NOTE: CharTokenizer does no useful work.
         It just provides a framework for descendant char-by-char tokenizers
 */



#include <iostream>
#include <string>

#ifndef TOKENIZER_H
#include "Tokenizer.h"
#endif

class CharTokenizer : public Tokenizer {
public:

  using Tokenizer::temp;
  using Tokenizer::is;

  // Member functions:

  void process_string(std::string & wd) override {
    std::cout << "PROCESS STRING: \"" << wd << "\"\n";
    wd.clear();
  };

  /* check(c) should return true (in descendant classes)
   * if 'c' is special, and therefore not to be appended to 'temp'
   */
  virtual bool check(char c) {
    return false;
  };

  void tokenize() override {
    char c;

    while(true) {
      is.get(c);

      if(!is)
        break;

      if ( check(c) )
        continue;
      else
        temp += c;
    } // while

    if(temp.length() > 0)
      process_string(temp);
  };

  // Constructor(s) and destructor:
  CharTokenizer(std::istream & i) : Tokenizer(i) {};
  ~CharTokenizer() = default;
};

#endif
