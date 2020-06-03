#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadcrea.hpp>

#include <components/esm/loadcont.hpp>
#include <components/esm/spelllist.hpp>
#include <components/esm/aipackage.hpp>
#include <components/esm/transport.hpp>

#include "esm/esmreader.hpp"

#include "esm/loadcont.hpp"
#include "esm/transport_dest.hpp"

using namespace luabridge;

namespace ESM
{
    class LCreature
    {
        public:
            LCreature() {
            }
            ~LCreature() {
            }
            unsigned int getRecordId() const {
                return this->data.sRecordId;
            }
            std::string getRecordType() const {
                return this->data.getRecordType();
            }
            int getType() const {
                return this->data.mData.mType;
            }
            int getLevel() const {
                return this->data.mData.mLevel;
            }
            int getStrength() const {
                return this->data.mData.mStrength;
            }
            int getIntelligence() const {
                return this->data.mData.mIntelligence;
            }
            int getWillpower() const {
                return this->data.mData.mWillpower;
            }
            int getAgility() const {
                return this->data.mData.mAgility;
            }
            int getSpeed() const {
                return this->data.mData.mSpeed;
            }
            int getEndurance() const {
                return this->data.mData.mEndurance;
            }
            int getPersonality() const {
                return this->data.mData.mPersonality;
            }
            int getLuck() const {
                return this->data.mData.mLuck;
            }
            int getHealth() const {
                return this->data.mData.mHealth;
            }
            int getMana() const {
                return this->data.mData.mMana;
            }
            int getFatigue() const {
                return this->data.mData.mFatigue;
            }
            int getSoul() const {
                return this->data.mData.mSoul;
            }
            int getCombat() const {
                return this->data.mData.mCombat;
            }
            int getMagic() const {
                return this->data.mData.mMagic;
            }
            int getStealth() const {
                return this->data.mData.mStealth;
            }
            int getAttack(lua_State* L) {
                LuaRef table = newTable(L);
                for (int i = 0; i < 6; i++) {
                    table.append(this->data.mData.mAttack[i]);
                }
                push(L, table);
                return 1;
            }
            int getGold() const {
                return this->data.mData.mGold;
            }
            int getBloodType() const {
                return this->data.mBloodType;
            }
            unsigned char getFlags() const {
                return this->data.mFlags;
            }
            bool getPersistent() const {
                return this->data.mPersistent;
            }
            float getScale() const {
                return this->data.mScale;
            }
            std::string getId() const {
                return this->data.mId;
            }
            std::string getModel() const {
                return this->data.mModel;
            }
            std::string getName() const {
                return this->data.mName;
            }
            std::string getScript() const {
                return this->data.mScript;
            }
            std::string getOriginal() const {
                return this->data.mOriginal;
            }
            int getInventory(lua_State* L) {
                LuaRef table = newTable(L);
				std::vector<ContItem> vec = this->data.mInventory.mList;
				for (auto i = vec.begin(); i != vec.end(); i++) {
					table.append(RefCountedPtr<LContItem>(new LContItem(*i)));
				}
				push(L, table);
				return 1;
            }
            int getSpells(lua_State* L) {
                LuaRef table = newTable(L);
				std::vector<std::string> vec = this->data.mSpells.mList;
				for (auto i = vec.begin(); i != vec.end(); i++) {
					table.append(*i);
				}
				push(L, table);
				return 1;
            }
            int getAiData(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            int getAiPackage(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            int getTransport(lua_State* L) {
                LuaRef table = newTable(L);
				std::vector<Transport::Dest> vec = this->data.mTransport.mList;
				for (auto i = vec.begin(); i != vec.end(); i++) {
					table.append(RefCountedPtr<LDest>(new LDest(*i)));
				}
				push(L, table);
				return 1;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Creature data;
    };
}
