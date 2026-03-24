#ifndef CHAR_XML_TOKENIZER_H
#include "CharXMLTokenizer.h"
#endif

#include <fstream>

using namespace std;


int main() {

  ifstream ifs("simple.xml");

  CharXMLTokenizer cxt0(ifs);
  cxt0.tokenize();

  ifs.close();

  return 0;

}
