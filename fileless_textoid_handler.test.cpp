#include "fileless_textoid_handler.h"

using namespace std;
const std::size_t initial_slotsize = 500;
typedef fileless_textoid<char,initial_slotsize> elem_t;
typedef fileless_textoid_handler<char,initial_slotsize> fth_t;
typedef std::size_t size_t;

void print_element(const fth_t& fth, size_t idx) {
  cout << "element " << idx << " with offset " << fth[idx].get_offset();
  cout << ", and slotsize " << fth[idx].get_slotsize() << ", and slot_capacity " << fth[idx].get_slot_capacity() << '\n';
};

int main() {

  fth_t fth1("textoid", 2);

  fth1.add(elem_t{"My first fileless_textoid."});
  cout << "fth1[0]: ";
  print_element(fth1, 0);
  cout << '\n';
  //return 0;
  fth1.add(elem_t{"My second fileless_textoid."});
  cout << "fth1.print_state() after adding the second elem_t:\n";
  fth1.print_state(cout);
  fth1.add(elem_t{"My third fileless_textoid."},2);

  /*
  fth1.increase_slotsize(initial_slotsize*2);
  cout << "fth1.increase_slotsize(" << fth1.slotsize << ") results in fth1[1] having ";
  fth1.print_state();
  */

  cout << "fth1.print_state() after adding the third elem_t (2 slots):\n";
  fth1.print_state(cout);

  cout << "\nfts.increase_slotsize_by(1,1): ";
  fth1.increase_slotsize_by(1,1);

  cout << "fth1.print_state(std::cout):\n";
  fth1.print_state(cout);
  //cout << "fth1.print_free(std::cout)\n"; fth1.print_free(cout);

  fth1.add(elem_t{"My fourth fileless_textoid."});

  fth1.print_state(cout);
  /*
  cout << "Reuse an offset for 1 slotsize(s):\n";
  fth1.reuse_offset_for_n_slots(1);

  cout << "fth1.print_size_offsets_and_slotsizes(std::cout), again:\n";
  fth1.print_free(cout);
  */

  // fth1.write_size_offsets_and_slotsizes();

  fth1.write_size_offsets_and_slotsizes();

  fth_t fth2("textoid");
  fth2.add(elem_t{"My fifth fileless_textoid."});
  fth2.print_state(cout);
  //fth_t fth3;
  //fth_t fth4("textoid", 4);

  fth1.store();

  return 0;
}
