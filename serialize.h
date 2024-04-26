#ifndef SERIALIZE_H
#define SERIALIZE_H

#ifndef SERIALIZE_STRING_H
#include "serialize_string.h"
#endif

// global serialize_sized() functions use serialize_sized_string():
template<typename OUT = std::ostream, typename T>
OUT& serialize_sized(OUT& o, T t) {o << t << ' '; return o;};
template<typename OUT = std::ostream>
OUT& serialize_sized(OUT& o, const std::string & s) {serialize_sized_string(o,s); return o;};

// global deserialize_sized() functions use deserialize_sized_string():
template<typename IN = std::istream, typename T>
IN& deserialize_sized(IN& in, T& t) {in >> t; return in;};
template<typename IN = std::ostream>
IN& deserialize_sized(IN& in, std::string & s) {deserialize_sized_string(in,s); return in;};


// global serialize_sep() functions use serialize_sep_string():
template<typename OUT = std::ostream, typename T>
OUT& serialize_sep(OUT& o, T t) {o << t << ' '; return o;};
template<typename OUT = std::ostream>
OUT& serialize_sep(OUT& o, const std::string & s) {serialize_sep_string(o,s); return o;};



#endif
