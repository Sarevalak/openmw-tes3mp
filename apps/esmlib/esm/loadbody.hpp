#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadbody.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LBodyPart
    {
        public:
            LBodyPart() {
            }
            ~LBodyPart() {
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
            std::string getModel() const {
                return this->data.mModel;
            }
            std::string getRace() const {
                return this->data.mRace;
            }
            unsigned char getPart() const {
                return this->data.mData.mPart;
            }
            unsigned char getVampire() const {
                return this->data.mData.mVampire;
            }
            unsigned char getFlags() const {
                return this->data.mData.mFlags;
            }
            unsigned char getType() const {
                return this->data.mData.mType;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            BodyPart data;
    };
}
