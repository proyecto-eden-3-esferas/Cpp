#ifndef TOKENIZER_H
#define TOKENIZER_H

/*
 * TODO
 [ ] regular expressions 'wd_regex' and so on need appending ".*" for them to match
     strings starting with a word, an identifier, and so on
 */

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

template <typename CHAR=char>
class tokenizer {
public:
  typedef std::size_t size_t;
  typedef std::size_t pos_t;
  typedef std::basic_string<CHAR> string_type;
  typedef std::basic_regex<CHAR> regex_type;
  typedef std::map<string_type,string_type> string_to_regex_string_map_type;
  typedef std::map<string_type, regex_type> string_to_regex_map_type;
  typedef tokenizer<CHAR> tokenizer_type;
//protected:
  string_to_regex_string_map_type name_to_regex_string;
  string_to_regex_map_type        name_to_regex;
  mutable std::smatch sm; // declared mutable because it is not a state variable
  mutable std::cmatch cm; // declared mutable because it is not a state variable
public:
  bool       matches(const string_type& txt,             const regex_type & re) const;
  bool       matches(const string_type& txt, size_t pos, const regex_type & re) const;
  size_t starts_with(const string_type& txt,             const regex_type & re) const;
  size_t starts_with(const string_type& txt, size_t pos, const regex_type & re) const;
  virtual void initialize_maps();
  tokenizer_type& add(const string_type& k, const string_type& re);
  size_t  size() const {return name_to_regex.size();};
  void   clear()       {       name_to_regex.clear();}
  void   clear_all();
  // The following return: "typename string_to_regex_map_type::iterator"
  auto  begin()       {return name_to_regex.begin();};
  auto    end()       {return name_to_regex.end();};
  auto cbegin() const {return name_to_regex.cbegin();};
  auto   cend() const {return name_to_regex.cend();};
  bool       matches(const string_type& txt,                  const string_type& key) const;
  bool       matches(const string_type& txt, std::size_t pos, const string_type& key) const;
  size_t starts_with(const string_type& txt,                  const string_type& re)  const;
  size_t starts_with(const string_type& txt, std::size_t pos, const string_type& re)  const;
  const string_type& get_key_for_longest_match(const string_type& str, pos_t pos) const;
  // constructor(s) and destructor:
  tokenizer() {initialize_maps();};
};

#endif
