#ifndef WORD_TRIM_TOKENIZER_H
#define WORD_TRIM_TOKENIZER_H

/* Class WordTrimTokenizer is a child of WordTokenizer
 * Its trim(STRING) member function removes punctuation
   from its in-out string parameter.
 * This enables writing powerfull tokenizers,
   much like its cousin CharListTokenizer
 * For instance, an override of trim might turn "eaten?--they"
   into word "eaten", punctuation '?', '-', and '-',  and word "they"
 *
 */

#include <cctype>  // for ispunct(CHAR)
#include <iostream>
#include <string>

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif


class WordTrimTokenizer : public WordTokenizer {
public:
  using WordTokenizer::temp;
  using WordTokenizer::is;
  bool drop_trailing_punctuation;

  // Member functions:

  virtual void trim(std::string & wd) {
    if(drop_trailing_punctuation)
      while(ispunct(wd.back()))
        wd.pop_back();
  };

  void tokenize() override {
    while(true) {
      is >> temp;
      if(is) {
        trim(temp);
        process_string(temp);
      }
      else
        break;
    }
  };

  // Constructor:

  WordTrimTokenizer(std::istream & i, bool dtp = true) : WordTokenizer(i), drop_trailing_punctuation(dtp) {};
  ~WordTrimTokenizer() = default;

};

#endif
