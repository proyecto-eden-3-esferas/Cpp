/** Lazy Strings
 *  In order to save RAM space we could store strings in files
    and only recall them if and when needed.
    (This would enable holding large texts in memory.)
 *  So you could manage large "texts" where mark up and some strings
    (titles, short descriptions, navigational elements...) lived in main memory
    whereas most content lived in files on hard disks and were referenced
    through some scheme, such as:
    (1) by initial position and length (if enough room is allocated,
        such strings could grow
    (2) just by length
 *  Maybe this scheme could be carried over to any sizable data structure:
    lazy storage
 */

/* Generalization to Containers:
 * Serializable containers hold either strings/text,
   or non-string basic types, or composite types.
 *
 */
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "serialization/serialize_string.h"

/* Three overloaded global functions size(filestream<>& fs)
 *
 */
template <typename CH=char>
std::size_t size(std::basic_fstream<CH>& fs) {
  fs.seekg(0, std::ios_base::end);    // go to theend
  return fs.tellg();
};
template <typename CH=char>
std::size_t size(std::basic_ifstream<CH>& ifs) {
  ifs.seekg(0, std::ios_base::end);    // go to the end
  return ifs.tellg();
};
template <typename CH=char>
std::size_t size(std::basic_ofstream<CH>& ofs) {
  ofs.seekp(0, std::ios_base::end);    // go to the end
  return ofs.tellp();
};
/* Alternatively, use <filesystem> and fs::path:
     std::filesystem::file_size("myfile.ext");
*/

/* global functions
     read(istream, offset, length, string)
   and
     write(ostream, offset, length, string)
 * They take a string length ('length') parameter in.
   I don't like this. Let's wait and see how I feel about it
   further down the road.
 */
template <typename CH = char>
void read(std::basic_istream<CH>& is, std::size_t offset, std::size_t len, std::basic_string<CH>& str) {
  char * pChar = new char[len + 1];
  is.seekg(offset);
  is.read(pChar, len);
  pChar[len] = 0;
  str = pChar;
  delete [] pChar;
};
template <typename CH = char>
void write(std::basic_ostream<CH>& os, std::size_t offset, std::size_t len, std::basic_string<CH>& str) {
  os.seekp(offset);
  os.write(str.data(), len);
};




























/** class string_serializer<CH>
 *  Originally meant for char
 *  TODO:
 *  (1) load and store member functions:
 *  (2) A dual scheme for load/store:
 *      - null ('\0') or some other char denotes end of string (sep_strings)
        - string on file preceded by uint + ' ' (space) (sized strings)
    (3) Do something about return type = bool because I am not happy with it.
 */
template <typename CH = char>
class string_serializer {
public:
  typedef std::basic_string<CH>   string_t;
  typedef std::size_t               size_t;
  typedef std::basic_fstream<CH> fstream_t;
protected:
  bool get_sep_string_at(fstream_t& ifs, size_t off, string_t & str, char sep = '\0') {
    ifs.seekg(off);
    deserialize_sep_string(ifs,str,sep);//std::getline(ifs, str, sep);
    return true;
  };
  bool get_sized_string_at(fstream_t& ifs, size_t off, string_t & str, char sep = '\0') {
    ifs.seekg(off);
    deserialize_sized_string(ifs,str);
    return true;
  };
  bool put_sep_string_at(fstream_t& ofs, size_t off, string_t & str, char sep = '\0') {
    ofs.seekg(off);
    serialize_sep_string(ofs,str,sep);//std::getline(ofs, str, sep);
    return true;
  };
  bool put_sized_string_at(fstream_t& ofs, size_t off, string_t & str, char sep = '\0') {
    ofs.seekg(off);
    serialize_sized_string(ofs,str);
    return true;
  };
};













/** Class holder<CHAR,METADATA...)> manages holder<>::held_string's
    which are held in a std::vector
    and loaded from and stored to a std::fstream.
 *  Such a file is supposedly made up of slots (fixed-sized runs of bytes).
 *  Additionally, a scheme is provided for handling metadata within slots
    through setting of the start of the string on disk by some metaoffset.
 *  Handling of metadata (which so far migh include a 1-line title)
    could be further refined or enlarged in would-be derived classes.
 *  Generally, some member functions have been declared virtual so as
    to enable specialization of behaviour:
    (1) through slots larger than a single slotsize
        overload virtual offset(idx), get_net_slotsize(idx) ...
    (2) through initialization of held_string's with some title,
        and generally holding several variable sized strings in one slot.
        overload [...]
    (3) by choosing an end of string terminator (between '\n' and '\0')
        or an alternative serialization scheme based on prepending the string's size
        through overloading virtual members: +get_string_at() and +put_string_at()
 * TODO:
   (1) Overload virtual members in derived classes, as explained above
   (2) ...
 */
template
<typename CH = char,                // I don't know whether a different character type would work well.
 typename METADATA = int,  std::size_t METASIZE = sizeof(METADATA)> // Allow for inclusion of metadata.
