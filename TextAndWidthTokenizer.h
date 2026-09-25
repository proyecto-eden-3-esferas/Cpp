#ifndef TEXT_AND_WIDTH_TOKENIZER_H
#define TEXT_AND_WIDTH_TOKENIZER_H

/* Class TextAndWidthTokenizer is a tokenizer
   that assumes UTF-8 encoding
   and works out the width of
   - single-byte ASCII characters, and
   - some two-byte characters (previously registered)
 * The width of a multibyte character is calculated
   by mapping it to a same-width ASCII character
 * As is my habit, member functions are declared virtual
   in case another programmer wants to derive from it
 * TODO
 [ ] A class hierarchy like:
       class dimtoken;

       class TrivialTokenizer; // based on looping through ISTREAM > STRING
       class ASCII_dimtokenizer : public TrivialTokenizer
         // for non-monospace fonts
       class monospace_dimtokenizer : public TrivialTokenizer;
       class dimtokenizer : public ASCII_dimtokenizer {};
         // adds UTF-8 awareness
         // reuses ASCII_dimtokenizer::charwidth(CHAR)
       class entity_dimtokenizer : public dimtokenizer {};
         // adds a FSM for retrieving entities from streams
 [ ] This Compilation Unit might be renamed utf8_dimtokenizer
 [v] Member function string_width(...) should load 'utf_2B_leader'
     with character matching pattern 110x xxxx
     whenever it is found, and clear it when it is not found.
 [v] Member 'follows_up_utf_2B_leader(CHAR)'
     should check 'utf_2B_leader' is set,
     then if CHAR is not ASCII but 'utf_2B_leader' is '\0',
     throw an exception.
 [v] Member function string_width(STRING) should be non-constant
     as it sets or clears char 'utf_2B_leader'.
     Alternatively, make 'utf_2B_leader' mutable.
 [ ] Tokens should have get_depth() and get_height() members,
     besides get_text() and get_width(),
     but perhaps that is the job of class token_handler<>
 [v] a non-default constructor should initialize map 'charpair_to_char'
 [ ] Perhaps you want to add a float template parameter:
       template <typename F = double>
       class TextAndWidthTokenizer ...
 [ ] Perhaps you want to add a token template parameter:
       template <typename TOKEN, typename F = double>
       class TextAndWidthTokenizer ...
 [ ] Perhaps you want to enforce tokens to implement
     member functions get_text() and get_width()
 [ ] a descendant class should process XML &entities;
 */

#include <cctype>
#include <initializer_list>
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
     representing a UTF-8 2-byte multicharacter
     to an equivalent ASCII char,
     where "equivalent" means having like dimensions (esp. width).
   * For instance Spanish 'ñ' is the same width as ASCII 'n'.
   */
  typedef std::pair<char,char> charpair_t;
  std::map<charpair_t,char> charpair_to_char;
  /* register_2B(STRING,CHAR) adds an entry in 'charpair_to_char'
     if STRING.length() == 2
   * Overrides in derived classes might handle 3- and 4-byte chars
   */
  virtual void register_2B(std::string_view two, char one);
  void add_2B_entries(std::initializer_list<std::pair<std::string, char> > il);

  char map_to_ASCII(char leader, char follower) const;
  char map_to_ASCII(             char follower) const;
  char utf_2B_leader; // set whenever  110x xxxx char is found
  static bool leads_2B_utf8(  char c);
  static bool follows_up_utf8(char c);
         bool follows_up_utf_2B_leader(char c); // requires utf_2B_leader != '\0'
  static bool leads_3B_utf8(char c);
  static bool leads_4B_utf8(char c);

  std::map<char,float_type> char_to_width_map;
  void register_charwidth(char c, float_type w);
  virtual float_type   char_width(            char   c) const;
  virtual float_type string_width(std::string_view str);

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
  TextAndWidthTokenizer()
  : utf_2B_leader('\0') {};
  TextAndWidthTokenizer(std::initializer_list<std::pair<std::string, char> > il)
  : utf_2B_leader('\0')
  { add_2B_entries(il);};
  virtual ~TextAndWidthTokenizer() = default;

};

#endif


#ifndef TEXT_AND_WIDTH_TOKENIZER_CPP
#define TEXT_AND_WIDTH_TOKENIZER_CPP

void TextAndWidthTokenizer::register_2B(std::string_view two, char one) {
  charpair_to_char[std::make_pair(two[0], two[1])] = one;
};

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
bool TextAndWidthTokenizer::follows_up_utf8(char c) {
  return (c & 128) && !(c & 64);
};
bool TextAndWidthTokenizer::follows_up_utf_2B_leader(char c) {
  return follows_up_utf8(c) && (utf_2B_leader != '\0');
};
bool TextAndWidthTokenizer::leads_3B_utf8(char c) {
  const char mask_l3B(128 + 64 + 32);
  return (c & mask_l3B) && !(c & 16);
};
bool TextAndWidthTokenizer::leads_4B_utf8(char c) {
  const char mask_l4B(128 + 64 + 32 + 16);
  return (c & mask_l4B) && !(c & 8);
};
void TextAndWidthTokenizer::register_charwidth(char c, float_type w) {
  char_to_width_map[c] = w;
};
double TextAndWidthTokenizer::char_width(char c) const {
  if( char_to_width_map.contains(c))
    return char_to_width_map.at(c);
  else {
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
      case '_': return 0.9;
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
  } // else
};

double TextAndWidthTokenizer::string_width(std::string_view str) {
  float_type w = 0.0;
  for(const auto c : str) {
    if(leads_2B_utf8(c)) {
      utf_2B_leader = c;
    }
    else {
      if(follows_up_utf_2B_leader(c)) {
        if(    charpair_to_char.contains(std::make_pair(utf_2B_leader,c)))
          w += char_width( charpair_to_char[         std::make_pair(utf_2B_leader,c)] );
        else // (utf_2B_leader,c) is not a registered 2B char with var 'charpair_to_char'
          w += 1;
      } else {
        w += char_width(c);
      }
      utf_2B_leader = '\0';
    } // outer else
  }
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

void TextAndWidthTokenizer::add_2B_entries(
  std::initializer_list<std::pair<std::string, char> > il)
{
  for(const auto & elem : il)
      if(elem.first.length() == 2)
        register_2B(elem.first, elem.second);
};

#endif
