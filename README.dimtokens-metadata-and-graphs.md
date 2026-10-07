# `dimtoken`'s, Metadata and Graphs

These are major themes with me:
- A class (`dimtoken`) for estimating the width of a token (a no-spaces run of characters, a mathematical formula...). This would make it quite straightforward to break a long string (paragraph) into typographical lines, which would be especially usefull for printing paragraph-long strings inside SVG shapes.
- Metadata classes
- Graphs, mainly the tried and tested Boost Graph Library

## TODOs:
[ ] Currently I very much favour metadata based on UDC (see ~/latest_books/books/unclassified/classification/UDC/)
[ ] `extern` declare and define
    a std::(multi)map<STRING,STRING> or std::unordered_(multi)map<STRING,STRING>
    from UDC subject codes to matiching descriptions
    through inclusion of "decimal_to_description.h"
[ ] ...

## `dimtoken`'s

A `dimtoken` is a class or object thereof that holds strings of non-space characters (typically within some text, typically a paragraph-length string), and some dimensional information, mainly its width given a font, and also its depth and height. A typical dimtoken will be a word, that is a run of characters between conscutive spaces, so that "Hello!" is a dimtoken.

In typography a dimtoken is a box. Typographical boxes are placed along horizontal baselines. Their depth means how far below the baseline the bottom of the box is. Its height means how high above the baseline its top is.

A dimtokenizer will:
1. break a long string into dimtoken's (a fairly easy task)
2. append dimensional information to each token

The product of dimtokenization is expected to be stored in a sequence container, such as a std::vector. This sequence can be easily converted into typographical lines that do not exceed a given width (maximum line width). And these break-downs can be printed inside rectangles in SVG or PostScript.

A `dimtoken` may be a mathematical formula in MathML.

A block-display mathematical formula belongs in a paragraph-like element holding the mathematical formula as its sole dimtoken.

## Metadata

We are dealing with paragraphs. We might:
- Either build one large sequence with all of our paragraphs. We would expect the client to read our sequence from start to finish.
- Or attach some information to each unit (paragraphs, sections and so on). Such information about text is called metadata. A section that we attach metadata to may be made up of a sequence of paragraphs. So we would end up with a collection or set of units. This can be regarded as an implicit ordering. From this implicit ordering we may go on to structure our information as a sequence of units, as a tree or hierarchy (like a technical book) or as a set of linked units, or graph.

### Universal Decimal Coding (UDC)

UDC codes a lot of metadata into a single string.

Two compilation units handle UDC:

- *UDC* (*UDC.h*, tested by *UDC.test.cpp*)
- *extract-UDC-facets* (*extract-UDC-facets.h* and *extract-UDC-facets.cpp*, tested by *extract-UDC-facets.test.cpp*)


## Graphs

To the best of my knowledge, the Boost Graph Library seems the best open-source option.


## Presentation and Content

Breaking text into lines is a matter of presentation.

Should we put off writing content until the perfect typographical system is available? Or should we start right away and trust we will manage to convert our paragraph + metadata structures to whatever we end up demanding?

We might write initialization lists like:
```
  {"paragraph00", metadata, from_ids, to_ids},
  {"paragraph01", metadata, from_ids, to_ids}
  ...
```
from_ids/to_ids might be in the form: {id0, id1, ...}

So the hard task is to settle for a metadata format.


### Variable Declaration and Definition in C/C++
In one file we declare:
```
extern int i;
```
In another we define:
```
int i = 3;
```
# A Survey of Current Projects

- class registered_key is being developed in file "temp.cpp" / "registered_key.test.cpp".
  It explores the possibilities of the STL associative containers: std::map and std::multimap,
  as well as their hash versions (std::unordered_(multi)map).
  An exception is thrown if an unregistered key is used.
- Compilation unit "information" develops classes information<> and its child class dataitem<>
- Compilation unit UDC... defines mapping variable 'basic_UDC<>::decimal_to_description'
- Compilation unit "extract-UDC-facets" defines global functions
  for extracting UDC facets
