[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

# TurboMath
TurboMath is an all inline SIMD C++ Math-Library for use in Games and Graphics Windows-Apps


## Example


```cpp
Vector4 vec1,vec2;
vec1.NullVec();
vec2.Set(100.0f,100.0f,100.0f);
vec1 += vec2;
vec2 = vec1;


Matrix mat1;
mat1.Identity();

vec1 *= mat1;
vec2 = vec1 * mat1;

```



## Requirements

The only required features are a C++ compiler with SSE-support on your target platform. As a curiosity it also includes an Xbox 360 implementation.

## How to use

```cpp
#include "TurboMath.h"
```

## Features

* fast inline SSE2-Code with VectorCall (Calling-Convention)
* Vector2, Vector3, Vector4, Point2, Point3, Point4
* Color-Class with Color define
* Matrix
* Quaternion
* Conversion construction and assignment
* Basic operators +, *, -, / for all Types
* Per-component comparison operators ==, !=, >, <, >=, <=
* Collision-Tests for Ray, ABB, OBB, Sphere, Triangle etc
* many Additional matrix functions: determinant, transpose, inverse etc
* WayPoints with Interpolation

Missing/planned:

* swizzling 
* boolN types
* more Inline and VectorCall