#pragma once
#include "types.h"

namespace hks
{
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
}
