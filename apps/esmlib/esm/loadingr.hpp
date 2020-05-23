#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadingr.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LIngredient
    {
        public:
            LIngredient() {
            }
            ~LIngredient() {
            }
            unsigned int getRecordId() const {
                return this->data.sRecordId;
            }
            std::string getRecordType() const {
                return this->data.getRecordType();
            }
            float getWeight() const {
                return this->data.mData.mWeight;
            }
            int getValue() const {
                return this->data.mData.mValue;
            }
            int getEffectID(lua_State* L) {
                LuaRef table = newTable(L);
                for (int i = 0; i < sizeof(this->data.mData.mEffectID) / sizeof(int); i++) {
                    table.append(this->data.mData.mEffectID[i]);
                }
                push(L, table);
                return 1;
            }
            int getSkills(lua_State* L) {
                LuaRef table = newTable(L);
                for (int i = 0; i < sizeof(this->data.mData.mSkills) / sizeof(int); i++) {
                    table.append(this->data.mData.mSkills[i]);
                }
                push(L, table);
                return 1;
            }
            int getAttributes(lua_State* L) {
                LuaRef table = newTable(L);
                for (int i = 0; i < sizeof(this->data.mData.mAttributes) / sizeof(int); i++) {
                    table.append(this->data.mData.mAttributes[i]);
                }
                push(L, table);
                return 1;
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
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Ingredient data;
    };
}
