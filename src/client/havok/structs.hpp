#pragma once

namespace lua
{
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
	struct lua_State;

	typedef hksUint32 hksBytecodeInstruction;
	typedef hksUint32 HksNativeValueAsInt;
	typedef void* (*lua_Alloc)(void*, void*, size_t, size_t);
	typedef int (*hks_debug_map)(const char*, int);
	typedef hksInt32(*lua_CFunction)(lua_State*);
	struct lua_Debug;
	typedef void (*lua_Hook)(lua_State*, lua_Debug*);

	enum HksError : __int32
	{
		HKS_NO_ERROR = 0x0,
		LUA_ERRSYNTAX = -1,
		LUA_ERRFILE = -2,
		LUA_ERRRUN = -3,
		LUA_ERRMEM = -4,
		LUA_ERRERR = -5,
		HKS_THROWING_ERROR = -6,
		HKS_GC_YIELD = 0x1,
	};

	enum HksBytecodeEndianness : __int32
	{
		HKS_BYTECODE_DEFAULT_ENDIAN = 0x0,
		HKS_BYTECODE_BIG_ENDIAN = 0x1,
		HKS_BYTECODE_LITTLE_ENDIAN = 0x2,
	};

	enum HksBytecodeSharingMode : __int64
	{
		HKS_BYTECODE_SHARING_OFF = 0,
		HKS_BYTECODE_SHARING_ON = 1,
		HKS_BYTECODE_SHARING_SECURE = 2
	};

	enum HksObjectType : __int32
	{
		TANY = -2,
		TNONE = -1,
		TNIL = 0x0,
		TBOOLEAN = 0x1,
		TLIGHTUSERDATA = 0x2,
		TNUMBER = 0x3,
		TSTRING = 0x4,
		TTABLE = 0x5,
		TFUNCTION = 0x6,
		TUSERDATA = 0x7,
		TTHREAD = 0x8,
		TIFUNCTION = 0x9,
		TCFUNCTION = 0xA,
		TUI64 = 0xB,
		TSTRUCT = 0xC,
		NUM_TYPE_OBJECTS = 0xE,
	};

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

	struct GenericChunkHeader
	{
		hksSize m_flags;
	};

	struct ChunkHeader : GenericChunkHeader
	{
		ChunkHeader* m_next;
	};

	struct ChunkList
	{
		ChunkHeader m_head;
	};

	struct InternString : GenericChunkHeader
	{
		hksSize m_lengthbits;
		hksUint32 m_hash;
		char m_data[30];
		char padding[6];
	};

	struct StructInst;
	struct cclosure;
	struct HksClosure;
	struct HashTable;
	struct UserData;
	struct StructInst;
	struct InternString;

	union HksValue
	{
		cclosure* cClosure;
		HksClosure* closure;
		UserData* userData;
		HashTable* table;
		StructInst* tstruct;
		InternString* str;
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

	struct hksInstruction
	{
		hksBytecodeInstruction code;
	};

	struct UserData : ChunkHeader
	{
		HashTable* m_env;
		Metatable* m_meta;
		char m_data[8];
	};

	struct RuntimeProfileData
	{
		struct Stats
		{
			hksUint64 hksTime;
			hksUint64 callbackTime;
			hksUint64 gcTime;
			hksUint64 cFinalizerTime;
			hksUint64 compilerTime;
			hksUint32 hkssTimeSamples;
			hksUint32 callbackTimeSamples;
			hksUint32 gcTimeSamples;
			hksUint32 compilerTimeSamples;
			hksUint32 num_newuserdata;
			hksUint32 num_tablerehash;
			hksUint32 num_pushstring;
			hksUint32 num_pushcfunction;
			hksUint32 num_newtables;
			int padding;
		};

		hksInt64 stackDepth;
		hksInt64 callbackDepth;
		hksUint64 lastTimer;
		Stats frameStats;
		hksUint64 gcStartTime;
		hksUint64 finalizerStartTime;
		hksUint64 compilerStartTime;
		hksUint64 compilerStartGCTime;
		hksUint64 compilerStartGCFinalizerTime;
		hksUint64 compilerCallbackStartTime;
		hksInt64 compilerDepth;
		void* outFile;
		lua_State* rootState;
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

	typedef void (*HksLogFunc)(lua_State*, const char*, ...);
	typedef void (*HksEmergencyGCFailFunc)(lua_State*, size_t);

	struct MemoryManager
	{
		enum ChunkColor : __int32
		{
			WHITE = 0x0,
			BLACK = 0x1,
		};

		lua_Alloc m_allocator;
		void* m_allocatorUd;
		ChunkColor m_chunkColor;
		hksSize m_used;
		hksSize m_highwatermark;
		ChunkList m_allocationList;
		ChunkList m_sweepList;
		ChunkHeader* m_lastKeptChunk;
		lua_State* m_state;
	};

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
		void* m_jumpPoint;
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

	enum LuaStateStatus : __int32
	{
		NEW = 0x1,
		RUNNING = 0x2,
		YIELDED = 0x3,
		DEAD_ERROR = 0x4,
	};

	struct lua_State
	{
		enum Status : __int32
		{
			NEW = 0x1,
			RUNNING = 0x2,
			YIELDED = 0x3,
			DEAD_ERROR = 0x4,
		};

		ChunkHeader baseclass;
		HksGlobal* m_global;
		CallStack m_callStack;
		ApiStack m_apistack;
		UpValue* pending;
		HksObject globals;
		HksObject m_cEnv;
		ErrorHandler m_callsites;
		hksInt32 m_numberOfCCalls;
		void* m_context;
		InternString* m_name;
		lua_State* m_next;
		lua_State* m_nextStateStack;
		Status m_status;
		HksError m_error;
		DebugHook m_debugHook;
	};

	typedef hksInt32(*lua_CFunction)(lua_State*);

	typedef struct luaL_Reg
	{
		const char* name;
		lua_CFunction func;
	} luaL_Reg;
}


