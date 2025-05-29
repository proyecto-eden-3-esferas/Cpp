/* File "string_view_variant_tokenizer.test.cpp"
   - includes class basic_string_view_variant_tokenizer<CHAR>
   - includes  classes/types jdoc, jarray value_t in namespace j, in file "json.h"
 * This file ...
 * TODO
 [ ] Load from a single JSON object string
 [ ] Load from an array of JSON objects
 [ ] Code some provision for escaping,
     possibly relying on 'json_escaper' in file "escaper.h"
 [ ] Generally, handle special characters in strings

 */

#ifndef STRING_VIEW_VARIANT_TOKENIZER_H
#include "string_view_variant_tokenizer.h"
#endif
#ifndef STRING_VIEW_VARIANT_TOKENIZER_CPP
#include "string_view_variant_tokenizer.cpp"
#endif

#include <string>
#include <string_view>
#include <iostream>

typedef std::string string_type;
typedef string_view_variant_tokenizer<char> string_view_variant_tokenizer_type;
typedef typename string_view_variant_tokenizer_type::char_string_quote_type
                                                     char_string_quote_type;
/* The 'string_view_variant_print_***' functions below
 * extract and print all tokens in a tokenizer object ('t')
 * to an out-stream
 */
void string_view_variant_print_special_or(string_view_variant_tokenizer_type& t,
                                      std::ostream& o = std::cout);
void string_view_variant_print_char_or_quote(string_view_variant_tokenizer_type& t,
                                             std::ostream& o = std::cout,
                                             bool dq = true);
void string_view_variant_print_char_word_or_quote(string_view_variant_tokenizer_type& t,
                                                  std::ostream& o = std::cout,
                                                  bool dq = true);

string_type jsondelims("{}[],:");
string_type xmldelims0("<>=\'&");
string_type xmldelims1("<>=\'&[];/");

string_type jsonrec0("{\"name\" : \"Carlos Fdez-Victorio\", \"age\": 55}, {\"name\" : \"Francisco\", \"age\": null}");
string_type jsonrec1(R"({
  "name": "Annie",
  "married-to": "Phil",
  "interests": ["buddhism:mahayana", "yoga", "mathematics"],
  "address": {
    "street": "Olafsen",
    "number": 11,
    "door": null
  },
  "favourite-book": "\"So long\" she said."
})");
string_type xmlrec0(R"(<p id="first">Herein we strive ...</p>)");
string_type xmlrec1(R"(<book encoding="utf">
  <title>Synthesis</title>
  <p>There&apos;s a ...</p>
</book>)");


string_view_variant_tokenizer_type simple_tokenizer0(jsonrec0,  jsondelims);
string_view_variant_tokenizer_type simple_tokenizer1(jsonrec1, jsondelims);
string_view_variant_tokenizer_type simple_tokenizer2( xmlrec0, xmldelims0);
string_view_variant_tokenizer_type simple_tokenizer3( xmlrec1, xmldelims1);

/*
string_view_variant_tokenizer_type simple_tokenizer1(jsonrec1, jsondelims);
*/

