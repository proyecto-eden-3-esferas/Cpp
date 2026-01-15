#ifndef XML_COMPONENTS_H
#include "XMLelement.h"
#endif

#ifndef XML_GLOBALS_H
#include "XML.globals.h"
#endif


using namespace std;

typedef XMLelement<std::list> XMLelem_t;

int main() {
  
  // Declare an XMLText object ('t') and serialize it / deserialize it into/out of a stringstream (ss):
  cout << "Declare an XMLText object (\'t\'),\n";
  cout << "CONTENTS: A text section,\nnot an <element kind=\"whatever\"/> ...\n";
  XMLText t("A text section,\nnot an <element kind=\"whatever\"/> ...");
  cout << "serialize \'t\' to screen: " << '\"'; serialize_string(cout, t.text); cout << '\"' << endl;
  cout << "last serialize it / deserialize it into/out of a stringstream (\'ss\'):\n";
  stringstream ss;
  serialize_string(ss,t.text);
  cout << "contents of \'ss\': \"" << ss.str() << '\"' << endl << endl;
  
  cout << "Then deserialize_string(ss) into pChar, of type char*\n";
  char* pChar = deserialize_string(ss);
  cout << "pChar: \"" << pChar << '\"' << endl << endl;
  
  cout << "A CData section (<manifold \\ / ?... \"&) should be output as it is, with no entity conversions.\n";
  XMLCDATA cdata("<manifold \\ / ?... \"&");
  cout << cdata;
  cout << endl << endl;
  
  cout << "Declare an XMLelement variable \'h\' with name \'holder\' and make it hold text, subelements etc.\n";
  XMLelem_t h("holder");
  cout << "The name of XMLelement \'h\' is \'" << h.name << '\'' << endl << endl;
  
  cout << "Now add attributes to \'h\'\n";
  h["colour"] = "thisle";
  h("xml:id", "1243")("href", "www.google.com");

  cout << "Then add some a text node to \'h\' as well as a \'subholder\' element holding some more text and a \'subelement\' element:\n";
  //
  h.children.push_back("some text.");
  // Add subelement 's' after initializing it:
  XMLelem_t s("subholder");
    s.children.push_back("subtext");
    s.children.push_back("Some more subtext");
    // s += XMLText("Still some more"); // Fails to compile!!!
    s.children.push_back(XMLelem_t("subelement"));
  h.children.push_back(s);

  h.children.push_back(cdata);

  XMLprocessing_instruction pi("ps2pdf", "file1.ps");
  h.children.push_back(pi);
  
  // Now check the inserter:
  cout << "Now use inserter recursively: " << endl;
  cout << h << endl << endl << "serialize \'h\': " << endl;
  serialize(cout, h);
  
  cout << "\n\ntest unicode character € (\\u20AC):\n";
  cout << endl << "\u20AC1.00" << endl;
  
  return 0;
}
