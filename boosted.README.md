# Boosted Libraries

Boosted libraries or code are code that relies on boost libraries, their concepts, interfaces and implementations, whenever possible.

To date, some boost libraries to be relied on are:

- boost::geometry, esp. for its point concept and classes

- boost::graph

# Boosted Geometry versus Boost-like Geometry
Currently each compilation unit takes about twelve seconds to compile into object. With no separate compilation, each build takes a little longer than twelve seconds, no matter how basic the code may be. Therefore I have decided to write my own library yet follow the Boost.Geometry interfaces or concepts as closely as I can manage.


# Boosted Geometry

## `model::point`
In this section we shall discuss:
- including libraries for model::point
- constructing a model::point object
- accessing coordinates in an instance of model::point

### `model::point` Includes

`model::point` is included through a line like: `#include <boost/geometry.hpp>`

For conveniance, you might define: `namespace bg = boost::geometry;`
```


### `model::point` Constructors

The constructors for points in boost::geometry are pretty intuitive. A three dimentional point would be constructed like:
```
point_type my_point(X,Y,Z);
```

(Now, you can provide fewer input parameters, say just `point_type my_point(X);`, and the others will be default initialized)

### `model::point` Accessors

The accessors consist of the `get<D>()` and `set<D>(VALUE)` interface, where D is the dimension you want to access (from 0 to N - 1) and VALUE is the new value you want to set.

Both accessor functions may be either a global function or a member functions. This means that `bg::get<0>(point1);` and `point1.get<0>(1);` return the first coordinate

```


