#ifndef JSON_PRINTER_CPP
#define JSON_PRINTER_CPP

#ifndef JSON_PRINTER_H
#include "JSON.printer.h"
#endif


template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::null_t & n) const { os << level << "null";};

template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::integer_t & i) const {
  os << level << i ;
};

template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::float_t & f)   const { os << level << f;};

template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const bool & b) const {
  os << level << std::boolalpha << b ;
};

#ifdef USE_STRING
template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::string_t & s) const {
  os << level << '\"' << s << '\"';
};
#else
template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::string_view_t & sv) const {
  os << level << '\"' << sv << '\"';
};
#endif

template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::JSONarray_t & arr) const {
  os << '\n' << level << '[';
  bool tail{false};
  for(auto it = arr.cbegin(); it != arr.cend(); ++it) {
    if (tail)
      os << ",\n";
    else
      os  << '\n';
    std::visit(JSONprinter<SEQ,MAP>(os, level.get() + 1), *it);
    tail=true;
  } // for
  os << '\n' << level << ']' << '\n';
};

template <template <typename>          typename SEQ,
          template <typename,typename> typename MAP,
                                       typename LEVEL>
void JSONprinter<SEQ,MAP,LEVEL>::operator() (const typename JSON_t::JSONobj_t & obj) const {
  os << '\n' << level << '{';
  bool tail{false};
  for(auto it = obj.cbegin(); it != obj.cend(); ++it) {
    if (tail)
      os << ",\n";
    else
      os  << '\n';
    os << level << '\"' << it->first << "\": ";
    std::visit(JSONprinter<SEQ,MAP>(os, level.get() + 1), it->second);
    tail=true;
  } // for
  os << '\n' << level << '}';
};

#endif
