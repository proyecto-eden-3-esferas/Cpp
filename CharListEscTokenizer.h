#ifndef CHARLISTESC_TOKENIZER_H
#define CHARLISTESC_TOKENIZER_H

/* class CharListEscTokenizer improves on CharListTokenizer
   by recognizing escape characters and quotes.
(1) When an escape character is found, the next character is read and
    process_escaped(char ch) is called even if it is a special character, too.
    Thus, the sequence \" should not treat " as a special character
    and thereby signal termination of a string, but append " to 'temp'
(2) Quote characters (default is "):
    - toggle boolean variable 'in_quotes'
    - cause processing of 'temp' string (alternatively, they just get appended to 'temp')
 * This class comes still closer to processing JSON!!!
 * TODO
   [ ] 'check_against_quot(CHAR)' should process the whole run until the closing quotes (is_quote(c)==true)
       Going into quotes should process escapes but not characters in 'charlist'
   [ ] Would this enable doing away with member variable 'in_quotes'?
       Well, process_string(STRING) depends on 'in_quotes'
       Besides, checking 'in_quotes' is a safeguard. If is.eof() is reached before the closing quote,
       then an exception should be thrown.
   [ ] review initialization of 'skip_ws'
   [ ] replace use of 'skip_ws' with 'skip_leading_ws' and/or 'skip_trailing_ws'
   [ ] add a boolean 'skip_ws' so that white space is dropped outside quotes
       by and large, lines like "is >> std::ws" or just involving std::ws need reviewing
 */

#ifndef CHARLIST_TOKENIZER_H
#include "CharListTokenizer.h"
#endif


class CharListEscTokenizer : public CharListTokenizer {
public:
  using CharListTokenizer::temp;
  using CharListTokenizer::is;
  //using CharListTokenizer::charlist;
  //using CharListTokenizer::skip_leading_ws;
  //using CharListTokenizer::skip_trailing_ws;

  // Member variables:
  bool skip_ws;
  char esc;
  char quot;
  bool in_quotes;

  // Member functions:

  virtual bool is_esc(char c) {
    if(c == esc) {
      return true;
    } else
      return false;
  }

  /* 'is_quote(c)' could be overriden to recognize more quote characters
      (such as both single and double) */
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
    if(is_esc(c)) {
      temp += is.get(); // just append the next char to 'temp'
      return true;
    } else
      return false;
  };

  virtual bool check_against_quot(char c) {
    if(is_quote(c)) {
      if(in_quotes) {
        process_string(temp);
        in_quotes = false;
        std::cout << "ERROR: check_against_quot() called when \'in_quotes\' == true \n";
      }
      else { // into a run between quotes
        process_string(temp);
#ifndef FORMER
        // read and append chars to 'temp' up until another quote
        char ch = is.get();
        while( ! is_quote(ch) ) {
          if(is_esc(ch))
            temp += is.get();
          else {
            temp += ch;
          }
          ch = is.get();
        } // while
#else
        in_quotes = true;
#endif
      } // else (being in a run between quotes
      //temp += c;
      return true;
    }
    else
      return false;
  };

  bool check(char c) override {
    if(skip_ws && ! in_quotes)
      is >> std::ws;
    return check_against_quot(c) || check_against_charlist(c) || check_against_esc(c) ;
  };

  // Constructor(s) and destructor:
  CharListEscTokenizer(std::istream & i, const std::string & cl,
                       bool slws = true, bool stws = true,
                       char e = '\\', char q = '\"')
  : CharListTokenizer(i,cl, slws, stws), esc(e), quot(q), in_quotes(false), skip_ws(slws || stws)
  {};
  ~CharListEscTokenizer() = default;
};

#endif
