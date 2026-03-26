#ifndef CONNECTION_CPP
#define CONNECTION_CPP

#include <format>

template <typename CHAR>
template <typename... Args>
std::string Connection<CHAR>::dynamic_print(std::string_view rt_fmt_str, Args&&... args)
{
  return std::vformat(rt_fmt_str, std::make_format_args(args...));
};


template <typename CHAR>
void Connection<CHAR>::run(string_view_t cmd) const {
  system(cmd.data());
};

template <typename CHAR>
Connection<CHAR>::string_t Connection<CHAR>::get_result_string() const {
  return resultss.str();
};

template <typename CHAR>
void Connection<CHAR>::redirect_output_to_string() {
  std::cout.rdbuf(ss_buf);
  output_redirected = true;
};

template <typename CHAR>
Connection<CHAR>::~Connection() {
  if(output_redirected) {
    std::cout.rdbuf(cout_buf);
    output_redirected=false;
  }
};

#endif
