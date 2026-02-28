#ifndef INET_CONNECTION_H
#define INET_CONNECTION_H

#include <format>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <stdlib.h>

/* Class InetConnection<CHAR> handles connections to (a server)
 * It arose as a parent for CouchDB
 * TODO:
   [ ] query() and query(RESOURCE) should rely on (protected) members:
       - make_query_string(), and
       - make_query_string(RESOURCE)
   [x] produce formated strings with <format>
   [ ] improve on stdlib::system(COMMAND)
       possibly though a static boolean 'is_unix'
   [x] Instances of 'InetConnection' hold collections of resources as strings (names)
 */

#ifndef CONNECTION_H
#include "Connection.h"
#endif

template <typename CHAR = char>
class InetConnection : public Connection<CHAR> {
public:
  typedef     Connection<CHAR>     Connection_t;
  typedef InetConnection<CHAR> InetConnection_t;
  typedef unsigned int port_t;
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  // Member variables
  using Connection_t::user;
  using Connection_t::password;
  port_t port;
  string_t IP_address;
  static inline const       string_t    local_IP_address{"127.0.0.1"};
  static inline std::vector<string_t> installed_browsers{"falkon", "firefox"};

  // Member functions:
  virtual void run(string_view_t cmd) const;
  virtual void check() const = 0;
  virtual void query() const = 0;
  virtual void query( string_view_t resource) const = 0;
  virtual void create(string_view_t resource)       = 0;
  virtual void erase( string_view_t resource)       = 0;
  virtual void add_document_to(string_view_t doc, string_view_t resource) = 0;

  // Interface for redirecting cout to a std::basic_stringstream<CHAR> (stringstream):
  typedef std::basic_streambuf<   CHAR>    streambuf_t;
  typedef std::basic_stringstream<CHAR> stringstream_t;
  stringstream_t resultss;
  bool output_redirected;
  string_t get_result_string() const;
  streambuf_t *cout_buf; //
  streambuf_t *  ss_buf;
  void redirect_output_to_string();

  // Constructor(s) and virtual destructor:
  InetConnection(port_t prt, string_view_t usr="admin", string_view_t pw = "skyblue", string_view_t IPaddr="127.0.0.1");
  virtual ~InetConnection();
};



// Implementations:

template <typename CHAR>
void InetConnection<CHAR>::run(string_view_t cmd) const {
  system(cmd.data());
};

template <typename CHAR>
InetConnection<CHAR>::string_t InetConnection<CHAR>::get_result_string() const {
  return resultss.str();
};

template <typename CHAR>
void InetConnection<CHAR>::redirect_output_to_string() {
  std::cout.rdbuf(ss_buf);
  output_redirected = true;
};

template <typename CHAR>
InetConnection<CHAR>::InetConnection(port_t prt, string_view_t usr, string_view_t pw, string_view_t IPaddr)
  : Connection_t(usr, pw),
    port(prt), IP_address(IPaddr),
    output_redirected(false), cout_buf(std::cout.rdbuf()), ss_buf(resultss.rdbuf())
  {};

template <typename CHAR>
InetConnection<CHAR>::~InetConnection() {
  if(output_redirected) {
    std::cout.rdbuf(cout_buf);
    output_redirected=false;
  }
};

#endif
