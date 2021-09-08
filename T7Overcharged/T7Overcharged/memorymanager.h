#pragma once
#include "types.h"


namespace hks
{
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
}
