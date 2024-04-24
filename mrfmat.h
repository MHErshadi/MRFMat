/*
MIT License

Copyright (c) 2023 MetaReal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#ifndef __MRFMAT__
#define __MRFMAT__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

#define MRFMAT_VERSION "0.1.0"
#define MRFMAT_VERSION_MAJOR 0
#define MRFMAT_VERSION_MINOR 1
#define MRFMAT_VERSION_PATCH 0

#if defined(__GNUC__) || defined(__clang__) || defined(_MSC_VER)
#   ifdef _WIN32
#       define __MRFMAT_DECLSPEC_EXPORT __declspec(dllexport)
#       define __MRFMAT_DECLSPEC_IMPORT __declspec(dllimport)
#   else
#       define __MRFMAT_DECLSPEC_EXPORT
#       define __MRFMAT_DECLSPEC_IMPORT
#   endif
#else
#   define __MRFMAT_DECLSPEC_EXPORT
#   define __MRFMAT_DECLSPEC_IMPORT
#endif

#ifdef __MRFMAT_SHARED__
#   ifdef __MRFMAT_COMPILE_TIME__
#       define __MRFMAT_DECLSPEC __MRFMAT_DECLSPEC_EXPORT
#   else
#       define __MRFMAT_DECLSPEC __MRFMAT_DECLSPEC_IMPORT
#   endif
#else
#   define __MRFMAT_DECLSPEC
#endif

/* data types */

typedef uint8_t mrfmat_bool_t;
typedef int8_t mrfmat_sbyte_t;
typedef uint8_t mrfmat_byte_t;
typedef int16_t mrfmat_sshort_t;
typedef uint16_t mrfmat_short_t;
typedef int32_t mrfmat_slong_t;
typedef uint32_t mrfmat_long_t;
typedef int64_t mrfmat_slonglong_t;
typedef uint64_t mrfmat_longlong_t;

typedef float mrfmat_float_t;
typedef double mrfmat_double_t;

typedef size_t mrfmat_size_t;

typedef mrfmat_byte_t *mrfmat_data_t;

#define MRFMAT_TRUE ((mrfmat_bool_t)1)
#define MRFMAT_FALSE ((mrfmat_bool_t)0)

enum __MRFMAT_TYPES_ENUM
{
    MRFMAT_TYPES_BOOL,
    MRFMAT_TYPES_SBYTE,
    MRFMAT_TYPES_BYTE,
    MRFMAT_TYPES_SSHORT,
    MRFMAT_TYPES_SHORT,
    MRFMAT_TYPES_SLONG,
    MRFMAT_TYPES_LONG,
    MRFMAT_TYPES_SLONGLONG,
    MRFMAT_TYPES_LONGLONG,
    MRFMAT_TYPES_FLOAT,
    MRFMAT_TYPES_DOUBLE
};
typedef mrfmat_byte_t mrfmat_type_t;

#pragma pack(push, 1)
struct __MRFMAT_T
{
    mrfmat_data_t _data;
    mrfmat_size_t _size;
    mrfmat_size_t _capa;

    mrfmat_type_t _type;
};
#pragma pack(pop)
typedef struct __MRFMAT_T mrfmat_t[1];
typedef struct __MRFMAT_T *mrfmat_p;

typedef const struct __MRFMAT_T *mrfmat_ct[1];

#define MRFMAT_DATA(x) ((x)->_data)
#define MRFMAT_SIZE(x) ((x)->_size)
#define MRFMAT_CAPA(x) ((x)->_capa)
#define MRFMAT_TYPE(x) ((x)->_type)

enum __MRFMAT_RES_ENUM
{
    MRFMAT_RES_NOERROR,
    MRFMAT_RES_MEM_ERROR
};
typedef mrfmat_byte_t mrfmat_res_t;

/* init functions */

__MRFMAT_DECLSPEC void mrfmat_init(
    mrfmat_t mat, mrfmat_type_t type);
__MRFMAT_DECLSPEC void mrfmat_inits(
    mrfmat_type_t type, mrfmat_p mat, ...);

__MRFMAT_DECLSPEC void mrfmat_free(
    mrfmat_t mat);
__MRFMAT_DECLSPEC void mrfmat_frees(
    mrfmat_p mat, ...);

__MRFMAT_DECLSPEC void mrfmat_clear(
    mrfmat_t mat);
__MRFMAT_DECLSPEC void mrfmat_clears(
    mrfmat_p mat, ...);

#ifdef __cplusplus
}
#endif

#endif
