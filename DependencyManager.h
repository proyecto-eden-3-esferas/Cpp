#ifndef DEPENDENCY_MANAGER_H
#define DEPENDENCY_MANAGER_H

#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>

/* class DependencyManager<>
 * Tokens are the name, numerical identifier, address etc. of an object
 * Use hash containers for large sets
 * What about using another sequence container instead of a linked list?
 * Applications:
 * - file dependencies
 * - dependencies of sections in a book
 * TODO
   [ ] add constructors taking (1) a pair of iterators, (2) an initialization list
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
  typedef typename dependencies_t::value_type value_type;
  typedef typename dependencies_t::mapped_type::      iterator       iterator;
  typedef typename dependencies_t::mapped_type::const_iterator const_iterator;
  typedef std::pair<iterator,iterator> iterator_pair_t;
  typedef std::queue<TOKEN>              token_queue_t; // a queue of tokens in dependency order
  typedef std::ostream ostream_t;

  // Member variables that are initialized on construction or shortly afterwards:
  dependencies_t dependencies; // map each token to the tokens it depends on;
                               // 'dependencies' must implement members cbegin() and cend()
  tokens_set_t          already_added;
  token_queue_t queue_of_dependencies;

  /* Member functions for querying and inserting dependencies:
   * Initially, dependencies are added through 'add_dependency(TOKEN,TOKEN)'
   * Then reset_and_satisfy is called.
   * To customize resulting behaviour, just override 'execute_on_backtracking(TOKEN)' in child classes
   */
  bool has_dependency(const TOKEN& token) const;
  void add_dependency(const TOKEN& token, const TOKEN& dep);
  void insert(const value_type& d);
  template <typename ITER>
  void insert(ITER first, ITER last) {dependencies.insert(first, last);};

  // Procedures for computing dependencies, which get stored in 'queue_of_dependencies':
  void reset_queue();
  void reset_already_added();
  virtual void execute_on_backtracking(ostream_t& o, const TOKEN& tkn);
  void           satisfy(ostream_t& o, const TOKEN & tkn); // calls build() then processes result
  void reset_and_satisfy(ostream_t& o, const TOKEN & tkn); // resets 'queue_of_dependencies',
                                                           // then satisfies(TOKEN)
  /* build(TOKEN) adds tokens to (empty or not) 'token_queue_t'
   * so that dependencies are satisfied.
   * This is the main function.
   * It implements a depth-first search through recursion, not through a stack.
   */
   void build(const TOKEN & tkn);

   // Constructors and destructor:
   DependencyManager() {};
   template <typename ITER>
   DependencyManager(ITER first, ITER last)           : dependencies(first,last) {};
   DependencyManager(std::initializer_list<value_type> il) : dependencies(il) {};
};

#ifndef SEPARATE_COMPILATION
#include "DependencyManager.cpp"
#endif

#endif
