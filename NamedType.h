#ifndef NAMED_TYPE_H
#define NAMED_TYPE_H

/* This file defines class NamedType<T,TAG>
   and its partial specializations for TAG,
   thereby obtaining template classes for measurements
   such as Kelvin<FLOAT>, Radian<FLOAT> and so on.
 * This template class was proposed by Jonathan Boccara
 * It takes input parameters by value and does not defines a move copy constructor
   (unlike Boccara's class)
 *

 * TODO:
 * [ ] Compare with user-defined literals.
 *     Which is better?
 */

#include <iostream>
#include <numbers>

template <typename T, typename TAG>
class NamedType
{
public:
    explicit NamedType(T val) : value(          val)  {};
    T&       get()       { return value; }
    T const& get() const { return value; }
private:
    T value;
};



/* Then to be used like so:
    struct WidthTag {};
    using Width = NamedType<double, WidthTag>;
 * Actually, WidthTag can be declared within the using statement, making it possible to instantiate strong types in just one line of code:
    using Width = NamedType<double, struct WidthTag>;
*/

/* Partial specializations for converting between:
 * per-cent and per-one
 * sexagesimal degrees and radians
 * Kelvin, Celsius and Fahrenheit
 */

// Conversion between per-cent and per-one values
struct PerOneTag{};
struct PerCentTag{};
template <typename FLOAT>
class NamedType<FLOAT,PerCentTag> {
public:
  /*explicit */NamedType(NamedType<FLOAT,PerOneTag> pop) : value(pop.get() * 100.0) {};
  explicit NamedType(          FLOAT            val) : value(val)               {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};
template <typename FLOAT>
class NamedType<FLOAT,PerOneTag> {
public:
  /*explicit */NamedType(NamedType<FLOAT,PerCentTag> pcp) : value(pcp.get() / 100.0) {};
  explicit NamedType(          FLOAT             val) : value(val)               {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};

// Conversion between sexagesimal degrees and radians:
struct RadiansTag {};
struct SexagesimalsTag {};
template <typename FLOAT>
class NamedType<FLOAT,RadiansTag> {
public:
  NamedType(NamedType<FLOAT,SexagesimalsTag> deg) : value( (deg.get() / 180) * std::numbers::pi_v<FLOAT>) {};
  explicit  NamedType(FLOAT                  val) : value(val)  {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};
template <typename FLOAT>
class NamedType<FLOAT,SexagesimalsTag> {
public:
  NamedType(NamedType<FLOAT,RadiansTag> rad) : value( ( rad.get() / std::numbers::pi_v<FLOAT>) * 180 ) {};
  explicit NamedType(FLOAT val) : value(val)  {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};

// Conversion between Kelvin, Celsius and Fahrenheit
struct KelvinTag     {};
struct CelsiusTag    {};
struct FahrenheitTag {};
template <typename FLOAT>
class NamedType<FLOAT,KelvinTag> {
public:
  NamedType(const NamedType<FLOAT,CelsiusTag>   & cel) :
    value(  cel.get()           + 273.15) {};
  NamedType(const NamedType<FLOAT,FahrenheitTag>& fah) :
    value( (fah.get() - 32)*5/9 + 273.15) {};
  explicit NamedType(FLOAT val) : value(val)  {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};
template <typename FLOAT>
class NamedType<FLOAT,FahrenheitTag> {
public:
  NamedType(NamedType<FLOAT,KelvinTag> kel)  : value( (kel.get() * 9/5) + 32 + 273.15) {};
  NamedType(NamedType<FLOAT,CelsiusTag> cel) : value( (cel.get() * 9/5) + 32 ) {};
  explicit NamedType(FLOAT val)              : value(val)               {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};
template <typename FLOAT>
class NamedType<FLOAT,CelsiusTag> {
public:
  NamedType(NamedType<FLOAT,KelvinTag> kel) :
    value(kel.get() - 273.15) {};
  NamedType(NamedType<FLOAT,FahrenheitTag> fah) : value( (fah.get() - 32)*5/9 ) {};
  explicit NamedType( FLOAT val)                      : value(val)               {};
  FLOAT&       get()       { return value; }
  FLOAT const& get() const { return value; }
private:
  FLOAT value;
};


// Redefinition of two-template-parameter types for ease of use:

template <typename FLOAT = double>
using Length = NamedType<FLOAT, struct LengthTag>;
template <typename FLOAT = double>
using Radius = NamedType<FLOAT, struct RadiusTag>;
template <typename FLOAT = double>
using Width  = NamedType<FLOAT, struct WidthTag>;
template <typename FLOAT = double>
using Height = NamedType<FLOAT, struct HeightTag>;

template <typename FLOAT = double>
using Area = NamedType<FLOAT, struct AreaTag>;
template <typename FLOAT = double>
using Volume = NamedType<FLOAT, struct VolumeTag>;

template <typename FLOAT = double>
using PerOne = NamedType<FLOAT, struct PerOneTag>;
template <typename FLOAT = double>
using PerCent = NamedType<FLOAT, struct PerCentTag>;


/*
 */


template <typename FLOAT = double>
using Radian = NamedType<FLOAT, struct RadiansTag>;
template <typename FLOAT = double>
using Sexagesimal = NamedType<FLOAT, struct SexagesimalsTag>;
template <typename FLOAT = double>
using Degree      = NamedType<FLOAT, struct SexagesimalsTag>;


/*
 */

template <typename FLOAT = double>
using Kelvin = NamedType<FLOAT, struct KelvinTag>;
template <typename FLOAT = double>
using Fahrenheit = NamedType<FLOAT, struct FahrenheitTag>;
template <typename FLOAT = double>
using Celsius = NamedType<FLOAT, struct CelsiusTag>;

#endif
