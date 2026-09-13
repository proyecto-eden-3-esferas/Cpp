This README refers to Boost-like (Geometry) libraries, whereas Boosted (Geometry) libraries are different, are based on Boost code, and is cumbersome and slow to compile.

# Boosted Geometry versus Boost-like Geometry
Currently each Boost.Geometry-compliant compilation unit takes about twelve seconds to compile into object. With no separate compilation, each build takes a little longer than twelve seconds, no matter how basic the code may be. Therefore I have decided to write my own library yet follow the Boost.Geometry interfaces or concepts as closely as I can manage.

# TODOs
[ ] Review ANGLE as a template parameter.
    It seems that your main target languages, SVG and PostScript, use sexagesimal degrees.
[ ] SVG shapes might then be made clickable to send the user to another page or place
    This is to be done like this:
    ```
    <a href "DESTINATION">
      <SHAPE>
      </SHAPE>
    </a>
    ```
[ ] write *boost-like.arrowhead.h* to define an arrowhead
    and its styles: stick, solid, hollow... (an enum type)

## PostScript
[ ] write PostScript printing code in *boost-like.print_as_PS.h* and *boost-like.print_as_PS.cpp*,
    very much analogously to *boost-like.print_as_SVG.h* and *boost-like.print_as_SVG.cpp*
[ ] PostScript shapes might then be made clickable to send the user to another page or place


