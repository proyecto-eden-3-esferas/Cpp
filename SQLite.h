#ifndef SQLITE_H
#define SQLITE_H

/* class SQLite for handling SQLite though SQL
 */

class SQL {
public:
};

#include <iostream>
#include <map>
#include <set>
#include <variant>




#ifndef SQL_DB_H
#include "SQLDataBase.h"
#endif


template <template <typename,typename> typename MAP=std::map,
          template <         typename> typename SET=std::set,
                                       typename CHAR=char>
class SQLite : public SQLDataBase<MAP,SET,CHAR> {
public:
  typedef std::string name_t;
  typedef std::basic_ostream<CHAR> ostream_t;
  //
  typedef DataBase<MAP,SET,CHAR> DataBase_t;
  using typename DataBase_t::null_t;
  using typename DataBase_t::integer_t;
  using typename DataBase_t::real_t;
  using typename DataBase_t::text_t;
  using typename DataBase_t::blob_t;
  //
  typedef std::variant<null_t, integer_t, real_t, text_t, blob_t> data_variant_t;
  typedef MAP<name_t, data_variant_t> row_t;
  struct table {
    typedef std::set<name_t> nameset_t;
    typedef MAP<name_t, data_variant_t> row_t;
    name_t       name;
    integer_t   idint;
    nameset_t nameset;
    //
    ostream_t& insert_row(ostream_t& o, const row_t & r);
    //
    table(const name_t & nm)                       : name(nm), idint(0) {}
    table(const name_t & nm, const nameset_t&  ns) : name(nm), idint(0), nameset(ns) {};
    table(const name_t & nm,       nameset_t&& ns) : name(nm), idint(0), nameset(ns) {};
  }; // class table
};

#ifndef SEPARATE_COMPILATION
#include "SQLite.cpp"
#endif



#endif
