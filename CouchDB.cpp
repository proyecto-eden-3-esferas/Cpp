#ifndef COUCHDB_CPP
#define COUCHDB_CPP

#ifndef COUCHDB_H
#include "CouchDB.h"
#endif


template <typename CHAR>
void CouchDB<CHAR>::check() const  {
  run(std::format("curl http://{}:5984/", IP_address));
};


// Implementations of Member Functions make_query_string() and query()

template <typename CHAR>
CouchDB<CHAR>::string_t CouchDB<CHAR>::make_query_string() const {
  return std::format("curl -u {}:{} -X GET http://{}:{}/_all_dbs",
                     user,
                     password,
                     IP_address,
                     port);
};
template <typename CHAR>
CouchDB<CHAR>::string_t CouchDB<CHAR>::make_query_string(string_view_t resource) const {
  return std::format("curl -u {}:{} -X GET http://{}:{}/{}",
                     user,
                     password,
                     IP_address,
                     port,
                     resource.data());
};

template <typename CHAR>
void CouchDB<CHAR>::query() const {
#ifdef DEBUG
  std::cout << "Query String is: " << make_query_string() << '\n';
#endif
  run(make_query_string());
};
template <typename CHAR>
void CouchDB<CHAR>::query(string_view_t res) const {
  run(make_query_string(res));
};

template <typename CHAR>
void CouchDB<CHAR>::query(string_view_t resource, string_view_t selector) {
  run(std::format("curl -u {}:{} -X POST -H \"Content-Type: application/json\"\
                  http://{}:{}/{}/_find -d \'{{\"selector\": {}}}\'",
                  user,
                  password,
                  IP_address,
                  port,
                  resource.data(),
                  selector.data())
      );
};
template <typename CHAR>
void CouchDB<CHAR>::query(string_view_t resource, string_view_t selector, string_view_t fields) {
  run(std::format("curl -u {}:{} -X POST -H \"Content-Type: application/json\"\
                  http://{}:{}/{}/_find -d \'{{\"selector\": {}, \"fields\": {} }}\'",
                  user,
                  password,
                  IP_address,
                  port,
                  resource.data(),
                  selector.data(),
                  fields.data())
      );
};

template <typename CHAR>
void CouchDB<CHAR>::create(string_view_t res) {
  register_resource(res);
  run(std::format("curl -u {}:{} -X PUT http://{}:{}/{}",
                  user,
                  password,
                  IP_address,
                  port,
                  res.data()));
};
template <typename CHAR>
void CouchDB<CHAR>::erase(string_view_t res) {
  unregister_resource(res);
  run(std::format("curl -u {}:{} -X DELETE http://{}:{}/{}",
                  user,
                  password,
                  IP_address,
                  port,
                  res.data()));
};
template <typename CHAR>
void CouchDB<CHAR>::add_document_to(string_view_t doc, string_view_t resource) {
  run(std::format("curl -u {}:{} -X POST -H \"Content-Type: application/json\" -d \'{}' http://{}:{}/{}",
                  user,
                  password,
                  doc,
                  IP_address,
                  port,
                  resource.data()));
};

template <typename CHAR>
void CouchDB<CHAR>::get_all_docs(string_view_t resource) const {
  run(std::format("curl -u {}:{} http://{}:{}/{}/_all_docs",
                  user,
                  password,
                  IP_address,
                  port,
                  resource.data()));
};


#endif
