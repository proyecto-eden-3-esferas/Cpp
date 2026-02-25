#ifndef DEPENDENCY_MANAGER_CPP
#define DEPENDENCY_MANAGER_CPP

#ifndef DEPENDENCY_MANAGER_H
#include "DependencyManager.h"
#endif

template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
bool DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::has_dependency(const TOKEN& token) const {
  return dependencies.contains(token);
};

template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::add_dependency(const TOKEN& token, const TOKEN& dep) {
  dependencies[token].push_back(dep);
};

template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::insert(const value_type& d) {
  dependencies.insert(d);
};

template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::reset_queue() {
  for(int i = queue_of_dependencies.size(); i > 0; --i)
    queue_of_dependencies.pop();
};

template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::reset_already_added() {
  already_added.clear();
};


template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::execute_on_backtracking(ostream_t& o, const TOKEN& tkn) {
    o << "EXECUTING TOKEN: " << tkn << '\n';
  };


template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::satisfy(ostream_t& o, const TOKEN & tkn) {
  // Fill the 'queue_of_dependencies' (possibly recursively):
  build(tkn);
  // Then execute() and pop() each item in the 'queue_of_dependencies':
  while(! queue_of_dependencies.empty()) {
    execute_on_backtracking(o, queue_of_dependencies.front());
    queue_of_dependencies.pop();
  }
};
template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::reset_and_satisfy(ostream_t& o, const TOKEN & tkn) {
  reset_queue();
  satisfy(o,tkn);
};


template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::build(const TOKEN & tkn) {

  if(dependencies.contains(tkn)) {

    const_iterator it = dependencies[tkn].cbegin();
    const_iterator en = dependencies[tkn].cend();

    // increment 'it' until it points to a non-added token:
    while(it != en && already_added.contains(*it))
      ++it;

    if(it != en) { // 'it' now points to an unsatisfied dependency:
      for(; it != en; ++it) {
        if(!already_added.contains(*it))
          build(*it);
      }  // for
    } // outer if

  } // outermost if

  // tkn has no unsatisfied dependencies, so add/push it
  queue_of_dependencies.push(tkn);
  already_added.insert(tkn);

};

#endif
