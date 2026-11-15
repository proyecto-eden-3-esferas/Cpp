#ifndef RECORD_DESCRIPTION_H
#define RECORD_DESCRIPTION_H

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <utility>
#include <vector>

/* Class record_description<MAP>
   is good for describing a relational database table/relation.
 * Enumeration record_description<MAP>::type
 * NOTE: the first element is NIL instead of NULL,
   which is a reserved C++ word,
 * TODO
   [ ] on-demand automatic generation of ID (compilation unit 'id')
   [ ] use std::optional for possibly-NULL values
   [ ] implement a means of enforcing uniqueness (through std::set or std::unordered_set)
 */

template <template <typename K,typename M> typename MAP=std::map>
class record_description {
protected:
  mutable std::size_t sz;
public:
  typedef std::string string_t;
  enum class type       {NIL, BOOL, INT, FLOAT, TEXT};
  enum class constraint {NONE, NOT_NULL, BOOL, INT, FLOAT, TEXT};
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
  typedef std::fstream::off_type off_t;
protected:
  MAP<string_t, index_t> from_field_name_to_index;
  MAP<string_t,   off_t> from_field_name_to_offset;
  void update_offsets() {}; // TO BE IMPLEMENTED
public:
  off_t get_offset(std::string_view name) const {return from_field_name_to_offset.at(name);};
  // Constructor(s) and destructor
};

#ifndef RECORD_DESCRIPTION_CPP
#include "record_description.cpp"
#endif

#endif
