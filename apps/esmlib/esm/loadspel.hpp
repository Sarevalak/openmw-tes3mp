#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadspel.hpp>

#include "esm/esmreader.hpp"
#include "esm/effectlist.hpp"

using namespace luabridge;

namespace ESM
{
    class LSpell
    {
        public:
            LSpell() {
            }
            ~LSpell() {
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
            int getCost() const {
                return this->data.mData.mCost;
            }
            int getFlags() const {
                return this->data.mData.mFlags;
            }
            std::string getId() const {
                return this->data.mId;
            }
            std::string getName() const {
                return this->data.mName;
            }
            int getEffects(lua_State* L) {
                LuaRef table = newTable(L);
                std::vector<ENAMstruct> vec = this->data.mEffects.mList;
                for (auto i = vec.begin(); i != vec.end(); i++) {
                    table.append(RefCountedPtr<LENAMstruct>(new LENAMstruct(*i)));
                }
                push(L, table);
                return 1;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Spell data;
    };
}
