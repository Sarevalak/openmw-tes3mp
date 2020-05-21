#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/effectlist.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LENAMstruct
	{
	public:
		LENAMstruct(ENAMstruct &data) {
			this->data = data;
		}
		LENAMstruct() {
            this->data = {};
		}
		~LENAMstruct() {
		}
        int getEffectID() const {
			return this->data.mEffectID;
		}
        int getSkill() const {
			return this->data.mSkill;
		}
        int getAttribute() const {
			return this->data.mAttribute;
		}
		int getRange() const {
			return this->data.mRange;
		}
		int getArea() const {
			return this->data.mArea;
		}
		int getDuration() const {
			return this->data.mDuration;
		}
		int getMagnMin() const {
			return this->data.mMagnMin;
		}
		int getMagnMax() const {
			return this->data.mMagnMax;
		}
	private:
		ENAMstruct data;
    };
}

