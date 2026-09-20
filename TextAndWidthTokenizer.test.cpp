#ifndef TEXT_AND_WIDTH_TOKENIZER_H
#include "TextAndWidthTokenizer.h"
#endif

#include <fstream>
#include <string>
#include <utility>
#include <vector>

/* A trivial text-and-its-width construct is declared as a
     std::pair<std::string, double>
 * Then a sequence container of such pairs is declared.
 * This is passed into member function TextAndWidthTokenizer::tokenize(SEQUENCE)
 * TASKS:
   Reassigning an istream fails, as an std::iostream has no copy assignment (deleted)
   [ ]
 */

// A trivial text-and-width structure:
typedef std::pair<std::string, double> tw_token_type;
std::vector<tw_token_type> vot; // vector of tokens

std::ifstream ifs("README.txt");
TextAndWidthTokenizer tawt;

using namespace std;

int main() {

  tawt.tokenize(vot, ifs);

  for(const auto & tk : vot) {
    cout << "word: \"" << tk.first << "\" has width: " << tk.second << '\n';
  }

  string n("n"), ny("ñ"), aa("á"), adm("¡"), ag("à");
  cout << boolalpha;
  cout << "Is " << n << n.length() << " lead by a 110x xxxx character? ";
  cout << TextAndWidthTokenizer::leads_2B_utf8(n[0]) << '\n';

  cout << "Is " << ny << ny.length() << " lead by a 110x xxxx character? ";
  cout << TextAndWidthTokenizer::leads_2B_utf8(ny[0]) << '\n';
  cout << "Is ny[0] a follow-up character? ";
  cout << TextAndWidthTokenizer::follows_multibyte_utf8_leader(ny[0]) << '\n';
  cout << "Is ny[1] a follow-up character? ";
  cout << TextAndWidthTokenizer::follows_multibyte_utf8_leader(ny[1]) << '\n';

  cout << "Is " << aa << aa.length() << " lead by a 110x xxxx character? ";
  cout << TextAndWidthTokenizer::leads_2B_utf8(aa[0]) << '\n';

  cout << "Is " << ag << ag.length() << " lead by a 110x xxxx character? ";
  cout << TextAndWidthTokenizer::leads_2B_utf8(ag[0]) << '\n';

  cout << "Is " << adm << adm.length()  << " lead by a 110x xxxx character? ";
  cout << TextAndWidthTokenizer::leads_2B_utf8(adm[0]) << '\n';

  cout << "Character " << adm << " is  " << adm.length() << " bytes long.\n";



  return 0;
}
