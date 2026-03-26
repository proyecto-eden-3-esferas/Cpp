#ifndef AUTH_CONNECTION_H
#define AUTH_CONNECTION_H

#include <string>
#include <string_view>

/* Class AuthConnection<> just holds variables 'user' and 'password'
 * It is a parent of InetConnection<>
 * Most DataBase Management Systems require a user:password
   (except SQLite)
 */

template <typename CHAR = char>
class AuthConnection {
public:
  typedef std::basic_string<     CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;

  // Member variables
  string_t user     = "admin";
  string_t password = "skyblue";

  // Constructors and destructor
  AuthConnection(string_view_t usr = "admin", string_view_t pw = "skyblue") : user(usr), password(pw) {};

};



#endif
