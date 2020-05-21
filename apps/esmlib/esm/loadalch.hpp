#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadalch.hpp>

#include "esm/esmreader.hpp"
#include "esm/effectlist.hpp"

using namespace luabridge;

namespace ESM
{

/*
 * Alchemy item (potions)
 */

class LPotion
{
	public:
		LPotion() {
		}
		~LPotion() {
		}
		unsigned int getRecordId() const {
			return this->potion.sRecordId;
		}
		std::string getRecordType() const {
			return this->potion.getRecordType();
		}
		float getWeight() const {
            return this->potion.mData.mWeight;
		}
		int getValue() const {
            return this->potion.mData.mValue;
		}
		int getAutoCalc() const {
            return this->potion.mData.mAutoCalc;
		}
		std::string getId() const {
			return this->potion.mId;
		}
		std::string getName() const {
			return this->potion.mName;
		}
		std::string getModel() const {
			return this->potion.mModel;
		}
		std::string getIcon() const {
			return this->potion.mIcon;
		}
		std::string getScript() const {
			return this->potion.mScript;
		}
        int getEffects(lua_State* L) {
			LuaRef table = newTable(L);
            std::vector<ENAMstruct> vec = this->potion.mEffects.mList;
            for (auto i = vec.begin(); i != vec.end(); i++) {
                table.append(RefCountedPtr<LENAMstruct>(new LENAMstruct(*i)));
            }
            push(L, table);
            return 1;
		}
		void load(LESMReader* esm, bool isDeleted) {
			this->potion.load(*esm->getReader(), isDeleted);
		}
	private:
		Potion potion;
    };
}
