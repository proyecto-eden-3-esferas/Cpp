#ifndef COMMA_SEPARATED_ARRAY_OF_STRINGS_H
#define COMMA_SEPARATED_ARRAY_OF_STRINGS_H

#include <string>

template <template <typename> typename CONT, typename CHAR = char>
void write_comma_separated_array_of_strings(std::basic_string<CHAR>& res,
                                            const CONT<std::basic_string<CHAR> > & container,
                                            CHAR opening='[')
{
  res.clear();
  res += opening;
  int i = 0;
  for(const std::string& s : container) {
    if(i != 0)
        res += ", ";
    res += '\"';
    res += s;
    res += '\"';
    ++i;
  } // for
  switch (opening) {
    case '{': res += '}'; break;
    case '[': res += ']'; break;
    case '<': res += '>'; break;
    case '(': res += ')'; break;
  }
};

#endif
