#pragma once

#include "chunks.h"
#include "enums.h"
#include "garbagecollector.h"
#include "HksCompilerSettings.h"
#include "lua_Debug.h"
#include "types.h"
#include "hksobject.h"
#include "memorymanager.h"
#include "runtimeprofiledata.h"

struct lua_State;



namespace hks
{
	typedef void (*HksLogFunc)(lua_State*, const char*, ...);
	typedef void (*HksEmergencyGCFailFunc)(lua_State*, size_t);

	struct HksGlobal
	{
		MemoryManager m_memory;
		GarbageCollector m_collector;
		StringTable m_stringTable;
		__int64 padding3;
		HksBytecodeSharingMode m_bytecodeSharingMode;
		int padding;
		HksObject m_registry;
		ChunkList m_userDataList;
		lua_State* m_root;
		StaticStringCache m_staticStringCache;
		DebugInstance* m_debugger;
		void* m_profiler;
		RuntimeProfileData m_runProfilerData;
		HksCompilerSettings m_compilerSettings;
		lua_CFunction m_panicFunction;
		void* m_luaplusObjectList;
		int m_heapAssertionFrequency;
		int m_heapAssertionCount;
		HksLogFunc m_logFunction;
		HksEmergencyGCFailFunc m_emergencyGCFailFunction;
		HksBytecodeEndianness m_bytecodeDumpEndianness;
		int padding2;
	};

	struct ApiStack
	{
		HksObject* top;
		HksObject* base;
		HksObject* alloc_top;
		HksObject* bottom;
	};

	struct CallStack
	{
		struct ActivationRecord
		{
			HksObject* m_base;
			const hksInstruction* m_returnAddress;
			hksShort16 m_tailCallDepth;
			hksShort16 m_numVarargs;
			hksInt32 m_numExpectedReturns;
		};

		ActivationRecord* m_records;
		ActivationRecord* m_lastrecord;
		ActivationRecord* m_current;
		const hksInstruction* m_current_lua_pc;
		const hksInstruction* m_hook_return_addr;
		hksInt32 m_hook_level;
		hksInt32 padding;
	};

	struct CallSite
	{
		_jmp_buf m_jumpBuffer;
		CallSite* m_prev;
	};
	typedef CallSite* ErrorHandler;
}

typedef struct luaL_Reg
{
	const char* name;
	lua_CFunction func;
} luaL_Reg;

struct lua_State
{
	enum Status : __int32
	{
		NEW = 0x1,
		RUNNING = 0x2,
		YIELDED = 0x3,
		DEAD_ERROR = 0x4,
	};

	hks::ChunkHeader baseclass;
	hks::HksGlobal* m_global;
	hks::CallStack m_callStack;
	hks::ApiStack m_apistack;
	hks::UpValue* pending;
	HksObject globals;
	HksObject m_cEnv;
	hks::ErrorHandler m_callsites;
	hksInt32 m_numberOfCCalls;
	void* m_context;
	hks::InternString* m_name;
	lua_State* m_next;
	lua_State* m_nextStateStack;
	Status m_status;
	HksError m_error;
	hks::DebugHook m_debugHook;
};

struct LUIPoolUserData
{
	unsigned __int16 poolIndex;
	unsigned __int16 iteration;
};

struct OpenedMenuData
{
	int nameHash;
	LUIPoolUserData menuElementPoolData;
	char name[32];
};