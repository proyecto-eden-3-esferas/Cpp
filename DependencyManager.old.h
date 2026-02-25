#ifndef DEPENDENCY_MANAGER_H
#define DEPENDENCY_MANAGER_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>

/* class DependencyManager<> (former version)
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
          template <typename> typename    TOKEN_SET = std::list, // any sequence container
          template <typename,typename> typename MAP = std::map,
          template <typename> typename          SET = std::set
         >
class DependencyManager {
public:
  typedef std::set<TOKEN> tokens_set_t;
  typedef std::map<TOKEN,TOKEN_SET<TOKEN>> dependencies_t;
  typedef dependencies_t::      iterator       iterator;
  typedef dependencies_t::const_iterator const_iterator;
  typedef std::pair<iterator,iterator> iterator_pair_t;
  typedef std::stack<TOKEN>              token_stack_t;
  typedef std::stack<iterator_pair_t>     path_stack_t;
  // Member variables that are initialized on construction or shortly afterwards:
  dependencies_t dependencies; // map each token to the tokens it depends on;
                               // 'dependencies' must implement members cbegin() and cend()
  //
  tokens_set_t          already_added;
  token_stack_t stack_of_dependencies;
  path_stack_t  path_stack;
  /* Member functions.
   * Initially, dependencies are added through 'add_dependency(TOKEN,TOKEN)'
   * Then reset_and_satisfy is called.
   * To customize resulting behaviour, just override 'execute(TOKEN)' in child classes
   */
  void add_dependency(const TOKEN& token, const TOKEN& dep);
  void reset_stack();
  void reset_already_added();
  virtual void execute(TOKEN& tkn) {std::cout << "EXECUTING TOKEN: " << tkn << '\n';};
  virtual void reset_and_satisfy(const TOKEN & tkn); // calls build() then processes result
  void build(const TOKEN & tkn); // adds tokens to (empty or not) 'token_stack_t'
                                 // this is the main function
                                 // it implements a depth-first search
};

#ifndef SEPARATE_COMPILATION
#include "DependencyManager.old.cpp"
#endif

#endif
