/* File "registered_key.test.cpp" explores the possibilities of
    the STL associative containers: std::map and std::multimap,
    as well as their hash versions (std::unordered_(multi)map)
 *
 */

#include <initializer_list>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>

/*
 * Keys must be unregistered or an exception gets thrown upon access
 * Registered keys are just allowed attributes or properties
 * The third template argument allows:
   - choosing a multimap (non-unique keys: one key matching several values)
   - selecting a hashed associative container (unordered_(multi)map)
 * TODO
   [ ] add member function   register_key(std::string_view newkey)
   [ ] add member function unregister_key(std::string_view newkey)
 *
 */
template <typename KEY = std::string,
          typename VAL = std::string,
          template <typename K,typename M> typename MAP = std::map
          >
class registered_key : public std::map<KEY,VAL> {
public:
  typedef KEY key_type;
  typedef VAL mapped_type;
  typedef MAP<KEY,VAL> map_t;
  typedef std::set<KEY>     set_t;
  using map_t::map;
  // Member variables:
  std::set<key_type> allowed_keys;
  /* Accessors throw std::out_of_range exception
   * if a key not contained in 'allowed_keys' is requested */
        auto & operator[] (const key_type& k);
  const auto & at(         const key_type& k) const;
  //
  registered_key(std::initializer_list<key_type> il) : allowed_keys(il) {};
};
template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
auto & registered_key<KEY,VAL,MAP>::operator[] (const key_type& k) {
  if(! allowed_keys.contains(k)) {
    throw std::out_of_range("key not present in \'allowed_keys\'");
  }
  return map_t::operator[](k);
};
template <typename KEY, typename VAL, template <typename K,typename M> typename MAP>
const auto & registered_key<KEY,VAL,MAP>::at(const key_type& k) const {
  if(! allowed_keys.contains(k)) {
    throw std::out_of_range("key not present in \'allowed_keys\'");
  }
  return map_t::at(k);
};

using namespace std;

typedef registered_key<std::string,std::string, std::map> stringmap_t;

// Define some initializer_list<string>'s for maps from string:
std::initializer_list<std::string> infoil = {"author", "date", "description"};

stringmap_t info0{"author", "date", "description"}, info1(infoil);

int main (int argc, const char** argv) {


  info1["author"] = "Coltrane";
  cout << "info1.author=" << info1[ "author"] << '\n';

  // cout << "info1.date="   << info1.at("date") << '\n'; // no such key


  // Use an unregistered key to elicit an out_of_range exception:
  // info1["genre"]  = "composition";                     // "genre" not allowed

  info1["date"] = "1966";

  cout << "\nNow copy \'info1\' to so far empty \'info0\' and query for \"author\":\n";
  info0 = info1;
  cout << "info0.author=" << info0[ "author"] << '\n';

  cout << '\n';


  return 0;

}
