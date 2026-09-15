#include <string>
#include <string_view>
#include <vector>

template <typename F = double, template <typename> typename CONT = std::vector>
class paragraph_in_lines  {
public:
  typedef std::string      string_type;
  typedef std::string_view string_view_type;
  typedef std::string_view line_type;


  typedef CONT<line_type> lines_type;

  F max_width;
  lines_type lines;

  typename lines_type::const_iterator  begin() const {return lines.cbegin();};
  typename lines_type::const_iterator    end() const {return lines.cend();};
  typename lines_type::const_iterator cbegin() const {return lines.cbegin();};
  typename lines_type::const_iterator   cend() const {return lines.cend();};

  void push_back(line_type l) {lines.push_back(l);};
  void initialize_lines() {};

  virtual F   length(             char      c) {return 1.0;};
  virtual F   length( string_view_type   word) = 0; // overloads should take multibyte into account
  virtual void split(const string_type & para) = 0; // load 'lines' with lines in 'para'


  paragraph_in_lines() {};
  paragraph_in_lines(const string_type& para, F w) : max_width(w) {initialize_lines();};

};
