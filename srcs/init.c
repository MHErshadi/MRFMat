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
    mrfmat_t mat, mrfmat_type_t type)
{
    MRFMAT_SIZE(mat) = 0;
    MRFMAT_CAPA(mat) = 0;
    MRFMAT_TYPE(mat) = type;
}

void mrfmat_inits(
    mrfmat_type_t type, mrfmat_p mat, ...)
{
    va_list mats;

    va_start(mats, mat);
    do
    {
        MRFMAT_SIZE(mat) = 0;
        MRFMAT_CAPA(mat) = 0;
        MRFMAT_TYPE(mat) = type;

        mat = va_arg(mats, mrfmat_p);
    } while (mat);
    va_end(mats);
}

void mrfmat_free(
    mrfmat_t mat)
{
    if (MRFMAT_CAPA(mat))
        free(MRFMAT_DATA(mat));
}

void mrfmat_frees(
    mrfmat_p mat, ...)
{
    va_list mats;

    va_start(mats, mat);
    do
    {
        if (MRFMAT_CAPA(mat))
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
