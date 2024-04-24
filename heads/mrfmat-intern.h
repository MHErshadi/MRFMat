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

#define MRFMAT_FREE(x)            \
    do                            \
    {                             \
        if (MRFMAT_CAPA(x))       \
        {                         \
            free(MRFMAT_DATA(x)); \
                                  \
            MRFMAT_SIZE(x) = 0;   \
            MRFMAT_CAPA(x) = 0;   \
        }                         \
    } while (0)

#endif
