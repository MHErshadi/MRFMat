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
    MRFMAT_TYPES_INT8,
    MRFMAT_TYPES_UINT8,
    MRFMAT_TYPES_INT16,
    MRFMAT_TYPES_UINT16,
    MRFMAT_TYPES_INT32,
    MRFMAT_TYPES_UINT32,
    MRFMAT_TYPES_INT64,
    MRFMAT_TYPES_UINT64,
    MRFMAT_TYPES_DEC16,
    MRFMAT_TYPES_DEC32,
    MRFMAT_TYPES_DEC64
};
typedef mrfmat_byte_t mrfmat_type_t;

#pragma pack(push, 1)
struct __MRFMAT_T
{
    mrfmat_data_t _data;
    mrfmat_size_t _row;
    mrfmat_size_t _col;

    mrfmat_type_t _type : 7;
    mrfmat_bool_t _row_major : 1;
};
#pragma pack(pop)
typedef struct __MRFMAT_T mrfmat_t[1];
typedef struct __MRFMAT_T *mrfmat_p;

typedef const struct __MRFMAT_T mrfmat_ct[1];

#define MRFMAT_DATA(x) ((x)->_data)
#define MRFMAT_ROW(x) ((x)->_row)
#define MRFMAT_COL(x) ((x)->_col)
#define MRFMAT_TYPE(x) ((x)->_type)
#define MRFMAT_ROW_MAJOR(x) ((x)->_row_major)

enum __MRFMAT_RES_ENUM
{
    MRFMAT_RES_NOERROR,
    MRFMAT_RES_MEM_ERROR
};
typedef mrfmat_byte_t mrfmat_res_t;

/* init functions */

__MRFMAT_DECLSPEC void mrfmat_init(
    mrfmat_t mat, mrfmat_type_t type, mrfmat_bool_t row_major);
__MRFMAT_DECLSPEC void mrfmat_inits(
    mrfmat_type_t type, mrfmat_bool_t row_major, mrfmat_p mat, ...);

__MRFMAT_DECLSPEC void mrfmat_init2(
    mrfmat_t mat, mrfmat_data_t data, mrfmat_size_t row, mrfmat_size_t col, mrfmat_type_t type, mrfmat_bool_t row_major);

__MRFMAT_DECLSPEC mrfmat_res_t mrfmat_init_alloc(
    mrfmat_t mat, mrfmat_type_t type, mrfmat_bool_t row_major, mrfmat_size_t row, mrfmat_size_t col);
__MRFMAT_DECLSPEC mrfmat_res_t mrfmat_alloc(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col);

__MRFMAT_DECLSPEC void mrfmat_free(
    mrfmat_t mat);
__MRFMAT_DECLSPEC void mrfmat_frees(
    mrfmat_p mat, ...);

__MRFMAT_DECLSPEC void mrfmat_clear(
    mrfmat_t mat);
__MRFMAT_DECLSPEC void mrfmat_clears(
    mrfmat_p mat, ...);

__MRFMAT_DECLSPEC mrfmat_res_t mrfmat_clear_realloc(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col);

__MRFMAT_DECLSPEC mrfmat_res_t mrfmat_clear_expand(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col);

__MRFMAT_DECLSPEC mrfmat_res_t mrfmat_clear_shrink(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col);

__MRFMAT_DECLSPEC void mrfmat_swap(
    mrfmat_t mat1, mrfmat_t mat2);

/* data functions */

inline mrfmat_data_t mrfmat_get_data(
    mrfmat_t mat)
{
    return MRFMAT_DATA(mat);
}

inline mrfmat_size_t mrfmat_get_row(
    mrfmat_ct mat)
{
    return MRFMAT_ROW(mat);
}

inline mrfmat_size_t mrfmat_get_col(
    mrfmat_ct mat)
{
    return MRFMAT_COL(mat);
}

inline mrfmat_size_t mrfmat_get_size(
    mrfmat_ct mat)
{
    return MRFMAT_ROW(mat) * MRFMAT_COL(mat);
}

inline mrfmat_type_t mrfmat_get_type(
    mrfmat_ct mat)
{
    return MRFMAT_TYPE(mat);
}

inline mrfmat_bool_t mrfmat_get_row_major(
    mrfmat_ct mat)
{
    return MRFMAT_ROW_MAJOR(mat);
}

#ifdef __cplusplus
}
#endif

#endif
