#ifndef QNAME_H
#define QNAME_H

#include <string>
#include<string_view>

/* Class qname holds a string as a Fully Qualified Name,
   and provides member functions for getting
   (1) its prefix (namespace, URI), and
   (2) local part or name
   which are separated by a colon (:), as in "html:section".
 * The prefix may be absent, as in "section"
 */

template <typename CHAR=char>
class qname {
public:
  typedef std::basic_string<CHAR>      string_t;
  typedef std::basic_string_view<CHAR> string_view_t;
  typedef string_t::size_type size_type;
public:
  string_t str;
  const static inline size_type npos = string_t::npos;
  //operator       string& ()       {return str;};
  operator string_view_t () const {return string_view_t(str);};
  const CHAR* data() const {return str.data();};
        string_t& get();
  const string_t& get() const;
  //
  static bool contains_colon(const string_t& s);
  static size_type find_colon(const string_t& s);
  static string_view_t get_prefix_sv(const string_t& s);
  static string_view_t get_local_part_sv(const string_t& s);
  //
  bool contains_colon() const  {return contains_colon(str);};
  size_type find_colon() const {return find_colon(str);};
  string_view_t get_prefix_sv()     const {return get_prefix_sv(    str);};
  string_view_t get_local_part_sv() const {return get_local_part_sv(str);};
  //
  qname() {};
  qname(const string_t& s) : str(s) {};
  qname(const string_t& pre, const string_t& loc) : str(pre + ':' + loc) {};
};

// Implementations:

template <typename CHAR>
      std::basic_string<CHAR>& qname<CHAR>::get() {
  return str;
};
template <typename CHAR>
const std::basic_string<CHAR>& qname<CHAR>::get() const {
  return str;
};

// Static Members:

template <typename CHAR>
bool qname<CHAR>::contains_colon(const string_t& s) {
  return s.contains(':')
;};

template <typename CHAR>
std::basic_string<CHAR>::size_type qname<CHAR>::find_colon(const string_t& s) {
  return s.find(':');
};

template <typename CHAR>
std::basic_string_view<CHAR> qname<CHAR>::get_prefix_sv(const string_t& s) {
  if(contains_colon(s))
    return string_view_t(s.data(), find_colon(s));
  else
    return string_view_t(s.data(), 0);
};

template <typename CHAR>
std::basic_string_view<CHAR> qname<CHAR>::get_local_part_sv(const string_t& s) {
  if(contains_colon(s))
    return string_view_t(s).substr(find_colon(s)+1);
  else
    return string_view_t(s);
};



// Global:

template <typename CHAR>
bool operator<(const qname<CHAR>& left, const qname<CHAR>& right) {
  return left.str < right.str;
};

#endif
