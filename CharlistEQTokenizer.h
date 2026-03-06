#ifndef CHARLISTESC_TOKENIZER_H
#define CHARLISTESC_TOKENIZER_H

/* class CharlistEQTokenizer improves on CharlistTokenizer
   by recognizing escape characters and quotes.
(1) When an escape character is found, the next character is read and
    process_escaped(char ch) is called even if it is also a special character.
    Thus, the sequence \" should not treat " as a special character
    and thereby signal termination of a string, but append " to 'temp'
(2) Quote characters (default is "):
    - toggle boolean variable 'in_quotes'
    - cause processing of 'temp' string (alternatively, they just get appended to 'temp')
 * This class comes still closer to processing JSON!!!
   Actually, in "CharlistEQTokenizer.test.cpp" a JSON tokenizer is derived like so:
     class JSONtokenizer : public CharlistEQTokenizer {
     public:
       JSONtokenizer(std::istream & i)
       : CharlistEQTokenizer(i,",.:{}[]", true,true, '\\', '\"') {};
      };

 * TODO
   [ ] Tokenizing a JSON object:
   {"name": "Plain", "claim" :"an\"pa"}
   with CharlistEQTokenizer(STRINGSTREAM,",.:{}[]", true,true)
   (Having made 'skip_leading_space' and 'skip_trailing_space' true)
   results in errors:
     (1) PROCESS IN QUOTES: "claim"
         PROCESS OUT OF QUOTES: " "
         that is, space has not been duly dropped
   [ ] Would this enable doing away with member variable 'in_quotes'? No...
       because 'process_string(STRING)' depends on 'in_quotes'.
       Besides, checking 'in_quotes' is a safeguard. If is.eof() is reached before the closing quote,
       then an exception should be thrown: possibly the text was not compliant.
   [ ] review initialization of 'skip_ws'
   [ ] replace use of 'skip_ws' with 'skip_leading_ws' and/or 'skip_trailing_ws'
 */

#ifndef CHARLIST_TOKENIZER_H
#include "CharlistTokenizer.h"
#endif


class CharlistEQTokenizer : public CharlistTokenizer {
public:
  using Tokenizer::has_non_space_char;
  using CharlistTokenizer::temp;
  using CharlistTokenizer::is;
  //using CharlistTokenizer::charlist;
  //using CharlistTokenizer::skip_leading_ws;
  //using CharlistTokenizer::skip_trailing_ws;

  // Member variables:
  char esc;       // what the escape char is (usually: \)
  char quot;      // what the quote char is (usually: " or ')
  bool drop_empty_string_when_out_of_quotes;
  bool in_quotes;

  // Member functions:

  virtual bool is_esc(char c) const ;
  // 'is_quote(c)' could be overriden to recognize more quote characters:
  virtual bool is_quote(char c) const;

  virtual void process_string(std::string & wd);

  /* The check() "engine":
   - check(CHAR) is called by CharTokenizer::tokenize(),
   - check(CHAR) in turn calls:
     check_against_quot(CHAR)
     check_against_charlist(CHAR)
     check_against_esc(CHAR)
   */
  virtual bool check_against_esc(char c);
  virtual bool check_against_quot(char c);
  bool check(char c) override {
    if(skip_leading_ws && ! in_quotes)
      is >> std::ws;
    return check_against_quot(c) || check_against_charlist(c) || check_against_esc(c) ;
  };

  // Constructor(s) and destructor:
  CharlistEQTokenizer(std::istream & i, const std::string & cl,
                       bool slws = true, bool stws = true,
                       char e = '\\', char q = '\"')
  : CharlistTokenizer(i,cl, slws, stws),
    esc(e), quot(q), drop_empty_string_when_out_of_quotes(slws || stws),
    in_quotes(false)
  {};
  ~CharlistEQTokenizer() = default;
};

#ifndef SEPARATE_COMPILATION
#include "CharlistEQTokenizer.cpp"
#endif


#endif
