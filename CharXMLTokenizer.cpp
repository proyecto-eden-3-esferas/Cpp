#ifndef CHAR_XML_TOKENIZER_CPP
#define CHAR_XML_TOKENIZER_CPP

#ifndef CHAR_XML_TOKENIZER_H
#include "CharXMLTokenizer.h"
#endif

#include <cctype>

// CharXMLTokenizer::process_string(STRING) should also handle entities (&quot; and such)
void CharXMLTokenizer::process_string(std::string & wd) {
  std::cout << "TEXT NODE: \"" << wd << "\"\n";
  wd.clear();
};

void CharXMLTokenizer::process_opening_tag() {
  std::getline(is, temp, '>');
  if(temp.back() == '/')
    std::cout << "STAND-ALONE TAG: \"" << temp << "\"\n";
  else
    std::cout << "OPENING TAG: \"" << temp << "\"\n";
  temp.clear();
};

bool CharXMLTokenizer::check_gt_alnum(char c) {
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

void CharXMLTokenizer::process_closing_tag() {
  std::getline(is, temp, '>');
  std::cout << "CLOSING TAG: \"" << temp << "\"\n";
  temp.clear();
};
bool CharXMLTokenizer::check_gt_slash(char c) {
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


void CharXMLTokenizer::process_question() {
  std::getline(is, temp, '>');
  if(temp.back() == '?') {
    temp.pop_back();
    std::cout << "QUESTION: <?" << temp << "?>\n";
  }
  else
    std::cout << "QUASI-QUESTION: <?" << temp << ">\n";
  temp.clear();
};
bool CharXMLTokenizer::check_gt_question(char c) {
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
bool CharXMLTokenizer::check_gt_bang(char c) {
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
