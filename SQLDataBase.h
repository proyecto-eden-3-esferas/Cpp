#ifndef SQL_DB_H
#define SQL_DB_H

#include <map>
#include <set>
#include <string>
#include <vector>

template <template <typename,typename> typename MAP=std::map,
          template <         typename> typename SET=std::set,
                                       typename CHAR=char>
class DataBase {
public:
  typedef                    char null_t;
  typedef           signed int integer_t;
  typedef                  double real_t;
  typedef std::basic_string<CHAR> text_t;
  typedef std::vector<      CHAR> blob_t;
};

template <template <typename,typename> typename MAP=std::map,
          template <         typename> typename SET=std::set,
                                       typename CHAR=char>
class SQLDataBase : public  DataBase<MAP,SET,CHAR> {
public:
};

#endif
