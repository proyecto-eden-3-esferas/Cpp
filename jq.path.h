#ifndef JQ_PATH_H
#define JQ_PATH_H

#include <variant>
#include <vector>

template <                    typename CHAR,
          template <typename> typename SEQ>
struct jq<CHAR,SEQ>::path {
  typedef std::size_t index_t;
  typedef std::basic_string<CHAR> string_t;
  typedef std::basic_string_view<CHAR> string_view_t;
  typedef std::variant<string_t, index_t> variant_t;
  typedef SEQ<variant_t> sequence_t;

  sequence_t pith;

  path& add(string_view_t name) {
    pith.push_back(name.data());
    return *this;
  };
  /*
  path& add(const char* name) {
    pith.push_back(name);
    return *this;
  };
  */
  path& add(index_t idx)  {
    pith.push_back(idx);
    return *this;
  };

  // The iterator interface:
  std::size_t size() const {return pith.size();};
  typedef typename sequence_t::const_iterator const_iterator;
  typedef typename sequence_t::      iterator       iterator;
  iterator        begin()       {return pith.begin();};
  iterator          end()       {return pith.end();};
  const_iterator cbegin() const {return pith.cbegin();};
  const_iterator   cend() const {return pith.cend();};

  /* Instances of jq<>::path::printer
   * are meant to be the first argument of std::visit, as in
   * std::visit(PRINTER_OBJ, VARIANT)
   */
  struct printer {
    std::ostream& os;
    void operator() (const string_t& s) const {os << '\"' << s << '\"';};
    void operator() (       index_t  i) const {os <<         i;};
    printer(std::ostream& o) : os(o) {};
  };

  std::ostream& print(std::ostream& o) const {
    printer pr(o);
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
  }
};

#endif
