#ifndef BASIC_TOKENIZER_H
#define BASIC_TOKENIZER_H

#include <iostream>
#include <string>
#include <cctype>

/* File "basic_tokenizer.h" declares and defines several classes:
 * basic_tokenizer<CHAR.STRING>
 * basic_tokenizer<CHAR.STRING>::iterator
 * text_tokenizer< CHAR.STRING>
 */

template <typename CH = char, typename STR = std::basic_string<CH> >
class basic_tokenizer {
/** Class basic_tokenizer<> is meant for building tokenizer-lexers
 *  It consist mainly of typedef, using declarations, and static member functions
 *
 */
public:
  typedef std::basic_istream<CH> istream_t;
  typedef std::basic_string< CH>  string_t;
public:
  istream_t& in;
  //constructor(s) and destructor:
  basic_tokenizer() = delete;
  basic_tokenizer(istream_t& i) : in(i) {};
  /** static member functions:
   *  @note instantiation of basic_tokenizer<> requires initialization with a std::istream reference
   */
  static std::size_t tokenize(istream_t& i, string_t& s) {
    //* Get one word (space delimited string) from an input stream into a string
    i >> s;
    return s.size();
  };
  static bool   ends_with_punct(const string_t& s) {return std::ispunct(s. back());}; // C++ 20
  static bool starts_with_punct(const string_t& s) {return std::ispunct(s.front());}; // C++ 20
  static bool get_through_lt(istream_t& i, string_t& s); // eat up to and including the next '<' character
  class iterator {
  /** basic_tokenizer<>::iterator is used for reading space separated strings from an std::istream
   */
  public:
    istream_t* inP;
    string_t s;
  public:
    using iterator_category = std::input_iterator_tag;
    typedef string_t  value_type;
    typedef string_t* pointer;
    typedef string_t& reference;
  public:
    iterator begin() { return iterator(*inP);}
    iterator end()   { return iterator(); }
    // operators:
          reference operator*( )       {return s;}
    const reference operator*( ) const {return s;}
          pointer*  operator->()       {return &s;}
    const pointer*  operator->() const {return &s;}
    iterator& operator++() {
      *inP >> s;
      if(inP->eof())
        inP = nullptr;
      return *this;
    };
    iterator operator++(int) {iterator tmp = *this; ++(*this); return tmp;}
    friend bool operator== (const iterator& lft, const iterator& rgt) {
      if(lft.inP == nullptr && rgt.inP == nullptr)
        return true;
      else
        return false;
    };
    friend bool operator!= (const iterator& lft, const iterator& rgt) {
      if(lft.inP == nullptr && rgt.inP == nullptr)
        return false;
      else
        return true;
    };
    // constructor:
    iterator()             : inP(nullptr) {s.clear();};
    iterator(istream_t& i) : inP(&i)      {s.clear();};
  };  // end of class iterator
  //
  iterator begin() {return iterator(in);};
  iterator end()   {return iterator();};
};

template <typename CH = char, typename STR = std::basic_string<CH>>
class text_tokenizer {
/** A class for tokenizing ordinary text.
 0.  Lots of text is made up of strings of some or no alphanumeric characters plus some or no punctuation.
 1.  Then some member function might return a list of its components in an in-out variable
     or some other scheme might be implemented, such as setting when the alphanumeric part starts, where it ends...
 2.  What about strings without spaces but with punctuation characters between alphanumeric characters? Like O'Hara
 */
 enum class part_types {alphabetic=1, numeric=2,
                        punctuation=4, opening_quote=8, closing_quote=16, single_quote};
public:


};

#endif
