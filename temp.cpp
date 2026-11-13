/* count_and_zero_stringmap.test.cpp */

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <utility>
#include <vector>



#ifndef RECORD_DESCRIPTION_H
#define RECORD_DESCRIPTION_H

template <template <typename K,typename M> typename MAP=std::map>
class record_description {
protected:
  mutable std::size_t sz;
public:
  typedef std::string string_t;
  enum class type {NIL, BOOL, INT, FLOAT, TEXT};
  typedef std::pair<type, std::size_t> type_t;
  // public member variables:
  MAP<string_t, type_t> structure;
  // constructors and destructor:
};

template <template <typename K,typename M> typename MAP=std::map>
class record_layout : public record_description<MAP> {
public:
  typedef std::string string_t;
  typedef std::size_t index_t;
  typedef std::fstream::off_type off_type;
  MAP<string_t, index_t> from_field_name_to_index;
  off_type get_offset(std::string_view name) const;
};

#endif

#ifndef RECORD_DESCRIPTION_H
#include "record_description.h"
#endif

#include <iostream>
using namespace std;

int main() {




  return 0;
}
