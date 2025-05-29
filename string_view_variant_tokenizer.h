#ifndef STRING_VIEW_VARIANT_TOKENIZER_H
#define STRING_VIEW_VARIANT_TOKENIZER_H

/* Class string_view_variant_tokenizer<CHAR>
 * Member get_char_or_quote() is good for tokenizing JSON
 * Still, it should
   [ ] recognize integers
   [ ] recognize floats
   [ ] recognize other "words" (null, true, false...)
   [ ] check for matching quotes through:
       bool is_closing_quote(CHAR c) const;
       and possibly raise an exception if not.
 * Member get_special_or() is good for tokenizing XML
 * TODO s
 [ ] honour parameter bool drop_quotes when false
 [ ] should bool 'after_escape' and all related checks be removed?
 */


#include <cctype> // for bool issspace(char c)
#include <iostream>
#include <string>
#include <string_view>
#include <variant>

template <typename CHAR=char>
class string_view_variant_tokenizer {
public:
  typedef std::size_t size_t;
  typedef string_view_variant_tokenizer<CHAR> string_view_variant_tokenizer_type;
  typedef        std::basic_string_view<CHAR> string_view_type;
  typedef                  std::variant<CHAR, string_view_type> char_string_type;
  // declare struct sense and define some variants relying on it:
  template <size_t N>
  struct sense {
    string_view_type sns;
                   string_view_type value() const {return sns;};
    operator       string_view_type      () const {return sns;};
    //operator const string_view_type      () const {return sns;};
    //std::ostream& operator<< (std::ostream& o) const {o << this->sns; return o;};
    sense(string_view_type svt) : sns(svt) {};
  };
  typedef sense<0>  word_type;
  typedef sense<1> quote_type;
  typedef std::variant<CHAR,word_type,quote_type> char_string_quote_type;
  typedef std::variant<CHAR, int, double,
                       word_type,quote_type>    char_num_string_quote_type; // for future use
  typedef std::basic_string<CHAR> string_type;
protected:
  const string_type& str;    // 'str' holds a run of characters to be tokenized
  const string_type  special_chars;
  unsigned int       offset = 0;  // offset for next character to be read
  const string_type  quotes; // possibly in pairs
  bool skws;
protected: // Vars used by member functions:
  string_view_type::size_type next_delim_pos;
  string_view_type::size_type      start_pos;
  bool after_escape;
  bool inside_quotes;
  char last_quote_char; // for matching quotes, such as '<' and '>' in XML
protected:
  void check_for_escape();
  void skip_white_space();
  bool is_special(char c) const {return special_chars.contains(c);};
  bool is_quote(  char c) const {return        quotes.contains(c);};
  bool is_closing_quote(CHAR c) const;
  size_t how_many_natural(size_t off) const; // how many succeding characters are digits?
  size_t how_many_natural()           const {return how_many_natural(offset);};
  size_t how_many_integer(size_t off) const; // how many chars are [-]digit+?
  bool is_minus(          size_t off) const {return str[off] == '-';};
  bool is_minus_or_digit( size_t off) const {return is_minus(off) || isdigit(str[off]);};
  size_t how_many_integer()           const {return how_many_natural(offset);};
  void toggle_after_escape();
  void toggle_inside_quotes(); // AS YET UNUSED!
  string_view_type remaining_string() {return str.substr(offset);};
public:
  void reset(size_t off = 0) {offset = off;};
  operator bool () const {return offset < str.length();};
  bool  is_valid() const {return offset < str.length();};
public: // Member variables and functions for telling identifiers/words
  string_type other_mid_chars{"_.:-"}; // characters allowed besides alphanumeric
  string_type other_beg_chars{"_"}; // characters allowed besides letters, typically underscore (_)
  bool digits_allowed = true;  // Are digits allowed after the first character?
protected:
  virtual bool is_allowed_beg(CHAR c) const;
  virtual bool is_allowed_mid(CHAR c) const;
  virtual bool is_allowed_end(CHAR c) const {return is_allowed_mid(c);};
  string_view_type process_quote(bool drop_quotes = true);
  quote_type       process_into_quote(bool dq=true) {return quote_type(process_quote(dq));};
  word_type        process_word();
  word_type        process_into_word() {return word_type(process_word());};
public:
  char_string_type       get_special_or(); // output either a special char or a string holding no sp. chars
  char_string_type       get_char_or_quote(bool drop_quotes = true);      // Output variant<CHAR,    QUOTE>
  char_string_quote_type get_char_word_or_quote(bool drop_quotes=true); // Output variant<CHAR,STR,QUOTE>
  /* Constructor(s):
   * They take a string of text ('s') and two short strings for
   * (1) special characters ('sp')
   * (2) characters for quoting, such as " and ' ('q')
   * Now, for its member get_char_or_quote() to work correctly
   * 'quotes' and 'special_chars' should not overlap */
  string_view_variant_tokenizer(const string_type& s,
                                const string_type& sp = ",:;{}()[]<>/\'\"",
                                size_t off = 0,
                                const string_type& q = "\"",
                                bool iq = false, // str is understood to be outside quotes
                                bool skws = true)
                                : str(s), special_chars(sp), offset(off),
                                  quotes(q), inside_quotes(iq), skws(skws) {};
  //
  static bool starts_with(const string_view_type& s, const string_view_type& w, size_t off=0);
  bool starts_with(const string_view_type& w, size_t off) const {return starts_with(str, w, off);};
  bool starts_with(const string_view_type& w)                  const {return starts_with(str, w, offset);};
  char_string_type get_char_or_quote_former();
};

#endif
