#ifndef ID_H
#define ID_H

#include <queue>

/* Class id holds an id field ('itsId') as an unsigned integer,
 * which is got through member id::get_id()
 * Static members are in charge of providing the id
   to initialize the next id object with.
 * Class id is useful for attaching ids to objects
   of classes derived from class id
 * TODO
 [ ] add a member to hold/return the address of an id self or descendant object
 [ ] add a move constructor
 *
 * (From https://cplusplus.com/reference/queue/queue/)
Member functions:
(constructor) Construct queue (public member function)
empty(): Test whether container is empty (public member function)
size(): Return size (public member function)
front(): Access next element (public member function)
back(): Access last element (public member function)
push(ELEMENT): Insert element (public member function)
emplace(ARGS): Construct and insert element (public member function)
pop(): Remove next element (public member function)
swap(?): Swap contents (public member function)
 */
class id {
  typedef unsigned int id_t;
  static id_t nextId;
public:
  const  id_t      itsId;
  id_t get_id() const {return itsId;};
protected:
  static std::queue<id_t> available_ids;
  virtual id_t get_next_id() {
    if(available_ids.size() > 0) {
      id_t frontId = available_ids.front();
#ifdef DEBUG
      std::cout << "[\'available_ids\' has " << available_ids.size() << " element(s).]\n";
      std::cout << "[\'frontId\' has value: " << frontId] << std::endl;
#endif
      available_ids.pop();
      return frontId;
    }
    else
      return ++nextId;
  };
public:
           id() : itsId(get_next_id()) {};
  virtual ~id()                        {available_ids.push(itsId);};
};

// Declare/Define static members:
typename id::id_t id::nextId = 0;
std::queue<id::id_t> id::available_ids;

#endif
