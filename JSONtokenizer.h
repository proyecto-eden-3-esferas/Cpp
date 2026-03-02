#ifndef JSON_TOKENIZER_H
#define JSON_TOKENIZER_H

//#include <fstream>
#include <iostream>
//#include <stack>
#include <string>

template <typename CHAR=char>
class UniversalTokenizer {
public:

};

template <typename CHAR=char>
class JSONtokenizer {
public:
  typedef std::stack<CHAR> charstack_t;
  typedef std::basic_string<CHAR> string_t;
  typedef std::basic_istream<CHAR> istream_t;

  // Member variables:
  string_t    result_string;
  istream_t & is;

  // Member functions:
  virtual void quotes_found();
  virtual void  colon_found();
  virtual void opening_brace_found();
  virtual void closing_brace_found();
  virtual void opening_bracket_found();
  virtual void closing_bracket_found();
  virtual void escape_found();
  void run();

  // Constructor and destructor:
  JSONtokenizer(istream_t & i) : is(i) {};
  ~JSONtokenizer() = default;
};
