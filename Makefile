CLANG = clang++ -std=c++2b
Gplusplus   = c++    -std=c++23
RAPIDXML = rapidxml*.zip
%: %.cpp
	c++    -std=c++23 $<  -o $@

Level.test: Level.test.cpp Level.h
	g++ -std=c++23 $<  -o $@

# XML.test: XML.test.cpp XML.h
XML.test: XML.test.cpp  XML.h
	g++ -std=c++23 $<  -o $@

XMLelement.test: XMLelement.test.cpp XMLelement.h XML.globals.h
	g++ -std=c++23 $<  -o $@


%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -std=c++23 -c -std=c++17 $<


clean:
	$(RM)  a.out *.test *.o


save_to_Dropbox:
	cp --update *.h *.cpp *.md *.txt $(RAPIDXML) ~/Dropbox/cpp_code/XML/
