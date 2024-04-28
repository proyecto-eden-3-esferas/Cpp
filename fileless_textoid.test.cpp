#include <cmath>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>


#define DEBUG_HANDLER
#ifdef DEBUG_HANDLER
#define TEXTOID_H
#include <string_view>
template <typename CH = char, std::size_t SLOTSIZE=1000>
struct fileless_textoid { // a dummy class for testing purposes
  typedef std::basic_string<CH>      string_t;
  typedef std::basic_string_view<CH> string_view_t;
  typedef std::basic_fstream<CH>    fstream_t;
  typedef  fstream_t::off_type          off_type;
  typedef std::size_t                  size_t;
  string_t contents;
  off_type offset;
  size_t slotsize;
  //
  off_type get_offset() const {return offset;};
  void     set_offset(off_type off) {offset=off;};
  size_t   get_slotsize() const {return slotsize;};
  void     set_slotsize(size_t ss) {slotsize=ss;};
  size_t get_slot_capacity() const {return slotsize - 4;};
  void   set_slot_capacity() {/*DUMMY*/};
  bool store(fstream_t& f) {/*DUMMY*/ return true;};
  bool load( fstream_t& f) {/*DUMMY*/ return true;};
  fileless_textoid()                :              slotsize(SLOTSIZE) {/*DUMMY*/};
  fileless_textoid(string_view_t s) : contents(s), slotsize(SLOTSIZE) {/*DUMMY*/};
};
#else
#include "textoid.h"
#endif // end of #ifdef DEBUG_HANDLER

#include "fileless_textoid_handler.h"

using namespace std;
const std::size_t initial_slotsize = 500;
typedef fileless_textoid<char,initial_slotsize> elem_t;
typedef fileless_textoid_handler<char,initial_slotsize> fth_t;
typedef std::size_t size_t;


int main() {

#ifdef TEST_FILELESS_TEXTOID
  fstream fs("io.text");
  string s1("first");

  elem_t ft0, ft1(0), ft2(s1), ft3(s1,0);
  cout << "A fileless_textoid<char> is " << sizeof(ft3);
  cout << " bytes, whereas a std::string is " << sizeof(s1) << " bytes.\n";
  ft3.store(fs);
  ft1.load(fs);
  //ft1="fifth";
  ft1.store(fs);

  fs.close();
#endif

  return 0;

};
