#ifndef BOOSTLIKE_LABELED_BLOCK_CPP
#define BOOSTLIKE_LABELED_BLOCK_CPP

#ifndef BOOSTLIKE_LABELED_BLOCK_H
#include "boost-like.labeled_block.h"
#endif


template < typename F, typename POINT, typename ANGLE>
labeled_block<F,POINT,ANGLE>::label_type &
labeled_block<F,POINT,ANGLE>::get_inner_label_at(index_type idx) {
  return bilabels[idx].first;
};

template < typename F, typename POINT, typename ANGLE>
const labeled_block<F,POINT,ANGLE>::label_type &
labeled_block<F,POINT,ANGLE>::get_inner_label_at(index_type idx) const {
  return bilabels[idx].first;
};

template < typename F, typename POINT, typename ANGLE>
void labeled_block<F,POINT,ANGLE>::set_inner_label_at_to(index_type idx, const label_type & lbl) {
  bilabels[idx].first = lbl;
};

template < typename F, typename POINT, typename ANGLE>
labeled_block<F,POINT,ANGLE>::label_type &
labeled_block<F,POINT,ANGLE>::get_outer_label_at(index_type idx) {
  return bilabels[idx].second;
};
template < typename F, typename POINT, typename ANGLE>
const labeled_block<F,POINT,ANGLE>::label_type &
labeled_block<F,POINT,ANGLE>::get_outer_label_at(index_type idx) const {
  return bilabels[idx].second;
};
template < typename F, typename POINT, typename ANGLE>
void labeled_block<F,POINT,ANGLE>::set_outer_label_at_to(index_type idx, const label_type & lbl) {
  bilabels[idx].second = lbl;
};


#endif
