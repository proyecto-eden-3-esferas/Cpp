#ifndef FILESTRING_H
#define FILESTRING_H

#include <fstream>
#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

/* File "filestring.h"
 * Compilation unit "filestring" contains classes:
   - filestring_container<CONT>, and
   - filestring_container<CONT>::filestring (essentially, a text class)
 * Class filestring_container<CONT> is a container of filestring's.
   It also holds a reference to a in-out file (std::fstream)
   plus some members for assigning offsets to the filestring's it holds.
 * A filestring is an inner class that holds a string and a file offset
   for loading the string from a file (starting at said offset)
   or storing the string away.
 * TODO
 [ ] filestring_container<CONT>::CONT should be indexable
     as otherwise offsets couldn't be assigned and adjusted consistently
 [ ] store() should check that the string fits in its slot...
     just how can that be checked?
 [ ] implement filestring::push_back
 [ ] implement load() / store() for zero-terminated strings
 [ ]
 */


template <template <typename STR> typename CONT = std::vector >
class filestring_container {
public:
  typedef std::fstream fstream_t;
  typedef              fstream_t::off_type off_type;
  fstream_t & iofile;
  off_type offset_step;


  class filestring {
  public:
    typedef std::fstream fstream_t;
    typedef              fstream_t::off_type off_type;
  protected:
    off_type    offset;
    bool        changed, loaded;
    std::string text;
    //
    void load( fstream_t& f);
    void store(fstream_t& f);
    void check(fstream_t& f);
  public:
    bool has_changed() const {return changed;};
          std::string& get(fstream_t& f)       {check(f); changed=true; return text;};
    const std::string& get(fstream_t& f) const {check(f);               return text;};
    //
    filestring(                 off_type off) : offset(off), changed(false), loaded(false) {};
    filestring(fstream_t&  iof, off_type off) : offset(off), changed(false), loaded(true)  {load(iof);};
    filestring(std::string_view sv, off_type off) : offset(off), changed(true), loaded(true), text(sv) {};
    friend class filestring_container<CONT>;
  }; // class filestring

  //
protected:
  CONT<filestring> filestrings;
public:
  virtual       filestring& operator[](std::size_t idx);
  virtual const filestring& operator[](std::size_t idx) const;
  std::size_t size() const {return filestrings.size();};
  virtual std::size_t next_index() const {return size();};
  virtual void emplace_back(std::string_view sv);
  //virtual void    push_back(std::string_view sv);
  //
  filestring_container(fstream_t& iof, std::size_t step) : iofile(iof), offset_step(step) {};
  ~filestring_container(); // destructor should check that each string fits in its slot
};

#ifndef SEPARATE_COMPILATION
#include "filestring.cpp"
#endif

#endif
