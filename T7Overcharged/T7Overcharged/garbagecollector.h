#pragma once
#include <csetjmp>

#include "hksobject.h"
#include "lstate.h"
#include "memorymanager.h"


namespace hks
{
	typedef int HksGcCost;

	struct HksGcWeights
	{
		HksGcCost m_removeString;
		HksGcCost m_finalizeUserdataNoMM;
		HksGcCost m_finalizeUserdataGcMM;
		HksGcCost m_cleanCoroutine;
		HksGcCost m_removeWeak;
		HksGcCost m_markObject;
		HksGcCost m_traverseString;
		HksGcCost m_traverseUserdata;
		HksGcCost m_traverseCoroutine;
		HksGcCost m_traverseWeakTable;
		HksGcCost m_freeChunk;
		HksGcCost m_sweepTraverse;
	};

	struct ResumeData_Header
	{
		HksObjectType m_type;
	};

	enum GCResumePhase : __int32
	{
		GC_STATE_MARKING_UPVALUES = 0x0,
		GC_STATE_MARKING_GLOBAL_TABLE = 0x1,
		GC_STATE_MARKING_REGISTRY = 0x2,
		GC_STATE_MARKING_PROTOTYPES = 0x3,
		GC_STATE_MARKING_SCRIPT_PROFILER = 0x4,
		GC_STATE_MARKING_FINALIZER_STATE = 0x5,
		GC_TABLE_MARKING_ARRAY = 0x6,
		GC_TABLE_MARKING_HASH = 0x7,
	};

	struct ResumeData_State
	{
		ResumeData_Header h;
		int padding;
		lua_State* m_state;
		GCResumePhase m_phase;
		int padding2;
		UpValue* m_pending;
	};

	struct ResumeData_Table
	{
	  ResumeData_Header h;
	  int padding;
	  HashTable* m_table;
	  hksUint32 m_arrayIndex;
	  hksUint32 m_hashIndex;
	  hksInt32 m_weakness;
	  int padding2;
	};

	struct ResumeData_Closure
	{
	  ResumeData_Header h;
	  int padding;
	  HksClosure* m_closure;
	  hksInt32 m_index;
	  int padding2;
	};

	struct ResumeData_CClosure
	{
	  ResumeData_Header h;
	  int padding;
	  cclosure* m_cclosure;
	  hksInt32 m_upvalueIndex;
	  int padding2;
	};

	/* 2620 */
	struct ResumeData_Userdata
	{
		ResumeData_Header h;
		int padding;
		UserData* m_data;
	};

	union ResumeData_Entry
	{
		ResumeData_State State;
		ResumeData_Table HashTable;
		ResumeData_Closure Closure;
		ResumeData_CClosure CClosure;
		ResumeData_Userdata Userdata;
	};

	struct GarbageCollector
	{
		struct ResumeStack
		{
			ResumeData_Entry* m_storage;
			hksInt32 m_numEntries;
			hksUint32 m_numAllocated;
		};

		struct GreyStack
		{
			HksObject* m_storage;
			hksSize m_numEntries;
			hksSize m_numAllocated;
		};

		struct RemarkStack
		{
			HashTable** m_storage;
			hksSize m_numAllocated;
			hksSize m_numEntries;
		};

		struct WeakStack_Entry
		{
			hksInt32 m_weakness;
			HashTable* m_table;
		};

		struct WeakStack
		{
			WeakStack_Entry* m_storage;
			hksInt32 m_numEntries;
			hksUint32 m_numAllocated;
		};

		HksGcCost m_target;
		HksGcCost m_stepsLeft;
		HksGcCost m_stepLimit;
		HksGcWeights m_costs;
		HksGcCost m_unit;
		jmp_buf* m_jumpPoint;
		lua_State* m_mainState;
		lua_State* m_finalizerState;
		MemoryManager* m_memory;
		void* m_emergencyGCMemory;
		hksInt32 m_phase;
		ResumeStack m_resumeStack;
		GreyStack m_greyStack;
		RemarkStack m_remarkStack;
		WeakStack m_weakStack;
		hksBool m_finalizing;
		HksObject m_safeTableValue;
		lua_State* m_startOfStateStackList;
		lua_State* m_endOfStateStackList;
		lua_State* m_currentState;
		HksObject m_safeValue;
		void* m_compiler;
		void* m_bytecodeReader;
		void* m_bytecodeWriter;
		hksInt32 m_pauseMultiplier;
		HksGcCost m_stepMultiplier;
		hksSize m_emergencyMemorySize;
		bool m_stopped;
		lua_CFunction m_gcPolicy;
		hksSize m_pauseTriggerMemoryUsage;
		hksInt32 m_stepTriggerCountdown;
		hksUint32 m_stringTableIndex;
		hksUint32 m_stringTableSize;
		UserData* m_lastBlackUD;
		UserData* m_activeUD;
	};
}
