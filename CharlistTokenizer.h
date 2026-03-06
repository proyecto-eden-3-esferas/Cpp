#ifndef CHARLIST_TOKENIZER_H
#define CHARLIST_TOKENIZER_H

/*
 * Class CharlistTokenizer discriminates between
   - select/special characters (typically punctuation)
   - all other characters (including white space)
 * It is an improvement on CharTokenizer, though.
   and gets very near to tokenizing JSON if second argument of constructor is ",.:{}[]"
   but, not being aware of being inside or outside quotes
   --as opposed to its child CharlistEQTokenizer, which is--
   all punctuation will be treated as special.
 * Derived classes further override virtual member check(CHAR), while here's
   CharlistTokenizer::check(CHAR) just calls CharlistTokenizer::check_against_charlist(CHAR)
 TODO
 [x] by and large, lines like "is >> std::ws" or just involving std::ws need reviewing
 */



#include <iostream>
#include <string>
#include <cctype>

#ifndef CHAR_TOKENIZER_H
#include "CharTokenizer.h"
#endif

class CharlistTokenizer : public CharTokenizer {
public:

  using CharTokenizer::temp;
  using CharTokenizer::is;

  // Member variables:
  std::string charlist;
  bool skip_leading_ws;
  bool skip_trailing_ws;

  // Member functions:
  virtual void process_char(char ch);
  void process_string(std::string & wd) override;
  virtual bool check_against_charlist(char c);
  /* check(CHAR) is called from inside CharTokenizer::tokenize().
   * It is defined in the body of the class for clarity.
   */
  bool check(char c) override {
    return check_against_charlist(c);
  };

  // Constructor(s) and destructor:
  CharlistTokenizer(std::istream & i, const std::string & cl, bool sws = true)
  : CharTokenizer(i), charlist(cl), skip_leading_ws(sws), skip_trailing_ws(sws)
  {};
  CharlistTokenizer(std::istream & i, const std::string & cl, bool slws , bool stws)
  : CharTokenizer(i), charlist(cl), skip_leading_ws(slws), skip_trailing_ws(stws)
  {};
  ~CharlistTokenizer() = default;

}; // class CharlistTokenizer

#ifndef SEPARATE_COMPILATION
#include "CharlistTokenizer.cpp"
#endif

#endif
