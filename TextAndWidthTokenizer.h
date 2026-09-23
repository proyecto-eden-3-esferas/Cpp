#ifndef TEXT_AND_WIDTH_TOKENIZER_H
#define TEXT_AND_WIDTH_TOKENIZER_H

/* Class TextAndWidthTokenizer is an oversimple tokenizer
 * As is my habit, member functions are declared virtual
   in case another programmer wants to derive from it
 * TODO
 [ ] Member function tokenize(...) should load 'utf_2B_leader'
     with character matching pattern 110x xxxx
     whenever it is found, and clear it when it is not found.
 [ ] Member 'follows_up_utf_2B_leader(CHAR)'
     should check 'utf_2B_leader' is set,
     then if CHAR is not ASCII but 'utf_2B_leader' is '\0',
     throw an exception.
 [ ] Member function string_width(STRING) should be non-constant
     as it sets or clears char 'utf_2B_leader'.
     Alternatively, make 'utf_2B_leader' mutable.
 [ ] Tokens should have get_depth() and get_height() members,
     besides get_text() and get_width(),
     but perhaps that is the job of class token_handler<>
 [ ] a non-default constructor should initialize map 'charpair_to_char'
 [ ] Perhaps you want to add a float template parameter:
       template <typename F = double>
       class TextAndWidthTokenizer ...
 [ ] Perhaps you want to add a token template parameter:
       template <typename TOKEN, typename F = double>
       class TextAndWidthTokenizer ...
 [ ] Perhaps you want to enforce tokens to implement
     member functions get_text() and get_width()
 [ ] a descendant class should process XML entities
 */

#ifndef WORD_TOKENIZER_H
#include "WordTokenizer.h"
#endif

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

class TextAndWidthTokenizer {
public:

  typedef double float_type;

protected:
  /* process_string(STRING) and its client, tokenize(),
   * are kept for testing purposes.
   */
  virtual void process_string(std::string & wd) {
    std::cout << "Word \"" << wd << "\" has width: " << string_width(wd) << "\n";
  };

public:

  /* Map a pair (110x xxxx, 10xx xxxx)
   * to an equivalent ASCII char
   * where "equivalent" means having like dimensions.
   */
  typedef std::pair<char,char> charpair_t;
  std::map<charpair_t,char> charpair_to_char;
  char map_to_ASCII(char leader, char follower) const;
  char map_to_ASCII(             char follower) const;
  char utf_2B_leader; // set whenever  110x xxxx char is found
  static bool leads_2B_utf8(char c);
  static bool follows_up_utf_2B_leader(char c);
  static bool leads_3B_utf8(char c);
  static bool leads_4B_utf8(char c);

  virtual float_type   char_width(            char   c) const;
  virtual float_type string_width(std::string_view str) const;

  /* Load a sequence container
   * with tokens containing text and width dimensions.
   * If an input stream is not provided, as in the second member function,
   * std::cin is assumed
   */
  template <typename TOKEN, template<typename> typename SEQ>
  void tokenize(SEQ<TOKEN>& st, std::istream& in);
  template <typename TOKEN, template<typename> typename SEQ>
  void tokenize(SEQ<TOKEN>& st); // Deprecated or unconvincing...

  // Constructors and Destructor:
  TextAndWidthTokenizer()          = default;
  virtual ~TextAndWidthTokenizer() = default;

};

#endif


#ifndef TEXT_AND_WIDTH_TOKENIZER_CPP
#define TEXT_AND_WIDTH_TOKENIZER_CPP

char TextAndWidthTokenizer::map_to_ASCII(            char follower) const {
  if(charpair_to_char.contains(charpair_t(utf_2B_leader,follower)))
    return charpair_to_char.at(charpair_t(utf_2B_leader, follower));
  else
    return 'n';
};
char TextAndWidthTokenizer::map_to_ASCII(char leader, char follower) const {
  if(charpair_to_char.contains(charpair_t(leader,follower)))
    return charpair_to_char.at(charpair_t(leader,follower));
  else
    return 'n';
};

bool TextAndWidthTokenizer::leads_2B_utf8(char c) {
  const char mask_l2B(128 + 64);
  if((c & mask_l2B) && !(c & 32))
    return true;
  else
    return false;
};
bool TextAndWidthTokenizer::follows_up_utf_2B_leader(char c) {
  const char mask_l2B(128 + 64);
  if((c & 128) && !(c & 64))
    return true;
  else
    return false;
}
bool TextAndWidthTokenizer::leads_3B_utf8(char c) {
  const char mask_l3B(128 + 64 + 32);
  if((c & mask_l3B) && !(c & 16))
    return true;
  else
    return false;
};
bool TextAndWidthTokenizer::leads_4B_utf8(char c) {
  const char mask_l4B(128 + 64 + 32 + 16);
  if((c & mask_l4B) && !(c & 8))
    return true;
  else
    return false;
};




double TextAndWidthTokenizer::char_width(char c) const {
  switch (c) {
    case 'm':
    case 'M': return 2.0;
              break;
    case 'f': return 0.66;
              break;
    case 'i':
    case 'I':
    case 'l':
    case '1':
    case '-':
    case '_': return 0.5;
              break;
    default:
      if(ispunct(c)) {
        return 0.4;
      } else {
        if(isalnum(c))
          return 1.0;
      }
  } // switch
  return 0.0;
};

double TextAndWidthTokenizer::string_width(std::string_view str) const {
  float_type w = 0.0;
  for(const auto c : str)
    w += char_width(c);
  return w;
};

template <typename TOKEN, template<typename> typename SEQ>
void TextAndWidthTokenizer::tokenize(SEQ<TOKEN>& st, std::istream& in) {
  std::string temp;
  while(true) {
    in >> temp;
    if(in)
      st.emplace_back(temp, string_width(temp));
    else
      break;
  }
};

template <typename TOKEN, template<typename> typename SEQ>
void TextAndWidthTokenizer::tokenize(SEQ<TOKEN>& st) {tokenize<TOKEN,SEQ>(st,std::cin);};

#endif
