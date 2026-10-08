#ifndef FILESTRING_CPP
#define FILESTRING_CPP
template <template <typename STR> typename CONT>
      filestring_container<CONT>::filestring&
filestring_container<CONT>::operator[](std::size_t idx)
{
  filestrings[idx].changed = true;
  return filestrings[idx];
};
template <template <typename STR> typename CONT>
const filestring_container<CONT>::filestring&
filestring_container<CONT>::operator[](std::size_t idx) const
{
  return filestrings[idx];
};

template <template <typename STR> typename CONT>
void filestring_container<CONT>::filestring::load(fstream_t& f) {
  // load string
  loaded = true;
};
template <template <typename STR> typename CONT>
void filestring_container<CONT>::filestring::store(fstream_t& f) {
  // store string into a file slot
  changed = false;
};
template <template <typename STR> typename CONT>
void filestring_container<CONT>::filestring::check(fstream_t& f) {
  if( loaded == false ) {
    load(f);
    changed = false;
    loaded = true;
  }
};

template <template <typename STR> typename CONT>
void filestring_container<CONT>::emplace_back(std::string_view sv) {
  filestrings.emplace_back(sv, offset_step*next_index());
};

template <template <typename STR> typename CONT>
filestring_container<CONT>::~filestring_container()  {
  for(auto & fs : filestrings) {
    if( fs.has_changed())
      fs.store(iofile);
  }
};

#endif
