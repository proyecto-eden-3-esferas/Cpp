## TODO

# Concerning XMLText:

[ ] Review default PrintTransformer for XMLText
[ ] Implement overrides XMLText::print(std::basic_ostream<CHAR>& o, LEVEL l) const = 0;


[ ] Implement overrides XMLText::print_transformed(std::basic_ostream<CHAR>& o,
                                 const PrintTransformer_t& pt,
                                 LEVEL l=LEVEL(0)) const;
[ ] Implement overrides XMLText::print_transformed(std::basic_ostream<CHAR>& o,
                                 const PrintTransformer_t& pt,
                                 const string_t& str,
                                 LEVEL l=LEVEL(0)) const;


# Concerning XMLelement:

[ ] define enum (class) block_enum and holds_inlines_enum
    and use them in constructor

[ ] an XMLelement class without a Namespaces object,
    wherefrom to derive an XMLelement class holding a Namespaces object.


[ ] add qname module (from *qname.h*) to class Namespaces
