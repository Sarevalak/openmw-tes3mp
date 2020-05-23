#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/variant.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LVariant
    {
        public:
            LVariant(const Variant* data) {
                this->data = data;
            }
            LVariant() {
                this->data = NULL;
            }
            ~LVariant() {
                this->data = NULL;
            }
            int getType() const {
                return this->data->getType();
            }
            std::string getString() const {
                return this->data->getString();
            }
            int getInteger() const {
                return this->data->getInteger();
            }
            float getFloat() const {
                return this->data->getFloat();
            }
        private:
            const Variant* data;
    };
}
