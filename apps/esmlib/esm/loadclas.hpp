#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadclas.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LClass
    {
        public:
            LClass() {
            }
            ~LClass() {
            }
            unsigned int getRecordId() const {
                return this->data.sRecordId;
            }
            std::string getRecordType() const {
                return this->data.getRecordType();
            }
            int getSpecializationIds(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            int getGmstSpecializationIds(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            std::string getId() const {
                return this->data.mId;
            }
            std::string getName() const {
                return this->data.mName;
            }
            std::string getDescription() const {
                return this->data.mDescription;
            }
            int getAttribute(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            int getSpecialization() const {
                return this->data.mData.mSpecialization;
            }
            int getSkills(lua_State* L) {
                // TODO: implement method!
                return 0;
            }
            int getIsPlayable() const {
                return this->data.mData.mIsPlayable;
            }
            int getCalc() const {
                return this->data.mData.mCalc;
            }
            int getSkill(int index, bool major) const {
                return this->data.mData.getSkill(index, major);
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Class data;
    };
}
