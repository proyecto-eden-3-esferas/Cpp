#ifndef XML_PRINT_H
#define XML_PRINT_H

#include <iostream>
#include      <map>
#include    <stack>
#include   <string>
#include  <utility>

#include "Level.h"

/* Class XMLprint for printing (into) an XML std::basic_ostream.
 * TODO:
   [ ] if two maps are printed as attribute pairs or namespaces,
       the class should check for same-named pairs
   [ ] a derived class might keep track of attributes and namespaces
       defined or inherited
   [ ] entities should be handled
   [ ]
 */

template <template <typename,typename> typename  MAP=std::map> // containers for attributes
class XMLprint {                                               // and namespaces
public:
  typedef std::ostream ostream_type;
  typedef std::string   string_type;
  typedef std::pair<    string_type,string_type> attribute_pair_type;
  typedef std::map<string_type,string_type> string_map_type;
  typedef Level<signed int> level_type;


protected:
  ostream_type & out;

public:
  std::stack<string_type> stack_of_names;
  level_type level;

  virtual void printXMLheader();
  virtual void printXMLdoctype(const string_type& dt);

  virtual void  open_opening_tag(const string_type & name);
  virtual void close_opening_tag();
  virtual void close_standalone_tag();
  virtual void close_element();
  virtual void add_style(const string_map_type& sty);

  // Constructor(s) and Destructor:
  XMLprint(ostream_type & o)                             : out(o) {};
  XMLprint(ostream_type & o, const string_map_type& sty) : out(o) {add_style(sty);};
  virtual ~XMLprint();
};

template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::printXMLheader() {
  out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
};
template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::printXMLdoctype(const string_type& dt) {
  out << "<!DOCTYPE " << dt <<">\n";
};
template <template <typename,typename> typename  MAP>
void XMLprint<MAP>:: open_opening_tag(const string_type & name) {
  stack_of_names.push(name);
  out << "<" << name;
};
template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::close_opening_tag() {
  out << '>';
};
template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::close_standalone_tag() {
  stack_of_names.pop();
  out << "/>";
};
template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::close_element() {
  out << "</" << stack_of_names.top() << '>';
  stack_of_names.pop();
};

template <template <typename,typename> typename  MAP>
void XMLprint<MAP>::add_style(const string_map_type& sty) {
  for(const auto & p : sty) {
    out << ' ' << p.first;
    out << "=\"" << p.second << '\"';
  }
};

template <template <typename,typename> typename  MAP>
XMLprint<MAP>::~XMLprint() {
  while(! stack_of_names.empty())
    close_element();
};

#endif
