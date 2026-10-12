#ifndef FILESTRING_HANDLER_H
#define FILESTRING_HANDLER_H

#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

/* Class filestring_handler<CONTAINER> is abstract,
   and the would-be parent of zero_filestring_handler<CONTAINER>
   and offset_filestring_handler
 * TODO
   [ ] write the implementations of filestring_handler's member functions
   [ ] Develop offset_filestring_handler from units fileless_textoid and textoid.h
       as a child of filestring_handler's
   [ ]
 */

template <template <typename> typename CONTAINER = std::vector >
class filestring_handler : protected CONTAINER<std::string> {
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
  // CONT<std::string> strings;
  virtual void load() = 0;
  virtual void store() = 0;
public:
  // constructors and destructor:
  filestring_handler(fstream_t    && fs, bool read = false);
  filestring_handler(const char * fname, bool read = false);
  filestring_handler(fstream_t & fs, std::initializer_list<string_t> il) : filestream(fs), container_t(il) {};
  virtual ~filestring_handler();
};


#endif
