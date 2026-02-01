#ifndef XML_COMPONENTS_H
#define XML_COMPONENTS_H

//#include "../boost_selector_classes.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <variant>   // C++17
#include <sstream>   // for testing


/* A hierarchy for holding XML as objects
 *  -------------------------------------
 * I have used C struct's instead of classes.
 * These classes hold C text (==are initialized with C-strings), thus characters {<, >, &, ', "} are inserted into std::ostreams as
   "&lt;", "&gt;", "&amp;", "&apos;" and "&quot;",
 * an XML element (including an XML document's root) may contain:
    - elements (class XMLelement<>)
    - text (class XMLText)
    - a CDATA section (class XMLCDATA)
    - a processing instruction (struct XMLprocessing_instruction)
 */

/*
 * NOTES:
 * char* deserialize_string(std::istream& is) uses new and Who is going to erase it? When? How?
 *  (in violation of Resource Acquisition is Initialization) 
 * 
 */

struct XMLText {
  std::string text;
  XMLText(const std::string& s) : text(s) {};
};

struct XMLprocessing_instruction {
  std::string name;
  std::string instruction;
  XMLprocessing_instruction(const std::string& n, const std::string& i) : name(n), instruction(i) {};
};

struct XMLCDATA {
  const std::string text;
  XMLCDATA(const std::string& s) : text(s) {};
};

// forward declaration of XMLelement<>
template <template <typename> typename CONT>
class XMLelement;

template <template <typename> typename CONT = std::list>
class XMLelement {
public:
  typedef std::string string_t;
  typedef             string_t name_t;
  using XMLelement_t = XMLelement<CONT>;
  using XMLelement_text_or_CDATA = std::variant<
                                     std::string,
                                     XMLelement_t,
                                     XMLCDATA,
                                     XMLprocessing_instruction>;
  //
  const name_t name;
  std::list<XMLelement_text_or_CDATA> children;
  std::map<string_t, string_t> attributes;
  // Member functions to handle member variables:
  string_t& operator[](const string_t& s) {return attributes[s];};
  XMLelement_t& operator()(const string_t& n, const string_t& attr) {attributes[n] = attr; return *this;};
  XMLelement_t& operator+=(const XMLText&                   t) {children.push_back(t); return *this;};
  XMLelement_t& operator+=(const XMLprocessing_instruction& p) {children.push_back(p); return *this;};
  XMLelement_t& operator+=(const XMLCDATA&                  d) {children.push_back(d); return *this;};
  XMLelement_t& operator+=(const XMLelement_t&              e) {children.push_back(e); return *this;};
  // Constructor(s):
  XMLelement(const string_t& s) : name(s) {};
};

#endif

