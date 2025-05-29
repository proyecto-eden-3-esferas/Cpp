#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

/* Classes and struct's are defined in namespace 'j'
   and tested through file "json.cpp",
   so make changes (such as renaming classes, structs, members etc.)
   to both and (so far) only "json.{h|cpp}"
 * Five source types:
   TEXT (defaults to std::string),
   INT (int),
   FLOAT (double), and
   bool           = {true, false}
   std::nullopt_t = {std::nullopt}
 * std::nullopt_t is used for null.
 * the 'level' parameter into 'print_pair' and 'print_variant'
   mean the level of depth, which determines indentation...
 * TODO
   [ ] test initialization of jarray with {"peligro", 2, false}
   [ ] review and rewrite, if necessary, all-important global functions
       'print_pair' and 'print_variant'
   [ ] discuss and comment on            all-important global functions
       'print_pair' and 'print_variant'
   [v] handle commas
   [ ] handle indentation
   [ ] make it easy to use a std::string_view as a text type,
       instead of std::string
 */

namespace j {

  // forward declaration of 'jdoc':
  template <typename INT, typename FLOAT, typename TEXT>
  class jdoc;

  // forward declaration of 'jarray':
  template <typename INT, typename FLOAT, typename TEXT>
  struct jarray;

  template <typename INT, typename FLOAT, typename TEXT>
  using value_t = std::variant<std::nullopt_t, bool, TEXT, INT, FLOAT,
                                                 jdoc<INT, FLOAT,TEXT>, // use forward declaration of jdoc<>
                                               jarray<INT, FLOAT,TEXT>  // use forward declaration of jarray<>
                              >;
  template <typename INT = int, typename FLOAT = double, typename TEXT = std::string>
  struct jarray : public std::vector<      value_t<INT,FLOAT,TEXT> > {};

  template <typename INT = int, typename FLOAT = double, typename TEXT = std::string>
  class jdoc    : public std::map<   TEXT, value_t<INT,FLOAT,TEXT> > {
  public:
    typedef              std::map<   TEXT, value_t<INT,FLOAT,TEXT> > parent_type;
    using parent_type::map;
    //using parent_type::insert;
    //using parent_type::size;
  };

  template <typename OSTREAM = std::ostream>
  OSTREAM& oindent(OSTREAM& o, std::size_t level, std::size_t numsp = 2) {
    for(int i = 0; i < level; ++i) {
      for(int j = 0; j < numsp; ++j)
        o << ' ';
    }
    return o;
  }

  template <typename INT, typename FLOAT, typename TEXT>
  void print_variant(std::ostream& o,
                     const value_t<INT,FLOAT,TEXT>& v,
                     std::size_t level = 0) {
    std::size_t i{0};
    oindent(o,level);
    switch(v.index()) {
      case 0 : o <<         "null"                      /*<< std::endl*/; break;
      case 1 : o << std::boolalpha << std::get<bool>(v) /*<< std::endl*/; break;
      case 2 : o << '\"' << std::get<TEXT>( v) << "\""  /*<< std::endl*/; break;
      case 3 : o <<         std::get<INT>(  v)          /*<< std::endl*/; break;
      case 4 : o <<         std::get<FLOAT>(v)          /*<< std::endl*/; break;
      case 5 : o << '{' << std::endl;
               for(auto& s : std::get<jdoc<  INT,FLOAT,TEXT> >(v) ) {
                 print_pair<INT,FLOAT,TEXT>(o, s, level + 1);
                 if(i > 0)
                   o << ",\n";
                 ++i;
                 //o << std::endl;
               }
               o << "\n";
               oindent(o,level) << "}" /*<< std::endl*/;
               break;
      case 6 : o << '[' << std::endl;
               for(auto& s : std::get<jarray<INT,FLOAT,TEXT> >(v) ) {
                 print_variant<INT,FLOAT,TEXT>(o,s, level + 1);//print_variant<INT,FLOAT,TEXT>(o, s);
                 if(i > 0)
                   o << ",\n";
                 ++i;
               }
               o << "\n";
               oindent(o,level) << "]" /*<< std::endl*/;
               break;
      default: break;
    }
  };

  template <typename INT, typename FLOAT, typename TEXT>
  void print_pair(std::ostream& o,
                     const std::pair<TEXT,value_t<INT,FLOAT,TEXT>>& e,
                     std::size_t level = 0,
                     bool tell_idx = false) {
    int idx = e.second.index();
    std::size_t i{0};
    oindent(o,level) << '\"' << e.first << "\": ";
    if(tell_idx)
      o << " (has index " << idx << ") ";
    switch(idx) {
      case 0 : o <<         "null"                             /*<< std::endl*/; break;
      case 1 : o << std::boolalpha << std::get<bool>(e.second) /*<< std::endl*/; break;
      case 2 : o << '\"' << std::get<TEXT>( e.second) << "\""  /*<< std::endl*/; break;
      case 3 : o <<         std::get<INT>(  e.second)          /*<< std::endl*/; break;
      case 4 : o <<         std::get<FLOAT>(e.second)          /*<< std::endl*/; break;
      case 5 : o << '{' << std::endl;
               for(auto& s : std::get<jdoc<INT,FLOAT,TEXT> >(e.second) ) {
                 if(i > 0)
                   o << ",\n";
                 ++i;
                 print_pair<INT,FLOAT,TEXT>(o, s, level + 1);
               }
               o << '\n';
               oindent(o,level) /*<< std::endl*/;
               break;
      case 6 : o << '[' << std::endl;
               for(auto& s : std::get<jarray<INT,FLOAT,TEXT> >(e.second) ) {
                 if(i > 0)
                   o << ",\n";
                 ++i;
                 print_variant<INT,FLOAT,TEXT>(o, s, level + 1);
               }
               o << "\n";
               oindent(o,level) << "]" /*<< std::endl*/;
               break;
      default: break;
    }
  };

} // end of namespace j
#endif
