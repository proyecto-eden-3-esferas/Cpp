#ifndef TEXT_AND_WIDTH_TOKENIZER_H
#define TEXT_AND_WIDTH_TOKENIZER_H

/* Class WordTokenizer is an oversimple tokenizer
   that relies on extractor (operator>>) into a string
 * It does little more than chunking text up into manageable strings.
   enough to make a good tokenizer of text
   but for the fact that punctuation gets appended (as in "lemon.")
 * Member functions are declared virtual
   in case another programmer wants to derive from WordTokenizer
 */

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif

#include <iostream>
#include <cctype>
#include <string>
#include <string_view>

class TextAndWidthTokenizer : public WordTokenizer {
public:
  using WordTokenizer::temp;
  using WordTokenizer::is;

  typedef double float_type;

  // Member functions:

  void process_string(std::string & wd) override {
    std::cout << "Word \"" << wd << "\" has width: " << string_width(wd) << "\n";
  };

  virtual float_type string_width(std::string_view str) const;


  // Constructor:
  TextAndWidthTokenizer(std::istream & i) : WordTokenizer(i) {};
  virtual ~TextAndWidthTokenizer() = default;

};

#endif


#ifndef TEXT_AND_WIDTH_TOKENIZER_CPP
#define TEXT_AND_WIDTH_TOKENIZER_CPP

double TextAndWidthTokenizer::string_width(std::string_view str) const {
  float_type w = 0.0;
  for(const auto c : str) {
    switch (c) {
      case 'm':
      case 'M': w += 2.0;
                break;
      case 'f': w += 0.66;
                break;
      case 'i':
      case 'I':
      case 'l':
      case '1':
      case '-':
      case '_': w += 0.5;
                break;
      default:
        if(ispunct(c)) {
          w += 0.4;
        } else {
          if(isalnum(c))
            w += 1.0;
        }
    } // switch
  }
  return w;
};


#endif
