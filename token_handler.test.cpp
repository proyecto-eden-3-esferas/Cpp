#ifndef TOKEN_HANDLER_H
#include "token_handler.h"
#endif

typedef double float_type;

typedef token_handler<float_type,std::vector> token_handler_type;
typedef typename token_handler_type::token token_t;
typedef typename token_handler_type::line< token_t> line_t;


#include <iostream>
using namespace std;

int main() {

  token_t h("hello", 4.0);
  token_t t("there!", 4.75);

  cout << '\"' << h.get_text() << "\" has width: " << h.get_width() << '\n';
  cout << '\"' << t.get_text() << "\" has width: " << t.get_width() << '\n';

  line_t l0{h,t};

  token_handler_type th0;

  return 0;
}
