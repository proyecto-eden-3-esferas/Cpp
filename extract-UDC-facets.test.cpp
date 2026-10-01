#ifndef EXTRACT_UDC_FACETS_H
#include "extract-UDC-facets.h"
#endif

// Some test strings:
std::string time0(R"(42"1915-1925")"), time1(R"()"), time2(R"()"), time3(R"()");
std::string lang0(R"(42=34)");
std::string general_characteristics0(R"(42-03:44)");
std::string place0(R"(931.33(11)=34)");
//std::string decimal_with_(R"()");
//string_t decimal_with_(R"()");


using namespace std;
int main()
{
  /*
  cout << "Has " << time0 << " facet time? " << boolalpha << has_facet(time0, time_matcher_regex) << '\n';
  cout << "Has " << lang0 << " facet time? " << boolalpha << has_facet(lang0, time_matcher_regex) << "\n\n";

  cout << "Has " << lang0 << " facet lang? " << boolalpha << has_facet(lang0, lang_matcher_regex) << '\n';
  cout << "Has " << time0 << " facet lang? " << boolalpha << has_facet(time0, lang_matcher_regex) << "\n\n";

  cout << "Has " << general_characteristics0 << " facet gc? " << boolalpha
       << has_facet(general_characteristics0,gc_matcher_regex) << '\n';
  cout << "Has " << time0 << " facet gc? " << boolalpha
       << has_facet(time0,gc_matcher_regex) << "\n\n";

  */
  cout << "Print_facets(ALL STRINGS):\n";
  print_facets(time0);
  print_facets(lang0);
  print_facets(general_characteristics0);
  print_facets(place0);
  //print_facets();

  /* Calling print_facets_match_default(ALL STRINGS)
     produces much the same results:
  cout << "Last, print_facets_match_default(ALL STRINGS):\n";
  print_facets_match_default(time0);
  print_facets_match_default(lang0);
  print_facets_match_default(general_characteristics0);
  print_facets_match_default(place0);
  //print_facets_match_default(STRING);
  */

  return 0;
}
