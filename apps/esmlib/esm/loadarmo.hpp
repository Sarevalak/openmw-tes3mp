#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadarmo.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{

	class LPartReference
	{
		public:
			LPartReference(PartReference &data) {
				this->data = data;
			}
			LPartReference() {
				this->data = {};
			}
			~LPartReference() {
			}
			int getPart() const {
				return this->data.mPart;
			}
            std::string getMale() const {
				return this->data.mMale;
			}
            std::string getFemale() const {
				return this->data.mFemale;
			}
		private:
			PartReference data;
    };

	class LArmor
	{
		public:
            LArmor() {
			}
			~LArmor() {
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
			std::string getName() const {
				return this->data.mName;
			}
			std::string getModel() const {
				return this->data.mModel;
			}
			std::string getIcon() const {
				return this->data.mIcon;
			}
			std::string getScript() const {
				return this->data.mScript;
			}
			std::string getEnchantId() const {
				return this->data.mEnchant;
			}
			
			int getType() const {
				return this->data.mData.mType;
			}
            float getWeight() const {
				return this->data.mData.mWeight;
			}
			int getValue() const {
				return this->data.mData.mValue;
			}
			int getHealth() const {
				return this->data.mData.mHealth;
			}
			int getEnchant() const {
				return this->data.mData.mEnchant;
			}
			int getArmor() const {
				return this->data.mData.mArmor;
			}
			
			int getParts(lua_State* L) {
				LuaRef table = newTable(L);
				std::vector<PartReference> vec = this->data.mParts.mParts;
				for (auto i = vec.begin(); i != vec.end(); i++) {
					table.append(RefCountedPtr<LPartReference>(new LPartReference(*i)));
				}
				push(L, table);
				return 1;
			}
			
			void load(LESMReader* esm, bool isDeleted) {
				this->data.load(*esm->getReader(), isDeleted);
			}
		private:
			Armor data;
	};

}

