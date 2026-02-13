/* File "event-driven-parser.test.cpp"
 */

#include <fstream>
#include <iostream>
#include <stack>
#include <string>


#ifndef SIMPLE_EVENT_DRIVEN_PARSER_H
#define SIMPLE_EVENT_DRIVEN_PARSER_H

template <typename CHAR=char, typename STRING=std::basic_string<CHAR> >
class simple_xml_parser {
public:
  typedef   CHAR   char_t;
  typedef STRING string_t;
  typedef STRING buffer_t;
  typedef std::basic_ifstream<char_t> ifstream_t;
  typedef std::stack<string_t> name_stack_t;
  // boolean member variables:
  // enum class status {node_text, tag};
  bool in_angles  = false;
  bool in_entity  = false;
  bool ignore_empty_text_nodes = true;
  // remaing member variables:
  CHAR c; // used for reading from stream
  ifstream_t ifs;
  string_t buffer;
  string_t entity_buffer;
  string_t name;
  name_stack_t name_stack;
  // member functions:
  bool good() {return ifs.good();};
  virtual void read_char()       {ifs.get(c); std::cout << '_' << std::flush;};
  virtual CHAR  get_char() const {return c;};
  virtual void parse_to_the_end(); // parse to the end;
  virtual void parse(char_t c);
protected:
  bool buffer_empty(const buffer_t& buf) const;
  virtual void read_name()              {read_name(name);};
  virtual void read_name(buffer_t& buf)                   ;
  virtual void read_entity_name_and_tag_tail();
  virtual void into_angles();
  virtual void closing_angle();
  virtual void process_text_node();
  virtual void process_question(); // "<?" has just been read
  virtual void process_bang();     // "<!" has just been read
  virtual void start_entity();
  virtual void   end_entity();
  virtual void dispatch_entity();
  virtual void amp_in_entity(); // '&' is ilegal inside an entity
  //
  virtual void dispatch_opening_tag() {};
  virtual void dispatch_closing_tag() {};
  virtual void dispatch_text_node(const buffer_t& buf) {};
public:  // Constructors and destructor:
  simple_xml_parser(const CHAR * fn) : ifs(fn) {};
  virtual ~simple_xml_parser()        {ifs.close();};
};

#endif

#ifndef SIMPLE_EVENT_DRIVEN_PARSER_CPP
#define SIMPLE_EVENT_DRIVEN_PARSER_CPP

#ifndef SIMPLE_EVENT_DRIVEN_PARSER_H
#include "event-driven-parser.h"
#endif


// Implementations of member functions of class simple_xml_parser<>:

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::parse_to_the_end() {
  while (true) {
    read_char();
    if(good())
      parse(c);
    else
      break;
  } // while
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::read_name(buffer_t& buf) {
  read_char();
  while( isalnum(c) || c == ':' || c == '-') {
    buf += c;
    read_char();
  }
#ifdef DEBUG
  std::cout << "[READ NAME \"" << buf << "\"]" << std::flush;
#endif
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::read_entity_name_and_tag_tail() {
  name.clear();
  name += c;
  read_name(name);
  name_stack.push(name);
  while (get_char() != '>') {
    buffer += get_char();
    read_char();
  } // Now c holds character '>'
  std::cout << "NAME: \"" << name << "\", AND TAIL: \"" << buffer << "\"\n";
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::into_angles() {
  process_text_node();
  in_angles = true;
  buffer.clear();
  // read the next character after '<' then process it:
  read_char();
  switch (c) {
    case '?': process_question();
              break;
    case '!': process_bang();
              break;
    case '/': name.clear();
              read_name();
              if(name != name_stack.top()) {
                std::cout << "\n\"" << name << "\" != \"" << name_stack.top() << "\"\n";
                // raise an exception or issue a warning!!!
              }
              name_stack.pop();
              break;
    default:  read_entity_name_and_tag_tail();
              break;
  } // switch
  buffer.clear();
  name.clear();
  in_angles = false;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::parse(char_t c) {
  switch (c) {
    case '<': into_angles();
              break;
    case '&': if(!in_entity) {
                start_entity();
              } else
                amp_in_entity();
              break;
    case ';': if(in_entity) {
                end_entity();
              } else
                buffer += c;
              break;
    case '>': closing_angle();
              break;
    default:  buffer += c;
  }
};

template <typename CHAR, typename STRING>
bool simple_xml_parser<CHAR,STRING>::buffer_empty(const buffer_t& buf) const {
  for(CHAR c : buffer)
    if(!isspace(c))
      return false;
  return true;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::closing_angle() {
  process_text_node();
  in_angles = false;
  buffer.clear();
};
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_text_node() {
  if( ! (ignore_empty_text_nodes && buffer_empty(buffer)) ) {
#ifdef DEBUG
    std::cout << "TEXT NODE: \"" << buffer << "\"\n";
#endif
    dispatch_text_node(buffer);
  }
};


template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_question() {
  buffer.clear();
  read_name();
  // skip white space
  while (true) {
    if ( c == '?')
      break;
    else {
      buffer += c;
      read_char();
    }
  }
  std::cout << "READ NAME \"" << name << "\", THEN \"" << buffer << "\"";
  read_char(); // c == '>'
  if ( c != '>')
    std::cout << ", THEN EXPECTED > BUT READ \'" << c << '\'';
  std::cout << '\n';
  in_angles = false;
};
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_bang() {
  buffer.clear();
  read_name();
  // skip white space
  while (true) {
    if ( c == '!')
      break;
    else {
      buffer += c;
      read_char();
    }
  }
  std::cout << "READ NAME \"" << name << "\", THEN \"" << buffer << "\"";
  read_char(); // c == '>'
  if ( c != '>')
    std::cout << ", THEN EXPECTED > BUT READ \'" << c << '\'';
  std::cout << '\n';
  in_angles = false;
};


template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::start_entity() {
  entity_buffer.clear();
  in_entity = true;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::end_entity() {
  dispatch_entity();
  in_entity = false;
};
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::dispatch_entity() {
  std::cout << "Entity: \"" << entity_buffer << "\"\n";
  in_entity = false;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::amp_in_entity() {
  std::cout << "An \'\' does not belong inside an entity name!\n";
};

#endif



typedef char char_type;
typedef simple_xml_parser<char_type> simple_xml_parser_t;

int main()
{

  simple_xml_parser_t sp0("simple.xml");

  std::cout << "\nParse file as XML:\n";
  sp0.parse_to_the_end();

  return 0;
}
