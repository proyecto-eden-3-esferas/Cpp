#ifndef UTF8_TOKENIZER_H
#define UTF8_TOKENIZER_H

#ifndef DIMTOKEN_H
#include "dimtoken.h"
#endif


#include <cctype>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

/*
 * A class hierarchy:
   - trivial_tokenizer
   - ascii_tokenizer
   - utf8_tokenizer
 *
 *
 * TODO
   [ ] initialize dimtoken's (that is, types satisfying concept DIMTOKEN)
       with their (maximum) depth and (maximum) height
   [ ] code xml_tokenizer, as handling tags,
       by default, drop them and keep the text in between
   [ ] code xml_tokenizer, as handling entities,
       by default, they are left as such,
       with provisions for an override to process them

   [x] enforce concept DIMTOKEN so that a type has members:
       - get_text()
       - get_width()
       - get_depth()
       - get_height()
 */

/* Class trivial_tokenizer is a tokenizer
 * for monospace ASCII characters
 */
class trivial_tokenizer {
public:
  typedef double float_type;
  virtual float_type char_width(char c) const;
  virtual float_type string_width(std::string_view str);
  /* Load a sequence container
   * with tokens containing text and width dimensions.
   */
  template <DIMTOKEN TOKEN, template <DIMTOKEN> typename SEQ>
  void tokenize(SEQ<TOKEN>& st, std::istream& in = std::cin);
  //protected:
  /* process_string(STRING) is meant for testing purposes.
   * This member function must not be declared const
     as member string_width(STRING) might change its internal state
     throughout its processing,
   * The solution is to declare said state variables as "mutable"
   */
  virtual void process_string(std::string & wd);
};
// Implementations:
double trivial_tokenizer::char_width(char c) const {
  if(isprint(c))
    return 1.0;
  else
    return 0.0;
};
double trivial_tokenizer::string_width(std::string_view str) {
  double w = 0.0;
  for(auto c : str)
    w += char_width(c);
  return w;
};
template <DIMTOKEN TOKEN, template <DIMTOKEN> typename SEQ>
void trivial_tokenizer::tokenize(SEQ<TOKEN>& st, std::istream& in) {
  std::string temp;
  while(true) {
    in >> temp;
    if(in)
      st.emplace_back(temp, string_width(temp));
    else
      break;
  }
};
void trivial_tokenizer::process_string(std::string & wd) {
  std::cout << "Word \"" << wd << "\" has width: " << string_width(wd) << "\n";
};



/* Class ascii_tokenizer is a tokenizer
 * for variable width ASCII characters
 */

class ascii_tokenizer : public trivial_tokenizer {
public:
  typedef double float_type;

  std::map<char,float_type> char_to_width_map;
  void       register_charwidth(char c, float_type w);
  float_type char_width(char c) const override;

};

// Implementations of ascii_tokenizer members:
void ascii_tokenizer::register_charwidth(char c, float_type w) {
  char_to_width_map[c] = w;
};
double ascii_tokenizer::char_width(char c) const {
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


/* Class utf8_tokenizer is a tokenizer
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
       class utf8_tokenizer ...
 [ ] Perhaps you want to add a token template parameter:
       template <typename TOKEN, typename F = double>
       class utf8_tokenizer ...
 [ ] Perhaps you want to enforce tokens to implement
     member functions get_text() and get_width()
 [ ] a descendant class should process XML &entities;
 */


class utf8_tokenizer : public ascii_tokenizer {
public:
  typedef double float_type;
  typedef ascii_tokenizer ascii_tokenizer_t;

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


  using ascii_tokenizer_t::char_to_width_map;
  using ascii_tokenizer_t::char_width;

  float_type string_width(std::string_view str) override;

  // Constructors and Destructor:
  utf8_tokenizer()
  : utf_2B_leader('\0') {};
  utf8_tokenizer(std::initializer_list<std::pair<std::string, char> > il)
  : utf_2B_leader('\0')
  { add_2B_entries(il);};
  virtual ~utf8_tokenizer() = default;

};

class xml_tokenizer : public utf8_tokenizer {
public:
  typedef double float_type;
  float_type string_width(std::string_view str) override;
/* An XML-tag_remover function
   will remove tags in XML text.
 * Thus, string
     A <strong>weak</strong> supporter
   will become
     A weak supporter
 * This is good for calculating an XML string's width on a page.
 * This tactic works well on inline elements
   (such as HTML::strong elements)
   but poorly on:
   - mathematical formulas
   - subscripts and superscripts
 * This sequence may then be passed
   into member function utf8_tokenizer::tokenize(SEQUENCE)
 */
  static void remove_XML_tag(std::string_view in, std::string & out);
  // Constructors and Destructor:
  xml_tokenizer() = default;
  xml_tokenizer(std::initializer_list<std::pair<std::string, char> > il)
  : utf8_tokenizer(il) {};
};
//Implementations:
void xml_tokenizer::remove_XML_tag(std::string_view in, std::string & out) {
  bool in_tag = false;
  for(char c : in) {
    if(in_tag) {
      if( c == '>')
        in_tag = false;
    } else {
      if( c == '<')
        in_tag = true;
      else
        out += c;
    } // outer else
  } // for loop
};
double xml_tokenizer::string_width(std::string_view str) {
  std::string temp;
  remove_XML_tag(str,temp);
  return utf8_tokenizer::string_width(temp);
};


#endif


#ifndef UTF8_TOKENIZER_CPP
#define UTF8_TOKENIZER_CPP

void utf8_tokenizer::register_2B(std::string_view two, char one) {
  charpair_to_char[std::make_pair(two[0], two[1])] = one;
};

char utf8_tokenizer::map_to_ASCII(            char follower) const {
  if(charpair_to_char.contains(charpair_t(utf_2B_leader,follower)))
    return charpair_to_char.at(charpair_t(utf_2B_leader, follower));
  else
    return 'n';
};
char utf8_tokenizer::map_to_ASCII(char leader, char follower) const {
  if(charpair_to_char.contains(charpair_t(leader,follower)))
    return charpair_to_char.at(charpair_t(leader,follower));
  else
    return 'n';
};

bool utf8_tokenizer::leads_2B_utf8(char c) {
  const char mask_l2B(128 + 64);
  if((c & mask_l2B) && !(c & 32))
    return true;
  else
    return false;
};
bool utf8_tokenizer::follows_up_utf8(char c) {
  return (c & 128) && !(c & 64);
};
bool utf8_tokenizer::follows_up_utf_2B_leader(char c) {
  return follows_up_utf8(c) && (utf_2B_leader != '\0');
};
bool utf8_tokenizer::leads_3B_utf8(char c) {
  const char mask_l3B(128 + 64 + 32);
  return (c & mask_l3B) && !(c & 16);
};
bool utf8_tokenizer::leads_4B_utf8(char c) {
  const char mask_l4B(128 + 64 + 32 + 16);
  return (c & mask_l4B) && !(c & 8);
};

double utf8_tokenizer::string_width(std::string_view str) {
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

void utf8_tokenizer::add_2B_entries(
  std::initializer_list<std::pair<std::string, char> > il)
{
  for(const auto & elem : il)
      if(elem.first.length() == 2)
        register_2B(elem.first, elem.second);
};

#endif
