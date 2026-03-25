#ifndef CHAR_XML_TOKENIZER_CPP
#define CHAR_XML_TOKENIZER_CPP

#ifndef CHAR_XML_TOKENIZER_H
#include "CharXMLTokenizer.h"
#endif

#include <cctype>
#include <cstring>

// CharXMLTokenizer::process_string(STRING) should also handle entities (&quot; and such)
void CharXMLTokenizer::process_string(std::string & wd) {
  if(has_non_space_char(wd))
    std::cout << "TEXT NODE: \"" << wd << "\"\n";
  wd.clear();
};

void CharXMLTokenizer::dispatch_opening_name() {
  std::cout << "NAME IN OPENING TAG: " << temp << '\n';
};
void CharXMLTokenizer::process_opening_name() {
  dispatch_opening_name();
  name_stack.push(temp);
  temp.clear();
};
bool CharXMLTokenizer::is_XML_name_char(char c) const {
  return isalnum(c) || (strchr(":-_.", c) != NULL) ;
}
void CharXMLTokenizer::read_name(std::string & nm) {
  nm.clear();
  while (  is_XML_name_char(is.peek())) {
    nm += is.get();
  }
};
void CharXMLTokenizer::dispatch_attribute_pair() {
  std::cout << "attribute_map[\"" << attribute_name << "\"] = \"" << attribute_value << "\"\n";
};
void CharXMLTokenizer::process_opening_tag() {
  char c;
  //std::cout << "ABOUT TO READ NAME STARTING WITH CHAR IS: \'" << (char) is.peek() << "\'\n";
  temp.clear();
  read_name(temp);
  process_opening_name();
  is >> std::ws;
  while( isalnum(is.peek()) )
  {
    attribute_name.clear();
    read_name(attribute_name);
    is >> std::ws;
    c = is.get(); // read '='
    if(c != '=')
      std::cout << "EXPECTED \'=\' BUT GOT: \'" << c << "\'\n";
    is >> std::ws;
    // read into value
    is >> c;
    if( (c != '\"') && (c != '\'') )
      std::cout << "NON-DELIMITER CHAR: \'" << c << "\'\n";
    std::getline(is, attribute_value, c);
    attribute_map[attribute_name] = attribute_value;
    dispatch_attribute_pair();
    attribute_name.clear();
    attribute_value.clear();
    is >> std::ws;
  } // while
  c = is.get();
  if(c == '/') {
    std::cout << "STAND-ALONE TAG\n";
    name_stack.pop();
    is.ignore();
  }
  else
    std::cout << "CLOSING OPENING TAG\n";
  temp.clear();
};

bool CharXMLTokenizer::check_lt_alnum(char c) {
  if(c== '<') {
    if( isalnum( is.peek() ) ) {
      process_string(temp);
      process_opening_tag();
      return true;
    }
    else
      return false;
  }
  else
    return false;
};
void CharXMLTokenizer::dispatch_closing_tag() {std::cout << "CLOSING TAG: \"" << temp << "\"\n";};
void CharXMLTokenizer::process_closing_tag() {
  std::getline(is, temp, '>');
  if( temp.compare(name_stack.top()) )
    std::cout << "MISMATCH: " << temp << " != " << name_stack.top() << '\n';
  else {
    dispatch_closing_tag();
    name_stack.pop();
  }
  temp.clear();
};
bool CharXMLTokenizer::check_lt_slash(char c) {
  if(c== '<') {
    if( is.peek() == '/' ) {
      process_string(temp);
      is.ignore();
      process_closing_tag();
      return true;
    }
    else
      return false;
  }
  else
    return false;
};

void CharXMLTokenizer::xml_declaration(const std::string& attributes) const {
  std::cout << "XML DECLARATION WITH ATTRIBUTES: " << attributes << '\n';
};

void CharXMLTokenizer::process_pi(const std::string& name, const std::string& instruction) const {
  std::cout << "READ NAME: <?"  << attribute_name << " AND INSTRUCTION: "  << attribute_value << '\n';
};

void CharXMLTokenizer::process_question() {
#ifndef FORMER

  // read the name of the processing instruction into 'attribute_name':
  attribute_name.clear();
  is >> attribute_name;
  std::cout << "READ NAME: <?"  << attribute_name << '\n';
  is >> std::ws;

  //read the remainder until "?>" is come across:
  char c = is.get();
  while(true) {
    if(c == '?') {
      if(is.peek() == '>') {
        is.ignore(); // don't push '?' and drop '>''
        break;
      }
      else
        attribute_value += c; // push '?'
    }
    else
      attribute_value += c;
    c = is.get();
  } // while

  // Dispatch name and instruction:
  if(attribute_name.compare("xml"))
    process_pi(attribute_name, attribute_value);
  else
    xml_declaration(attribute_value);
#else
  std::getline(is, temp, '>');
  if(temp.back() == '?') {
    temp.pop_back();
    std::cout << "QUESTION: <?" << temp << "?>\n";
  }
  else
    std::cout << "QUASI-QUESTION: <?" << temp << ">\n";
  temp.clear();
#endif
};
bool CharXMLTokenizer::check_lt_question(char c) {
  if(c== '<') {
    if( is.peek() == '?' ) {
      process_string(temp);
      is.ignore();
      process_question();
      return true;
    }
    else
      return false;
  }
  else
    return false;
};

void CharXMLTokenizer::process_bang() {
  std::getline(is, temp, '>');
  if(temp.back() == '!') {
    temp.pop_back();
    std::cout << "BANG: <!" << temp << "!>\n";
  }
  else
    std::cout << "QUASI-BANG: <!" << temp << ">\n";
  temp.clear();
};
bool CharXMLTokenizer::check_lt_bang(char c) {
  if(c== '<') {
    if( is.peek() == '!' ) {
      process_string(temp);
      process_bang();
      return true;
    }
    else
      return false;
  }
  else
    return false;
};


/*
bool CharXMLTokenizer::check_gt(char c) {
  if(c == '<') {
    process_string(temp);
    std::getline(is, temp, '>');
    std::cout << "TAG: <" << temp << ">\n";
    temp.clear();
    return true;
  }
  else
    return false;
};
*/

#endif
