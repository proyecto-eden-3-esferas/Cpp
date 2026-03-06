#ifndef CHARLIST_TOKENIZER_CPP
#define CHARLIST_TOKENIZER_CPP

#ifndef CHARLIST_TOKENIZER_H
#include "CharlistTokenizer.h"
#endif

// Implementation of CharlistTokenizer Members:


void CharlistTokenizer::process_string(std::string & wd) {
  if(skip_trailing_ws) {
    while(isspace(wd.back()))
      wd.pop_back();
  }
  CharTokenizer::process_string(wd);
};

void CharlistTokenizer::process_char(char ch) {
  std::cout << "PROCESS CHAR: \'" << ch << "\'\n";
};

bool CharlistTokenizer::check_against_charlist(char c) {
  std::string::size_type sz;
  sz = charlist.find(c);
  if(sz != std::string::npos) {
    if(temp.length() > 0)
      process_string(temp);
    if(is) {
      process_char(c);
      // drop space after 'c' so that 'temp' gets no leading space:
      if(skip_leading_ws)
        is >> std::ws;
      //continue;
    }
    else {
#ifdef DEBUG
      std::cout << "got special character \'" << c << "\', but \'is\' tests false, so break our of while!\n";
#endif
      //break;
    }
    return true;
  } // if
  return false;
};


// Constructors:


#endif
