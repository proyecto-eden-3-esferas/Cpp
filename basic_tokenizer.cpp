#ifndef BASIC_TOKENIZER_CPP
#define BASIC_TOKENIZER_CPP

template <typename CH, typename STR>
bool basic_tokenizer<CH,STR>::get_through_lt(
    std::basic_istream<CH>& i,
    std::basic_string< CH>& s)
  {
    std::getline(i, s, '<'); //* doesn't seem to work with std::istringstream: it ignores the delimiter
    if(i.good())
      return true;
    else
      return false;
  };
#endif
