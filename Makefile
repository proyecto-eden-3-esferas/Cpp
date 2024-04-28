CLANG = clang++ -std=c++2b
Gplusplus   = c++    -std=c++23
%: %.cpp
	c++    -std=c++23 $<  -o $@


indent: indent.test.cpp indent.h
	c++ -std=c++23 $<  -o $@
escaper: escaper.test.cpp escaper.h
	c++ -std=c++23 $<  -o $@

serialize_binary: serialize_binary.test.cpp serialize_binary.h
	c++ -std=c++23 $<  -o $@
serialize_string: serialize_string.test.cpp serialize_string.h
	c++ -std=c++23 $<  -o $@
serialize: serialize.test.cpp serialize.h serialize_string.h
	c++ -std=c++23 $<  -o $@

fileless_textoid: fileless_textoid.test.cpp textoid.h
	g++ -std=c++23 $<  -o $@
textoid: textoid.test.cpp textoid.h
	touch io.text
	g++ -std=c++23 $<  -o $@
fileless_textoid_handler: fileless_textoid_handler.test.cpp fileless_textoid_handler.h textoid.h
	touch textoid.str
	g++ -std=c++23 $<  -o $@

%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -c -std=c++23 $<

clean_former:
	$(RM)  bitenum basic_tokenizer xml_tokenizer case-insensitive-string-cmp ai_set test_concepts test_XML
clean:
	$(RM)  serialize serialize_string serialize_binary
	$(RM)  sized_strings.txt sep_strings.txt strings.txt
	$(RM)  out.text out.txt out.bin
	$(RM)  textoid fileless_textoid fileless_textoid_handler textoid.str textoid.off
	$(RM)  a.out *.test escaper indent
