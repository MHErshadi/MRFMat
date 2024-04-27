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

#include <mrfmat-intern.h>
#include <stdarg.h>

void mrfmat_init(
    mrfmat_t mat, mrfmat_type_t type, mrfmat_bool_t row_major)
{
    MRFMAT_DATA(mat) = NULL;
    MRFMAT_ROW(mat) = 0;
    MRFMAT_COL(mat) = 0;
    MRFMAT_TYPE(mat) = type;
    MRFMAT_ROW_MAJOR(mat) = row_major;
}

void mrfmat_inits(
    mrfmat_type_t type, mrfmat_bool_t row_major, mrfmat_p mat, ...)
{
    va_list mats;

    va_start(mats, mat);
    do
    {
        MRFMAT_DATA(mat) = NULL;
        MRFMAT_ROW(mat) = 0;
        MRFMAT_COL(mat) = 0;
        MRFMAT_TYPE(mat) = type;
        MRFMAT_ROW_MAJOR(mat) = row_major;

        mat = va_arg(mats, mrfmat_p);
    } while (mat);
    va_end(mats);
}

void mrfmat_init2(
    mrfmat_t mat, mrfmat_data_t data, mrfmat_size_t row, mrfmat_size_t col, mrfmat_type_t type, mrfmat_bool_t row_major)
{
    MRFMAT_DATA(mat) = data;
    MRFMAT_ROW(mat) = row;
    MRFMAT_COL(mat) = col;
    MRFMAT_TYPE(mat) = type;
    MRFMAT_TYPE(mat) = row_major;
}

mrfmat_res_t mrfmat_init_alloc(
    mrfmat_t mat, mrfmat_type_t type, mrfmat_bool_t row_major, mrfmat_size_t row, mrfmat_size_t col)
{
    mrfmat_size_t size;

    MRFMAT_TYPE(mat) = type;
    MRFMAT_ROW_MAJOR(mat) = row_major;

    size = row * col;
    if (!size)
    {
        MRFMAT_DATA(mat) = NULL;
        MRFMAT_ROW(mat) = 0;
        MRFMAT_COL(mat) = 0;
        return MRFMAT_RES_NOERROR;
    }

    if (type == MRFMAT_TYPES_BOOL)
        size = (size + 7) >> 3;
    else
        size *= mrfmat_sizeof_cell(type);

    MRFMAT_ALLOC(mat, row, col, size);
}

mrfmat_res_t mrfmat_alloc(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col)
{
    mrfmat_size_t size;

    size = row * col;
    if (!size)
        return MRFMAT_RES_NOERROR;

    if (MRFMAT_TYPE(mat) == MRFMAT_TYPES_BOOL)
        size = (size + 7) >> 3;
    else
        size *= mrfmat_sizeof_cell(MRFMAT_TYPE(mat));

    MRFMAT_ALLOC(mat, row, col, size);
}

void mrfmat_free(
    mrfmat_t mat)
{
    free(MRFMAT_DATA(mat));
}

void mrfmat_frees(
    mrfmat_p mat, ...)
{
    va_list mats;

    va_start(mats, mat);
    do
    {
        free(MRFMAT_DATA(mat));
        mat = va_arg(mats, mrfmat_p);
    } while (mat);
    va_end(mats);
}

void mrfmat_clear(
    mrfmat_t mat)
{
    MRFMAT_FREE(mat);
}

void mrfmat_clears(
    mrfmat_p mat, ...)
{
    va_list mats;

    va_start(mats, mat);
    do
    {
        MRFMAT_FREE(mat);
        mat = va_arg(mats, mrfmat_p);
    } while (mat);
    va_end(mats);
}

mrfmat_res_t mrfmat_clear_realloc(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col)
{
    mrfmat_size_t size;

    size = row * col;
    if (size == MRFMAT_ROW(mat) * MRFMAT_COL(mat))
        return MRFMAT_RES_NOERROR;

    if (!size)
    {
        MRFMAT_FREE(mat);
        return MRFMAT_RES_NOERROR;
    }

    if (MRFMAT_TYPE(mat) == MRFMAT_TYPES_BOOL)
        size = (size + 7) >> 3;
    else
        size *= mrfmat_sizeof_cell(MRFMAT_TYPE(mat));

    MRFMAT_CLEAR_REALLOC(mat, row, col, size);
}

mrfmat_res_t mrfmat_clear_expand(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col)
{
    mrfmat_size_t size;

    size = row * col;
    if (MRFMAT_TYPE(mat) == MRFMAT_TYPES_BOOL)
        size = (size + 7) >> 3;
    else
        size *= mrfmat_sizeof_cell(MRFMAT_TYPE(mat));

    MRFMAT_CLEAR_REALLOC(mat, row, col, size);
}

mrfmat_res_t mrfmat_clear_shrink(
    mrfmat_t mat, mrfmat_size_t row, mrfmat_size_t col)
{
    mrfmat_size_t size;

    size = row * col;
    if (!size)
    {
        MRFMAT_FREE(mat);
        return MRFMAT_RES_NOERROR;
    }

    if (MRFMAT_TYPE(mat) == MRFMAT_TYPES_BOOL)
        size = (size + 7) >> 3;
    else
        size *= mrfmat_sizeof_cell(MRFMAT_TYPE(mat));

    MRFMAT_CLEAR_REALLOC(mat, row, col, size);
}

void mrfmat_swap(
    mrfmat_t mat1, mrfmat_t mat2)
{
    mrfmat_data_t data;
    mrfmat_size_t size;
    mrfmat_type_t type;
    mrfmat_bool_t row_major;

    data = MRFMAT_DATA(mat1);
    MRFMAT_DATA(mat1) = MRFMAT_DATA(mat2);
    MRFMAT_DATA(mat2) = data;

    size = MRFMAT_ROW(mat1);
    MRFMAT_ROW(mat1) = MRFMAT_ROW(mat2);
    MRFMAT_ROW(mat2) = size;

    size = MRFMAT_COL(mat1);
    MRFMAT_COL(mat1) = MRFMAT_COL(mat2);
    MRFMAT_COL(mat2) = size;

    type = MRFMAT_TYPE(mat1);
    MRFMAT_TYPE(mat1) = MRFMAT_TYPE(mat2);
    MRFMAT_TYPE(mat2) = type;

    row_major = MRFMAT_ROW_MAJOR(mat1);
    MRFMAT_ROW_MAJOR(mat1) = MRFMAT_ROW_MAJOR(mat2);
    MRFMAT_ROW_MAJOR(mat2) = row_major;
}
