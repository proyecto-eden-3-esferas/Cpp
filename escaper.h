#ifndef ESCAPER_H
#define ESCAPER_H

/** An escaper is a class whose objects turn strings
    into other strings where certain characters have been escaped.
    You could:
    (1) Feed them a list of characters to be backslash-escaped (good enough for making C-strings), or
    (2) Specify a substitution string for each special character (as map_escaper<CH> does).
        This approach includes substituting "\c" for a character "c"
    NOTE:
    (!) Objects of class escaper<> and its child map_escaper<> do not contain a string
 */
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

template <typename CH = char>
class escaper {
public:
  typedef std::basic_string<     CH> string_t;
  typedef std::basic_string_view<CH> string_view_t;
  virtual void     escape(const string_t& in, string_t & out) const = 0;
  virtual string_t escape(const string_t& in) const;
};

template <typename CH = char>
class map_escaper : public escaper<CH> {
public:
  typedef map_escaper<CH> map_escaper_t;
  typedef std::basic_string<     CH> string_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::pair<CH,string_t> pair_t;
  typedef std::basic_ostream<CH> ostream_t;
  //
  std::map<CH,string_t> ch_to_str;
  //
  map_escaper_t& add(CH c, const string_t& s);
  void     escape(const string_t& in, string_t & out) const override;
  string_t escape(const string_t& in) const override;
  ostream_t& insert(ostream_t& o, const string_t& str) const;
  // Constructor(s) and destructor:
  map_escaper() = default;
  map_escaper(std::initializer_list<pair_t> il);
};

template <typename CH = char>
class xml_escaper : public map_escaper<CH> {
public:
  xml_escaper() {map_escaper<char>::
    add('&', "&amp;").add('\'', "&apos;").add('\"', "&quot;").add('<', "&lt;").add('>', "&gt;");};
};
template <typename CH = char>
class sql_escaper : public map_escaper<CH> {
public:
  sql_escaper() {map_escaper<char>:: add('\'', "\'\'");};
};
/*

Required Escapes

• Double quote (") → \"
• Backslash (\) → \\
• Newline / Line feed → \n
• Carriage return → \r
• Tab → \t
• Backspace → \b
• Form feed → \f
• Other control characters (U+0000 to U+001F) → \u00XX (4-digit hex code)

Optional Escapes
• Forward slash (/) → \/ (optional, sometimes used to avoid </script> issues in HTML)
• Other Unicode characters → \uXXXX (not required in valid UTF-8 JSON, though supported)
(Note: Single quotes ' and non-control characters like accents or emojis do not need escaping in JSON strings.) For quick testing, you can also paste raw text into JSONLint Escape to see how it gets formatted.
 */
template <typename CH = char>
class json_escaper : public map_escaper<CH> {
public:
  json_escaper() {/*map_escaper<char>:: add('\'', "\'\'");*/};
};

template <typename CH = char>
class general_escaper : public escaper<CH> {}; // UNIMPLEMENTED

#ifndef ESCAPER_CPP
#include "escaper.cpp"
#endif

#endif
