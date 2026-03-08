#ifndef CHAR_XML_TOKENIZER_H
#define CHAR_XML_TOKENIZER_H

#ifndef CHAR_TOKENIZER_H
#include "CharTokenizer.h"
#endif

/* class CharXMLTokenizer
 *
 * TODO:
 [ ] prevent printing "empty" text nodes
 [ ] process_opening_tag(),
     which is good for both opening and stand-alone tags,
     should:
     - read a tag name
     - call dispatch_tagname()
     - push name on a stack
     - read attributes, if any, and dispatch them
       as a reference to a map of strings
     - pop name off stack if it turns out to be a stand-alone tag
       and dispatch so
 [ ] process_closing_tag() should:
     - read a name into temp
     - check temp.compare(name_stack.top()) == 0
       then execute name_stack.pop()
       and dispatch closing tag
 */

class CharXMLTokenizer : public CharTokenizer {
public:
  using CharTokenizer::temp;
  using CharTokenizer::is;

  // Member variables:
  std::string tag_string;

  // Member Functions:
  void process_string(std::string & wd) override;

  virtual void process_opening_tag();
  virtual bool check_gt_alnum(char c);

  virtual void process_closing_tag();
  virtual bool check_gt_slash(char c);

  virtual void process_question();
  virtual bool check_gt_question(char c);

  virtual void process_bang();
  virtual bool check_gt_bang(char c);

  //virtual bool check_gt(char c);
  bool check(char c) override{
    return check_gt_alnum(c) || check_gt_slash(c) || check_gt_question(c) || check_gt_bang(c);
  };

  // Constructor(s) and destructor:
  CharXMLTokenizer(std::istream & i) : CharTokenizer(i) {};
  ~CharXMLTokenizer() = default;
};



#ifndef SEPARATE_COMPILATION
#include "CharXMLTokenizer.cpp"
#endif

#endif
