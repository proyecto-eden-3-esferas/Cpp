#ifndef SIMPLE_EVENT_DRIVEN_PARSER_CPP
#define SIMPLE_EVENT_DRIVEN_PARSER_CPP

#ifndef SIMPLE_EVENT_DRIVEN_PARSER_H
#include "event-driven-parser.h"
#endif

// Implementations of exceptions:

template <typename CHAR, typename STRING>
struct simple_xml_parser<CHAR,STRING>::non_matching_tagname: public std::exception {
  const char * what() const noexcept override {
    return "Non-matching tagname!";
  };
};
template <typename CHAR, typename STRING>
struct simple_xml_parser<CHAR,STRING>::zero_length_buffer: public std::exception {
  const char * what() const noexcept override {
    return "name just read has length == 0!";
  };
};
template <typename CHAR, typename STRING>
struct simple_xml_parser<CHAR,STRING>::equals_char_missing: public std::exception {
  const char * what() const noexcept override {
    return "character \'=\' in attribute key-value pair: none found!";
  };
};


// Implementations of member functions of class simple_xml_parser<>:

template <typename CHAR, typename STRING>
bool simple_xml_parser<CHAR,STRING>::is_head_char_in_name(CHAR c) const {
  return isalpha(c) || (c == '_');
};
template <typename CHAR, typename STRING>
bool simple_xml_parser<CHAR,STRING>::is_tail_char_in_name(CHAR c) const {
  return isalnum(c) || (c == '_') || c == ':' || c == '-';
};
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::read_name(std::istream& is, string_t& buf) {
  is >> std::ws;
  if(is_head_char_in_name(is.peek()))
    buf += is.get();
  while (is_tail_char_in_name(is.peek()))
    buf += is.get();
};
template <typename CHAR, typename STRING>
bool simple_xml_parser<CHAR,STRING>::is_empty_text_node(const string_t& str) const {
  for(CHAR c : str) {
    if(!isspace(c))
      return false;
  }
  return true;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process() {
  //if (ifs.good())
  if(ifs.peek() == '<')
    ifs.ignore();
  else
    throw std::exception();
  while(true) {
    get_chars_between_angles();
    ifs >> std::ws;
    if(ifs.good()) {
      if(ifs.peek() == '<') {
        ifs.ignore();
        continue;
      } else
        get_chars_outside_angles();
    }
    else
      break;  // break out of while loop if ifs isn't good()
  } // while
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::get_chars_between_angles() {
  std::getline(ifs,buffer,'>');
  ss_t tag(buffer);
  process_tag(tag, buffer);
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_opening_tag(std::istream& is, string_t buf) {
  read_name(is, name_buffer);
  name_stack.push(name_buffer);
#ifdef DEBUG
  std::cout << "PROCESS_OPENING_TAG... PUSHING NAME: \"" << name_buffer << "\"\n";
#endif
    process_attributes_and_namespaces(is,current_attributes);
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_question(std::istream& is, string_t buf) {
  std::getline(is, buf, '?');
  is.ignore(); // skip closing '>'
  static string_t question_name;
  question_name.clear();
  ss_t ss(buf);
  read_name(ss,question_name);
#ifdef DEBUG
  std::cout << "PROCESS_QUESTION... \"" << buf << "\": NAME: \"" << question_name << "\"\n";
#endif
  process_attributes_and_namespaces(ss, current_attributes);
};
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_bang(std::istream& is, string_t buf) {
  is.ignore();
  std::getline(is, buf, '!');
  is.ignore(); // skip closing '>'
#ifdef DEBUG
  std::cout << "PROCESS_BANG... \"" << buf << "\"\n";
#endif
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_closing_tag(std::istream& is, string_t buf) {
  is.ignore(); // skip '/'
  read_name(is, name_buffer);
  if(name_buffer.length() == 0)
    throw zero_length_buffer();
  if(name_stack.top() == name_buffer) {
#ifdef DEBUG
    std::cout << "POPPING NAME: \"" << name_stack.top() << "\"\n";
#endif
    name_stack.pop();
  } else {
    std::cout << "\'name_buffer\': \"" << name_buffer << "\", name_stack.top(): \"" << name_stack.top() << "\"\n" << std::flush;
    throw non_matching_tagname();
  }
};

/*
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_tag(std::istream& is, string_t buf) {
#ifdef DEBUG
  std::cout << "PROCESS_TAG <" << buf <<  ">\n";
#endif
  name_buffer.clear();
  if(is_head_char_in_name(is.peek())) {
    process_opening_tag(is, name_buffer);
  } else {
    if(is.peek() == '/')
      process_closing_tag(is,name_buffer);
    else
      //std::cout << "NEITHER BUT: <" << is << ">\n";
      std::cout << "<NEITHER>\n";
  } // else
};
 */
template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_tag(std::istream& is, string_t buf) {
#ifdef DEBUG
  std::cout << "PROCESS_TAG <" << buf <<  ">, ITSELF STARTING WITH CHAR \'" << (CHAR) is.peek() << "\'\n";
#endif
  name_buffer.clear();
  c = is.peek();
  switch (c) {
    case '/': //is.ignore();
              process_closing_tag(is,name_buffer);
              break;
    case '?': is.ignore();
              process_question(is,name_buffer);
              break;
    case '!': is.ignore();
              process_bang(is,name_buffer);
              break;
    default:  if(is_head_char_in_name(is.peek()))
                process_opening_tag(is, name_buffer);
              else
                std::cout << "<NEITHER>\n";
              break;
  }
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_attributes_and_namespaces(std::istream& is, attributes_t& attrs) {
  attrs.clear();
  is >> std::ws;
  while(is_head_char_in_name(is.peek())) {
    name_buffer.clear();
    read_name(is, name_buffer);             // read attribute name into 'name_buffer'
    is >> std::ws >> c >> std::ws >> delim; // load 'delim' with opening quoting char
    if(c != '=')
      throw equals_char_missing();
    std::getline(is, value_buffer, delim);  // read attribute value into 'value_buffer'
    attrs[name_buffer] = value_buffer;      // add entry to map 'attrs'
#ifdef DEBUG
    std::cout << "ATTRIBUTES[\"" << name_buffer<< "\"] = \"" << value_buffer << "\"\n";
#endif
    is >> std::ws;                          // drop intervening whitespace
  }
  if(is.peek() == '>')
    is.ignore();
#ifdef DEBUG
  print_attributes_and_namespaces(std::cout, attrs);
#endif
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::print_attributes_and_namespaces(ostream_t& o, attributes_t& attrs) const {
  std::cout << "ATTRIBUTES AND NAMESPACES: ";
  for (const auto & p : attrs) {
    o << ' ' << p.first << "=\"" << p.second << '\"';
  }
  o << '\n' << std::flush;
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::get_chars_outside_angles() {
  if(drop_leading_space)
    ifs >> std::ws;
  std::getline(ifs,buffer,'<');
  ss_t node(buffer);
  process_text_node(node,buffer);
};

template <typename CHAR, typename STRING>
void simple_xml_parser<CHAR,STRING>::process_text_node(std::istream& is, string_t buf) const {
  if(!drop_empty_text_nodes || !is_empty_text_node(buf)) {
#ifdef DEBUG
  std::cout << "[OUTSIDE ANGLE BRACKETS (TEXT): \"" << buf <<  "\"]\n";
#endif
  }
};

#endif