class holder : protected string_serializer<CH> {                       // Should metadata include a 1-line title?
public:                                                // Ostensibly, sizeof(METADATA) is pretty crude.
  typedef string_serializer<CH> string_serializer_t;
  typedef std::basic_istream<CH>   istream_t;
  typedef std::basic_fstream<CH>   fstream_t;
  typedef std::size_t                 size_t;
  typedef std::basic_string<CH>     string_t;
protected: // member variables
  class held_string; // forward declaration
  const CH * const filename;
  fstream_t        its_fstream;
  size_t           total_room;
  size_t           slotsize;
  size_t           num_slots; // number of num_slots
  const size_t     metasize; // size of metadata
  std::vector<held_string> held_strings; // a vector of held_string's
  virtual bool get_string_at(size_t off, string_t & str, char sep = '\0') {
    return string_serializer_t::get_sep_string_at(its_fstream, off, str, sep);
  };
  virtual bool put_string_at(size_t off, string_t & str, char sep = '\0') {
    return string_serializer_t::put_sep_string_at(its_fstream, off, str, sep);
  };
  void resize_file(std::uintmax_t num_bytes) {
    if( num_bytes >= slotsize * num_slots) { // do not shrink THE file
      std::filesystem::resize_file(filename,num_bytes);
      total_room = num_bytes;
      num_slots = num_bytes/slotsize;
    }
  };
public: // some trivial getters:
  const CH * const   get_filename ()          const {return filename;};
          size_t     get_num_slots()          const {return num_slots;};
          size_t     get_slotsize()           const {return slotsize;};
  virtual size_t     get_metasize()           const {return metasize;};
  virtual size_t     get_metasize(size_t idx) const {return metasize;};
          size_t get_net_slotsize()           const {return slotsize          - metasize;};
  // get_slotsize(idx) might never get used for implementing variable sized slots:
  virtual size_t     get_slotsize(size_t idx) const {return slotsize;};
          size_t get_net_slotsize(size_t idx) const {return get_slotsize(idx) - get_metasize(idx);};
public:
  bool get_string(size_t idx, string_t& str, char sep = '\0') { // analogous to std::getline(...)
    if(idx < size() /*&& held_strings[idx].loaded*/) {
      get_string_at(offset(idx), str, sep);
      return true;
    } else return false;
  };
  void push_back(const string_t& s) {held_strings.push_back(held_string(s));};
  virtual size_t     metaoffset(size_t idx) const {return   slotsize*idx                ;}; // the beginning of a slot
  virtual size_t         offset(size_t idx) const {return metaoffset(idx) + get_metasize(idx);};
        held_string& operator[](size_t idx)       { return held_strings[idx];};
  const held_string& operator[](size_t idx) const { return held_strings[idx];};
  size_t size()     const {return held_strings.size();};
  //size_t capacity() const {return held_strings.capacity();};
  size_t capacity() const {return num_slots;};
  // member functions:
  size_t remainder() const {return total_room - num_slots*slotsize;};
  //
  void resize_slots(std::uintmax_t ns) {
    if(ns > num_slots)
      resize_file(ns * slotsize);
  };
  // (meta)load and (meta)store:-
  virtual void metaload( )           {}; //  load all metadata, to be overridden
  virtual void metastore()           {}; // store all metadata, to be overridden
  virtual void metaload( size_t idx) {}; //  load all metadata, to be overridden
  virtual void metastore(size_t idx) {}; // store all metadata, to be overridden
  // +load(), +load(idx), +store(), +store(idx)
  void load() {
    for(int i = 0; i < size(); ++i) {
      metaload(i);
      load(i);
    }
  };
  void load(size_t idx) {
    its_fstream.seekg(offset(idx));
    std::getline(its_fstream, held_strings[idx].text, '\0');
    held_strings[idx].loaded = true;
  };
  void store() {
    for(int i = 0; i < size(); ++i) {
      metastore(i);
      store(i);
    }
  };
  void store(size_t idx) {
    if(held_strings[idx].changed) {
      its_fstream.seekp(offset(idx));
      its_fstream.write(held_strings[idx].c_str(), held_strings[idx].size() + 1);
      for(int j = held_strings[idx].size() + 1; j < slotsize; ++j)
        its_fstream.put(' '); // fill in with spaces up to next slot
      held_strings[idx].changed = false;
    }
  };
  // constructor(s) and destructor
  holder(const CH * const fn, size_t sz, size_t msz = sizeof(METADATA))
  : filename(fn), its_fstream(fn), total_room(std::filesystem::file_size(fn)),
    slotsize(sz), num_slots(total_room/sz), held_strings(num_slots),
    metasize(msz + 1) // sllow for a space (' ') or a zero bye ('\0')
  {held_strings.clear();};
  ~holder() {
    store();
    its_fstream.close();
  };
protected:
  /* class holder<>::held_string yields evermore functionality
     to its enclosing class holder<> throug a "friend class" declaration. */
  class held_string {
    string_t text; // may be initialized, may be not
    bool   loaded;
    bool  changed;
  public: // member functions
    friend class holder<CH>;
    const string_t & get_text() const {return text;};
    const CH * c_str()          const {return text.c_str();};
    const CH * data()           const {return text.data();};
    void clear()                       {text.clear();};
    const size_t size()         const {return text.length();};
    void operator=(const string_t& s) {text=s; changed=true; loaded=true;};
    bool load(istream_t& is = std::cin) { // read a line into 'text'
      if(loaded)                          // for impromptu initializations.
        return false;
      std::getline(is, text);
      loaded = true;
      changed = true;
      return true;
    };
    // constructor(s) and destructor
    held_string(const string_t & str) : text(str), loaded(true),  changed(true)  {};
    held_string(/*size_t l = 0*/) : /*length(l),*/ loaded(false), changed(false) {};
    ~held_string() = default;
  }; // end of class holder<>::held_string
}; // end of class holder<>

















