int main(int argc, char** argv)
{
  std::cout << "Type a number then ENTER for \'simple_tokenizer\' to parse a string of your choice.\n\
  0 : a      shortish JSON record\n\
  1 : a medium-length JSON record\n\
  2 : a      shortish  XML record\n\
  3 : a medium-length  XML record\n";
  int i,j;
  std::cin >> i;
  std::cout << "You have requested to parse: \"\n";
  switch (i) {
    case 0:  std::cout << jsonrec0.c_str() << "\"\n";
             break;
    case 1:  std::cout << jsonrec1.c_str() << "\"\n";
             break;
    case 2:  std::cout << xmlrec0.c_str() << "\"\n";
             break;
    case 3:  std::cout << xmlrec1.c_str() << "\"\n";
             break;
    default: std::cout << xmlrec1.c_str() << "\", (which is the default)\n";
             break;
  }

  std::cout << "Which member function would you like your text to get parsed through?\n\
Type 0, 1\n\
(0) Quit\n\
(1) get_special_or(),   (good for  XML), or\n\
(2) get_char_or_quote() (good for JSON)\n\
(3) get_char_word_or_quote() (good for JSON)\n";

  std::cin >> j;

  bool dq{true};
  std::cout << "Would you like quotes to be dropped?\n\
(0) No.  Don\'t drop quoting characters, thanks. (Currently fails)\n\
(1) Yes. Drop quoting characters, please.\n";
  std::cin >> dq;

  if(j == 'y') {
    std::cout << "Bye!\n";
    return 0;
  } else {
    switch (j) {
      case 1:
        switch (i) {
          case 0:  string_view_variant_print_special_or(simple_tokenizer0,std::cout); break;
          case 1:  string_view_variant_print_special_or(simple_tokenizer1,std::cout); break;
          case 2:  string_view_variant_print_special_or(simple_tokenizer2,std::cout); break;
          case 3:  string_view_variant_print_special_or(simple_tokenizer3,std::cout); break;
          default: string_view_variant_print_special_or(simple_tokenizer3,std::cout); break;
        }
        break;
      case 2:
        switch (i) {
          case 0:  string_view_variant_print_char_or_quote(simple_tokenizer0,std::cout, dq); break;
          case 1:  string_view_variant_print_char_or_quote(simple_tokenizer1,std::cout, dq); break;
          case 2:  string_view_variant_print_char_or_quote(simple_tokenizer2,std::cout, dq); break;
          case 3:  string_view_variant_print_char_or_quote(simple_tokenizer3,std::cout, dq); break;
          default: string_view_variant_print_char_or_quote(simple_tokenizer3,std::cout, dq); break;
        }
        break;
        case 3:
        switch (i) {
          case 0:  string_view_variant_print_char_word_or_quote(simple_tokenizer0,std::cout, dq); break;
          case 1:  string_view_variant_print_char_word_or_quote(simple_tokenizer1,std::cout, dq); break;
          case 2:  string_view_variant_print_char_word_or_quote(simple_tokenizer2,std::cout, dq); break;
          case 3:  string_view_variant_print_char_word_or_quote(simple_tokenizer3,std::cout, dq); break;
          default: string_view_variant_print_char_word_or_quote(simple_tokenizer3,std::cout, dq); break;
        }
        break;
      default:
        std::cout << "No valid choice. Bye!\n\n";
        break;
    }
  }
  return 0;

} // main(...)

void string_view_variant_print_special_or(string_view_variant_tokenizer_type& t,
                                      std::ostream& o) {
  while (t) {
    typename string_view_variant_tokenizer_type::char_string_type v = t.get_special_or();
    if(v.index() == 0)
       o << '[' << std::get<0>(v) << ']';
    else
       o << '^' << std::get<1>(v) << '$';
  }
};

void string_view_variant_print_char_or_quote(string_view_variant_tokenizer_type& t,
                                             std::ostream& o,
                                             bool dq) {
  while (t) {
    //typename string_view_variant_tokenizer_type::char_string_type v = t.get_char_or_quote(dq);
    typename string_view_variant_tokenizer_type::char_string_type v = t.get_char_or_quote(true);
    if(v.index() == 0)
       o << '[' << std::get<0>(v) << ']';
    else
       o << '^' << std::get<1>(v) << '$';
  }
};

void string_view_variant_print_char_word_or_quote(string_view_variant_tokenizer_type& t,
                                             std::ostream& o,
                                             bool dq) {
  while (t) {
    typename string_view_variant_tokenizer_type::char_string_quote_type
    v = t.get_char_word_or_quote(true);
    switch (v.index()) {
      case 0:  o << '[' << std::get<0>(v) << ']'; // output "[CHAR]"
               break;
      case 1:  o << '<' << std::get<1>(v).value() << '>'; // output "<WORD>"
               break;
      case 2:  o << '^' << std::get<2>(v).value() << '$'; // output "^QUOTE$"
               break;
      default: break;
    }
  }
};
