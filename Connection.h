#ifndef CONNECTION_H
#define CONNECTION_H

/* Class Connection<CHAR> for connecting (to a server, etc.)
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

  // Member variables
  string_t user     = "admin";
  string_t password = "skyblue";

  // The resource (databases, actually) interface:
  typedef string_t resource_t;
  typedef std::set<resource_t> resources_t;
  resources_t resources;
  void   register_resource(string_view_t res)       {resources.emplace(res.data());};
  void unregister_resource(string_view_t res)       {resources.erase(  res.data());};
  bool        has_resource(string_view_t res) const {return resources.contains(res.data());};

  // Constructors and destructor
  Connection(string_view_t usr = "admin", string_view_t pw = "skyblue") : user(usr), password(pw) {};

};


#endif
