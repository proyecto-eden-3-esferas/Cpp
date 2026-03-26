#ifndef INET_CONNECTION_H
#define INET_CONNECTION_H

#include <format>
#include <iostream>
#include <set>
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

#ifndef AUTH_CONNECTION_H
#include "AuthConnection.h"
#endif

template <typename CHAR = char>
class InetConnection : public Connection<CHAR>, AuthConnection<CHAR> {
public:
  typedef     Connection<CHAR>     Connection_t;
  typedef InetConnection<CHAR> InetConnection_t;
  typedef AuthConnection<CHAR> AuthConnection_t;
  typedef unsigned int port_t;
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  // Member variables
  using Connection_t::run;
  using AuthConnection_t::user;
  using AuthConnection_t::password;
  port_t port;
  string_t IP_address;
  static inline const       string_t    local_IP_address{"127.0.0.1"};
  static inline std::vector<string_t> installed_browsers{"falkon", "firefox"};

  // Member functions:
  virtual void check() const = 0;
  virtual void query() const = 0;
  virtual void query( string_view_t resource) const = 0;
  virtual void create(string_view_t resource)       = 0;
  virtual void erase( string_view_t resource)       = 0;
  virtual void add_document_to(string_view_t doc, string_view_t resource) = 0;

  // Interface for redirecting cout to a std::basic_stringstream<CHAR> (stringstream):
  using Connection_t::redirect_output_to_string;
  using Connection_t::get_result_string;
  using Connection_t::output_redirected;

  // Constructor(s) and virtual destructor:
  InetConnection(port_t prt, string_view_t usr="admin", string_view_t pw = "skyblue", string_view_t IPaddr="127.0.0.1");
  ~InetConnection() override = default;
};


// Implementations:

template <typename CHAR>
InetConnection<CHAR>::InetConnection(port_t prt, string_view_t usr, string_view_t pw, string_view_t IPaddr)
  : AuthConnection_t(usr, pw),
    port(prt), IP_address(IPaddr)
  {};

#endif
