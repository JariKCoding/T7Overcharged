#pragma once
#include "types.h"


namespace hks
{
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
}
