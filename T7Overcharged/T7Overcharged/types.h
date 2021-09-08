#pragma once

typedef int hksBool;
typedef char hksChar;
typedef unsigned __int8 hksByte;
typedef __int16 hksShort16;
typedef unsigned __int16 hksUshort16;
typedef float HksNumber;
typedef int hksInt32;
typedef unsigned int hksUint32;
typedef __int64 hksInt64;
typedef unsigned __int64 hksUint64;
typedef size_t hksSize;
typedef int ErrorCode;

struct _jmp_buf
{
	void* _jb[12];
};

typedef hksUint32 hksBytecodeInstruction;
typedef hksUint32 HksNativeValueAsInt;
typedef void* (*lua_Alloc)(void*, void*, size_t, size_t);
typedef int (*hks_debug_map)(const char*, int);

