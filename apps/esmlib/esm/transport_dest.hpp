#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/transport.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LDest
    {
        public:
            LDest(Transport::Dest &data) {
                this->data = data;
            }
            LDest() {
            }
            ~LDest() {
            }
            float getX() const {
                return this->data.mPos.pos[0];
            }
            float getY() const {
                return this->data.mPos.pos[1];
            }
            float getZ() const {
                return this->data.mPos.pos[2];
            }
            float getRotX() const {
                return this->data.mPos.rot[0];
            }
            float getRotY() const {
                return this->data.mPos.rot[1];
            }
            float getRotZ() const {
                return this->data.mPos.rot[2];
            }
            std::string getCellName() const {
                return this->data.mCellName;
            }
        private:
            Transport::Dest data;
    };
}
