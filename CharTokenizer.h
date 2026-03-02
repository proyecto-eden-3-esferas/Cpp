#ifndef CHAR_TOKENIZER_H
#define CHAR_TOKENIZER_H

/*
 * Class CharTokenizer processes an in-stream character by character
 * It defines two virtual public member functions:
   (1) tokenize(), which unlike WordTokenizer::tokenize() works char by char
   (2) check(CHAR c), which acts on c and returns true if c is "special"
       and shouldn't be appended to string WordTokenizer::temp
   NOTE: descendants just override check()
   NOTE: check() is only called withing tokenize()
         and derived classes just override check()
   NOTE: parent WordTokenizer is only used
         (1) as an interface, specifically tokenize()
         (2) to inherit variables (string) temp and (istream &) is;
 */



#include <iostream>
#include <string>

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif

class CharTokenizer : public WordTokenizer {
public:

  using WordTokenizer::temp;
  using WordTokenizer::is;

  // Member variables:

  // Member functions:

  void process_string(std::string & wd) override {
    std::cout << "PROCESS STRING: \"" << wd << "\"\n";
    wd.clear();
  };

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
  CharTokenizer(std::istream & i) : WordTokenizer(i) {};
  ~CharTokenizer() = default;
};

#endif
