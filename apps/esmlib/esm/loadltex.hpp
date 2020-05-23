#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadltex.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LLandTexture
    {
        public:
            LLandTexture() {
            }
            ~LLandTexture() {
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
            std::string getTexture() const {
                return this->data.mTexture;
            }
            int getIndex() const {
                return this->data.mIndex;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            LandTexture data;
    };
}
