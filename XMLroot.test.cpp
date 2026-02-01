#ifndef XMLROOT_H
#include "XMLroot.h"
#endif

typedef XMLroot<std::vector, std::map> XMLroot_t;
typedef XMLdoc<              std::map> XMLdoc_t;

using namespace std;

int main() {

  XMLdoc_t xmldoc("book");
  XMLroot_t xmlroot(xmldoc);

  return 0;
}
