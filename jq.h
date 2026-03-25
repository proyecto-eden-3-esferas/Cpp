#ifndef JQ_H
#define JQ_H

#include <iostream>
#include <format>
#include <string>
#include <string_view>

/* class jq
 */

#ifndef CONNECTION_H
#include "Connection.h"
#endif

template <typename CHAR=char>
class jq : public Connection<CHAR> {
public:
  typedef std::string string_t;
  typedef std::string_view string_view_t;

  typedef Connection<CHAR> Connection_t;
  using Connection_t::dynamic_print;

  //
  const string_t filename;


  //
  string_t map(const string_t& field) const {
    return dynamic_print("jq 'map(.[\"{}\"])' {}", field, filename);
  };
  string_t pretty() const {
    return dynamic_print("jq '.' {}", filename);
  };

  //
  jq(const string_t & fn) : filename(fn) {};
};


#ifndef SEPARATE_COMPILATION
#include "jq.cpp"
#endif

#endif
