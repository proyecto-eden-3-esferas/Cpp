#ifndef CHARLIST_TOKENIZER_H
#define CHARLIST_TOKENIZER_H

/*
 * Class CharListTokenizer discriminates between
   - select/special characters (typically punctuation)
   - all other characters (including white space)
 * It is an improvement on CharTokenizer, though.
   and gets very near to tokenizing JSON if second argument of constructor is ",.:{}[]"
   but, not being aware of being inside or outside quotes --as opposed to CharListEscTokenizer, which is--
   all punctuation will be treated as special.
 * Derived classes further override virtual member check(CHAR), while here
   CharListTokenizer::check(CHAR) just calls CharListTokenizer::check_against_charlist(CHAR)
 TODO
 [x] by and large, lines like "is >> std::ws" or just involving std::ws need reviewing
 */



#include <iostream>
#include <string>
#include <cctype>

#ifndef CHAR_TOKENIZER_H
#include "CharTokenizer.h"
#endif

class CharListTokenizer : public CharTokenizer {
public:

  using CharTokenizer::temp;
  using CharTokenizer::is;

  // Member variables:
  std::string charlist;
  bool skip_leading_ws;
  bool skip_trailing_ws;

  // Member functions:

  void process_string(std::string & wd) override {
    if(skip_trailing_ws) {
      while(isspace(wd.back()))
        wd.pop_back();
    }
    CharTokenizer::process_string(wd);
  };

  virtual void process_char(char ch) {
    std::cout << "PROCESS CHAR: \'" << ch << "\'\n";
  };

  virtual bool check_against_charlist(char c) {
    std::string::size_type sz;
    sz = charlist.find(c);
    if(sz != std::string::npos) {
      if(temp.length() > 0)
        process_string(temp);
      if(is) {
        process_char(c);
        // drop space after 'c' so that 'temp' gets no leading space:
        if(skip_leading_ws)
          is >> std::ws;
        //continue;
      }
      else {
#ifdef DEBUG
        std::cout << "got special character \'" << c << "\', but \'is\' tests false, so break our of while!\n";
#endif
        //break;
      }
      return true;
    } // if
    return false;
  };

  bool check(char c) override {
    return check_against_charlist(c);
  };

  // Constructor(s) and destructor:
  CharListTokenizer(std::istream & i, const std::string & cl, bool sws = true)
  : CharTokenizer(i), charlist(cl), skip_leading_ws(sws), skip_trailing_ws(sws)
  {};
  CharListTokenizer(std::istream & i, const std::string & cl, bool slws , bool stws)
  : CharTokenizer(i), charlist(cl), skip_leading_ws(slws), skip_trailing_ws(stws)
  {};
  ~CharListTokenizer() = default;
};

#endif
