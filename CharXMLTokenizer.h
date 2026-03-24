#ifndef CHAR_XML_TOKENIZER_H
#define CHAR_XML_TOKENIZER_H

#ifndef CHAR_TOKENIZER_H
#include "CharTokenizer.h"
#endif

#include <map>
#include <stack>

/* class CharXMLTokenizer is a child of CharTokenizer
   which overrides virtual member check(CHAR),
   which in turn calls some new member functions:
   - virtual bool check_lt_alnum(char c);
   - virtual bool check_lt_slash(char c);
   - virtual bool check_lt_question(char c);
   - virtual bool check_lt_bang(char c);
 * WARNING New versions of code is selected by asserting macro NEW
 * WARNING This class cannot parse DOCTYPE declarations (with or without entities), like
<!DOCTYPE book [
  <!ENTITY nwalsh "Norman Walsh">
  <!ENTITY chap1 SYSTEM "json.txt">
]>
           Its child 'CharEntXMLTokenizer' will be able to.
 * TODO:
 [x] prevent printing "empty" text nodes
 [x] test thoroughly then remove macro 'NEW'
 [x] member 'process_question()' should process PIs (processing instructions)
     by reading a name and a value (<?NAME VALUE?>)
 [x] member 'process_question()' should not treat an XML declaration as a processing instruction
 [ ] write:
            virtual void dispatch_***
                                       member functions
     for all output to std::cout
     and invoke them
 [?] process_opening_tag(),
     which is good for both opening and stand-alone tags,
     should:
     - read a tag name
     - call dispatch_tagname()
     - push name on a stack
     - read attributes, if any, and dispatch them
       as a reference to a map of strings
     - pop name off stack if it turns out to be a stand-alone tag
       and dispatch so
 [x] process_closing_tag() should:
     - read a name into temp
     - check temp.compare(name_stack.top()) == 0
       then execute name_stack.pop()
       and dispatch closing tag
 */

class CharXMLTokenizer : public CharTokenizer {
public:
  using Tokenizer::has_non_space_char;
  using CharTokenizer::temp; // for text nodes, element names...
  using CharTokenizer::is;

  // Member variables:
  std::string attribute_name, attribute_value;
  std::map<std::string,std::string> attribute_map;
  std::stack<std::string> name_stack;

  // Member Functions:
  void process_string(std::string & wd) override;

  virtual void dispatch_opening_name();
  virtual void process_opening_name(); // name read in opening tag
  virtual bool is_XML_name_char(char c) const;
  virtual void read_name(std::string & nm);
  virtual void dispatch_attribute_pair();
  virtual void process_opening_tag();
  virtual bool check_lt_alnum(char c);

  virtual void dispatch_closing_tag();
  virtual void process_closing_tag();
  virtual bool check_lt_slash(char c);

  virtual void xml_declaration(const std::string& attributes) const;
  virtual void process_pi(const std::string& name, const std::string& instruction) const;
  virtual void process_question();
  virtual bool check_lt_question(char c);

  virtual void process_bang();
  virtual bool check_lt_bang(char c);

  //virtual bool check_gt(char c);
  bool check(char c) override{
    return check_lt_alnum(c) || check_lt_slash(c) || check_lt_question(c) || check_lt_bang(c);
  };

  // Constructor(s) and destructor:
  CharXMLTokenizer(std::istream & i) : CharTokenizer(i) {};
  ~CharXMLTokenizer() = default;
};



#ifndef SEPARATE_COMPILATION
#include "CharXMLTokenizer.cpp"
#endif

#endif
