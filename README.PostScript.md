# PostScript

A set of classes for writing PostScript, which is a programming language.

Some years ago I wrote a PostScript library in PostScript. I now see it as excessively involved. (Currently I am centred on the SVG format, instead.) It made heavy use of PostScript data structures, control structures and general syntax and semantics (logic), whereas currently I favour moving the logic to a more familiar, mainstream programming language such as C++ (or FORTRAN, if you are so bent) and only keeping the most basic, minimal PostScript operators.

For example, instead of defining a procedure for moving a point horizontally in PostScript syntax and semantics, I would just do the transformation in a C++ class and then write the transformed point into a PostScript file.

I could then use my C++ point class to write to any other graphic file format, such as SVG.

So the main design guidelines are:

1. Write *direct* PostScript, use just the minimum graphic subset of the language and perform all computations in C++

2. Handle opening and closing of PostScript files automatically: eschew memorizing detailed conventions

3. Still, some mechanism must be provided for declaring some PostScript procedures that perform computations that C++ just cannot do, often enough based on the position of the so-called current point and the width of a string given a font.


## Parent `PostScript_base` and its child `PostScriptFile`

Presumably, the only responsability of class `PostScriptFile` would be to open and close PostScript files, Also setting the Bounding Box in the PostScript prolog.

## Embedded PostScript (EPS)

For Embedded PostScript, to be realized through a derived class, the bounding box would be kept up-to-date as code is written into the EPS and then the destructor would go back to the prolog and write the updated bounding box.

Such a class might perform some other checks...
