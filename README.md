# Directory *cpp_code/*

Subdirectory Electric_files/cpp_code/ contains code either original or just copied and lightly tweeked.

File *Makefile.cpp_code* should enable clients to test my programmes and learn the file dependencies. It very much provides an overview.


## On Grouping Files into a Project

## Some Considerations regarding Textoids

Textoids are strings that are loaded from/to a file on demand. This scheme enables handling large amounts of text. A textoid stores:
- a file position
- possibly a file handler
- possibly some boolean variables: has it been modified (that is, has a getter returned a non-const reference?), has it been loaded?

- *fileless_textoid.h* includes yet does not use *optional_ref.h*
- *fileless_textoid.h* is tested by *fileless_textoid.test.cpp*
- *fileless_textoid.test.cpp* also defines:
```
  class fileless_textoid_handler<CH,
                                 SLOTSIZE=1000,
                                 ELEM = fileless_textoid<CH,SLOTSIZE>,
                                 CONT=std::vector<ELEM> >
```
A fileless_textoid_handler object handles several textoid strings. For instance, if a string outgrows its alloted size, it should be relocated or the next string should be relocated (marked as dirty, its file offset changed to point to some empty run in the file) so as to make room for the overgrown string.

- *fileless_textoid.test.cpp* defines a mostly dummy fileless_textoid<> class
to speed up compilation


## On Other Moved Files

There are two copies of *boost_selector_classes.h*: one here (cpp_code/) and another in ./boost/ (cpp_code/boost/). They might eventually diverge, that is, hold different, possibly incompatible, contents. Actually, I no longer use boost selector classes thanks to a recent C++ feature: template template parameters.

## On *temp.cpp*
This file is used for running tests and testing prototypes.
Once the code is verified, temp.cpp is copied to another file with a meaningful name.

## Several Strands
- example code: this should all be moved to *examples/*.
  These pieces of code are useful to introduce new stuff, clarify semantics, and exemplify syntax.
  These files must be self-standing and not be #include-d in other files,
  nor should they #include "other_files" themselves.
- useful code: this is code that does something and is not referenced by other compilations units (subdirectory useful/)
- Mappings between strings and integers and intelligent enumerations.
- Code to generate different versions of a chunk of text (a sentence, a paragraph etc.)
  This started as "string_facets.cpp" and continues in "text_version.cpp"


File id_base.h exemplifies static inline member variables (C++17), as in
  static inline int count = 0;


## PROJECTS

IMPORTANT: Directory NewGraphic01 holds my latest version of a C++ Graphic Library.


### A Programmed Book

First, I would like to write a "programmed book", that is a book contained within a program. Modification of the program would yield highly customizable books.

Let's talk XML. An element may have an identity and attributes, and an element is a sequence of either text or other elements... (see subdirectory)



### A Distributed Graph Chat Library

Next, I would like to carry out a project ("Distributed Graph Chat Library") joining the following:
(1) A graph library for holding text-vertices and word-weighted edges (see "A Programmed Book")
(2) A graph serializer
(3) A chat client and server that can communicate part of a graph or whole graphs through serialization (see 2)
(4) Joint graph building
(5) Diagram generation and transmittable (SVG + XHTML)


### Serialization

Project lives in serialization/
The main challenge is serializing strings.
For further details, read "serialization/README.txt"

### Tokenize, Parse-Word ...

See 'tokenizer.h' and 'tokenizer.test.cpp'

Can words be parsed through regular expressions?

Markers such as:
- number
- gender
- case
- likely role (vaguely identified with case)
- meaning of stem
- classifier
- entity type (concrete, event or development, fact-rule-law)

[ ] Generate pronounciations from spelled text: see https://proyecto-eden-3-esferas.github.io/phoneme-map.html

### Tokenizing and Parsing

See *README.tokenizer-parser.md*
