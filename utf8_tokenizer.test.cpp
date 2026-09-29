#ifndef UTF8_TOKENIZER_H
#include "utf8_tokenizer.h"
#endif

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


/* A trivial text-and-its-width data type is declared.
   Then a sequence container of such pairs is declared. */
typedef std::pair<std::string, double> tw_token_type;
typedef dimtoken<double, std::string> dimtoken_t;
std::vector<dimtoken_t> vot; // vector of tokens
typedef xml_tokenizer xml_tokenizer_t;

/* Some paragraph-length strings are defined:
   - WhenGodHadAWife: only contains plain ASCII (w)
   - WhenGodHadAWife_dash: contains plain ASCII and some dash and acute apostrophe chars (d)
   - Fraguas:              contains some common Spanish two-byte characters (f)
   - Fraguas_strong      : contains 2-byte characters and an XML <strong> element (s) */
std::string WhenGodHadAWife = R"(Despite what Jews and Christians-and indeed most people-believe, the ancient Israelites venerated several deities besides the Old Testament god Yahweh, including the goddess Asherah, Yahweh's wife, who was worshipped openly in the Jerusalem Temple. After the reforms of King Josiah and Prophet Jeremiah, the religion recognized Yahweh alone, and history was rewritten to make it appear that it had always been that way. The worship of Asherah and other goddesses was now heresy, and so the status of women was downgraded and they were blamed for God's wrath.)";
std::string WhenGodHadAWife_dash = R"(Despite what Jews and Christians–and indeed most people–believe, the ancient Israelites venerated several deities besides the Old Testament god Yahweh, including the goddess Asherah, Yahweh’s wife, who was worshipped openly in the Jerusalem Temple. After the reforms of King Josiah and Prophet Jeremiah, the religion recognized Yahweh alone, and history was rewritten to make it appear that it had always been that way. The worship of Asherah and other goddesses was now heresy, and so the status of women was downgraded and they were blamed for God’s wrath.)";
std::string Fraguas = R"(Fraguas, un pueblo en la Sierra Norte de Guadalajara, volvió a llenarse de vida cuando en 2013 varias personas decidieron asentarse allí. Su idea: vivir en armonía con la naturaleza, de forma autogestionada y tomando las decisiones de forma horizontal y a unos ritmos mucho más sanos que los preponderantes de la ciudad. El paso de los años no ha conseguido variar su modelo de vida, aunque sí ha trastocado la esperanza y futuro de este proyecto)";
std::string Fraguas_strong = R"(Fraguas, un pueblo en la Sierra Norte de Guadalajara, volvió a llenarse de vida cuando en 2013 varias personas decidieron asentarse allí. Su idea: vivir en armonía con la naturaleza, de forma autogestionada y tomando las decisiones de forma horizontal y a unos ritmos mucho más sanos que los preponderantes de la ciudad. El paso de los años no ha conseguido variar su modelo de <strong>vida</strong>, aunque sí ha trastocado la esperanza y futuro de este proyecto)";

std::ifstream ifs("README.txt");
xml_tokenizer tawt{
  {"á", 'a'},
  {"í", 'i'},
  {"ñ", 'n'}
  /*
  {"", ''},
  {"", ''},
  {"", ''},
  {"", ''},
  {"", ''},
  {"", ''},

  {"Ñ", 'N'},
  {"Í", 'I'}
  */

};

using namespace std;

int main() {
  /* remove_XML_tag(IN,OUT) */
  cout << "By means of global function xml_tokenizer::remove_XML_tag(IN_STRING, OUT_STRING)\n";
  std::string str_with_tags = "A <strong>weak</strong> supporter";
  std::string temp;
  xml_tokenizer_t::remove_XML_tag(str_with_tags, temp);
  cout << '\"' << str_with_tags << "\"\nbecomes\n\"" << temp << "\"\n\n";


  /* Get the user to choose a paragraph-length string, for it to be
   * (1) trivially tokenized into substrings without spaces
   * (2) dimensional tokens or dimtoken's
   */
  char choice;
  cout << "Type the character in round brackets, then press enter, to break the matching paragraph-length string into words-like tokens:\n";
  cout << "(w) WhenGodHadAWife: only contains plain ASCII\n";
  cout << "(d) WhenGodHadAWife_dash: contains plain ASCII and some dash and acute apostrophe chars\n";
  cout << "(f) Fraguas:              contains some common Spanish two-byte characters\n";
  cout << "(s) Fraguas_strong      : contains 2-byte characters and an XML <strong> element\n";
  cin >> choice;

  std::stringstream ss;
  switch (choice) {
    case 'w': ss << WhenGodHadAWife;
              break;
    case 'd': ss << WhenGodHadAWife_dash;
              break;
    case 'f': ss << Fraguas;
              break;
    case 's': ss << Fraguas_strong;
              break;
    default:  ss << WhenGodHadAWife;
              break;
  }
  while (true) {
    ss >> temp;
    if(ss)
      std::cout << '[' << temp << ']';
    else {
      std::cout << '\n';
      break;
    }
  }

  // Reload std::stringstream 'ss' with the same std::string as before:
  ss.clear();
  switch (choice) {
    case 'w': ss << WhenGodHadAWife;
              break;
    case 'd': ss << WhenGodHadAWife_dash;
              break;
    case 'f': ss << Fraguas;
              break;
    case 's': ss << Fraguas_strong;
              break;
    default:  ss << WhenGodHadAWife;
              break;
  }

  // Make Spanish '\ñ' be as wide as 'n'
  // tokenize 'ss' into a vector of tokens ('vot'):
  //tawt.register_2B("ñ", 'n');
  //tawt.register_2B("í", 'i');
  tawt.tokenize(vot, ss);
  // and print the thus generated tokens:
  for(const auto & tk : vot) {
    cout << "word: \"" << tk.get_text() << "\" has width: " << tk.get_width() << '\n';
  }

  /* Test member functions:
     - utf8_tokenizer::leads_2B_utf8(CHAR)
     - utf8_tokenizer::follows_up_utf_2B_leader(CHAR)
   */
  string n("n"), ny("ñ"), aa("á"), adm("¡"), ag("à");
  cout << boolalpha;
  cout << "Is " << n << n.length() << " lead by a 110x xxxx character? ";
  cout << utf8_tokenizer::leads_2B_utf8(n[0]) << '\n';

  cout << "Is " << ny << ny.length() << " lead by a 110x xxxx character? ";
  cout << utf8_tokenizer::leads_2B_utf8(ny[0]) << '\n';
  cout << "Is ny[0] a follow-up character? ";
  cout << tawt.follows_up_utf_2B_leader(ny[0]) << '\n';
  cout << "Is ny[1] a follow-up character? ";
  cout << tawt.follows_up_utf_2B_leader(ny[1]) << '\n';

  cout << "Is " << aa << aa.length() << " lead by a 110x xxxx character? ";
  cout << utf8_tokenizer::leads_2B_utf8(aa[0]) << '\n';

  cout << "Is " << ag << ag.length() << " lead by a 110x xxxx character? ";
  cout << utf8_tokenizer::leads_2B_utf8(ag[0]) << '\n';

  cout << "Is " << adm << adm.length()  << " lead by a 110x xxxx character? ";
  cout << utf8_tokenizer::leads_2B_utf8(adm[0]) << '\n';

  cout << "Character " << adm << " is  " << adm.length() << " bytes long.\n";



  return 0;
}
