#include <std_include.hpp>
#include "asset_limits.hpp"
#include "game/game.hpp"

namespace asset_limits
{
	void resize(game::XAssetType type, int newSize)
	{
		auto structSize = game::DB_GetXAssetTypeSize(type);
		auto assetPool = &game::DB_XAssetPool[type];
		// TODO: Support resizing assetPools to be less than current size
		if (assetPool != 0 && assetPool->itemCount < newSize)
		{
			auto newBlock = (game::AssetLink*)calloc(newSize - assetPool->itemCount, structSize);
			if (newBlock != 0)
			{
				game::AssetLink* blockPtr = (game::AssetLink*)assetPool->pool;
				game::AssetLink* nextBlockPtr = newBlock;
				auto size_c = newSize - 1;
				do
				{
					if (!blockPtr->next)
					{
						blockPtr->next = nextBlockPtr;
						blockPtr = nextBlockPtr;
						nextBlockPtr = (game::AssetLink*)((uint8_t*)nextBlockPtr + structSize);
					}
					else
					{
						blockPtr = (game::AssetLink*)((uint8_t*)blockPtr + structSize);
					}
					--size_c;
				} while (size_c);
				assetPool->itemCount = newSize;
			}
		}
	}
}