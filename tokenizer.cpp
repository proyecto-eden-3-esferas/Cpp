#ifndef TOKENIZER_CPP
#define TOKENIZER_CPP

template <typename CHAR>
bool tokenizer<CHAR>::matches(const std::basic_string<CHAR>& txt,
                              const std::basic_regex< CHAR>& re) const {
  return std::regex_match(txt,re);
};
template <typename CHAR>
bool tokenizer<CHAR>::matches(const std::basic_string<CHAR>& txt,
                                    std::size_t pos,
                              const std::basic_regex<CHAR>& re) const {
  return std::regex_match(txt.c_str() + pos, re);
};

template <typename CHAR>
bool tokenizer<CHAR>::matches(const std::basic_string<CHAR>& txt,
                              const std::basic_string<CHAR>& key) const {
  if (name_to_regex.contains(key)) {
    return std::regex_match(txt, name_to_regex.at(key));
  }
  else
    return false;
};
template <typename CHAR>
bool tokenizer<CHAR>::matches(const std::basic_string<CHAR>& txt,
                              std::size_t pos,
                              const std::basic_string<CHAR>& key) const {
  if (name_to_regex.contains(key)) {
    return std::regex_match(txt.c_str() + pos, name_to_regex.at(key));
  }
  else
    return false;
};


template <typename CHAR>
std::size_t tokenizer<CHAR>::starts_with(const std::basic_string<CHAR>& txt,
                                         const std::basic_string<CHAR>& k) const {
  std::basic_regex<CHAR> tmp_regex;
  if(name_to_regex.contains(k)) {
    return starts_with(txt, name_to_regex.at(k));
  } else
    return 0;
};
template <typename CHAR>
std::size_t tokenizer<CHAR>::starts_with(const std::basic_string<CHAR>& txt,
                                         std::size_t pos,
                                         const std::basic_string<CHAR>& k) const {
  std::basic_regex<CHAR> tmp_regex;
  if(name_to_regex.contains(k)) {
    return starts_with(txt.c_str() + pos, name_to_regex.at(k));
  } else
    return 0;
};

template <typename CHAR>
std::size_t tokenizer<CHAR>::starts_with(const std::basic_string<CHAR>& txt,
                                         const std::basic_regex< CHAR>& re) const {
  if(matches(txt, re)) {
    std::regex_search(txt, sm, re);
    if(sm.size() > 1)
      return sm.length(sm.size() - 1);
    else
      return 0;
  }
  else {
    return 0;
  }
};
template <typename CHAR>
std::size_t tokenizer<CHAR>::starts_with(const std::basic_string<CHAR>& txt,
                                               std::size_t pos,
                                         const std::basic_regex< CHAR>& re) const {
  if(matches(txt, pos, re)) {
    std::regex_search(txt.c_str() + pos, cm, re);
    if(cm.size() > 1)
      return cm.length(cm.size() - 1);
    else
      return 0;
  }
  else {
    return 0;
  }
};

template <typename CHAR>
tokenizer<CHAR>& tokenizer<CHAR>::add(const std::basic_string<CHAR>& k,
                                      const std::basic_string<CHAR>& restr) {
  name_to_regex_string[k] = restr;
  name_to_regex[       k] = restr;
  return *this;
};

template <typename CHAR>
void tokenizer<CHAR>::clear_all() {
  name_to_regex_string.clear();
  name_to_regex       .clear();
};

template <typename CHAR>
void tokenizer<CHAR>::initialize_maps() {
  add("word",          R"(^([a-zA-Z]+).*)");
  add("identifier",    R"(^([_\w][_\w0-9]*).*)");
  add("integer",       R"(^([-+]?[0-9]+).*)");
  add("decimal",       R"(^([-+]?[0-9]*\.[0-9]*).*)");
  add("scientific",    R"(^([-+]?[0-9]*\.[0-9]*[eE][+-]?[0-9]+).*)");
  add("append-string", ".*");
  /*
  name_to_regex_string["word"]          = string_type{R"(^([a-zA-Z]+).*)"};
  name_to_regex_string["identifier"]    = string_type{R"(^([_\w][_\w0-9]*).*)"};
  name_to_regex_string["integer"]       = string_type{R"(^([-+]?[0-9]+).*)"};
  name_to_regex_string["decimal"]       = string_type{R"(^([-+]?[0-9]*.[0-9]*).*)"};
  name_to_regex_string["scientific"]    = string_type{R"(^([-+]?[0-9]*.[0-9]*[eE][+-]?[0-9]+).*)"};
  name_to_regex_string["append-string"] = string_type{".*"};
  */
};

#endif
