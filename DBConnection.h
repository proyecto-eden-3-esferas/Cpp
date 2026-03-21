#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

/* Class DBConnection<CHAR> for connecting to a database
 */



template <typename CHAR = char>
class DBConnection : virtual public Connection<CHAR> {
public:
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  typedef Connection<CHAR> Connection_t;
  using Connection_t::user;
  using Connection_t::password;
  using Connection_t::resources;
  using Connection_t::register_resource;
  using Connection_t::unregister_resource;
  using Connection_t::has_resource;

  // Member functions:
  virtual void create_database(string_view_t db) = 0;
  virtual void    use_database(string_view_t db) = 0;
  virtual void delete_database(string_view_t db) = 0;


  // Constructors and destructor
  DBConnection(string_view_t usr = "admin", string_view_t pw = "skyblue") : Connection_t(usr,pw) {};

};


#endif
