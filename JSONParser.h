#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "Level.h"

/* JSONParser is an event-driven parser.
 * Whenever an element is completed, a callback in invoked
 * for the client to read both state and buffers.
 * Intended use:
 * (1) first, it should be thoroughly tested.
 * (2) a parser is derived that initializes some JSON structure/class.
 *     (Such a parser is specific for that structure/class.)
 * (3) alternatively, you can build a JSON "querier"
 */

template <typename CHAR=char>
class JSONParser {
public:
  typedef std::stack<CHAR> charstack_t;
  typedef std::basic_string<CHAR> string_t;
  typedef std::basic_istream<CHAR> istream_t;
  //
  Level<signed int> level;
  string_t    result_string;
  charstack_t openers_stack; // holds '{', '['
  istream_t& is;
  //
  void until_colon(); // read name, consume closing quotes, space, colon, some more space
  void until_quote();
  virtual void into_array();
  virtual void out_of_array();
  virtual void into_object();
  virtual void out_of_object();
  virtual void read_name();
  virtual void string_completed();
  virtual void name_completed();
public:
  void run();
  //
  JSONParser(istream_t & i) : is(i) {};
};

template <typename CHAR>
void JSONParser<CHAR>::until_colon() { };

template <typename CHAR>
void JSONParser<CHAR>::until_quote() { };

template <typename CHAR>
void JSONParser<CHAR>::into_array() {
  ++level;
  openers_stack.push('[');
};
template <typename CHAR>
void JSONParser<CHAR>::out_of_array() {
  if(openers_stack.top() == '[') {
    openers_stack.pop();
    --level;
  }
  else std::cout << "CLOSING \']\' DOES NOT MATCH OPENER: \'" << openers_stack.top() << "\'\n";
};

template <typename CHAR>
void JSONParser<CHAR>::into_object() {
  ++level;
  openers_stack.push('{');
};
template <typename CHAR>
void JSONParser<CHAR>::out_of_object() {
  if(openers_stack.top() == '{') {
    openers_stack.pop();
    --level;
  }
  else std::cout << "CLOSING \'}\' DOES NOT MATCH OPENER: \'" << openers_stack.top() << "\'\n";
};

template <typename CHAR>
void JSONParser<CHAR>::read_name() {};
template <typename CHAR>
void JSONParser<CHAR>::string_completed() {};
template <typename CHAR>
void JSONParser<CHAR>::name_completed() {};

template <typename CHAR>
void JSONParser<CHAR>::run() {
  CHAR c;
  while( ! is.eof()) {
    is.get(c);
    switch (c) {
      case '[' : into_array();  break;
      case ']' : out_of_array();  break;
      case '{' : into_object(); break;
      case '}' : out_of_object(); break;
      case '\"': read_name();   break;
      default: result_string += c;
    }

  }

};




#endif
