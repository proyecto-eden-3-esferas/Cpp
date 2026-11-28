#ifndef RECORD_DESCRIPTION_H
#define RECORD_DESCRIPTION_H

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

/* These hierarchy of classes stores relational database records/tuples/rows
 * so as:
 * - the better to validate them
 * - to output them as an INSERT statement
 * - generally to convert them to other formats
 */

/* class simple_record_description<INT,FLOAT>
 * TODO:
   [ ] write inserter based on std::visit.
   [ ] To that end, you should rely on "C-string-to-SQL-str" compilation unit.
   [ ] Actually, you might make simple_record_description<INT,FLOAT>::extractor_visitor fully generic
       by
   [ ]
 */
template <typename   INT = signed int,
          typename FLOAT = float
         >
class simple_record_description {
public:
  typedef std::string string_t;
  typedef std::variant<std::nullptr_t, string_t, INT, FLOAT, bool> variant_t;
  typedef std::optional<variant_t> record_t;
  //
  char quote_char;
  struct extractor_visitor;
  // Constructor(s):
  simple_record_description(char q = '\'') : quote_char(q) {};
};

template <typename   INT, typename FLOAT>
struct simple_record_description<INT,FLOAT>::extractor_visitor {
  std::ostream & out;
  char quote_char;
  void operator() (const std::nullptr_t& ptr) { out << "NULL"; };
  void operator() (const std::string&  str) { out << quote_char << str << quote_char; };
  void operator() (  INT i) { out << i; };
  void operator() (FLOAT f) { out << f; };
  void operator() ( bool b) { out << std::boolalpha << b; };
  // Constructor(s):
  extractor_visitor(std::ostream & o = std::cout, char q = '\'') : out(o), quote_char(q) {};
};

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

template <typename I = signed int,
          typename F = float,
          template <typename K,typename M> typename MAP = std::map>
class record_description : public simple_record_description<I,F> {
protected:
  mutable std::size_t sz;
public:
  typedef simple_record_description<I,F> parent_t;
  using parent_t::variant_t;
  using parent_t:: record_t;
  typedef std::string string_t;
  enum class type       {NIL, BOOL, INT, FLOAT, TEXT};
  enum class constraint {UNIQUE, NOT_NULL};
  typedef std::pair<type, std::size_t> type_t;
  // public member variables:
  MAP<string_t, type_t> structure;
  // constructors and destructor:
};

template <typename I = signed int,
          typename F = float,
          template <typename K,typename M> typename MAP = std::map>
class record_layout : public record_description<I,F,MAP> {
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
