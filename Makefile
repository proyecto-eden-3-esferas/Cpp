CLANG = clang++ -std=c++2b
Gplusplus   = c++    -std=c++23
RAPIDXML = rapidxml*.zip
CPP_CODE_DIR = ../
LEVEL = Level.h Leveler.h

%: %.cpp
	c++    -std=c++23 $<  -o $@

Level.test:  Level.test.cpp           $(LEVEL)
	g++ -std=c++23 $<  -o $@

Indent.test: Indent.test.cpp Indent.h $(LEVEL)
	g++ -std=c++23 $<  -o $@


CascadeMap.test: CascadeMap.test.cpp CascadeMap.h
	g++ -std=c++23 $<  -o $@


XMLnode.former.test: XMLnode.former.test.cpp XMLnode.former.h $(LEVEL)
	g++ -std=c++23 $<  -o $@
Namespaces.former.test: Namespaces.former.test.cpp Namespaces.former.h XMLnode.former.h
	g++ -std=c++23 $<  -o $@
Entities.former.test: Entities.former.test.cpp Entities.former.h
	g++ -std=c++23 $<  -o $@
Entities.wordy.test: Entities.wordy.test.cpp Entities.wordy.h
	g++ -std=c++23 $<  -o $@
XML.former.test: XML.former.test.cpp  XML.former.h XMLprintable.h
	g++ -std=c++23 $<  -o $@

XML.old.test: XML.old.test.cpp  XML.old.h XMLprintable.h
	g++ -std=c++23 $<  -o $@

# Files without a "former" infix take a CHAR template parameter:
XMLnode.test: XMLnode.test.cpp XMLnode.h $(LEVEL)
	g++ -std=c++23 $<  -o $@
Attributes.test: Attributes.test.cpp Attributes.h XMLnode.h $(LEVEL)
	g++ -std=c++23 $<  -o $@
Namespaces.no-qname.test: Namespaces.no-qname.test.cpp Namespaces.no-qname.h XMLnode.h qname.h
	g++ -std=c++23 $<  -o $@
qname.h: $(CPP_CODE_DIR)qname.h
	cp --update $(CPP_CODE_DIR)qname.h ./
Namespaces.test: Namespaces.test.cpp Namespaces.h XMLnode.h qname.h $(LEVEL)
	g++ -std=c++23 $<  -o $@
Entities.test: Entities.test.cpp Entities.h
	g++ -std=c++23 $<  -o $@

XMLTEXT_HEADERS    = XMLText.h $(LEVEL) XMLnode.h CascadeMap.h Entities.h
XMLELEMENT_HEADERS = $(XMLTEXT_HEADERS) XMLelement.h Namespaces.h
XMLText.test:    XMLText.test.cpp    $(XMLTEXT_HEADERS)
	g++ -std=c++23 $<  -o $@
XMLelement.test: XMLelement.test.cpp $(XMLELEMENT_HEADERS)
	g++ -std=c++23 $<  -o $@

XML_DOCDECL_HEADERS = $(XMLELEMENT_HEADERS) XMLdocdecl.h
XMLdocdecl.test: XMLdocdecl.test.cpp $(XML_DOCDECL_HEADERS)
	g++ -std=c++23 $<  -o $@
XMLroot.test: XMLroot.test.cpp XMLroot.h $(XMLELEMENT_HEADERS)
	g++ -std=c++23 $<  -o $@

XMLdoc.test:  XMLdoc.test.cpp  XMLdoc.h  $(XMLELEMENT_HEADERS)
	g++ -std=c++23 $<  -o $@



# XMLelement.old.h defines macro: XML_COMPONENTS_H
XMLelement.old.test: XMLelement.old.test.cpp XMLelement.old.h XML.globals.h
	g++ -std=c++23 $<  -o $@



%.test: %.test.cpp %.h
	g++ -std=c++23 $<  -o $@
%.o: %.cpp
	g++ -std=c++23 -c -std=c++17 $<


clean:
	$(RM)  a.out *.test *.o


save_to_Dropbox:
	cp --update README-*.md Makefile *.h *.cpp *.md *.txt *.bak $(RAPIDXML) ~/Dropbox/cpp_code/XML/
