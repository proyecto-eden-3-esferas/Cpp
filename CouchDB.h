#ifndef COUCHDB_H
#define COUCHDB_H

#ifndef INET_CONNECTION_H
#include "InetConnection.h"
#endif

#ifndef COMMA_SEPARATED_ARRAY_OF_STRINGS_H
#include "write_comma_separated_array_of_strings.h"
#endif

/* Class CouchDB<CHAR> is derived from InetConnection<CHAR>
 * It handles connections to a CouchDB server
 * A big TODO list has been moved up to the InetConnection header ("InetConnection.h")
 * TODO:
   [ ] write a parent abstract/interface class (DataBase<>) and move some members up into it...
   [ ] write JQ sibling class
   [ ] make CouchDB and JQ children of JsonQuery,
       whereto write_comma_separated_array_of_strings() will be fittingly moved
   [ ] write SQLite cousin class
 */


template <typename CHAR = char>
class CouchDB : public InetConnection<CHAR> {
public:
  typedef     Connection<CHAR>     Connection_t;
  typedef InetConnection<CHAR> InetConnection_t;
  typedef CouchDB<   CHAR> CouchDB_t;
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;
  //
  using typename InetConnection_t::port_t;
  using InetConnection_t::port;
  using InetConnection_t::IP_address;
  using InetConnection_t::local_IP_address;

  // Member functions:
  using InetConnection_t::run;
  using InetConnection_t::user;
  using InetConnection_t::password;
  void check()                        const override;
  /* The query() overloads:
   * First a query string is put together, then it is run.
   * Note that parameter 'fields' is a JavaScript array like ["term", "definition"].
   * TODO
   * [ ] write an overload of make_query_string(RESOURCE,FIELDS):
         prototypes already been commented out, see below
   * [ ] taking a 'fields' parameter of type std::vector or any other container
   */
  string_t make_query_string()                       const;
  string_t make_query_string(string_view_t resource) const;
  /*
  string_t make_query_string(string_view_t resource, string_view_t selector) const;
  template <template <typename> typename CONT>
  string_t make_query_string(string_view_t resource, const CONT<string_t> & fields) const;
  */
  //
  void query()                        const override;
  void query( string_view_t resource) const override;
  void query(string_view_t resource, string_view_t selector);
  void query(string_view_t resource, string_view_t selector, string_view_t fields);
  template <template <typename> typename CONT>
  void query(string_view_t resource, string_view_t selector, const CONT<string_t> & fields) {
    string_t fields_string;
    write_comma_separated_array_of_strings(fields_string,fields);
    query(resource, selector, fields_string);
  };
  void create(string_view_t resource)       override;
  void erase( string_view_t resource)       override;
  //void get_all_docs_from(string_view_t doc, string_view_t resource);
  void add_document_to(string_view_t doc, string_view_t resource) override;
  void get_all_docs(string_view_t resource) const; // not very useful

  /* The resource (or databases here) interface
   * consists of (three) functions, which need bringing in.
   */
  using Connection_t::register_resource;
  using Connection_t::unregister_resource;
  using Connection_t::has_resource;

  // Constructors and destructor:
  CouchDB(port_t prt=5984, string_view_t usr="admin", string_view_t pw="skyblue", string_view_t IPaddr=local_IP_address)
  : InetConnection_t(prt, usr, pw, IPaddr)
  {};
};

#ifndef SEPARATE_COMPILATION
#include "CouchDB.cpp"
#endif

#endif
