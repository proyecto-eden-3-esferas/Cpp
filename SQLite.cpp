#ifndef SQLITE_CPP
#define SQLITE_CPP

#ifndef SQLITE_H
#include "SQLite.h"
#endif

// Implementations:

template <template <typename,typename> typename MAP,
          template <         typename> typename SET,
                                       typename CHAR>
std::basic_ostream<CHAR>& SQLite<MAP,SET,CHAR>::table::insert_row(ostream_t& o, const row_t & r) {
  ++idint;
  o << "INSERT (" << ") INTO " << name << " WITH VALUES()\n";
  return o;
};

#endif
