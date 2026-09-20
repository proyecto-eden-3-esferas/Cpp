#ifndef SEQUENCE_MATCHER_H
#define SEQUENCE_MATCHER_H

#include <array>


template <std::size_t SIZE, typename T = char>
class sequence_matcher : protected std::array<T,SIZE> {
protected:
  typedef std::array<T,SIZE> array_type;
  using array_type::begin, array_type::end;

  std::size_t sz;
  virtual void increment_size();

public:
  std::size_t size() const;
  void clear();
  virtual void push_back(T elem);
  const T & operator[] (std::size_t idx) const;

  // Constructor
  sequence_matcher() : sz(0) {};

};

#endif


#ifndef SEQUENCE_MATCHER_CPP
#define SEQUENCE_MATCHER_CPP

#ifndef SEQUENCE_MATCHER_H
#include "sequence_matcher.h"
#endif

template <std::size_t SIZE, typename T>
void sequence_matcher<SIZE,T>::increment_size() {
  ++sz;
  if(sz==SIZE)
    sz = 0;
};
template <std::size_t SIZE, typename T>
std::size_t sequence_matcher<SIZE,T>::size() const {
  return array_type::size();
};

template <std::size_t SIZE, typename T>
void sequence_matcher<SIZE,T>::clear() {
  sz = 0;
};

template <std::size_t SIZE, typename T>
void sequence_matcher<SIZE,T>::push_back(T elem) {
  array_type::operator[] (sz) = elem;;
  increment_size();
};

template <std::size_t SIZE, typename T>
const T & sequence_matcher<SIZE,T>::operator[] (std::size_t idx) const {
  return array_type::operator[] (idx);
};

#endif
