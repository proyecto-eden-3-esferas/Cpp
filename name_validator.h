#ifndef NAME_VALIDATOR_H
#define NAME_VALIDATOR_H

#include <string>
#include <string_view>


/* Class name_validator<> tells if a given string
 * qualifies as a name given some reasonable assumptions:
 * (1) all letters are allowed
 * (2) numbers are allowed after the first character
 * (3) some other non-alphanumeric characters are allowed
 *     such as underscore (_),
 *     sometimes also hyphen (-), period (.)...
 * (4) fewer characters are allowed in the first position
 *     than in the following ones.
 */

template <typename CHAR = char, typename STRING = std::basic_string_view<CHAR> >
class name_validator : public STRING {
public:
 typedef std::basic_string<CHAR>      string_type;
 typedef std::basic_string_view<CHAR> string_view_type;
 string_type other_mid_chars;
 string_type other_beg_chars;
 bool digits_allowed = true;
 bool alpha_first = true;
 virtual bool is_allowed_mid(CHAR c) const;
 virtual bool is_allowed_beg(CHAR c) const;
 virtual bool is_allowed_end(CHAR c) const {return is_allowed_mid(c);};
public:
 virtual bool is_allowed(string_view_type sv) const;
 virtual bool operator()(string_view_type sv) const {return is_allowed(sv);};
 //
 name_validator(string_view_type omc = "_.:-",
                string_view_type ob = "_",
                bool da = true,
                bool af = true) :
                other_mid_chars(omc), other_beg_chars (ob), digits_allowed(da), alpha_first(af)
                {};
};
#endif
