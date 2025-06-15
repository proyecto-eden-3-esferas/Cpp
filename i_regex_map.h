#ifndef I_REGEX_MAP_H
#define I_REGEX_MAP_H

/* This compilation unit declares class i_regex_map<CHAR> for handling regular expressions
   without including <regex> in its header file,
   but in its implementation file (for separate compilation)
 * Prefix i_ stands for "interface"
 *
 * TODO
 [ ] write a concept class for i_regex_map<>
 [ ] implement some intelligent matching scheme: redefine identifier
 [ ] preclude modification of primitive categories
 [ ] add unicode sequences
 [ ] add hex, oct, and bin numbers
 [ ] json identifiers
 [ ] bool is_float(n) { if(is_decimal || is_scientific) return true; else return 0;};
 [ ] declare some of the member functions as virtual: add, match, starts_with
 [ ] write member 'nest_if_not()'
 [ ] regular expressions 'wd_regex' and so on need appending ".*" for them to match
     strings starting with a word, an identifier, and so on
 */

#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

template <typename CHAR=char>
class i_regex_map {
public:
  typedef std::size_t size_t;
  typedef std::size_t  pos_t;
  typedef std::basic_string<     CHAR> string_type;
  typedef std::basic_string_view<CHAR> string_view_t;
  typedef std::map<   string_type,string_type> string_to_string_map_type;
  typedef i_regex_map<CHAR> i_regex_map_type;
//protected:
  string_to_string_map_type name_to_regex_string;
public:
  /* Add a name to regex string mapping with set/add(KEY,REGEX_STR)
   * If KEY is already mapped to a REGEX_STR,
     add(KEY,REGEX_STR) will do nothing
   */
  virtual i_regex_map_type& set(const string_type& k, const string_type& re_str);
  virtual i_regex_map_type& add(const string_type& k, const string_type& re_str);
  // virtual void initialize_maps();
  size_t  size() const;
  virtual void   clear();
  virtual void   clear_all();
  // The following return: "typename string_to_regex_map_type::iterator"
  auto  begin()       {return name_to_regex_string.begin();};
  auto    end()       {return name_to_regex_string.end();};
  auto cbegin() const {return name_to_regex_string.cbegin();};
  auto   cend() const {return name_to_regex_string.cend();};
  //
  size_t     count(const CHAR       * pTxt, const string_type& key, pos_t pos=0) const;
  size_t     count(const string_type&  txt, const string_type& key, pos_t pos=0) const;
  string_view_t get_string_view(const CHAR       * pTxt, const string_type&  re, pos_t pos=0) const;
  string_view_t get_string_view(const string_type&  txt, const string_type&  re, pos_t pos=0) const;
  const string_type& get_key_for_longest_match(const string_type& str, pos_t pos) const;
  //
  enum class parsed_language {none, universal, json, xml, sql, javascript};
  virtual i_regex_map_type & initialize(parsed_language pl = parsed_language::universal);
  // constructor(s), assignments and destructor:
  i_regex_map();
  i_regex_map(parsed_language pl);
  template <typename ITERATOR>
  i_regex_map(ITERATOR b, ITERATOR e) : name_to_regex_string(b,e) {};
  // Copy constructors and and assignment operators:
  i_regex_map(const i_regex_map_type&  r);
  i_regex_map(      i_regex_map_type&& r);
  i_regex_map_type& operator=(const i_regex_map_type& r);
  i_regex_map_type& operator=(      i_regex_map_type&& r);
  //
  i_regex_map(std::initializer_list<typename string_to_string_map_type::value_type> il);
  i_regex_map_type&
   operator=( std::initializer_list<typename string_to_string_map_type::value_type> il);
};

#endif
