#ifndef XML_PRINTABLE_H
#define XML_PRINTABLE_H

/* XML Interface Struct XMLprintable<>
 * TODO
   [ ]  Handle indentation through passing level information in and out of the printable objects/calls
   [ ] write and import a light html headers-only file for HTML/XML (light-html.h)
   [ ] then close_standalone_tag(OSTREAM, ATTRS) should be moved to "light-html.h"
   [x] Implement adding attributes (class, id, stroke-width) to elements.
       This might be realized as the last input argument
       to global functions and constructors, as in:
       FUNCTION(..., const std::string & attr = "")
 */

#include <iomanip> // for std::setprecision(INT)
#include <iostream>
#include <map>
#include <string>


//template <typename F = double>
template <template <typename,typename> typename  MAP = std::map>    // containers for attributes and namespaces
struct XMLprintable {
  /* A typedef for a map from attribute keys to values.
   * These attributes are "non-essential" or intrinsic to the shape.
   * For example a circle's centre is essential (needed for code to make sense)
   * whereas a fill (a color) is non-essential and could be defined as CSS
   * Now, a <marker> id is an essential attribute, whereas a <circle> id is not.
   * Any member named print_opening_tag_unclosed(...) should print an unclosed opening tag like:
   *   <NAME ATTR1="VAL1" ATTR2="VAL2"...
   * (That is, unclosed means no > character, in case say some more attrs need appending)
   */
  typedef          std::string string_t;
  typedef MAP<string_t,string_t> attr_map_type;
  static void print_attrs(const attr_map_type& m, std::ostream& o = std::cout, char sep = '\"');
  //
  virtual void print_opening_tag_unclosed(std::ostream& o = std::cout)                        const = 0;
  virtual void print_opening_tag_unclosed(std::ostream& o,             const string_t& attrs) const;
  virtual void print_opening_tag(std::ostream& o = std::cout, const string_t& attrs = "") const;
  virtual void print_element(            std::ostream& o = std::cout, const string_t& attrs = "") const;
  void         close_standalone_tag(std::ostream& o = std::cout, const string_t& attrs = "") const;
  /* As yet unimplemented:
   */
  virtual void print_opening_tag_unclosed(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const;
  virtual void print_opening_tag(   const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const;
  virtual void print_element(             const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const;
  void         close_standalone_tag(const attr_map_type& m, std::ostream& o = std::cout, char sep='\"') const;
};

// Implementation of SVG Members taking a String 'attrs' Attribute:

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_opening_tag_unclosed(std::ostream& o, const string_t& attrs) const {
  print_opening_tag_unclosed(o);
  o << attrs;
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_attrs(const XMLprintable::attr_map_type& m,
                             std::ostream& o,
                             char sep)
{
  for(const auto& p : m)
    o << ' ' << p.first << '=' << sep << p.second << sep;
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_opening_tag(std::ostream& o, const std::string& attrs) const
{
  print_opening_tag_unclosed(o,attrs);
  o << ">\n";
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_element(std::ostream& o, const std::string& attrs) const
{
  print_opening_tag_unclosed(o);
  close_standalone_tag(o,attrs);
};


template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::close_standalone_tag(std::ostream& o, const std::string& attrs) const
{
  if(attrs.length() > 0)
    o << ' ' << attrs << ' ';
  o << "/>\n";
};

// Implementation of Attribute-Map SVG Members:

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_opening_tag_unclosed(const XMLprintable::attr_map_type& m,
                                    std::ostream& o,
                                    char sep) const {
  print_opening_tag_unclosed(o);
  print_attrs(m,o,sep);
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_opening_tag(const XMLprintable::attr_map_type& m,
                                       std::ostream& o ,
                                       char sep) const {
  print_opening_tag_unclosed(m,o,sep);
  o << ">\n";
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::print_element(const XMLprintable::attr_map_type& m,
                           std::ostream& o ,
                           char sep) const {
  print_opening_tag_unclosed(m,o,sep);
  close_standalone_tag(o);
};

template <template <typename,typename> typename  MAP>
void XMLprintable<MAP>::close_standalone_tag(const XMLprintable::attr_map_type& m,
                                        std::ostream& o ,
                                        char sep) const {
  print_attrs(m,o,sep);
  o << "/>\n";
};

#endif
