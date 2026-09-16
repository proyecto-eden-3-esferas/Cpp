#ifndef TOKEN_HANDLER_H
#define TOKEN_HANDLER_H

#include <initializer_list>
#include <span>
#include <string>
#include <utility>
#include <vector>

/* Class token_handler<> manages lines of tokens.
 * Thus, its main member variable is a sequence container of lines,
   where a line is a container of tokens.
 * A token is a printable atom, usually a word,
   plus some dimensional information, such as its width
 * Printable atoms are separated by spaces, which may be stretchable or shrinkable.
 * Actually, such words might terminate in punctuation,
   because usually a typographical word is followed by punctuation
   without intervening spaces, as in "Hello!",
 * Words can also be just strings without spaces, like "12.4E6"
 * Other printable atoms are mathematical formulas, inline images, "foreign" glyphs...
   Just like a word, a mathematical formula is represented by a string
   in a given representational language, such as MathML or TeX.
   For instance:
   3^2 + 4^2 = 5^2
   which is treated as a token as long as it remains unsplittable.
 *
 * Turning a string of text into lines consists of three distinct tasks:
   1. chunking up text into words
      You might use WordTokenizer, in file "WordTokenizer.h"
   2. calcutating each word's width given a font
   3. fitting contiguous spans of tokens into lines not longer than a given width
 * A mathematical formula plus its length is a common non-word token
 * Tokens may be simply represented by a std::pair<STRING,WIDTH>
 * TODO
   [x] Define a 'TextAndWidth' concept
       Rename:
   [ ] class token_handler<>, and
   [ ] files "token_handler.h", "token_handler.test.cpp"
       to something meaningful,
       such as "token_paragraph" (where token = string + dimension)

   The following goals could be met
   if token_handler be made a child of and STL container:
   [ ] Iterator interface
   [ ] token_handler::push_back()

   [ ]
 */

template <typename TKN>
concept TextAndWidth = requires(TKN tkn)
{
  {tkn.get_text()} -> std::convertible_to<std::string_view>;
  {tkn.get_width()} -> std::convertible_to<double>;
  /*
  tkn.get_text();
  tkn.get_width();
   */
};


template <typename F = double,
          template <typename> typename CONT = std::vector>
class token_handler {
public:
  typedef std::string_view string_view_t;
  typedef unsigned int index_t;

  class token {
  protected:
    string_view_t text;
    F             width;
  public:
    string_view_t get_text()  const {return text;};
    F             get_width() const {return width;};
    token(string_view_t sv, F w) : text(sv), width(w) {};
  }; // embedded class token

  F max_width;
  virtual F get_max_width(index_t idx) const {return max_width;};

  template <TextAndWidth TOKEN = token>
  class line {
  protected:
    F current_width;
    CONT<TOKEN> tokens;
  public:
    typedef TOKEN token_t;
    virtual void add_token(const token_t& tk) {
      tokens.push_back(tk);
      current_width += tk.get_width();
    };
    std::size_t    size() const {return tokens.size();}; // spaces = size() - 1
    F width_less_spaces() const {return current_width;}; // return the sum of all widths
    F width(F spacewidth) const {return width_less_spaces() + spacewidth * (size() - 1);};
    //
    line()                                            : current_width(0.0) {};
    line(std::initializer_list<TOKEN> il, F cw = 0.0) : current_width(cw)  {
      for( const token_t & tk : il)
        add_token(tk);
    };
  }; // embedded class line

  // Member variable 'lines' holding instances of token_handler::line:
  typedef CONT<line<token> > container_t;
  container_t lines;
};


#endif
