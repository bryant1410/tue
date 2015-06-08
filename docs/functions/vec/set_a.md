[Tuesday](../../../README.md)/[`vec`](../../headers/vec.md)/`set_a`
===================================================================
Provided by header [`<tue/vec.hpp>`](../../headers/vec.md)

```c++
// (vec<T, 4> only)
template<typename T, int N>
void vec<T, N>::set_a(const T& a) noexcept;
```

Sets the fourth component of this [`vec`](../../headers/vec.md). This function
is only available when `N >= 4`.

License
-------
Copyright Jo Bates 2015.

Distributed under the Boost Software License, Version 1.0.

See accompanying file [LICENSE_1_0.txt](../../../LICENSE_1_0.txt) or copy at
http://www.boost.org/LICENSE_1_0.txt.