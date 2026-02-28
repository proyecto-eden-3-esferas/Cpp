#ifndef SQL_DB_H
#include "SQLite.h"
#endif

typedef SQLite<> SQLite_t;

SQLite_t sqlt0;
SQLite_t::table sqlt_tbl0("people");

int main() {

  return 0;
}
