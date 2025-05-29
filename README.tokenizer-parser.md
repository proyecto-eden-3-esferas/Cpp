# Introduction

I have written some C++ code to tokenize and parse text. I have focused on computer language text, especially JSON and XML.

My approach has been incremental, or "divide and conquer". I would first write a tokenizer that extracts token out of a string or even an input stream while advancing some cursor. (A cursor could be something as simple as a string or a file position.)

Then I would write a token processor which maintains some state such as:
- inside or outside a CDATA section (for HTML and other XML languages)
- inside an opening or a self-standing HTML tag: may be we are in the middle of ´<section id="suggestions">`, just after identifier *id*, so we would expect some or no white-space followed by an equals sign (=) and so on.
- where in the tree we are at. We may be parsing a paragraph in a section inside main inside the body of an HTML document. Or we may be inside an array which is the value of an object which is an element of an array (JSON).

To sum up, the stages in a tokenize-parse chain are:
1. produce tagged tokens on demand
2. consume/process them while keeping some state
3. concurrently, fill in some structure representing all the information; this structure should be straightforward to serialize out

## The Last Stage

The very last stage in parsing might be to initialize a data structure in memory. Then it would be very easy to produce the original computer-language file.

Some such structures are developed in:
- *XML/XML.h*
- *JSON.h* (tested in *JSON.cpp*)


## Helper Classes/Files

Often enough these classes are developed in same-named files (*CLASS_NAME.h* and *CLASS_NAME.cpp*), then tested in, say, *CLASS_NAME.test.cpp*.

- a `sense<T,std::size_t>` class for telling classes by intention or "sense". Thus, you might use `sense<string,0>` for words and `sense<string,1>` for numbers, and so on.

- global function `load_string_with_file(STRING&, FILENAME, offset=0)` loads a string with the contents of a file starting at offset (`FILE.tellg(offset)`). It is declared and defined in *load_string_with_file.h*. (It is tested in *load_string_with_file.test.cpp*.)

## class basic_tokenizer<CHAR,STRING>

Class `basic_tokenizer<CHAR,STRING>` consist mainly of typedef, using declarations, and static member functions.

An outstanding member of its is a (non-const) reference to an input stream.

Another is an inner iterator class: `class basic_tokenizer<CHAR,STRING>::iterator`

The files are named, as customary:
- *basic_tokenizer.h*
- *basic_tokenizer.cpp*
- *basic_tokenizer.test.cpp*

This "translation unit" of sorts also summarily sketches class `text_tokenizer<CHAR,STRING>`

I don't like about "project" basic_tokenizer<CHAR,STRING> that it relies on an iterator inner class for tokenizing.

Some nice member functions are:
- static bool   ends_with_punct(const string_t& s); // C++ 20
- static bool starts_with_punct(const string_t& s); // C++ 20
- static bool get_through_lt(istream_t& i, string_t& s); // eat up to and including the next '<' character


## string_view_variant_tokenizer{h.|.cpp|.test.cpp} (early May, 2025)

A very simple tokenizer would produce either a special character (typically punctuation that is relevant to the computer language that the string is assumed to be written in) or a run of characters up to the next special characters. As a variant (std::variant<CHAR,STRING>). This is the approach implemented by member function `string_view_variant_tokenizer<CHAR>::get_special_or()`

Another kind of member function tokenizes into quoted text and non-quoted tokens, possibly after skipping all white space (outside quoted text). This approach is particularly suitable for JSON files and is implemented by member function `string_view_variant_tokenizer<CHAR>::get_char_or_quote(bool drop_quotes = true)`

To that effect, a large class is declared, defined and tested in files:
- *string_view_variant_tokenizer.h*
- *string_view_variant_tokenizer.cpp*
- *string_view_variant_tokenizer.test.cpp*

I have stopped developing this code in favor of a `tokenizer<CHAR>`


## tokenizer<CHAR> (late May, 2025)

Files *tokenizer{.h|.cpp}* develop a same-named class `tokenizer<CHAR>`, which:
- recognizes patterns by means of regular expressions
- tells whether a strings starts with a given pattern
- tells how many initial characters in a string match a given pattern

Its latest version as of May 29th, 2025, holds a map of names (strings) to regular expressions.

For instance, name "decimal" would match a regular expression pattern for decimal numbers. And so on. The client is free to add and detract. Besides, each object is initialized with a default, reasonable set of patterns.

This class holds no text string by value or reference. Not its concern.


## Related Projects or Compilation Units

Tokenizing is strongly related to deserialization (reading structured data out of a file into computer memory or a string), which properly belongs in subdirectory *serialization/*.
