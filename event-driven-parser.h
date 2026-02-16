#ifndef SIMPLE_EVENT_DRIVEN_PARSER_H
#define SIMPLE_EVENT_DRIVEN_PARSER_H

/* Class simple_xml_parser<CHAR,STRING>
 * TODO
 * [ ] handle standalone tags
 * [ ] handle comments
 * [ ] check xml declaration
 * [ ] extract xml declaration
 * [ ] extract document declaration
 * [ ] handle processing instructions
 * [ ] handle namespaces through class qname in "qname.h"
 * [ ] write: dispatch_opening_tag()
 * [ ] write: dispatch_closing_tag()
 * [ ] write: dispatch_text_node()
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <string>

template <typename CHAR=char, typename STRING=std::basic_string<CHAR> >
class simple_xml_parser {
public:
  typedef   CHAR   char_t;
  typedef STRING string_t;
  typedef std::basic_stringstream<CHAR> ss_t; // stringstream type
  typedef std::map<string_t,string_t> attributes_t;
  typedef std::basic_ifstream<char_t> ifstream_t;
  typedef std::basic_istream<char_t> istream_t;
  typedef std::basic_ostream<char_t> ostream_t;
  typedef std::stack<string_t> name_stack_t;
  // boolean member variables:
  // enum class status {node_text, tag};
  bool xml_decl_read = false;
  bool drop_leading_space    = true;
  bool drop_empty_text_nodes = true;
  /* Remaining, non-Boolean, member variables.
   * A string for storing parsed characters is called a "buffer"
   */
  CHAR c; // used for reading from stream
  CHAR delim;
  ifstream_t ifs;
  string_t buffer;
  string_t name_buffer;
  string_t value_buffer;
  name_stack_t name_stack;
  string_t entity_buffer;
  attributes_t current_attributes; // includes namaspace declarations
  // exceptions:
  struct non_matching_tagname;
  struct   zero_length_buffer;
  struct  equals_char_missing;
//protected:
  // member functions:
  virtual bool is_head_char_in_name(CHAR c)            const;
  virtual bool is_tail_char_in_name(CHAR c)            const;
  virtual bool is_empty_text_node(const string_t& str) const;
public:
  virtual void read_name(std::istream& is, string_t& buf); // does not rely on member 'c'
  virtual void process();
  virtual void get_chars_between_angles(); // last char was '<'
  virtual void get_chars_outside_angles();
  //
  virtual void process_text_node(  std::istream& is, string_t buf) const;
  virtual void process_tag(        std::istream& is, string_t buf);
  virtual void process_opening_tag(std::istream& is, string_t buf); // also for standalone tags
  virtual void process_closing_tag(std::istream& is, string_t buf);
  virtual void process_question(   std::istream& is, string_t buf);
  virtual void process_bang(       std::istream& is, string_t buf);
  virtual void process_attributes_and_namespaces(std::istream& is, attributes_t& attrs);
  virtual void print_attributes_and_namespaces(ostream_t& os, attributes_t& attrs) const;
public:  // Constructors and destructor:
  simple_xml_parser(const CHAR * fn) : ifs(fn) {};
  virtual ~simple_xml_parser()        {ifs.close();};
};

#ifndef SEPARATE_COMPILATION
#include "event-driven-parser.cpp"
#endif


#endif
