#ifndef DIMTOKEN_H
#define DIMTOKEN_H

#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

/* Compilation unit 'dimtoken'
 * defines:
   (1) concept DIMTOKEN as implementing:
       - get_text()   -> std::string_view
       - get_width()  -> float type
       - get_depth()  -> float type
       - get_height() -> float type
   (2) class dimtoken<FLOAT>:
       a trivial implementation of concept DIMTOKEN
   (3) class dimline, which:
       1. knows how wide a line can get (member var 'max_width')
       2. tells whether it can accomodate a new DIMTOKEN object
       3. takes DIMTOKEN's in (push_back(DIMTOKEN))
   TODO
   [ ] a dimline should hold maximum depth and height variables,
       which would be updated whenever a deeper or higher token
       than the previous ones on the line is brought in.
   [v] write class dimtokenizer<> here
       or elsewhere in "dimtokenizer.h", then #include "it"
       Actually, most of this class has already been written
       in "TextAndWidthTokenizer.h" as class TextAndWidthTokenizer<>,
       with a focus on UTF-8 multibyte (2, 3, and 4) characters.

   * Improve on class TextAndWidthTokenizer:
   [ ] write code for handling XML entities.
   [ ] write code for choosing between monospace and non-monospace

   [ ] Could you write code to work out
       how many lines a given paragraph would be broken into?
   [ ] Could you write code to work out the total height
       (assuming vertical separation or not)?
   *
   *
   */
 */


/*
template <template <typename> typename TKN, typename F = double>
concept DIMTOKEN = requires(TKN<F> tkn)
*/
template <typename TKN>
concept DIMTOKEN = requires(TKN tkn)
{
  {tkn.get_text()  } -> std::convertible_to<std::string_view>;

  {tkn.get_width() } -> std::convertible_to<double>;
  {tkn.get_depth() } -> std::convertible_to<double>;
  {tkn.get_height()} -> std::convertible_to<double>;
};

template <typename F = double,
          typename TEXT=std::string // You want an owning string
                                    // in case the original string disappears
                                    // as when you are reading tokens from an std::istream
                                    // like so: ISTREAM >> WORD; // WORD is an std::string

         >
class dimtoken {
public:
  typedef std::string_view string_view_t;
  typedef             TEXT        text_t;
protected:
  text_t text;
  F      width, depth, height;
public:
  string_view_t get_text()  const {return text;};
  F             get_width() const {return width;};
  F             get_depth() const {return depth;};
  F             get_height() const {return height;};
  // Constructors:
  dimtoken(string_view_t sv, F w, F d = 1.0) : text(sv), width(w), depth(d), height(2*d) {};
  dimtoken(string_view_t sv, F w, F d, F h) : text(sv), width(w), depth(d), height(h) {};
}; // class token

template <typename F = double,
          typename TEXT = std::string, // You want an owning string
                                       // in case the original string disappears
          DIMTOKEN TKN = dimtoken<F,TEXT>,
          template <typename> typename CONT = std::vector>
class dimline {
public:
  typedef TKN token_t;
protected:
  F max_width;
  F spacewidth;
  F current_width;
  CONT<TKN> tokens;
public:
  virtual void add_token(const token_t& tk) {
    tokens.push_back(tk);
    current_width += tk.get_width();
  };
  std::size_t    size() const {return tokens.size();}; // spaces = size() - 1
  F width_less_spaces() const {return current_width;}; // return the sum of all widths
  F width(F sw) const {return width_less_spaces() + sw * (size() - 1);};
  F width() const {return width(spacewidth);};
  bool fits_token(const token_t& tk, F mw) const
  {
    return width() + spacewidth + tk.get_width() < mw;
  };
  bool fits_token(const token_t& tk) const {return fits_token(tk,max_width);};
  virtual bool add_token_if_fits(const token_t& tk) {
    if(fits_token(tk)) {
      add_token(tk);
      return true;
    }
    else
      return false;
  };
  //
  dimline(F mw = 33.0, F sw = 1.0) : max_width(mw), spacewidth(sw), current_width(0.0) {};
  ~dimline() = default;
  /*
  dimline(std::initializer_list<TKN> il, F mw = 33.0, F sw = 1.0)
  {
    for( const token_t & tk : il)
      add_token(tk);
  };
  */
}; // class dimline

#endif
