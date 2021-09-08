#pragma once
#include "lua_CFunction.h"
#include "types.h"

struct hksInstruction
{
	hksBytecodeInstruction code;
};

struct lua_Debug
{
	hksInt32 event;
	const char* name;
	const char* namewhat;
	const char* what;
	const char* source;
	hksInt32 currentline;
	hksInt32 nups;
	hksInt32 nparams;
	hksBool ishksfunc;
	hksInt32 linedefined;
	hksInt32 lastlinedefined;
	char short_src[512];
	hksInt32 callstack_level;
	hksBool is_tail_call;
};


namespace hks
{

	struct DebugHook
	{
		lua_Hook m_callback;
		hksInt32 m_mask;
		hksInt32 m_count;
		hksInt32 m_counter;
		bool m_inuse;
		const hksInstruction* m_prevPC;
	};

	struct DebugInstance
	{
		struct RuntimeProfilerStats
		{
			hksInt32 hksTime;
			hksInt32 callbackTime;
			hksInt32 gcTime;
			hksInt32 cFinalizerTime;
			hksInt64 heapSize;
			hksInt64 num_newuserdata;
			hksInt64 num_pushstring;
		};

		int m_savedObjects;
		int m_keepAliveObjects;
		lua_State* m_activeState;
		lua_State* m_mainState;
		void* m_owner;
		hksInt32 m_DebuggerLevel;
		hksInt32 stored_Hook_level;
		bool m_clearHook;
		const hksInstruction* stored_Hook_return_addr;
		hksInt32 m_debugStepLastLine;
		DebugInstance* m_next;
		const hksInstruction* m_activePC;
		hksInt32 runtimeProfileSendBufferWritePosition;
		RuntimeProfilerStats runtimeProfileSendBuffer[30];
	};
};