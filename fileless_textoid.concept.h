#ifndef FILELESS_TEXTOID_CPT
#define FILELESS_TEXTOID_CPT

#include <concepts>
#include <type_traits>

#include <iostream>
#include <fstream>

#include <string>
#include <string_view>

#include <variant>
#include "optional_ref.h"

/* Fileless_Textoid_Cpt<> is a */

template <typename FLT>
concept Fileless_Textoid_Cpt = requires (FLT flt, std::ifstream& ifs,
                                         std::fstream& fs,
                                         typename FLT::off_type off,
                                         typename FLT::size_t sz ) {
  {flt.length(fs)} -> std::same_as<typename FLT::size_t>;
   flt.clear();
  /* Required by Fileless_Textoid_handler<>: */
  {flt.set_offset(off)} -> std::same_as<FLT&>;
  {flt.get_offset()}    -> std::same_as<typename FLT::off_type>;

  {flt.get_slotsize()}  -> std::same_as<typename FLT::size_t>;
   flt.set_slotsize(sz);

   flt.set_slot_capacity();
  {flt.load( fs)}       -> std::same_as<bool>;
  {flt.store(fs)}       -> std::same_as<bool>;
};

#endif
