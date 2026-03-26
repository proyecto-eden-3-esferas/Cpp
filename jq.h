#ifndef JQ_H
#define JQ_H

#include <iostream>
#include <format>
#include <string>
#include <string_view>
#include <vector>

/* class jq
 */

#ifndef CONNECTION_H
#include "Connection.h"
#endif

template <                    typename CHAR = char,
          template <typename> typename SEQ  = std::vector>
class jq : public Connection<CHAR> {
public:
  typedef std::basic_string<CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  typedef Connection<CHAR> Connection_t;
  using Connection_t::dynamic_print;
  using Connection_t::run;

  //
  const string_t filename;

  //
  struct path;

  //


  virtual void exec(string_view_t gen) const;

  void pretty() const                  { exec(gen_pretty()     );};
  void get_value(const path& p) const  { exec(gen_get_value(p) );};

  void map(const string_t& field) const { exec( gen_map(field) );};


  /* Member functions prefixed with "gen_" generate command line strings,
   * which are then called by exec(CMD).
   * They could be chained through the pipe operator:
   *   exec( gen_pretty() + '|' + gen_map(<my_field>))
   */
  string_t gen_pretty() const;
  string_t gen_get_value(const path& p) const;
  //const string_t & gen_path(const path& p, string_t & s) const;

  string_t gen_map(const string_t& field) const;

  // Constructor(s) and destructor:
  jq(string_view_t fn) : filename(fn) {};
};

#ifndef JQ_PATH_H
#include "jq.path.h"
#endif

#ifndef SEPARATE_COMPILATION
#include "jq.cpp"
#endif

#endif
