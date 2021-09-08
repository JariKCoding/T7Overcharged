#pragma once
#include "lua_CFunction.h"
#include "lua_Debug.h"
#include "types.h"

namespace hks
{
	struct cclosure;
	struct HksClosure;
	struct HashTable;
	struct UserData;
	struct StructInst;
	struct InternString;
}

extern struct lua_State;

union HksValue
{
	hks::cclosure* cClosure;
	hks::HksClosure* closure;
	hks::UserData* userData;
	hks::HashTable* table;
	hks::StructInst* tstruct;
	hks::InternString* str;
	lua_State* thread;
	void* ptr;
	HksNumber number;
	HksNativeValueAsInt native;
	hksInt32 boolean;
};

typedef struct HksObject
{
	hksUint32 t;
	HksValue v;
} HksObject;

typedef HksObject HksRegister;

namespace hks
{
	struct StringPinner
	{
		struct Node
		{
			InternString* m_strings[32];
			Node* m_prev;
		};

		lua_State* const m_state;
		StringPinner* const m_prev;
		InternString** m_nextStringsPlace;
		Node m_firstNode;
		Node* m_currentNode;
	};

	struct StringTable
	{
		InternString** m_data;
		hksUint32 m_count;
		hksUint32 m_mask;
		StringPinner* m_pinnedStrings;
	};

	struct StructInst;

	struct InternString : GenericChunkHeader
	{
	  hksSize m_lengthbits;
	  hksUint32 m_hash;
	  char m_data[30];
	  char padding[6];
	};

	struct Metatable
	{
		__int8 gap0[1];
	};

	struct HashTable : ChunkHeader
	{
		struct Node
		{
			HksRegister m_key;
			HksRegister m_value;
		};

		Metatable* m_meta;
		hksUint32 m_mask;
		Node* m_hashPart;
		HksRegister* m_arrayPart;
		hksUint32 m_arraySize;
		Node* m_freeNode;
	};

	struct StaticStringCache
	{
		HksObject m_objects[42];
	};

	struct UserData : ChunkHeader
	{
		HashTable* m_env;
		Metatable* m_meta;
		char m_data[8];
	};

	struct cclosure : ChunkHeader
	{
		lua_CFunction m_function;
		HashTable* m_env;
		hksShort16 m_numUpvalues;
		hksShort16 m_flags;
		InternString* m_name;
		HksObject m_upvalues[1];
	};

	struct UpValue : ChunkHeader
	{
		HksObject m_storage;
		HksObject* loc;
		UpValue* m_next;
	};

	struct Method : ChunkHeader
	{
		struct hksInstructionArray
		{
			hksUint32 size;
			const hksInstruction* data;
		};

		struct HksObjectArray
		{
			hksUint32 size;
			HksObject* data;
		};

		struct MethodArray
		{
			hksUint32 size;
			Method** data;
		};

		struct LocalInfo
		{
			InternString* name;
			hksInt32 start_pc;
			hksInt32 end_pc;
		};

		struct hksUint32Array
		{
			hksUint32 size;
			unsigned int* data;
		};

		struct LocalInfoArray
		{
			hksUint32 size;
			LocalInfo* data;
		};

		struct InternStringArray
		{
			hksUint32 size;
			InternString** data;
		};

		typedef hksInstructionArray Instructions;
		typedef HksObjectArray Constants;
		typedef MethodArray Children;
		typedef LocalInfoArray Locals;
		typedef hksUint32Array LineInfo;
		typedef InternStringArray UpValueInfo;

		struct DebugInfo
		{
		  hksUint32 line_defined;
		  hksUint32 last_line_defined;
		  LineInfo lineInfo;
		  UpValueInfo upvalInfo;
		  InternString* source;
		  InternString* name;
		  Locals localInfo;
		};

		hksUint32 hash;
		hksUshort16 num_upvals;
		hksUshort16 m_numRegisters;
		hksByte num_params;
		hksByte m_flags;
		Instructions instructions;
		Constants constants;
		Children children;
		DebugInfo* m_debug;
	};

	struct HksClosure : ChunkHeader
	{
		struct MethodCache
		{
			const HksObject* consts;
			const hksInstruction* inst;
			hksUshort16 m_numRegisters;
			hksByte m_flags;
			hksByte num_params;
		};

		Method* m_method;
		HashTable* m_env;
		hksByte m_mayHaveUpvalues;
		MethodCache m_cache;
		UpValue* m_upvalues[1];
	};
}


