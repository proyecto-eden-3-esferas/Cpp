#ifndef DEPENDENCY_MANAGER_H
#define DEPENDENCY_MANAGER_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>

/* class DependencyManager<>
 * Using a std::queue or a std::priority_stack would achieve a different result
 * Use hash containers for large sets
 * What about using another sequence container instead of a linked list?
 * Applications:
 * - file dependencies
 * - dependencies of sections in a book
 * TODO
   [ ] member reset_and_satisfy(TOKEN) fails to yield correct results!!!
       it should be implemented by means of a depth-first search
   [ ]
 */
template <typename                            TOKEN = std::string,
          template <typename> typename        STACK = std::stack,
          template <typename,typename> typename MAP = std::map,
          template <typename> typename          SET = std::set
         >
class DependencyManager {
public:
  typedef std::set<TOKEN> tokens_set_t;
  typedef std::map<TOKEN,std::list<TOKEN>> dependencies_t;
  typedef std::stack<TOKEN> stack_t;
  // Member variables that are initialized on construction or shortly afterwards:
  tokens_set_t         tokens;
  dependencies_t dependencies; // map each token to the tokens it depends on;
                               // 'dependencies' must implement members cbegin() and cend()
  //
  tokens_set_t already_added;
  stack_t stack_of_dependencies;
  // Member functions:
  void add_dependency(const TOKEN& token, const TOKEN& dep) {
    dependencies[token].push_back(dep);
  };
  void reset_stack() {
    for(int i = stack_of_dependencies.size(); i > 0; --i)
      stack_of_dependencies.pop();
  };
  void reset_already_added() {
    already_added.clear();
  };
  virtual void execute(TOKEN& tkn) {std::cout << "EXECUTING TOKEN: " << tkn << '\n';};
  virtual void reset_and_satisfy(const TOKEN & tkn) {
    reset_stack();
    // Fill the 'stack_of_dependencies' (possibly recursively):
    build(tkn);
    // Then execute() and pop() each item in the 'stack_of_dependencies':
    while(! stack_of_dependencies.empty()) {
      execute(stack_of_dependencies.top());
      stack_of_dependencies.pop();
    }
  };
  void build(const TOKEN & tkn) {
    for(const auto & t : dependencies[tkn]) {
      if(!already_added.contains(t)) {
        stack_of_dependencies.push(t);
        std::cout << "PUSHING: " << t << '\n';
        already_added.insert(t);
      }
    }
    for(const auto & t : dependencies[tkn])
      build(t); // recursive call
  };
};

#endif
