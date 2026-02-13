#ifndef XMLTEXT_H
#define XMLTEXT_H

/* This unit contains a hierarchy of some tiny (XMLText, XMLComment, XMLCDATA etc.)
 * none of which either holds objects of other classes
                     or inherits    from other classes
 * TODO s
   [ ] XMLText::print(OSTREAM&,LEVEL) should process both default and defined entities
   [ ] XMLprocessing_instruction should have its name shortened
   [ ] XMLprocessing_instruction should be made a child of XMLText

   [ ] write XMLCommentBlock
   [ ] write XMLCDATABlock
   [ ] write XMLprocessing_instructionBlock
 */

#ifndef LEVEL_H
#include "Level.h"
#endif

#ifndef ENTITIES_H
#include "Entities.h"
#endif

#ifndef XMLNODE_H
#include "XMLnode.h"
#endif

template <typename CHAR = char,
          //PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          PrintTransformer PT = Entities<CHAR,std::basic_string<CHAR>, std::map>,
          typename LEVEL = Level<signed int> >
class XMLText : public XMLnode<CHAR,PT,LEVEL> {
public:
  typedef std::basic_string< CHAR>  string_t;
  typedef std::basic_ostream<CHAR> ostream_t;
  typedef Entities<CHAR,string_t,std::map> Entities_t;
protected:
  string_t text;
public:
  operator const CHAR * () const {return text.data();};
  void print(std::basic_ostream<CHAR>& o, LEVEL l) const override;
  void print_transformed(ostream_t& o, const PT& pt = PT(), LEVEL l=LEVEL(0)) const override;
  //
  XMLText(const std::basic_string<CHAR>& s) : text(s) {};
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
void XMLText<CHAR,PT,LEVEL>::print(ostream_t& o, LEVEL l) const {
  for(auto c : text)
    {
      switch (c) {
        case '<' : o << "&lt;";   break;
        case '>' : o << "&gt;";   break;
        case '\'': o << "&apos;"; break;
        case '\"': o << "&quot;"; break;
        case '&':  o << "&amp;";  break;
        default:   o << c;
      }
    }
};
template <typename CHAR,
          PrintTransformer PT,
          typename LEVEL>
void XMLText<CHAR,PT,LEVEL>::print_transformed(ostream_t& o, const PT& pt, LEVEL l) const {
  pt.print_transformed(o,text);
};

template <typename CHAR = char,
          PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          typename LEVEL = Level<signed int> >
struct XMLComment : XMLText<CHAR,PT,LEVEL> {
  using XMLText<CHAR,PT,LEVEL>::text;
  void print(std::basic_ostream<CHAR>& o, LEVEL l) const override { o << "<!-- " << text << " -->";};
  //
  XMLComment(const std::basic_string<CHAR>& com) : XMLText<CHAR,PT,LEVEL>(com) {};
};
template <typename CHAR = char,
          PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          typename LEVEL = Level<signed int> >
struct XMLCDATA : XMLText<CHAR,PT,LEVEL> {
  using XMLText<CHAR,PT,LEVEL>::text;
  void print(std::basic_ostream<CHAR>& o, LEVEL l) const override { o << "<![CDATA[" << text << "]]>";};
  //
  XMLCDATA(const std::basic_string<CHAR>& s) : XMLText<CHAR,PT,LEVEL>(s) {};
};
template <typename CHAR = char,
          PrintTransformer PT = DefaultPrintTransformer<CHAR>,
          typename LEVEL = Level<signed int> >
struct XMLprocessing_instruction {
  std::basic_string<CHAR> name;
  std::basic_string<CHAR> instruction;
  void print(std::basic_ostream<CHAR>& o, LEVEL l) const override { o << "<?" << name << ' ' << instruction  << " ?>";}
  //
  XMLprocessing_instruction(const std::basic_string<CHAR>& n, const std::basic_string<CHAR>& i) : name(n), instruction(i) {};
};




#endif
