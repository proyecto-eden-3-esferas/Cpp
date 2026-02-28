/* File "CouchDB.test.cpp" tests class CouchDB
 * TODO:
   [x] query() and query(RESOURCE) should rely on (protected) members:
       - make_query_string(), and
       - make_query_string(RESOURCE)
   [x] produce formated strings with <format>
   [ ] improve on stdlib::system(COMMAND)
       possibly though a static boolean 'is_unix'.
       For the time being, C-global run(COMMAND) outputs to cout,
       which may be redirected
   [x] Instances of 'InetConnection' hold collections of resources as strings (names)
 */


#ifndef COUCHDB_H
#include "CouchDB.h"
#endif

#include <vector>

using namespace std;

typedef CouchDB<char> CouchDB_t;

int main() {

  CouchDB_t cdb0;

  //cout << "falkon http://localhost:5984/_utils/ &\n" << flush;

//cdb0.run("curl http://127.0.0.1:5984/");
//system("curl http://127.0.0.1:5984/");

  cout << "\nRun check():\n";
  cdb0.check();

  cout << flush << "\nThis is an array of available CouchDB databases on this server (query()): " << flush;
  cdb0.query();

  cout << "\nNow query some user-written databases, like \'botany\':\n";
  cdb0.query("botany");

  cout << "\nand \'computing\' (print only \"term\" and \"definition\"):\n";
  cdb0.query("computing", "{}", "[\"term\", \"definition\"]");

  cout << "\nThe same but using an overload taking a container of fields (strings) as its 3rd param:\n";
  vector<string> fields{"term", "definition"};
  cdb0.query("computing", "{}", fields);

  cout << "\nget_all_docs(\"computing\"):\n";
  cdb0.get_all_docs("computing");



#ifdef TEST_REDIRECTION
  string db_choice;
  cout << "Now write the name of a database, then press ENTER. (We want to query (a DB).):\n";
  cin >> db_choice;

  cdb0.redirect_output_to_string();
  cdb0.query(db_choice);
  cout << cdb0.get_result_string() << '\n';
#endif

  cout << "\nBye!\n";

  return 0;
}
