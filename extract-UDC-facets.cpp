#ifndef EXTRACT_UDC_FACETS_CPP
#define EXTRACT_UDC_FACETS_CPP

#ifndef EXTRACT_UDC_FACETS_H
#include "extract-UDC-facets.h"
#endif

/** File "extract-UDC-facets.cpp"
 */

// regex_t UDC_specific_*** capture the inside of a facet (no punctuation)
const regex_t UDC_specific_time( R"(.*\"(.*[^\"]+)\".*)");
const regex_t UDC_specific_lang( R"(.*=([0-9\.]+).*)");
const regex_t UDC_specific_gc(   R"(.*-(0[0-9\.]*).*)");
const regex_t UDC_specific_place(R"(.*\(([1-9][^\)]*)\).*)");

const string_t regex_pre(".*");
const string_t regex_post(".*");

const string_t time_matcher(R"(.*(\"(.*[^\"]+)\").*)"); // match ".+"
const  regex_t time_matcher_regex(time_matcher);

const string_t lang_matcher(R"(.*(=([0-9]+)).*)"); // match =[0-9]+
const  regex_t lang_matcher_regex(lang_matcher);

const string_t gc_matcher(R"(.*(-(0[0-9\.]*)).*)"); // match -0[0.9]*
const  regex_t gc_matcher_regex(gc_matcher);

const string_t place_matcher(R"(.*(\(([1-9][^\)]*)\)).*)");
const  regex_t place_matcher_regex(place_matcher);


bool has_facet(const string_t& str, const regex_t& re) {
  return std::regex_match(str,re);
};

void print_facets(const string_t& str) {
  std::smatch sm;
  std::cout << "String \"" << str << "\" has facets:\n";
  std::regex_match(str,sm,time_matcher_regex);
  if(sm.size() > 0) {
    std::cout << "  [time:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,lang_matcher_regex);
  if(sm.size() > 0) {
    std::cout << "  [lang:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,gc_matcher_regex);
  if(sm.size() > 0) {
    std::cout << "  [general chars:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,place_matcher_regex);
  if(sm.size() > 0) {
    std::cout << "  [place:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  /**/
};

void print_facets_match_default(const string_t& str) {
  std::smatch sm;
  std::cout << "String \"" << str << "\" has facets:\n";
  std::regex_match(str,sm,time_matcher_regex, std::regex_constants::match_default);
  if(sm.size() > 0) {
    std::cout << "  [time:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,lang_matcher_regex, std::regex_constants::match_default);
  if(sm.size() > 0) {
    std::cout << "  [lang:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,gc_matcher_regex, std::regex_constants::match_default);
  if(sm.size() > 0) {
    std::cout << "  [general chars:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
  std::regex_match(str,sm,place_matcher_regex, std::regex_constants::match_default);
  if(sm.size() > 0) {
    std::cout << "  [place:] ";
    for(auto & m : sm)
      std::cout << '\"' << m << "\", ";
    std::cout << '\n';
  }
};


#endif
