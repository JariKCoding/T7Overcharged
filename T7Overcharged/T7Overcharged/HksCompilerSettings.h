#pragma once
#include "types.h"

int hks_identity_map(const char* filename, int lua_line);

struct HksCompilerSettings
{
    enum BytecodeSharingFormat : __int32
    {
        BYTECODE_DEFAULT = 0x0,
        BYTECODE_INPLACE = 0x1,
        BYTECODE_REFERENCED = 0x2,
    };


    enum IntLiteralOptions : __int32
    {
        INT_LITERALS_NONE = 0x0,
        INT_LITERALS_LUD = 0x1,
        INT_LITERALS_32BIT = 0x1,
        INT_LITERALS_UI64 = 0x2,
        INT_LITERALS_64BIT = 0x2,
        INT_LITERALS_ALL = 0x3,
    };

    hksBool m_emitStructCode = 0;
    int padding;
    const hksChar** m_stripNames = 0;
    BytecodeSharingFormat m_bytecodeSharingFormat = BYTECODE_INPLACE;
    IntLiteralOptions m_enableIntLiterals = INT_LITERALS_NONE;

    hks_debug_map m_debugMap = hks_identity_map;
};
