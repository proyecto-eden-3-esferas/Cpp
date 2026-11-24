#ifndef NAME_VALIDATOR_CPP
#define NAME_VALIDATOR_CPP

template <typename CHAR, typename STRING>
bool name_validator<CHAR,STRING>::is_allowed_mid(CHAR c) const {
  return is_allowed_beg(c) || other_mid_chars.contains(c) || isdigit(c);
};
template <typename CHAR, typename STRING>
bool name_validator<CHAR,STRING>::is_allowed_beg( CHAR c) const {
  return isalpha(c)        || other_beg_chars.contains(c);
};

template <typename CHAR, typename STRING>
bool name_validator<CHAR,STRING>::is_allowed(std::basic_string_view<CHAR> sv) const {
  if(sv.length() < 1)
   return false;
  else {
    if(! is_allowed_beg(sv[0]) )
      return false;
    for(CHAR c : sv)
      if(! is_allowed_mid(c))
        return false;
    return true;
  } // else
};

#endif
