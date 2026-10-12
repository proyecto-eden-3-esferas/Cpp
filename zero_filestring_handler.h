#ifndef ZERO_FILESTRING_HANDLER_H
#define ZERO_FILESTRING_HANDLER_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

/* Class zero_filestring_handler<CONTAINER> inherits from a container of strings
   and loads from and stores to a file (on construction and destruction, respectively).
   In a file, strings are terminated by '\0' (default) or some other chosen character.
 * Class zero_filestring_handler<CONTAINER> holds:
   - a container of strings
   - an std::fstream
   - a separator character
 * TODO
   [ ] Unit filestring should be renamed offset_filestring
/*
 *
 */

template <template <typename> typename CONTAINER = std::vector >
class zero_filestring_handler : protected CONTAINER<std::string> {
public:
  typedef std::string   string_t;
  typedef CONTAINER<string_t> container_t;
  typedef std::fstream fstream_t;
  using container_t::size;
  using container_t::operator[], container_t::at;
  using container_t::push_back, container_t::emplace_back;
  using container_t::begin, container_t::end;

protected:
  fstream_t filestream;
  char sep;
  // CONT<std::string> strings;
  virtual void load();
  virtual void store();
public:
  // constructors and destructor:
  zero_filestring_handler(fstream_t    && fs, bool read = false, char sep='\0');
  zero_filestring_handler(const char * fname, bool read = false, char sep='\0');
  zero_filestring_handler(fstream_t & fs, std::initializer_list<string_t> il) : filestream(fs), container_t(il) {};
  virtual ~zero_filestring_handler();
};

template <template <typename> typename CONT = std::vector>
std::ostream& operator<<(std::ostream& o, const zero_filestring_handler<CONT>& zfh);

#ifndef ZERO_FILESTRING_HANDLER_CPP
  #ifndef SEPARATE_COMPILATION
  #include "zero_filestring_handler.cpp"
  #endif
#endif

#endif

