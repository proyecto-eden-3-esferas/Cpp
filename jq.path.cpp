#ifndef JQ_PATH_CPP
#define JQ_PATH_CPP

#ifndef JQ_PATH_H
#include "jq.path.h"
#endif

template <                    typename CHAR,
          template <typename> typename SEQ>
jq<CHAR,SEQ>::path & jq<CHAR,SEQ>::path::add(string_view_t name) {
  pith.push_back(name.data());
  return *this;
};

template <                    typename CHAR,
          template <typename> typename SEQ>
jq<CHAR,SEQ>::path & jq<CHAR,SEQ>::path::add(index_t idx)  {
  pith.push_back(idx);
  return *this;
};

template <                    typename CHAR,
          template <typename> typename SEQ>
std::basic_ostream<CHAR>& jq<CHAR,SEQ>::path::print(std::basic_ostream<CHAR>& o) const {
  ostream_printer pr(o);
  bool tail{false};
  o << '[';
  for(const auto & el : pith ) {
    if(tail)
      o << ", ";
    else
      tail=true;
    std::visit(pr, el);
  }
  o << ']';
  return o;
};

template <                    typename CHAR,
          template <typename> typename SEQ>
std::basic_string<CHAR>& jq<CHAR,SEQ>::path::print(std::basic_string<CHAR>& s) const {
  string_printer sp(s);
  bool tail{false};
  s += '[';
  for(const auto & el : pith ) {
    if(tail)
      s += ", ";
    else
      tail=true;
    std::visit(sp, el);
  }
  s += ']';
  return s;
};


#endif
