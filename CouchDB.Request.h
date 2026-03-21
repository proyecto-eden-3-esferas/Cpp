#ifndef COUCHDB_REQUEST_H
#define COUCHDB_REQUEST_H

/* Class/Struct 'CouchDB_Request' is used like this:
     POST /{db}/_find <Request Headers> <CouchDB Request>
 * To define the member variables in this/these class(es) we need a working JSON class,
   specifically, so as to define types 'obj_t' (a JSON object) and 'array_t' (a JSON array)
 * This has been attempted in "json.h", "json.cpp",
   where the approach taken seems to me too ambitious
 * TODO
   [ ] Class/Struct 'CouchDB_Request' should be made a nested struct/class 'CouchDB::Request'
 */


struct CouchDB_Request {
  typedef std::string string_t;

  selector_t selector; // (object) – JSON object describing criteria used to select documents. More information provided in the section on selector syntax. Required
  unsigned int limit; // (number) – Maximum number of results returned. Default is 25. Optional
  unsigned int skip;  // (number) – Skip the first ‘n’ results, where ‘n’ is the value specified. Optional
  array_t sort; // (array) – JSON array following sort syntax. Optional
  array_t fields; /* (array) – JSON array specifying which fields of each object should be returned.
                     If it is omitted, the entire object is returned.
                     More information provided in the section on filtering fields. Optional */

  std::variant<string_t, array_t> use_index; // (string|array) – Request a query to use a specific index. Specified either as "<design_document>" or ["<design_document>", "<index_name>"]. It is not guaranteed that the index will be actually used because if the index is not valid for the selector, fallback to a valid index is attempted. Therefore that is more like a hint. When fallback occurs, the details are given in the warning field of the response. Optional
  bool allow_fallback; /* (boolean) – Tell if it is allowed to fall back to another valid index.
                           This can happen on running a query with an index specified by 'use_index'
                           which is not deemed usable, or when only the built-in _all_docs index would be picked in lack of indexes available to support the query.
                           Disabling this fallback logic causes the endpoint immediately return an error
                           in such cases. Default is true. Optional */

  bool conflicts; /* (boolean) – Include conflicted documents if true.
                     Intended use is to easily find conflicted documents, without an index or view.
                     Default is false. Optional */
  float_t r; /* (number) – Read quorum needed for the result.
                This defaults to 1, in which case the document found in the index is returned.
                If set to a higher value, each document is read from at least that many replicas
                before it is returned in the results.
                This is likely to take more time than using only the document stored locally with the index.
                Optional, default: 1 */
  string_t bookmark; /* (string) – A string that enables you to specify which page of results you require.
                        Used for paging through result sets.
                        Every query returns an opaque string under the bookmark key
                        that can then be passed back in a query to get the next page of results.
                        If any part of the selector query changes between requests,
                        the results are undefined. Optional, default: null */
  bool update; // (boolean) – Whether to update the index prior to returning the result. Default is true. Optional
  bool stable; // (boolean) – Whether or not the view results should be returned from a “stable” set of shards. Optional
  bool stale; /* (string) – Combination of update=false and stable=true options.
                 Possible options: "ok", false (default).
                 Optional Note that this parameter is deprecated. Use stable and update instead.
                 See Views Generation for more details. */
  bool execution_stats; // (boolean) – Include execution statistics in the query response. Optional, default: false
};

#endif
