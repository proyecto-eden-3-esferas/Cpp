#ifndef NAMESPACES_H
#include "Namespaces.h"
#endif

#include <string>
#include <utility>

typedef std::string key_type;
typedef std::string mapped_type;
typedef std::pair<key_type, mapped_type> pair_t;
typedef Namespaces<> Namespaces_type;

pair_t namespace_array[] = {
  pair_t{"db", "http://docbook.org/ns/docbook"},
  pair_t{"xs", "http://www.w3.org/2001/XMLSchema"},
  pair_t{"xsi", "http://www.w3.org/2001/XMLSchema-instance"},
  pair_t{"xlink", "http://www.w3.org/1999/xlink"},
  pair_t{"xi", "http://www.w3.org/2001/XInclude"},
  pair_t{"mml", "http://www.w3.org/1998/Math/MathML"},
  pair_t{"svg", "http://www.w3.org/2000/svg"}
};

Namespaces_type nss0, nss1("http://docbook.org/ns/docbook");


using namespace std;

int main() {

  cout << boolalpha;

  cout << "Has \'nss0\' a default namespace? " << nss0.has_default_namespace() << '\n';
  cout << "Has \'nss1\' a default namespace? " << nss1.has_default_namespace() << '\n';

  nss0.insert(std::begin(namespace_array),
              std::end(  namespace_array));
  nss0.set_default_namespace("http://www.w3.org/1999/HTML");
  nss0.print(cout);

  return 0;
}
