#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadglob.hpp>

#include "esm/esmreader.hpp"
#include "esm/variant.hpp"

using namespace luabridge;

namespace ESM
{
    class LGlobal
    {
        public:
            LGlobal() {
            }
            ~LGlobal() {
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
            RefCountedPtr<LVariant> getValue() const {
                return RefCountedPtr<LVariant>(new LVariant(&this->data.mValue));
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Global data;
    };
}
