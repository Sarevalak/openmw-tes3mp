#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadbsgn.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LBirthSign
    {
        public:
            LBirthSign() {
            }
            ~LBirthSign() {
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
            std::string getDescription() const {
                return this->data.mDescription;
            }
            std::string getTexture() const {
                return this->data.mTexture;
            }
            SpellList getPowers() const {
                return this->data.mPowers;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            BirthSign data;
    };
}
