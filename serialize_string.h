#ifndef SERIALIZE_STRING_H
#define SERIALIZE_STRING_H

#include <iostream>
#include <string>

/* Here, a dual scheme for loading (deserializing) and storing (serializing)
   a string is implemented:
   (1) null ('\0') or some other char denotes end of string (sep_string's)
   (2) string on file preceded by uint + ' ' (space) (sized_string's)
 * It more or less assumes that character type is 'char', of size = 1 byte.
   This assumption might be made explicit through partial specializations...
 * NOTE deserialize_sep_string(  ISTREAM&, STRING&, CHAR) is simpler than its
        analog deserialize_sized_string(ISTREAM&, STRING&).
 * Some applications would demand that the code serializing and deserializing a string
   to or from a file first moves the cursor to the writing or reading
   through memberts seekp() and seekg().
*/

template <typename CH=char,
          typename OUTSTREAM = std::basic_ostream<CH>>
OUTSTREAM& serialize_sized_string(OUTSTREAM& o, const std::basic_string<CH> & str);

template <typename CH=char,
          typename INSTREAM = std::basic_istream<CH>>
INSTREAM& deserialize_sized_string(INSTREAM& i, std::basic_string<CH> & str);

template <typename CH=char,
          typename OUTSTREAM = std::basic_ostream<CH>>
OUTSTREAM& serialize_sep_string(OUTSTREAM& o, const std::basic_string<CH> & str, CH sep = '\0');

template <typename CH=char,
          typename INSTREAM = std::basic_istream<CH>>
INSTREAM& deserialize_sep_string(INSTREAM& i, std::basic_string<CH>& str, CH sep = '\0');

// The implementations:

/* (de)serialize_sized_string(...) */
template <typename CH, typename OUTSTREAM>
OUTSTREAM& serialize_sized_string(OUTSTREAM& o, const std::basic_string<CH> & str)
{
  o << str.size() << ' ';
  o.write(str.c_str(), str.size());
  o << std::endl;
  return o;
};
/*
template <typename CH=char, typename OUTSTREAM = std::basic_ostream<CH>>
OUTSTREAM& serialize_sized_string(OUTSTREAM& o, const std::basic_string<CH> & str)
{
  o << str.size() << ' ' << str << std::endl;
  return o;
};
*/
template <typename CH, typename INSTREAM>
INSTREAM& deserialize_sized_string(INSTREAM& i, std::basic_string<CH> & str)
{
  i >> std::ws;
  int size;
  i >> size;
  i.ignore();
  char * tmp_c_str = new char[size + 1];
  i.read(tmp_c_str, size);
  str = tmp_c_str;
  delete tmp_c_str;
  return i;
}

/* (de)serialize_sep_string(...) */
template <typename CH, typename OUTSTREAM>
OUTSTREAM& serialize_sep_string(OUTSTREAM& o, const std::basic_string<CH> & str, CH sep)
{
  o << str << sep;
  return o;
};
template <typename CH, typename INSTREAM>
INSTREAM& deserialize_sep_string(INSTREAM& i, std::basic_string<CH>& str, CH sep)
{
  std::getline(i, str, sep);
  return i;
};

#endif
