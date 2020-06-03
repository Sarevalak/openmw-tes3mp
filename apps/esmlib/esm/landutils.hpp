#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <algorithm>

#include <osg/Image>
#include <osg/Plane>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadland.hpp>
#include <components/esm/esmcommon.hpp>
#include <components/misc/constants.hpp>

#include "esm/esmreader.hpp"
#include "esm/esmcommon.hpp"
#include "esm/loadland.hpp"

using namespace luabridge;

namespace ESM
{
    class LLandUtils
    {
        public:
            LLandUtils() { }
            ~LLandUtils() { }
            /** 
             * LandData must be loaded
             */
			static int getVtexIndexAt(LLand* lland, float x, float y) {
				int cellX = static_cast<int>(std::floor(x / float(Constants::CellSizeInUnits)));
				int cellY = static_cast<int>(std::floor(y / float(Constants::CellSizeInUnits)));
				
				const Land* land = lland->getLand();
				if (!land || !land->isDataLoaded(ESM::Land::DATA_VTEX))
					return 0;

                const ESM::Land::LandData* data = land->getLandData();
				if (!data)
					return 0;
				
				// Normalized position in the cell
				float nX = (x - (cellX * Constants::CellSizeInUnits)) / float(Constants::CellSizeInUnits);
				float nY = (y - (cellY * Constants::CellSizeInUnits)) / float(Constants::CellSizeInUnits);
				
				int texX = std::min((int) std::floor(nX * ESM::Land::LAND_TEXTURE_SIZE), ESM::Land::LAND_TEXTURE_SIZE - 1);
				int texY = std::min((int) std::floor(nY * ESM::Land::LAND_TEXTURE_SIZE), ESM::Land::LAND_TEXTURE_SIZE - 1);
				
				return data->mTextures[texX + texY * ESM::Land::LAND_TEXTURE_SIZE];
			}

            /**
             * Copied from components/esmterrain/storage.hpp getHeightAt
             * LandData must be loaded
             */
            static float getVertexHeight(const ESM::Land::LandData* data, int x, int y)
            {
                assert(x < ESM::Land::LAND_SIZE);
                assert(y < ESM::Land::LAND_SIZE);
                return data->mHeights[y * ESM::Land::LAND_SIZE + x];
            }
			
            static int getCellX(float x) {
                return static_cast<int>(std::floor(x / float(Constants::CellSizeInUnits)));
            }

            static int getCellY(float y) {
                return static_cast<int>(std::floor(y / float(Constants::CellSizeInUnits)));
            }

			/**
			 * Copied from components/esmterrain/storage.cpp getHeightAt
             * LandData must be loaded
			 */
            static float getHeightAt(LLand* lland, float x, float y, float z) {
                int cellX = getCellX(x);
                int cellY = getCellY(y);

                const Land* land = lland->getLand();
				if (!land || !land->isDataLoaded(ESM::Land::DATA_VHGT))
					return ESM::Land::DEFAULT_HEIGHT;

				const ESM::Land::LandData* data = land->getLandData();
				if (!data)
					return ESM::Land::DEFAULT_HEIGHT;

				// Mostly lifted from Ogre::Terrain::getHeightAtTerrainPosition

				// Normalized position in the cell
				float nX = (x - (cellX * Constants::CellSizeInUnits)) / float(Constants::CellSizeInUnits);
				float nY = (y - (cellY * Constants::CellSizeInUnits)) / float(Constants::CellSizeInUnits);

				// get left / bottom points (rounded down)
				float factor = ESM::Land::LAND_SIZE - 1.0f;
				float invFactor = 1.0f / factor;

				int startX = static_cast<int>(nX * factor);
				int startY = static_cast<int>(nY * factor);
				int endX = startX + 1;
				int endY = startY + 1;

				endX = std::min(endX, ESM::Land::LAND_SIZE-1);
				endY = std::min(endY, ESM::Land::LAND_SIZE-1);

				// now get points in terrain space (effectively rounding them to boundaries)
				float startXTS = startX * invFactor;
				float startYTS = startY * invFactor;
				float endXTS = endX * invFactor;
				float endYTS = endY * invFactor;

				// get parametric from start coord to next point
				float xParam = (nX - startXTS) * factor;
				float yParam = (nY - startYTS) * factor;

				/* For even / odd tri strip rows, triangles are this shape:
				even     odd
				3---2   3---2
				| / |   | \ |
				0---1   0---1
				*/

				// Build all 4 positions in normalized cell space, using point-sampled height
				osg::Vec3f v0 (startXTS, startYTS, getVertexHeight(data, startX, startY) / float(Constants::CellSizeInUnits));
				osg::Vec3f v1 (endXTS, startYTS, getVertexHeight(data, endX, startY) / float(Constants::CellSizeInUnits));
				osg::Vec3f v2 (endXTS, endYTS, getVertexHeight(data, endX, endY) / float(Constants::CellSizeInUnits));
				osg::Vec3f v3 (startXTS, endYTS, getVertexHeight(data, startX, endY) / float(Constants::CellSizeInUnits));
				// define this plane in terrain space
				osg::Plane plane;
				// FIXME: deal with differing triangle alignment
				if (true)
				{
					// odd row
					bool secondTri = ((1.0 - yParam) > xParam);
					if (secondTri)
						plane = osg::Plane(v0, v1, v3);
					else
						plane = osg::Plane(v1, v2, v3);
				}
				/*
				else
				{
					// even row
					bool secondTri = (yParam > xParam);
					if (secondTri)
						plane.redefine(v0, v2, v3);
					else
						plane.redefine(v0, v1, v2);
				}
				*/

				// Solve plane equation for z
				return (-plane.getNormal().x() * nX
						-plane.getNormal().y() * nY
						- plane[3]) / plane.getNormal().z() * Constants::CellSizeInUnits;

            }
    };
}
