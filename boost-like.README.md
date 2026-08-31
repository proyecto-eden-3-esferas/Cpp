This README refers to Boost-like (Geometry) libraries, whereas Boosted (Geometry) libraries are different, are based on Boost code, and is cumbersome and slow to compile.

# Boosted Geometry versus Boost-like Geometry
Currently each compilation unit takes about twelve seconds to compile into object. With no separate compilation, each build takes a little longer than twelve seconds, no matter how basic the code may be. Therefore I have decided to write my own library yet follow the Boost.Geometry interfaces or concepts as closely as I can manage.

# TODOs
[ ] write *boost-like.multiline.h* to hold a sequence of points as defined in *boost-like.point.h*
[ ] write *boost-like.arrowhead.h* to define an arrowhead and its styles: stick, solid, hollow... (an enum type)


