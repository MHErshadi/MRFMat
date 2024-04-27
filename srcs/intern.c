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

mrfmat_byte_t mrfmat_sizeof_cell(mrfmat_type_t type)
{
    switch (type)
    {
    case MRFMAT_TYPES_INT8:
    case MRFMAT_TYPES_UINT8:
        return 1;
    case MRFMAT_TYPES_INT16:
    case MRFMAT_TYPES_UINT16:
    case MRFMAT_TYPES_DEC16:
        return 2;
    case MRFMAT_TYPES_INT32:
    case MRFMAT_TYPES_UINT32:
    case MRFMAT_TYPES_DEC32:
        return 4;
    case MRFMAT_TYPES_INT64:
    case MRFMAT_TYPES_UINT64:
    case MRFMAT_TYPES_DEC64:
        return 8;
    }

    return 0;
}
