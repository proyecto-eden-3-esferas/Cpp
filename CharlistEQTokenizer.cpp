#ifndef CHARLISTESC_TOKENIZER_CPP
#define CHARLISTESC_TOKENIZER_CPP

#ifndef CHARLISTESC_TOKENIZER_H
#include "CharlistEQTokenizer.h"
#endif


bool CharlistEQTokenizer::is_esc(char c) const {
  if(c == esc) {
    return true;
  } else
    return false;
};
bool CharlistEQTokenizer::is_quote(char c) const {
  return c == quot;
};

void CharlistEQTokenizer::process_string(std::string & wd) {
  if(in_quotes) {
    std::cout << "PROCESS IN QUOTES: \"" << wd << "\"\n";
  }
  else {
#ifdef FORMER
    if(wd.length() > 0)
      std::cout << "PROCESS OUT OF QUOTES: \"" << wd << "\"\n";
#else
    if(drop_empty_string_when_out_of_quotes) {
      if(has_non_space_char(wd))
        std::cout << "PROCESS OUT OF QUOTES: \"" << wd << "\"\n";
    }
    else
      std::cout   << "PROCESS OUT OF QUOTES: \"" << wd << "\"\n";

#endif
  }
  wd.clear();
};

bool CharlistEQTokenizer::check_against_esc(char c) {
  if(is_esc(c)) {
    temp += is.get(); // just append the next char to 'temp'
    return true;
  } else
    return false;
};

bool CharlistEQTokenizer::check_against_quot(char c) {
  if(is_quote(c))
  { // into a run between quotes:
    process_string(temp);
    in_quotes=true;

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

    process_string(temp);
    in_quotes=false;

    return true;
  } // if (being our of (a run between) quotes
  else
    return false;
};













#endif
