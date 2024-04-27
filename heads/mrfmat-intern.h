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

#ifndef __MRFMAT_INTERN__
#define __MRFMAT_INTERN__

#include <mrfmat.h>
#include <stdlib.h>

#define MRFMAT_ALLOC(x, row, col, size)               \
    do                                                \
    {                                                 \
        MRFMAT_DATA(x) = (mrfmat_data_t)malloc(size); \
        if (!MRFMAT_DATA(x))                          \
            return MRFMAT_RES_MEM_ERROR;              \
                                                      \
        MRFMAT_ROW(x) = row;                          \
        MRFMAT_COL(x) = col;                          \
        return MRFMAT_RES_NOERROR;                    \
    } while (0)

#define MRFMAT_CLEAR_REALLOC(x, row, col, size)         \
    do                                                  \
    {                                                   \
        free(MRFMAT_DATA(mat));                         \
                                                        \
        MRFMAT_DATA(mat) = (mrfmat_data_t)malloc(size); \
        if (!MRFMAT_DATA(mat))                          \
        {                                               \
            MRFMAT_ROW(mat) = 0;                        \
            MRFMAT_COL(mat) = 0;                        \
            return MRFMAT_RES_MEM_ERROR;                \
        }                                               \
                                                        \
        MRFMAT_ROW(mat) = row;                          \
        MRFMAT_COL(mat) = col;                          \
        return MRFMAT_RES_NOERROR;                      \
    } while (0)

#define MRFMAT_FREE(x)        \
    do                        \
    {                         \
        free(MRFMAT_DATA(x)); \
                              \
        MRFMAT_ROW(x) = 0;    \
        MRFMAT_COL(x) = 0;    \
    } while (0)

mrfmat_byte_t mrfmat_sizeof_cell(mrfmat_type_t type);

#endif
