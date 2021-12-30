#ifndef SOGE_DEFINES_H_
#define SOGE_DEFINES_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

typedef int b32;
typedef _Bool b8;

#define TRUE 1
#define FALSE 0

#ifdef SOGE_EXPORT
// Exports
#ifdef _MSC_VER
#define SAPI __declspec(dllexport)
#else
#define SAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define SAPI __declspec(dllimport)
#else
#define SAPI
#endif
#endif

#endif  // !SOGE_DEFINES_H_