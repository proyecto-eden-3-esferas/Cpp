#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H

/* class/struct 'JSONprinter' defines operator() for each type in JSON::variant_t
   to pretty print through a Level object
 * Macro USE_STRING is carried over from the JSON compilation unit.
   (It selects owning std::string instead of non-owning std::string_view)
 * NOTE If no SEPARATE_COMPILATION macro is asserted,
 * implementation file "JSON.printer.cpp" is included at the bottom
 * TODO
 * [ ] Define a non-pretty printer for JSON (no reliance on a Level auxialiary class)
       This would be useful for compact printing meant for machines, not humans.
 */

#ifndef JSON_H
#include "JSON.h"
#endif

#ifndef LEVEL_H
#include "Level.h"
#endif

template <template <typename>          typename SEQ = std::vector,
          template <typename,typename> typename MAP = std::map,
                                       typename LEVEL = Level<signed int> >
struct JSONprinter {

  std::ostream& os;
  LEVEL level;

  typedef JSON<SEQ,MAP> JSON_t;
  void operator() (const typename JSON_t::null_t & n) const;
  void operator() (const typename JSON_t::integer_t & i) const;
  void operator() (const typename JSON_t::float_t & f)   const;
  void operator() (const                  bool & b) const;
#ifdef USE_STRING
  void operator() (const typename JSON_t::string_t & s) const;
#else
  void operator() (const typename JSON_t::string_view_t & sv) const;
#endif

  void operator() (const typename JSON_t::JSONarray_t & arr)    const;
  void operator() (const typename JSON_t::JSONarray_t * arrPtr) const {operator() (*arrPtr);};
  void operator() (const typename JSON_t::JSONobj_t   & obj)    const;
  void operator() (const typename JSON_t::JSONobj_t   * objPtr) const {operator() (*objPtr);};


  JSONprinter(std::ostream& o, LEVEL l=LEVEL(0)) : os(o), level(l) {};
};

#endif

#ifndef SEPARATE_COMPILATION
#include "JSON.printer.cpp"
#endif


