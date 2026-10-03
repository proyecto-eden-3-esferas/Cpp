#ifndef UDC_H
#define UDC_H

/** File "UDC.h"
 *  UDC stands for Universal Decimal Coding
 *  Given an UDC string, this code can return:
 *  - its decimal prefix as a string (with no dots)
 *  - a float (to be compared with other floats for inclusion in ranges)
 *  - its description
 * NOTE: variable 'decimal_to_description' may be either a std::map<string,string>
         or an std::unordered_map<string,string>
 * NOTE: accessors that return a result through setting a non-const in-out param (T&)
         are considered setters and are named set_x(...)
 * TODO:
 * Derive [basic_]UDC<> from would-be class classification<CH>
 */

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

template <typename CH=char>
class basic_UDC {
public:
  typedef      basic_UDC<CH>           basic_UDC_t;
  typedef std::basic_string<CH>           string_t;
  typedef std::basic_string<CH>              udc_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::map<string_t,string_t> map_t;
  static map_t decimal_to_description;
  string_t& operator[](const string_t& key) {return decimal_to_description[key];};
  static bool contains(const string_t& udc);
  static bool set_digit_string(const udc_t& inu, string_t& outs);
  static string_view_t get_after_decimal_part(const udc_t& inu) {
    string_view_t res(inu);
    res.remove_prefix(min(res.find_first_not_of("1234567890."), res.size()));
    return res;
  };
  static bool has_non_decimal_part(const udc_t& inu);
  static bool      included_in(const udc_t& subsp, const udc_t& sp);
  static const string_t& get_description(const udc_t& inu);
};
//
template <typename INT = unsigned long int, typename F=double, typename CH=char>
class UDC : public basic_UDC<CH> {
public:
  typedef basic_UDC<CH> basic_UDC_t;
  typedef INT  int_t;
  typedef F  float_t;
  typedef std::basic_string<CH> string_t;
  typedef std::basic_string<CH> udc_t;
  //
  udc_t udc;
  // Member functions, static or not
  std::size_t size()   const {return udc.size();};
  std::size_t length() const {return udc.size();};
  operator const string_t &() const {return udc;};
  //std::basic_ostream<CH>& operator<<(std::basic_ostream<CH>& o) const {return o << this->udc;};
         bool     included_in(const udc_t& sp) const {return included_in(udc.sp);};
  const string_t& get_description() const {return basic_UDC_t::get_description(udc);};
  static float_t get_digit_float( const udc_t& inu);
  int_t   get_class_int()   const {return 0;  }; // UNIMPLEMENTED
  float_t get_class_float() const {return 0.0;}; // UNIMPLEMENTED
  // constructor(s) and destructor:
  UDC(const udc_t&  u = udc_t()) : udc(u) {};
  UDC(      udc_t&& u          ) : udc(u) {};
};
template <typename INT, typename F, typename CH>
std::basic_ostream<CH>& operator<<(std::basic_ostream<CH>& o, UDC<INT,F,CH>& u) {return o << u.udc;};

// Implementation of some member functions of class basic_UDC<>
template <>
basic_UDC<char>::map_t basic_UDC<char>::decimal_to_description({
  {"0","Science and knowledge. Organization. Computer science. Information. Documentation. Librarianship. Institution. Publications"},
  {"1", "Philosophy. Psychology"},
  {"2", "Religion. Theology"},
  {"3", "Social sciences"},
  {"5", "Mathematics. Natural sciences"},
  {"6", "Applied sciences. Medicine. Technology"},
  {"7", "The arts. Recreation. Entertainment. Sport"},
  {"8", "Language. Linguistics. Literature"},
  {"9", "Geography. Biography. History"},
#include "decimal_to_description.h"
  /*
  {"", ""},
  {"", ""},
  {"", ""},
  {"", ""},
  */
  {"4", "[Currently Vacant]"}
});
//  \{"\1"\, "\2"},
template <typename CH>
bool basic_UDC<CH>::contains(const string_t& udc) {
  // return true;
  return basic_UDC_t::decimal_to_description.contains(udc);
};

// Implementation of some member functions of class UDC<>
template <typename CH>
bool    basic_UDC<CH>::set_digit_string(const udc_t& inu, string_t& outs) {
        std::size_t idx;
  const std::size_t len = inu.length();
  outs.clear();
  for(idx=0; idx < len; ++idx) {
    if(isdigit(inu[idx]))
      outs += inu[idx];
    else {
      if(inu[idx] != '.' || idx % 3 != 0)
        break;
    }
  } // for
  return true;
};

template <typename CH>
bool  basic_UDC<CH>::included_in(const udc_t& subsp, const udc_t& sp) {
  string_t subsp_digits,     sp_digits;
  if(has_non_decimal_part(sp)) // may yield a false negative, but comparing
    return false;              // non-decimal parts for inclusion is very hard.
  if(sp_digits.length() > subsp_digits.length())
    return false;
  set_digit_string(subsp, subsp_digits);
  set_digit_string(sp,       sp_digits);
  const  int l = sp_digits.length();
  for(int i = 0; i < l; ++i)
    if(subsp_digits[i] != sp_digits[i])
      return false;
  return true;
};

template <typename CH>
bool  basic_UDC<CH>::has_non_decimal_part(const udc_t& inu) {
  for(CH c : inu)
    if( !isdigit(c) && c != '.')
      return true;
  return false;
};
template <typename CH>
const std::basic_string<CH>& basic_UDC<CH>::get_description(const udc_t& inu) {
  string_t dec;
  bool check = set_digit_string(inu, dec);
  for(int i = dec.length() - 1; i >= 0; --i) {
    if(decimal_to_description.contains(dec.substr(0,i))) {
      return decimal_to_description[dec.substr(0,i)];
    }
  } // for
  return decimal_to_description["4"];
};

// Implementation of some members in UDC<>
template <typename INT, typename F, typename CH>
F UDC<INT,F,CH>::get_digit_float( const udc_t& inu) {
  string_t tmp, res("0.");
  basic_UDC_t::set_digit_string(inu,tmp);
  res += tmp;
  return std::stod(res);
};

#endif
