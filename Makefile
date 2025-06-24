CLANG = clang++ -std=c++2b
Gplusplus   = c++    -std=c++23
%: %.cpp
	c++    -std=c++23 $<  -o $@
Gplusplus   = c++    -std=c++23


temp: temp.cpp
	c++ -std=c++23 $<  -o $@

information: information.cpp information.h
	c++ -std=c++23 $<  -o $@
ai_set.test : ai_set.cpp
	c++ -std=c++23 $<  -o $@

paragraph.test: paragraph.h paragraph.main.cpp
	g++ -std=c++2a            paragraph.main.cpp -o $@
escaper.test: escaper.cpp escaper.h
	c++ -std=c++23 $<  -o $@
indent: indent.test.cpp indent.h
	c++ -std=c++23 $<  -o $@


name.test: name.test.cpp name.cpp name.h
	g++ -std=c++23         $<  -o $@
json.test: json.cpp json.h
	g++ -std=c++23         $<  -o $@

# Former tokenizer compilation units
basic_tokenizer.test: basic_tokenizer.test.cpp basic_tokenizer.h basic_tokenizer.cpp
	g++ -std=c++23 $<  -o $@
istream_variant_queue_tokenizer.debug: istream_variant_queue_tokenizer.test.cpp istream_variant_queue_tokenizer.h variant_queue_tokenizer.h
	g++ -std=c++23 -DDEBUG $<  -o $@
istream_variant_queue_tokenizer.test:  istream_variant_queue_tokenizer.test.cpp istream_variant_queue_tokenizer.h variant_queue_tokenizer.h
	g++ -std=c++23         $<  -o $@
string_view_variant_tokenizer.test: string_view_variant_tokenizer.test.cpp string_view_variant_tokenizer.h string_view_variant_tokenizer.cpp sense.h
	g++ -std=c++23         $<  -o $@

i_regex_map.test: i_regex_map.test.cpp i_regex_map.h i_regex_map.cpp
	g++ -std=c++23 $<  -o $@
i_regex_map.sep-comp.test: i_regex_map.test.o i_regex_map.o
	g++ -std=c++23 i_regex_map.test.o i_regex_map.o  -o $@
regex_map.test: regex_map.test.cpp regex_map.h regex_map.cpp
	g++ -std=c++23 $<  -o $@
regex_map.sep-comp.test: regex_map.o regex_map.test.o
	g++ -DSEPARATE_COMPILATION -std=c++23 regex_map.o regex_map.test.o -o regex_map.sep-comp.test
tokenizer.test: tokenizer.test.cpp tokenizer.h tokenizer.cpp
	g++ -std=c++23 $<  -o $@
tokenizer.sep-comp.test: tokenizer.o tokenizer.test.o
	g++ -DSEPARATE_COMPILATION -std=c++23 tokenizer.o tokenizer.test.o -o tokenizer.sep-comp.test

# Serialization and Deserialization:
serialize_binary: serialize_binary.test.cpp serialize_binary.h
	c++ -std=c++23 $<  -o $@
serialize_string: serialize_string.test.cpp serialize_string.h
	c++ -std=c++23 $<  -o $@
serialize: serialize.test.cpp serialize.h serialize_string.h
	c++ -std=c++23 $<  -o $@
serialize_container: serialize_container.test.cpp serialize_container.h serialize_string.h serialize.h
	touch io.text
	c++ -std=c++23 $<  -o $@

# lazy_strings, textoids and floids: their objects can hold either a large string
# or some reference/directions for loading the from a file on demand
lazy_strings.test: lazy_strings.cpp lazy_strings.h
	echo "19 dzogchen and tantra" > zettelkasten.ini
	c++ -std=c++23 $<  -o $@

fileless_textoid: fileless_textoid.test.cpp textoid.h
	touch io.text # we need for "io.text" to exist
	g++ -std=c++23 $<  -o $@
fileless_textoid.test: fileless_textoid.test.cpp fileless_textoid.h fileless_textoid.cpp
	touch io.text # we need for "io.text" to exist
	g++ -std=c++23 $<  -o $@
fileless_textoid.concept.test: fileless_textoid.concept.test.cpp fileless_textoid.concept.h fileless_textoid.h fileless_textoid.cpp
	g++ -std=c++23 -fconcepts-diagnostics-depth=3 $<  -o $@

textoid.test:                   textoid.test.cpp fileless_textoid.h fileless_textoid.cpp textoid.h textoid.cpp
	touch io.text # we need for "io.text" to exist
	g++ -std=c++23 $<  -o $@

fileless_textoid_handler: fileless_textoid_handler.test.cpp fileless_textoid_handler.h textoid.h
	touch textoid.str
	g++ -std=c++23 $<  -o $@
floid: floid.test.cpp floid.h
	touch io.text
	g++ -std=c++23 $<  -o $@
floid-visitor: floid-visitor.test.cpp floid.h
	g++ -std=c++23 $<  -o $@


load_string_with_file: load_string_with_file.test.cpp load_string_with_file.h
	g++ -std=c++23         $<  -o $@


%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp %.h
	g++ -DSEPARATE_COMPILATION -std=c++23 --compile $<
#	g++  -std=c++23 -c -std=c++17 $<
%.test.o: %.test.cpp %.h
	g++ -DSEPARATE_COMPILATION -std=c++23 --compile $<


clean_former:
	$(RM)  bitenum basic_tokenizer xml_tokenizer case-insensitive-string-cmp test_concepts test_XML
clean:
	$(RM)  temp information zettelkasten temp.txt
	$(RM)  serialize serialize_string serialize_binary serialize_container
	$(RM)  sized_strings.txt sep_strings.txt strings.txt
	$(RM)  out.text out.txt out.bin io.text
	$(RM)  textoid fileless_textoid.test fileless_textoid_handler textoid.str textoid.off
	$(RM)  a.out *.test escaper indent
clean_all:
	make clean
	rm *.o
