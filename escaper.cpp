#ifndef ESCAPER_CPP
#define ESCAPER_CPP


template <typename CH>
std::basic_string<CH> escaper<CH>::escape(const string_t& in) const {
  string_t res;
  escape(in,res);
  return res;
};


template <typename CH>
map_escaper<CH> & map_escaper<CH>::add(CH c, const string_t& s) {
  ch_to_str.insert({c,s});
  return *this;
};

template <typename CH>
void map_escaper<CH>::escape(const string_t& in, string_t & out) const {
  out.clear();
  for(CH c : in) {
    if(ch_to_str.contains(c))
      out += ch_to_str.at(c);
    else
      out += c;
  }
};
template <typename CH>
std::basic_string<CH> map_escaper<CH>::escape(const string_t& in) const {
  string_t res;
  this->escape(in,res);
  return res;
};

template <typename CH>
std::basic_ostream<CH>& map_escaper<CH>::insert(ostream_t& o, const string_t& str) const {
  for(CH c : str) {
    if(ch_to_str.contains(c))
      o << ch_to_str.at(c);
    else
      o << c;
  }
  return o;
};

template <typename CH>
map_escaper<CH>::map_escaper(std::initializer_list<pair_t> il)
  : ch_to_str(il.begin(), il.end())
  {};


/*

template <typename CH>
map_escaper<CH>::
 */


#endif
