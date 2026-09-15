#ifndef TOKEN_HANDLER_H
#define TOKEN_HANDLER_H

#include <span>
#include <string>
#include <utility>
#include <vector>

/* Turning a string of text into lines consists of two distinct tasks:
   [ ] chunking up text into tokens
   [ ] fitting contiguous spans of tokens into lines not longer than a given width
 * A token as a data structure consists of its texts plus dimensional information,
   such as its width
 * Most tokens are made up of a word plus its dimension (width)
 * In this approach, a word consists of a string of non-space characters,
   such as "allure", "allure;" or even "12.4E6"
 * A mathematical formula plus its length is a common non-word token
   Just like a word, a mathematical formula is represented by a string
   in a given representational language, such as MathML or TeX
 * Tokens may be simply represented by a std::pair<STRING,WIDTH>
 * TODO
   [ ] Define a 'TOKEN_C' concept
   [ ] Iterator interface
   [ ] token_handler::push_back()
   [ ] should a container of tokens be held by reference or by value?
       should one be held at all?
   [ ]
 */

template <typename TKN>
concept TextAndWidth = requires(TKN tkn)
{
  tkn.get_text();
  tkn.get_width();
  /*
  {tkn.get_text();} -> std::convertible_to<std::string_view>
  {tkn.get_width();} -> std::convertible_to<double>
   */
  // {v.buildHtml()} -> std::convertible_to<std::string>;
};


template <typename F = double,
          template <typename> typename CONT = std::vector>
class token_handler {
public:
  typedef std::string_view string_view_t;
  typedef                  string_view_t text_t;

  class token {
  protected:
    text_t text;
    F      width;
  public:
    text_t get_text()  const {return text;};
    F      get_width() const {return width;};
    token(string_view_t sv, F w) : text(sv), width(w) {};
  }; // embedded class token

  template <TextAndWidth TOKEN = token>
  class line {
    std::span<TOKEN> tokens;
  public:
    std::size_t    size() const {return tokens.size();}; // spaces = size() - 1
    F width_less_spaces() const {return 0;}; // return the sum of all widths
    F width(F spacewidth) const {return width_less_spaces + spacewidth * (size() - 1);};
  }; // class line

  // Member variable 'lines' holding instances of token_handler::line:
  typedef CONT<line<token> > container_t;
  container_t lines;
};


#endif
