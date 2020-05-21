#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadmgef.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{

	class LMagicEffect
	{
	public:
        LMagicEffect() {
		}
		~LMagicEffect() {
		}
		unsigned int getRecordId() const {
			return this->data.sRecordId;
		}
		std::string getRecordType() const {
			return this->data.getRecordType();
		}
		std::string getId() const {
			return this->data.mId;
		}
        std::string effectIdToString(short effectID) {
			return this->data.effectIdToString(effectID);
		}
        short effectStringToId(std::string effect) {
			return this->data.effectStringToId(effect);
		}
        short getResistanceEffect(short effect) {
			return this->data.getResistanceEffect(effect);
		}
        short getWeaknessEffect(short effect) {
			return this->data.getWeaknessEffect(effect);
		}
        int getMagnitudeDisplayType() const {
			return this->data.getMagnitudeDisplayType();
		}
        std::string getHit() const {
            return this->data.mHit;
        }
        std::string getArea() const {
            return this->data.mArea;
        }
        std::string getCasting() const {
            return this->data.mCasting;
        }
        std::string getIcon() const {
            return this->data.mIcon;
        }
        std::string getParticle() const {
            return this->data.mParticle;
        }
        std::string getBolt() const {
            return this->data.mBolt;
        }
        std::string getCastSound() const {
            return this->data.mCastSound;
        }
        std::string getBoltSound() const {
            return this->data.mBoltSound;
        }
        std::string getHitSound() const {
            return this->data.mHitSound;
        }
        std::string getAreaSound() const {
            return this->data.mAreaSound;
        }
        std::string getDescription() const {
            return this->data.mDescription;
        }
        int getIndex() const {
            return this->data.mIndex;
        }
        int getSchool() const {
            return this->data.mData.mSchool;
        }
        float getBaseCost() const {
            return this->data.mData.mBaseCost;
        }
        int getFlags() const {
            return this->data.mData.mFlags;
        }
        int getRed() const {
            return this->data.mData.mRed;
        }
        int getGreen() const {
            return this->data.mData.mGreen;
        }
        int getBlue() const {
            return this->data.mData.mBlue;
        }
        std::string indexToId(int index) {
            return this->data.indexToId(index);
        }
		void load(LESMReader* esm, bool isDeleted) {
			this->data.load(*esm->getReader(), isDeleted);
		}
	private:
		MagicEffect data;
	};
}
