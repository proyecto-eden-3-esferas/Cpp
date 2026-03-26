#ifndef JQ_CPP
#define JQ_CPP

#ifndef JQ_H
#include "jq.h"
#endif

#include <sstream>

template <                    typename CHAR,
          template <typename> typename SEQ >
void jq<CHAR,SEQ>::exec(string_view_t gen) const {
  run( dynamic_print("jq '{}' {}", gen, filename) );
};

/*
template <                    typename CHAR,
          template <typename> typename SEQ >
void jq<CHAR,SEQ>::get_value(const path& p) const {
  std::basic_stringstream<CHAR> ss;
  ss << "jq 'getpath(" ;
  p.print(ss);
  ss << ")' " << filename;
  run( ss.str() );
};
*/


/* Member functions generating a string to become a parameter into exec().
 * They bear prefix "gen_"
 */

template <                    typename CHAR,
          template <typename> typename SEQ >
std::basic_string<CHAR> jq<CHAR,SEQ>::gen_get_value(const path& p) const {
  std::basic_stringstream<CHAR> ss;
  ss << "getpath(";
  p.print(ss);
  ss << ')';
  return ss.str();
};

template <                    typename CHAR,
          template <typename> typename SEQ >
std::basic_string<CHAR> jq<CHAR,SEQ>::gen_pretty() const {
  //return dynamic_print("jq '.' {}", filename);
  return ".";
};

template <                    typename CHAR,
          template <typename> typename SEQ >
std::basic_string<CHAR> jq<CHAR,SEQ>::gen_map(const string_t& field) const {
  return dynamic_print("map(.[\"{}\"])", field);
};

/*
template <                    typename CHAR,
          template <typename> typename SEQ >
std::basic_string<CHAR> jq<CHAR,SEQ>::

template <                    typename CHAR,
          template <typename> typename SEQ >
std::basic_string<CHAR> jq<CHAR,SEQ>::
*/







#endif
