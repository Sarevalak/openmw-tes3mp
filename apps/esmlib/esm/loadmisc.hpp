#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadmisc.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LMiscellaneous
    {
        public:
            LMiscellaneous() {
            }
            ~LMiscellaneous() {
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
            int getIsKey() const {
                return this->data.mData.mIsKey;
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
            Miscellaneous data;
    };
}
