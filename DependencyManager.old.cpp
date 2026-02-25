#ifndef DEPENDENCY_MANAGER_CPP
#define DEPENDENCY_MANAGER_CPP

#ifndef DEPENDENCY_MANAGER_H
#include "DependencyManager.old.h"
#endif

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
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::reset_stack() {
  for(int i = stack_of_dependencies.size(); i > 0; --i)
    stack_of_dependencies.pop();
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
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::reset_and_satisfy(const TOKEN & tkn) {
  reset_stack();
  // Fill the 'stack_of_dependencies' (possibly recursively):
  build(tkn);
  // Then execute() and pop() each item in the 'stack_of_dependencies':
  while(! stack_of_dependencies.empty()) {
    execute(stack_of_dependencies.top());
    stack_of_dependencies.pop();
  }
};


template <typename                            TOKEN,
          template <typename> typename    TOKEN_SET,
          template <typename,typename> typename MAP,
          template <typename> typename          SET
         >
void DependencyManager<TOKEN,TOKEN_SET,MAP,SET>::build(const TOKEN & tkn) {
#ifndef FORMER
  iterator it = dependencies[tkn].cbegin();
  iterator en = dependencies[tkn].cend();
  if(it != en) {
    path_stack.emplace(it,en);

  }
  else {
    // tkn has no unsatisfied dependencies, so add/push it
    stack_of_dependencies.push(tkn);
  }


#else
  for(const auto & t : dependencies[tkn]) {
    if(!already_added.contains(t)) {
      stack_of_dependencies.push(t);
      std::cout << "PUSHING: " << t << '\n';
      already_added.insert(t);
    }
  }
  for(const auto & t : dependencies[tkn])
    build(t); // recursive call
#endif
};

#endif
