/* File "StringMatcher.test.cpp"
 * Classes StringMatcher<CHAR> and MultiStringMatcher<CONT,CHAR>
   can be used for building word-recognizers.
 * They work by consuming a character at each invocation
   and trying to complete a stored string to be matched.
 * For instance StringMatcher sm{"quiet"}
   would end up matching "quiet" in "She is soft-spoken and quiet".
 * MultiStringMatcher<CONT,CHAR> is essentially a container of StringMatcher<CHAR>'s.
 * It can be initialized with several strings, as in
     MultiStringMatcher<> msm0{"quiet", "quite", "very"};
 */

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

template <typename CHAR=char>
class StringMatcher {
public:
  typedef std::basic_string<CHAR> string_t;
  typedef  std::size_t size_t;
  typedef unsigned int uint;
  typedef   signed int sint;
  //
  const string_t str;
  const uint length;
  uint index;
  //
  bool update(CHAR c);
  const string_t & get_string() const {return str;};
  uint get_index() const {return index;};
  void  reset();
  //
  StringMatcher(const string_t& s) : str(s), length(s.length()), index(0) {};
};

template <typename CHAR>
bool StringMatcher<CHAR>::update(CHAR c) {
  if(c == str[index]) {
    ++index;
#ifdef DEBUG
    std::cout << '+';
#endif
    if(index == length)
      return true;
    else
      return false;
  }
  else {
    index = 0;
#ifdef DEBUG
    std::cout << '0';
#endif
    return false;
  }
};
template <typename CHAR>
void StringMatcher<CHAR>::reset() {
  index = 0;
};

template <template <typename> typename CONT = std::vector,
          typename CHAR=char>
class MultiStringMatcher {
public:
  typedef std::basic_string<CHAR> string_t;
  typedef  std::size_t size_t;
  typedef unsigned int uint;
  typedef   signed int sint;
  typedef StringMatcher<CHAR> StringMatcher_t;
  //
  uint match_index;
  sint get_match_index() const {return match_index;};
  const string_t get_matched_string() const {return StringMatchers[match_index].get_string();};
  CONT<StringMatcher_t> StringMatchers;
  //
  void reset();
  /* update(CHAR) takes in a character,
     tests for matches in each of its StringMatcher objects,
     and returns:
       -1 if no string has been completed so far
       the index of the StringMatcher that has just matched the run of characters
   */
  sint update(CHAR c);
  //
  //MultiStringMatcher(std::initializer_list<StringMatcher_t> il) : StringMatchers(il) {};
  MultiStringMatcher(std::initializer_list<string_t> il) : StringMatchers(il.begin(),il.end()) {};
};
template <template <typename> typename CONT,
          typename CHAR>
void MultiStringMatcher<CONT,CHAR>::reset() {
  match_index = -1;
  for(auto & sm : StringMatchers)
    sm.reset();
};
template <template <typename> typename CONT,
          typename CHAR>
signed int MultiStringMatcher<CONT,CHAR>::update(CHAR c) {
  for(int i = 0; i < StringMatchers.size(); ++i) {
    if(StringMatchers[i].update(c)) {
      match_index = i;
      return i;
    }
  }
  return -1;
};


typedef StringMatcher<char> StringMatcher_t;

using namespace std;

string sentence0{"You are looking very tired."};
string sentence1{"He is rather average."};

StringMatcher_t sm0("very");

typedef MultiStringMatcher<std::vector, char> MultiStringMatcher_t;
MultiStringMatcher_t msm0({"very", "rather"});
//MultiStringMatcher_t msm0({StringMatcher_t("very"), StringMatcher_t("rather")});

int main()
{
  cout << "\nTest for presence of \"very\" in sentence0 (" << sentence0 << "):\n";
  for(auto c : sentence0) {
    if(sm0.update(c)) {
      cout << "FOUND!\n";
      break;
    }
    else
      cout << "?";
  }

  sm0.reset();

  cout << "\nTest for presence of \"very\" in sentence1 (" << sentence1 << "):\n";
  for(auto c : sentence1) {
    if(sm0.update(c)) {
      cout << "FOUND!\n";
      break;
    }
    else
      cout << "?";
  }

  cout << "\nTest for presence of \"very\" or \"rather\" in sentence1 (" << sentence1 << "):\n";
  signed int MultiStringMatcher_index{-1};
  for(auto c : sentence1) {
    MultiStringMatcher_index = msm0.update(c);
    if (MultiStringMatcher_index >= 0) {
      cout << "Found \"" << msm0.get_matched_string() << "\" at index: " << MultiStringMatcher_index << '\n';
      break;
    }
    else
      cout << "-";
  }




  return 0;
}
