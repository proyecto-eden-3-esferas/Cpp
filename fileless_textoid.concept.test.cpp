#ifndef FILELESS_TEXTOID_CPT
#include "fileless_textoid.concept.h"
#endif

#ifndef FILELESS_TEXTOID_H
#include "fileless_textoid.h"
#endif

#ifndef FILELESS_TEXTOID_CPP
#include "fileless_textoid.cpp"
#endif

/* Test concept Fileless_Textoid_Cpt on class fileless_textoid<>  */

int main() {

  static_assert(Fileless_Textoid_Cpt< fileless_textoid<char,1000> >);

  return 0;
}
