#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadskil.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LSkill
    {
        public:
            LSkill() {
            }
            ~LSkill() {
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
            int getAttribute() const {
                return this->data.mData.mAttribute;
            }
            int getSpecialization() const {
                return this->data.mData.mSpecialization;
            }
            int getUseValue(lua_State* L) {
                LuaRef table = newTable(L);
                for (int i = 0; i < sizeof(this->data.mData.mUseValue) / sizeof(float); i++) {
                    table.append(this->data.mData.mUseValue[i]);
                }
                push(L, table);
                return 1;
            }
            int getIndex() const {
                return this->data.mIndex;
            }
            std::string getDescription() const {
                return this->data.mDescription;
            }
            std::string indexToId(int index) {
                return this->data.indexToId(index);
            }
        private:
            Skill data;
    };
}
