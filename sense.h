#ifndef SENSE_H
#define SENSE_H

template <typename T, int N = 0>
class sense : public T {
  using T::T;
  operator       T& ()       {return static_cast<      T&>(*this);};
  operator const T& () const {return static_cast<const T&>(*this);};
};

#endif
