#ifndef ZERO_FILESTRING_HANDLER_CPP
#define ZERO_FILESTRING_HANDLER_CPP

template <template <typename> typename CONT>
void zero_filestring_handler<CONT>::load() {
  string_t temp;
  filestream.seekg(0);
  while(true) {
    std::getline(filestream, temp, sep);
    if(filestream.eof())
      break;
    std::cout << "Loading \"" << temp << "\", of length=" << temp.length() << '\n';
    emplace_back(temp);
  }
  std::cout << '\n';
};

template <template <typename> typename CONT>
void zero_filestring_handler<CONT>::store() {
  filestream.seekp(0);
  for(auto ptr = container_t::begin(); ptr != container_t::end(); ++ptr) {
    std::cout << "Storing away \"" << *ptr << "\", of length=" << ptr->length() << '\n';
    filestream << *ptr << sep;
  }
  /*
  for(int i = 0; i < size(); ++i) {
    std::cout << "Storing away \"" << operator[](i) << "\", of length=" << operator[](i).length() << '\n';
    filestream << operator[](i) << sep;
  }
   */
  std::cout << '\n';
};

//

template <template <typename> typename CONT>
std::ostream& operator<<(std::ostream& o, const zero_filestring_handler<CONT>& zfh) {
  for(const std::string & str : zfh)
    o << "  " << str << '\n';
  return o;
}

// Implementation of constructors and destructor

template <template <typename> typename CONT>
zero_filestring_handler<CONT>::zero_filestring_handler(fstream_t && fs, bool read, char sp)
: filestream(std::move(fs)), sep(sp) {
  if(read)
    load();
};

template <template <typename> typename CONT>
zero_filestring_handler<CONT>::zero_filestring_handler(const char *fname, bool read, char sp) : sep(sp)
//: filestream(fname, std::fstream::in | std::fstream::out | std::fstream::app)
{
  if(read) {
    filestream.open(fname);
    load();
  }
  else
    filestream.open(fname, std::fstream::in | std::fstream::out | std::fstream::trunc);
};

template <template <typename> typename CONT>
zero_filestring_handler<CONT>::~zero_filestring_handler() {
  store();
  filestream.close();
};

#endif
