#ifndef CHARLISTESC_TOKENIZER_H
#define CHARLISTESC_TOKENIZER_H

/* class CharListEscTokenizer improves on CharListTokenizer
 * by recognizing escape characters and quotes.
 * When an escape character is found, the next character is read and
   process_escaped(char ch) is called even if it is a special character, too.
 * Thus, the sequence \" should not treat " as a special character
   and thereby signal termination of a string, but append " to 'temp'
 * Quote characters (default is "):
   - toggle boolean variable 'in_quotes'
   - cause processing of 'temp' string (alternatively, they just get appended to 'temp')
 * This class comes very close to processing JSON!!!
 * TODO
   [ ] add a boolean 'skip_ws' so that white space is dropped outside quotes
   [ ] by and large, lines like "is >> std::ws" or just involving std::ws need reviewing
   [ ] going into quotes should process escapes but not characters in 'charlist'
 */

#ifndef CHARLIST_TOKENIZER_H
#include "CharListTokenizer.h"
#endif


class CharListEscTokenizer : public CharListTokenizer {
public:
  using WordTokenizer::temp;
  using WordTokenizer::is;
  using CharListTokenizer::charlist;

  // Member variables:
  bool skip_ws;
  char esc;
  char quot;
  bool in_quotes;

  // Member functions:

  // 'is_quote(c)' could be overriden to recognize other quote characters
  virtual bool is_quote(char c) {
    return c == quot;
  };

  virtual void process_string(std::string & wd) {
    if(in_quotes) {
      std::cout << "PROCESS IN QUOTES: \"" << wd << "\"\n";

    }
    else {
      if(wd.length() > 0)
        std::cout << "PROCESS OUT OF QUOTES: \"" << wd << "\"\n";
    }
    wd.clear();
  };

  virtual bool check_against_esc(char c) {
    if(c == esc) {
      temp += is.get();
      return true;
    } else
      return false;
  };

  virtual bool check_against_quot(char c) {
    if(c == quot) {
      if(in_quotes) {
        process_string(temp);
        in_quotes = false;
      }
      else {
        process_string(temp);
        in_quotes = true;
      }
      //temp += c;
      return true;
    } else
      return false;
  };

  bool check(char c) override {
    if(skip_ws && ! in_quotes)
      is >> std::ws;
    return check_against_charlist(c) || check_against_esc(c) || check_against_quot(c) ;
  };


  // Constructor(s) and destructor:
  CharListEscTokenizer(std::istream & i, const std::string & cl, bool sws = true, char e = '\\', char q = '\"')
  : CharListTokenizer(i,cl), esc(e), quot(q), in_quotes(false), skip_ws(sws)
  {};
  ~CharListEscTokenizer() = default;
};

#endif
