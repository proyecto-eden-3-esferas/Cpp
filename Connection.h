#ifndef CONNECTION_H
#define CONNECTION_H

/* Class Connection<CHAR> for connecting (to a server, etc.)
 * Connection<> does several jobs (each declared in its own "interface"):
   - assembling strings (member 'dynamic_print(FORMAT_STRING, ARGS)')
   - executing commands (member 'run(STRING)')
   - redirecting output from the command line to a string (through a std::stringstream)
   - keeping track of resources
     (such as databases, documents, tables, files in a server)
   -

 * TODO
   [ ] Define a string nested class, possibly named 'command',
       that pipes in the Unix way:
       expression: "a | b" should execute: a + '|' + b
 */

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>

template <typename CHAR = char>
class Connection {
public:
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  /* Member 'dynamic_print(FORMAT_STRING, ARGS)' takes two arguments:
   * - a format string with {} place holders (such as "Her name is {} and she lives in {}")
   * - any number of arguments
   * Putting it all together, we would invoke:
   *   dynamic_print("Her name is {} and she lives in {}",
   *                  Ellen.name,
   *                  Ellen,city);
   */
  template <typename... Args>
  static std::string dynamic_print(std::string_view rt_fmt_str, Args&&... args);

  struct command : public string_t {
    using string_t::c_str, string_t::data;
    using string_t::string_t;
    //operator () const () {return c_str();};
    operator const string_t& () const {return static_cast<const string_t &>(*this);}
    friend string_t operator|(const string_t & l, const string_t& r) {
      return l + " | " + r;
    };
  };
  virtual void run(string_view_t cmd) const;

  // Interface for redirecting cout to a std::basic_stringstream<CHAR> (stringstream):
protected:
  typedef std::basic_streambuf<   CHAR>    streambuf_t;
  typedef std::basic_stringstream<CHAR> stringstream_t;
  stringstream_t resultss;
  bool output_redirected;
  streambuf_t *cout_buf;
  streambuf_t *  ss_buf;
public:
  void redirect_output_to_string();
  string_t get_result_string() const;

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
