#ifndef LEVELER_CONCEPT_H
#define LEVELER_CONCEPT_H

#include <concepts>
#include <iostream>

template<typename LEVEL, typename SINT = signed int>
concept Leveler = requires(LEVEL levelObj1,
                           LEVEL levelObj2,
                           std::ostream& o,
                           SINT n)
{
  //{ pt.print_transformed(o,str) } -> std::same_as<void>;
  { levelObj1.get() } -> std::same_as<SINT>;
  { levelObj1.get_level() } -> std::same_as<SINT>;
  { ++levelObj1 } -> std::same_as<LEVEL & >;
  { --levelObj1 } -> std::same_as<LEVEL & >;
  { levelObj1++ } -> std::same_as<LEVEL   >;
  { levelObj1-- } -> std::same_as<LEVEL   >;
  { levelObj1.print(o) } -> std::same_as<std::ostream & >;
  { levelObj2 = levelObj1} -> std::same_as<LEVEL & >;
  { LEVEL::max_level = n};
};

#endif