/* Self-standing, currently unmaintained lazy_string<> holds a string which may remain uninitialized,
   while other members hold cues (std::fstream &, offset and length) to initialization.
 * TODO:
 - reallocator:
   either changes offset and length
   or orchestrates a scheme for concatenating chunks of fixed length
   It should be declared to be a friend of lazy_string<> (make member vars private or protected)
 - empty file creator
 - encapsulate global functions read() and write() defined above
 */
template <typename CH = char>
class lazy_string {
public:
  typedef lazy_string<CH> lazy_string_t;
  class truncated : public std::exception {
    static constexpr const char * wh = "text truncated upon storing!";
  public:
    const char * what() const noexcept {return wh;};
  };
  typedef std::basic_fstream<CH> fstream_t;
  typedef std::size_t               size_t;
  typedef std::basic_string<CH>   string_t;
  fstream_t & fstream_ref;
  size_t offset;
  size_t room;
  string_t text; // may be initialized, may be not
  size_t length; // the length of string 'text'
  bool   loaded;
  bool  changed;
  //
  //    string_t & get_text()       {changed = true; return text;};
  const string_t & get_text() const {                return text;};
  void operator=(const string_t& s);
  bool load();
  bool store();
  bool store_and_clear() {store(); text.clear(); loaded = false; return true;};
  //lazy_string(const string_t & s) : text(s), length(s.length()) {};
  lazy_string(fstream_t & fs, size_t o, size_t r, size_t l = 0) : fstream_ref(fs), offset(o), room(r),
                                                                  length(l), loaded(false), changed(false) {}
  ~lazy_string() {
    if(changed && loaded) {
      store();
    }
  };
};
// Implementation of lazy_string<CH> member functions:
template <typename CH>
void lazy_string<CH>::operator=(const string_t& s) {
  length = s.length();
  if(length > room)
    throw lazy_string_t::truncated();
  text = s;
  changed = true;
  loaded  = true;
};
template <typename CH>
bool lazy_string<CH>::load() {
  if(length > room)
    throw lazy_string_t::truncated();
  read(fstream_ref, offset, length, text);
  loaded = true;
  changed = false; // you don't need to store 'text' away upon closing
  return true;
};
template <typename CH>
bool lazy_string<CH>::store() {
  length = text.length();
  if(length > room)
    throw lazy_string_t::truncated();
  write(fstream_ref, offset, length, text);
  changed = false;
  return true;
};





/** class proxy_string<> is a former version of lazy_string<>
    using a std::variant<string_t, pair<offset_t,length_t>
 *  ...
 */


template <typename CH = char>
class proxy_string {
public:
  typedef std::pair<std::size_t, std::size_t> string_ref_pair_t;
  typedef std::basic_string<CH> string_t;
  typedef       string_t        value_type;
  typedef       string_t &       reference;
  typedef const string_t & const_reference;
  mutable std::variant<string_t,string_ref_pair_t> string_or_ref;
  // accessors:
  bool holds_string() const {return string_or_ref.index() == 0;};
  bool  load_string() const {return true;}; // AS YET UNIMPLEMENTED
  std::size_t size() const {
    if(holds_string())
      return std::get<string_t>(string_or_ref).length();
    else
      return std::get<string_ref_pair_t>(string_or_ref).second;
  };
  reference       get_string()       {
    if(!holds_string())
      load_string();
    return std::get<string_t>(string_or_ref);
  };
  const_reference get_string() const {
    if(!holds_string())
      load_string();
    return get<string_t>(string_or_ref);
  };
  bool store_away(std::ofstream& ofs) const {
    if(holds_string())
      return false;
    else {
      string_or_ref = std::make_pair(ofs.tellp(), size());
      ofs << get_string();
      return true;
    }
  };
  // constructors and destructor:
  proxy_string(std::size_t p = 0, std::size_t l = 0) : string_or_ref(std::make_pair(p,l)) {};
  proxy_string(const string_t& s) : string_or_ref(s) {};
  proxy_string(std::size_t pos, std::size_t len, std::ifstream& ifs) {}; // AS YET UNIMPLEMENTED
  virtual ~proxy_string() {};
};
