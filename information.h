#include <optional>
#include <string>
#include "json.h"

/*    TODOs:
 (1)) remove uses of std::optional: use empty values and null pointers (nullptr) instead,
      or hide the implementation so that, say bool has_item() const is public and varoabñe item is not
 */

// This enumeration is likely to be useful to other source files and/or compilation units:
enum class  fileformat           { none=0, other, plaintext,  html,  other_xml,  pdf,  djvu,  ePUB,  ePUB3,  MOBI};
const char* fileformat_array[] = {"none","other","plaintext","html","other_xml","pdf","djvu","ePUB","ePUB3","MOBI"};

/**
 * Use:
        enum class std::filesystem::file_type {none, not_found,
                                               regular, directory, symlink,
                                               block, character,
                                               fifo, socket,
                                               unknown};
 */

template <typename DATE = long, typename CH = char, typename STR = std::basic_string<CH>>
class information {
public:
  typedef  STR string_t;
  typedef DATE date_t;
  string_t source; // either the author or the origin of a piece of information
  date_t     date; // date of creation or modification
  /** Now, variable 'desc' (for "description")
   *  may be used as a description (a sort of name or title of the piece of information concerned),
      whereas using it to hold actual information might overlap
   *  optionally, adding
        enum       desc_types {description, name, contents};
        desc_types desc_type;
      would clarify the purpose of each instance of 'desc'
   *  WARNING: using it for holding content would overshadow class datatype<>, though
   */
  string_t   desc;
public:
  // setters and getters for 'source', 'date' ...:
  void    set_source(const string_t& s)       {source = s;};
  string_t get_source()          const {return source;};
  bool     has_source()          const {return !source.empty();};
  void   set_date(date_t d)      {       date = d;};
  date_t get_date()        const {return date;};
  bool   has_date()        const {return static_cast<bool>(date);};
  void     set_desc(const string_t& s)        {desc = s;};
  string_t get_desc()           const {return  desc;};
  bool     has_desc()           const {return !desc.empty();};
  //
  virtual bool has_value() const {return false;};
  // constructors and destructor:
  information() : date(0) {};
  information(const string_t&  s) : source(s) {};
  information(const date_t d) : date(d) {};
  information(const string_t&  s, const DATE& d) : source(s), date(d) {};
  information(const string_t&  s, const string_t& des, const DATE& d = 0) : source(s), date(d), desc(des) {};
  ~information() = default;
};
template <typename DATE = long, typename CH = char>
std::basic_ostream<CH>& operator<<(std::basic_ostream<CH>& o, const information<DATE,CH>& i) {
  o << "source: ";
  if(i.has_source()) o << i.get_source() << ";";
  else               o << "none;";
  o << " date: ";
  if(i.has_date()) o << i.get_date() << ";";
  else             o << "none;";
  o << " desc: ";
  if(i.has_desc()) o << '\"' << i.get_desc() << "\";";
  else             o << "none;";
  return o;
};

/* class dataitem<>
 * has a partial specialization for JSON
 */

enum datatype { fact=0, rule,   json,   other}; // is this enum any use at all?
const char * datatype_array[] =
              {"fact", "rule", "json", "other"};


template <int DT = other,
          typename CH = char,
          typename DATE = double,
          typename STR = std::basic_string<CH>
          >
class dataitem : public information<DATE,CH,STR> {
public:
  int get_datatype() const {return DT;};
  std::optional<STR> contents;
  bool has_value()   const {return static_cast<bool>(contents);};
  //
  dataitem() = default;
  dataitem(const STR& s) : contents(s) {};
};
template <typename CH, typename DATE, typename STR>
class dataitem<json,CH,DATE,STR> : public information<DATE,CH,STR> {
public:
  typedef j::jdoc<int,double,STR> jsondoc_t;
  std::optional<jsondoc_t*> jsondoc_ptr;
  int get_datatype() const {return json;};
public:
  bool has_value()   const {return static_cast<bool>(jsondoc_ptr);};
       jsondoc_t * get_ptr()      {
    if(jsondoc_ptr) return jsondoc_ptr.value();
    else            return nullptr;
  };
  const jsondoc_t * get_ptr() const {
    if(jsondoc_ptr) return jsondoc_ptr.value();
    else            return nullptr;
  };
  // constructors and destructors:
  dataitem() = default;
  dataitem(jsondoc_t* jdp) : jsondoc_ptr(jdp) {};
};

enum DOM_parser {rapidxml, xrapidxml, html_rapidxml, pugixml};

template <int FMT, typename DATE = double, typename CH = char, typename STR = std::basic_string<CH>>
class text : public information<DATE,CH,STR> {
public:
  bool has_fileformat() const {return static_cast<bool>(FMT);};
  const char* get_fileformat_string() const {return fileformat_array[FMT];};
  //
  bool fiction;
  bool is_fiction() const {return fiction;};
public:
  text(bool f = true) : fiction(f) {};
  ~text() = default;
};
