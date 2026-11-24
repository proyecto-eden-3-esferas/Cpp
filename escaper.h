#ifndef ESCAPER_H
#define ESCAPER_H

/** An escaper is a class whose objects turned strings into
    other strings where certain characters have been escaped.
    You could (1) feed them a list of characters to be backslash-escaped, or
    (2) specify a substitution string for each special character.
 */
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>

template <typename CH = char>
class escaper {
public:
  typedef std::basic_string<CH> string_t;
  virtual string_t operator() (const string_t& in) const = 0;
};

template <typename CH = char>
class backslasher : public escaper<CH> {
public:
  typedef backslasher<CH> backslasher_t;
  typedef std::basic_string<CH> string_t;
  typedef std::pair<CH,string_t> pair_t;
  typedef std::basic_ostream<CH> ostream_t;
  //
  std::map<CH,string_t> ch_to_str;
  backslasher_t& add(CH c, const string_t& s) {
    ch_to_str.insert({c,s});
    return *this;
  };
  string_t operator() (const string_t& in) const {
    string_t res;
    for(CH c : in) {
      if(ch_to_str.contains(c))
        res += ch_to_str.at(c);
      else
        res += c;
    }
    return res;
  };
  ostream_t& operator() (ostream_t& o, const string_t& str) const {
    for(CH c : str) {
      if(ch_to_str.contains(c))
        o << ch_to_str.at(c);
      else
        o << c;
    }
    return o;
  };

  // constructor(s) and destructor:
};

template <typename CH = char>
class xml_escaper : public backslasher<CH> {
public:
  xml_escaper() {backslasher<char>::
    add('&', "&amp;").add('\'', "&apos;").add('\"', "&quot;").add('<', "&lt;").add('>', "&gt;");};
};
template <typename CH = char>
class sql_escaper : public backslasher<CH> {
public:
  sql_escaper() {backslasher<char>:: add('\'', "\'\'");};
};
template <typename CH = char>
class json_escaper : public backslasher<CH> {
public:
  json_escaper() {/*backslasher<char>:: add('\'', "\'\'");*/};
};

template <typename CH = char>
class general_escaper : public escaper<CH> {}; // UNIMPLEMENTED

#endif
