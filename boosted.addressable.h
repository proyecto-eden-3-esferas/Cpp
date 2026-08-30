#ifndef BOOSTED_ADDRESSABLE_H
#define BOOSTED_ADDRESSABLE_H

#ifndef BOOSTED_BLOCK_DIAGRAM_H
#include "boosted.block_diagram.h"
#endif

/* Class addressable<INT,ANGLE,F> is a pure interface
   with no member variables or implemented member functions.
   derived from both indexable<> and angular<>
 * Often enough, developers will be implemented
   either an indexable<> or an angular interface<>
 */
template < typename     F = double,
           typename   INT = unsigned int,
           typename ANGLE = Degree<F>
         >
class addressable : public indexable<F,INT>, public angular<F,ANGLE> {
public:
  using indexable<  F,INT>::get_x, indexable<F,INT>::get_y;
  using   angular<F,ANGLE>::get_x, angular<F,ANGLE>::get_y;

};

#endif
