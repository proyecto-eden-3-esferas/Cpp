#ifndef SPECIFIC_OSTREAM_H
#define SPECIFIC_OSTREAM_H

//#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

#include "Level.h"

class specific_ostream {
public:
  typedef std::ostream ostream_t;
  ostream_t & os;
  Level<signed int> level;
protected:
  specific_ostream() = delete;
  specific_ostream(ostream_t& o, unsigned int l = 0) : os(o), level(l) {};
  virtual ~specific_ostream() = default;
};

/* Class section comprises:
   - a title ('title'),
   - some text ('text'),
   - and a container of subsections ('subsections')
 * Class section is not suitable for XML
   in that an XML section (an "element") contains a sequence
   of either text or element nodes
 * TODO:
   [ ] Perhaps class section should have a template parameter for info
 */

// Forward declaration of class section<>
template <template <typename> typename CONT>
class section;

template <template <typename> typename CONT = std::vector>
class section {
public:
  typedef std::string      string_t;
  typedef std::string_view string_view_t;
  string_t title;
  string_t text;
  bool block;
  typedef CONT<section<CONT>> subsections_t;
                              subsections_t subsections;
  //
  bool has_title() const {return title.size() > 0;};
          string_view_t get_title() const  {return title;};
  virtual string_view_t get_info()         {return get_title();};
  string_view_t get_text()  const {return  text;};
  void add_subsection(string_view_t ti = "", string_view_t te = "", bool b=true) {
    subsections.emplace_back(ti,te,b);
  };

  /* The iterator interface
   * A partial specialization might implement operator[] (INDEX)
   */
  auto begin() {return subsections.begin();};
  auto end()   {return subsections.  end();};
  //const auto &   end() const {return subsections.  end();};
  //
  section(string_view_t ti = "", string_view_t te = "", bool b=true) : title(ti), text(te), block(b) {};
}; // class section

class sectioned_ostream : public specific_ostream {
public:
  using specific_ostream::level;
  std::stack<std::string> section_names;
  virtual void start_section(std::string_view sect);
  virtual void   end_section();
  // Constructor(s)
  sectioned_ostream(std::ostream& o = std::cout, signed int l=0) : specific_ostream(o,l) {};
};
void sectioned_ostream::start_section(std::string_view sect) {
  section_names.emplace(sect);
  ++level;
};
void sectioned_ostream::end_section() {
  section_names.pop();
  --level;
};

class LaTex_ostream : public sectioned_ostream {
public:
  using sectioned_ostream::level;
  typedef std::ostream ostream_t;
  using sectioned_ostream::os;
  const std::string doctype;
  void output_prefix();
  void output_postfix();
  LaTex_ostream(ostream_t& o=std::cout, std::string_view dt = "document");
  ~LaTex_ostream();
};
LaTex_ostream::LaTex_ostream(ostream_t& o, std::string_view dt) : sectioned_ostream(o,0), doctype(dt) {
  output_prefix();
};
LaTex_ostream::~LaTex_ostream() {
  output_postfix();
};


#ifndef SEPARATE_COMPILATION
#include "specific_ostream.cpp"
#endif


#endif
