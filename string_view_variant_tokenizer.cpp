#ifndef STRING_VIEW_VARIANT_TOKENIZER_CPP
#define STRING_VIEW_VARIANT_TOKENIZER_CPP

#ifndef STRING_VIEW_VARIANT_TOKENIZER_H
#include "string_view_variant_tokenizer.h"
#endif

/* Implementations of members of string_view_variant_tokenizer<>
 */

template <typename CHAR>
void string_view_variant_tokenizer<CHAR>::check_for_escape() {
  if(str[offset] == '\\')
    toggle_after_escape();
  else     after_escape = false;
};
template <typename CHAR>
void string_view_variant_tokenizer<CHAR>::skip_white_space() {
  if(skws) // increment 'offset' until str[offset] is not a space char
    while(isspace(str[offset]))
      ++offset;
};
template <typename CHAR>
bool string_view_variant_tokenizer<CHAR>::is_closing_quote(CHAR c) const {
  if(! is_quote(c))
    return false;
  switch (c) {
    case '\"': if(last_quote_char=='\"') return true;
               else                      return false;
               break;
    case '\'': if(last_quote_char=='\'') return true;
               else                      return false;
               break;
    case '}':  if(last_quote_char=='{') return true;
               else                      return false;
               break;
    case ']':  if(last_quote_char=='[') return true;
               else                      return false;
               break;
    case '>':  if(last_quote_char=='<') return true;
               else                      return false;
               break;
    default:   return false;
  }
};

template <typename CHAR>
std::size_t string_view_variant_tokenizer<CHAR>::how_many_natural(std::size_t off) const {
  int i{0};
  while( (off + i < str.length()) && isdigit(str[offset+i]))
    ++i;
  return i;
};
template <typename CHAR>
std::size_t string_view_variant_tokenizer<CHAR>::how_many_integer(std::size_t off) const {
  if( ! is_minus_or_digit(off) )
    return 0;
  else {
    if(isdigit(str[off + 1]))
      return how_many_natural(off);
    else {
      if(is_minus_or_digit(off + 1) )
        return 1 + how_many_integer(off + 1);
      else
        return 0;
    }
  } // outer else
};

template <typename CHAR>
void string_view_variant_tokenizer<CHAR>::toggle_after_escape() {
  if(after_escape)
    after_escape = false;
  else
    after_escape = true;
};
template <typename CHAR>
void string_view_variant_tokenizer<CHAR>::toggle_inside_quotes() {
  if(inside_quotes)
    inside_quotes = false;
  else
    inside_quotes = true;
};

/* The identifier interface */
template <typename CHAR>
bool string_view_variant_tokenizer<CHAR>::is_allowed_beg( CHAR c) const {
  return isalpha(c)        || other_beg_chars.contains(c);
};
template <typename CHAR>
bool string_view_variant_tokenizer<CHAR>::is_allowed_mid(CHAR c) const {
  return is_allowed_beg(c) || other_mid_chars.contains(c) || isdigit(c);
};



template <typename CHAR>
string_view_variant_tokenizer<CHAR>::char_string_type string_view_variant_tokenizer<CHAR>::get_special_or() {
  start_pos = offset;

  if(is_special(str[offset])) {
    ++offset;
    skip_white_space();
    return str[start_pos];
  }
  else { // output run of non-special characters
    next_delim_pos = str.find_first_of(special_chars, offset);
    if(next_delim_pos != std::basic_string<CHAR>::npos) {
      offset = next_delim_pos;
      return std::basic_string_view<CHAR>(str.data() + start_pos, str.data() + next_delim_pos);
    } else {
      offset = str.length();
      return std::basic_string_view<CHAR>(str.data() + start_pos);
    }
  }
};

template <typename CHAR>
string_view_variant_tokenizer<CHAR>::char_string_type string_view_variant_tokenizer<CHAR>::get_char_or_quote(bool drop_quotes) {
  // The text string is assumed to start outside a quote:
  skip_white_space();
  check_for_escape(); // regardless of whether in or out of quotes

  if(is_quote(str[offset])) {
    last_quote_char = str[offset];
    // if(drop_quotes)
      ++offset;
    return process_quote(drop_quotes);
  }
  else {
    // if(starts_with("null")) std::cout << "\nnull found!\n";
    return str[offset++];
  }
};

template <typename CHAR>
string_view_variant_tokenizer<CHAR>::char_string_quote_type string_view_variant_tokenizer<CHAR>::get_char_word_or_quote(bool drop_quotes) {
  // The text string is assumed to start outside a quote:
  skip_white_space();
  check_for_escape(); // regardless of whether in or out of quotes

  if(is_allowed_beg(str[offset]) )
    return process_into_word();

  if(is_quote(str[offset])) {
    last_quote_char = str[offset];
    // if(drop_quotes)
      ++offset;
    return process_into_quote(drop_quotes);
  }
  else {
    // check up on str[offset]
    return str[offset++];
  }
};



template <typename CHAR>
string_view_variant_tokenizer<CHAR>::string_view_type
string_view_variant_tokenizer<CHAR>::process_quote(bool drop_quotes) {
       start_pos = offset;
  next_delim_pos = offset;
  // current character is inside quotes
  while( ! is_quote(str[next_delim_pos])) {
    if(str[next_delim_pos] == '\\')
      next_delim_pos += 2;
    //if(drop_quotes)
      if(next_delim_pos < str.length())
        ++next_delim_pos; // drop closing quote
      else
        break;
  } // while
  inside_quotes = false;
  offset = next_delim_pos + 1;
  return std::basic_string_view<CHAR>(str.data() + start_pos, str.data() + next_delim_pos);
};
template <typename CHAR>
string_view_variant_tokenizer<CHAR>::word_type
string_view_variant_tokenizer<CHAR>::process_word() {
       start_pos = offset;
  next_delim_pos = offset + 1; //assume str[offset] qualifies as the 1st char in a word/identifier
  // current character is inside quotes
  while( is_allowed_mid(str[next_delim_pos]) ) {
    if(next_delim_pos < str.length())
      ++next_delim_pos; // drop closing quote
    else
      break;
  } // while
  offset = next_delim_pos;
  return std::basic_string_view<CHAR>(str.data() + start_pos, str.data() + next_delim_pos);
};


template <typename CHAR>
bool string_view_variant_tokenizer<CHAR>::starts_with(const string_view_type& s,
                                                      const string_view_type& w,
                                                      std::size_t off) {
  return (std::basic_string_view<CHAR>(s.data() + off)).starts_with(w);
};


/* DEPRECATED OR FORMER */
template <typename CHAR>
string_view_variant_tokenizer<CHAR>::char_string_type string_view_variant_tokenizer<CHAR>::get_char_or_quote_former() {

  start_pos = offset;

  // The text string starts outside a quote:
  if(!inside_quotes) {

    skip_white_space();

    if(str[offset] == '\\')
      toggle_after_escape();
    else     after_escape = false; // regardless of whether in or out of quotes

    if(is_quote(str[offset])) {
      inside_quotes = true;
      last_quote_char = str[offset];
      ++offset;
      return process_quote();
    }
    else
      return str[offset++];
  } // not inside quotes
  else
    inside_quotes = true;
    return process_quote();
};

#endif
