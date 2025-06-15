#ifndef I_REGEX_MAP_CPP
#define I_REGEX_MAP_CPP

#ifndef I_REGEX_MAP_H
#include "i_regex_map.h"
#endif

#include <regex>

template <typename CHAR>
using regex_type = std::basic_regex<CHAR>;

template <typename CHAR>
i_regex_map<CHAR>& i_regex_map<CHAR>::set(const std::basic_string<CHAR>& key,
                                          const std::basic_string<CHAR>& restr) {
  name_to_regex_string[key] = restr;
  return *this;
};
template <typename CHAR>
i_regex_map<CHAR>& i_regex_map<CHAR>::add(const std::basic_string<CHAR>& key,
                                          const std::basic_string<CHAR>& restr) {
  if(! name_to_regex_string.contains(key))
    return set(key,restr);
  else
    return *this;
};

template <typename CHAR>
std::size_t i_regex_map<CHAR>::size() const {return name_to_regex_string.size();};

template <typename CHAR>
void i_regex_map<CHAR>::clear()     {       name_to_regex_string.clear();}
template <typename CHAR>
void i_regex_map<CHAR>::clear_all() {       name_to_regex_string.clear();}



// Implementation of member functions count(TEXT,KEY) and count(TEXT,POS, KEY)
template <typename CHAR>
std::size_t i_regex_map<CHAR>::count(const CHAR * pTxt,
                                           const std::basic_string<CHAR>& key,
                                                 std::size_t pos) const {
  regex_type<CHAR> re;
  std::cmatch cm;
  if(name_to_regex_string.contains(key)) {
    re =                 name_to_regex_string.at(key);
    if(std::regex_search(pTxt + pos, cm, re)) {
      if(cm.size() > 0)
        return cm.length(cm.size() - 1);
      else
        return 0;
    }
    else return 0;
  }
  else {
    return 0;
  }
};
template <typename CHAR>
std::size_t i_regex_map<CHAR>::count(const std::basic_string<CHAR>& txt,
                                           const std::basic_string<CHAR>& key,
                                                 std::size_t pos) const {
  regex_type<CHAR> re;
  std::cmatch cm;
  if(    name_to_regex_string.contains(key)) {
    re = name_to_regex_string.at(      key);
    if(std::regex_search(txt.c_str() + pos, cm, re)) {
      if(cm.size() > 0)
        return cm.length(cm.size() - 1);
      else
        return 0;
    }
    else return 0;
  }
  else {
    return 0;
  }
};

// Implementations of member function get_string_view(TEXT,KEY,POS)
template <typename CHAR>
i_regex_map<CHAR>::string_view_t
i_regex_map<CHAR>::get_string_view(const CHAR       * pTxt, const string_type&  re, pos_t pos) const {
  return string_view_t(pTxt + pos, count(pTxt, re, pos));
};
template <typename CHAR>
i_regex_map<CHAR>::string_view_t
i_regex_map<CHAR>::get_string_view(const string_type&  txt, const string_type&  re, pos_t pos) const {
  return string_view_t(txt.c_str() + pos, count(txt, re, pos));
};

template <typename CHAR>
const i_regex_map<CHAR>::string_type&
      i_regex_map<CHAR>::get_key_for_longest_match(const i_regex_map<CHAR>::string_type& str,
                                                         i_regex_map<CHAR>::pos_t        pos) const
{
  std::size_t max_len{0}, temp_len{0};
  const string_type* keyPtr;
  for(const auto & pair : name_to_regex_string) {
    temp_len = count(str, pair.first, pos);
    if(temp_len > max_len) {
      max_len = temp_len;
      keyPtr = &pair.first;
    }
  }
  return *keyPtr;
};

template <typename CHAR>
i_regex_map<CHAR>& i_regex_map<CHAR>::initialize(i_regex_map<CHAR>::parsed_language pl) {
  switch (pl) {
    case parsed_language::none: break;
    case parsed_language::sql:
    case parsed_language::xml:
    case parsed_language::universal:
      set("word",          R"([a-zA-Z]+)"); // only letters
      set("identifier",    R"([_\w][_\w0-9]*)");
      set("integer",       R"([-+]?[0-9]+)");
      set("decimal",       R"([-+]?[0-9]*\.[0-9]*)");
      set("scientific",    R"([-+]?[0-9]*\.[0-9]*[eE][+-]?[0-9]+)");
      set("truth_value",   R"(true | false)");
      set("null",          R"(null)");
      set("undefined",     R"(undefined)");
    case parsed_language::javascript:
      set("identifier",    R"([$_\w][_\w0-9]*)"); // allow $ to be the 1st char
      break;

    default:
      break;
  }
  return *this;
};

// Constructors and destructor:

template <typename CHAR>
i_regex_map<CHAR>::i_regex_map()
{initialize();};
template <typename CHAR>
i_regex_map<CHAR>::i_regex_map(i_regex_map<CHAR>::parsed_language pl) {
  initialize(pl)
;};

// Copy and assignment:
template <typename CHAR>
i_regex_map<CHAR>::i_regex_map(const i_regex_map<CHAR>& r) :
  name_to_regex_string(r.name_to_regex_string)
{};
template <typename CHAR>
i_regex_map<CHAR>::i_regex_map(i_regex_map<CHAR>&& r) :
  name_to_regex_string(std::move(r.name_to_regex_string))
  {};

template <typename CHAR>
i_regex_map<CHAR> &
i_regex_map<CHAR>::operator=(const i_regex_map<CHAR>& r) {
  name_to_regex_string =           r.name_to_regex_string;
  return *this;
};
template <typename CHAR>
i_regex_map<CHAR> &
i_regex_map<CHAR>::operator=(      i_regex_map<CHAR>&& r) {
  name_to_regex_string = std::move(r.name_to_regex_string);
  return *this;
};

// Constructors with std::initializer_list<>
template <typename CHAR>
i_regex_map<CHAR>::
i_regex_map(std::initializer_list<typename i_regex_map<CHAR>::string_to_string_map_type::value_type> il) :
  name_to_regex_string(il)
  {};
template <typename CHAR>
i_regex_map<CHAR>&
i_regex_map<CHAR>::
operator=(std::initializer_list<typename i_regex_map<CHAR>::string_to_string_map_type::value_type> il) {
  name_to_regex_string = il;
  return *this;
};

#ifdef SEPARATE_COMPILATION
template class i_regex_map<char>;
#endif

#endif
