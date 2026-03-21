#ifndef JSON_H
#define JSON_H

/* Some classes/struct's are defined for JSON internal representation:
   - JSON (which only contains a bunch of typedef's)
   - JSONarray
   - JSONobj
 * The implementation relies on a std::variant type (JSON::variant_t)
   that includes all JSON types, some of them in a dual value-pointer version
   (for instance, both a JSON object/array or a pointer to a JSON object/array).
 * Holding JSON objects, arrays and strings by reference enables "cyclic "
 * Approximately:
     typedef std::variant<char, int, ... JSONobj, JSONobj *, ...> variant_t;
 * The first type is not a JSON type. This is intended to mean JSON null.
   How does this work? The default constructor selects the first type (remember, a non-JSON type),
   so "variant_t v" will select the first type
 * The default implementation (macro USE_STRING undefined) uses std::string_view,
   which holds strings by const reference (so to speak),
   instead of std::string
 * class/struct 'JSONprinter' is defined for use on JSON::variant_t, like so:
     std::visit(JSONprinter_t(std::cout, <level>), <variant>);
   It pretty prints JSON types, with indentation handles by a Level parameter (see "Level.h")
 * Note macro USE_STRING:
     It seems that declaring std::variant< ..., string, string_view, ...> does not work smoothly
     so this macro selects either std::string or std::string_view
 * TODO
   [ ] A non-pretty JSON-printer class ('uglyJSONprinter')
   [ ] Perhaps most using directives in JSONarray and JSONobj can be left out:
         using JSON_t::null_t;
         using JSON_t::integer_t, JSON_t::float_t;
         using typename JSON_t::string_t;
         using typename JSON_t::string_view_t;
         using JSON_t::JSONarray_t;
         using JSON_t::JSONobj_t;
       These would make our code shorter.
       Besides, the directives are repeated in JSONarray and JSONobj. Ugly.
   [ ]

 */

#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

// Forward declaration of JSON array and object:

template <template            <typename> typename SEQ,
          template  <typename, typename> typename MAP>
struct JSONarray; // forward declaration

template <template            <typename> typename SEQ,
          template  <typename, typename> typename MAP>
struct JSONobj;


template <template <typename>          typename SEQ = std::vector,
          template <typename,typename> typename MAP = std::map>
struct JSON {
  typedef              char       null_t;
  typedef        signed int    integer_t;
  typedef            double      float_t;
  typedef       std::string     string_t;
  typedef std::string_view string_view_t;
  typedef JSONarray<SEQ,MAP> JSONarray_t;
  typedef JSONobj<  SEQ,MAP>   JSONobj_t;
  //
  typedef std::variant<null_t,
                       integer_t,
                       float_t,
                       bool,
#ifdef USE_STRING
                       string_t,
#else
                       string_view_t,
#endif
                       JSONarray_t,
                       JSONarray_t*,
                       JSONobj_t,
                       JSONobj_t*> variant_t;
};


template <template <typename>          typename SEQ = std::vector,
          template <typename,typename> typename MAP = std::map>
struct JSONarray : public JSON<SEQ,MAP> {
  typedef JSON<SEQ,MAP> JSON_t;
  using JSON_t::null_t;
  using JSON_t::integer_t, JSON_t::float_t;
  using typename JSON_t::string_t;
  using typename JSON_t::string_view_t;
  using JSON_t::JSONarray_t;
  using JSON_t::JSONobj_t;

  using typename JSON_t::variant_t;
  typedef SEQ<variant_t> array_t;
  //
  array_t array;

  //
  void push_back(const variant_t& var) {array.push_back(var);};

  // The iterator interface:
  typedef  typename array_t::const_iterator const_iterator;
  typedef  typename array_t::      iterator       iterator;
  iterator begin()        {return array.begin();};
  iterator end()          {return array.end();};
  const_iterator cbegin() const {return array.cbegin();};
  const_iterator cend()   const {return array.cend();};

  //
  JSONarray() = default;
};



template <template <typename>          typename SEQ = std::vector,
          template <typename,typename> typename MAP = std::map>
struct JSONobj : public JSON<SEQ,MAP> {
  typedef JSON<SEQ,MAP> JSON_t;
  using JSON_t::null_t;
  using JSON_t::integer_t, JSON_t::float_t;
  using typename JSON_t::string_t;
  using typename JSON_t::string_view_t;
  using JSON_t::JSONarray_t;
  using JSON_t::JSONobj_t;

  using typename JSON_t::variant_t;
  typedef MAP<string_t, variant_t> properties_t;

  //
  properties_t properties;

  //
  void push_property(const string_t& name, const variant_t& var) {properties[name] = var;};

  // The iterator interface:
  auto begin()        {return properties.begin();};
  auto end()          {return properties.end();};
  auto cbegin() const {return properties.cbegin();};
  auto cend()   const {return properties.cend();};

  //
  JSONobj() = default;
};

#endif
