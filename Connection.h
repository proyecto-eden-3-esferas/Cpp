#ifndef CONNECTION_H
#define CONNECTION_H

/* Class Connection<CHAR> for connecting (to a server, etc.)
 * Connection<> does two jobs:
   - authorization (user:password)
   - keeping track of resources (such as databases, documents, tables, files)
     in a server
 * TODO
   [ ] consider renaming Connection<> to AuthConnection<>
       and deriving AuthConnection from Connection
 */


#include <set>
#include <sstream>
#include <string>
#include <string_view>

template <typename CHAR = char>
class Connection {
public:
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  //
  template <typename... Args>
  static std::string dynamic_print(std::string_view rt_fmt_str, Args&&... args)
  {
    return std::vformat(rt_fmt_str, std::make_format_args(args...));
  };
  virtual void run(string_view_t cmd) const;

  // Interface for redirecting cout to a std::basic_stringstream<CHAR> (stringstream):
  typedef std::basic_streambuf<   CHAR>    streambuf_t;
  typedef std::basic_stringstream<CHAR> stringstream_t;
  stringstream_t resultss;
  bool output_redirected;
  string_t get_result_string() const;
  streambuf_t *cout_buf; //
  streambuf_t *  ss_buf;
  void redirect_output_to_string();

  // The resource (usually databases, files, ...) interface:
  typedef string_t resource_t;
  typedef std::set<resource_t> resources_t;
  resources_t resources;
  void   register_resource(string_view_t res)       {resources.emplace(res.data());};
  void unregister_resource(string_view_t res)       {resources.erase(  res.data());};
  bool        has_resource(string_view_t res) const {return resources.contains(res.data());};

  // Constructors and destructor
  Connection() : output_redirected(false), cout_buf(std::cout.rdbuf()), ss_buf(resultss.rdbuf()) {};
  virtual ~Connection();
};


#ifndef SEPARATE_COMPILATION
#include "Connection.cpp"
#endif

#endif
