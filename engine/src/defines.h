#ifndef VALLY_DEFINES_H_
#define VALLY_DEFINES_H_

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
typedef char b8;

#define TRUE 1
#define FALSE 0

#define NULL ((void *)0)

#define BIT_MASK(n) (1 << n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#ifdef VALLY_EXPORT
// Exports
#ifdef _MSC_VER
#define VALLY_DLL __declspec(dllexport)
#else
#define VALLY_DLL __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define VALLY_DLL __declspec(dllimport)
#else
#define VALLY_DLL
#endif
#endif

// Inlining
#if defined(__clang__) || defined(__gcc__)
#define VALLY_INLINE __attribute__((always_inline)) inline
#define VALLY_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define VALLY_INLINE __forceinline
#define VALLY_NOINLINE __declspec(noinline)
#else
#define VALLY_INLINE static inline
#define VALLY_NOINLINE
#endif

#endif  // !VALLY_DEFINES_H_