#ifndef METADATA_BASE_H
#define METADATA_BASE_H

/* Class metadata_base is a non-template base class of class metadata_map<MAP>.
 * Much in the spirit of the STL,
   metadata_base is not an interface class (no pure virtual functions)
 * Class metadata_map<MAP> implements metadata as a map.
 * Its one template parameter allows for choosing
   - unique or multiple same-name keys
   - binary tree or hash table (_unordered suffix) underlying implementation
 * NOTE: member length() returns the length of string 'contents',
         whereas size() returns the size of the MAP<STRING,STRING> plus 1
 * TODO
   [ ] Define concepts...
   [ ] Define a count and zero terminated serialize/deserialize interface
 */

#include <initializer_list>
#include <map>
#include <string>
#include <string_view>

class metadata_base {

public:
  typedef std::string string_t;
  typedef std::string_view string_view_t;

  enum class fileformat {plaintext, html, xhtml, docbook, otherXML, PDF, markdown};
             fileformat get_fileformat() const {return its_fileformat;};
protected:
  string_t contents;
  fileformat its_fileformat;

public:
        string_t&  get_contents()       {return contents;};
  const string_t&  get_contents() const {return contents;};
  std::size_t            length() const {return contents.length();};

  metadata_base(string_view_t c="",
                fileformat ff=fileformat::plaintext) : contents(c), its_fileformat(ff) {};

}; // class metadata_base

#endif


#ifndef METADATA_MAP_H
#define METADATA_MAP_H

#ifndef METADATA_BASE_H
#include "metadata_base.h"
#endif

template <template <typename,typename> class MAP = std::map>
class metadata_map : public metadata_base,
                     public std::map<std::string, std::string>
{
public:
  using metadata_base::contents, metadata_base::get_contents, metadata_base::length;
  using metadata_base::fileformat, metadata_base::get_fileformat;

  typedef std::string string_t;
  typedef std::string_view string_view_t;

  typedef metadata_map<MAP> metadata_map_t;
  typedef MAP<string_t,string_t> map_t;

  std::size_t size() const {return map_t::size() + 1;};

  // Copy Assignments:
  metadata_map_t& operator=(const metadata_map_t& mdm) {
    contents = mdm.contents;
    its_fileformat = mdm.its_fileformat;
    map_t::clear();
    map_t::insert(mdm.begin(), mdm.end());
    return *this;
  };
  // Constructors:
  metadata_map(string_view_t c="",
               fileformat ff=fileformat::plaintext) : metadata_base(c,ff) {};
  template <typename ITER>
  metadata_map(ITER be, ITER en,
               string_view_t c="",
               fileformat ff=fileformat::plaintext)
  : metadata_base(c,ff), map_t(be,en) {};
  metadata_map(std::initializer_list<std::pair<string_t,string_t>> il,
               string_view_t c="",
               fileformat ff=fileformat::plaintext)
  : metadata_base(c,ff), map_t(il.begin(), il.end()) {};
  /*
  metadata_map(std::initializer_list<std::pair<string_view_t,string_view_t>> il,
               string_view_t c="",
               fileformat ff=fileformat::plaintext)
  : metadata_base(c,ff), map_t(il.begin(), il.end()) {};
  */
  // Copy and Move Constructor
  metadata_map(const metadata_map_t& mdm)
  : metadata_map_t(mdm.begin(), mdm.end(), mdm.contents, mdm.its_fileformat) {};
  metadata_map(metadata_map_t && mdm)
  : metadata_base(std::move(mdm.contents), mdm.its_fileformat), map_t(mdm.begin(), mdm.end()) {};
  /*
  metadata_map(string_view_t c="",
               fileformat ff=fileformat::plaintext) : metadata_base(c,ff)
  {};
  */


}; // class metadata_map

#endif
