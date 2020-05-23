#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadcont.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
    class LContItem
    {
        public:
            LContItem(ContItem &data) {
                this->data = data;
            }
            LContItem() {
            }
            ~LContItem() {
            }
            int getCount() const {
                return this->data.mCount;
            }
            std::string getItem() const {
                return this->data.mItem;
            }
        private:
            ContItem data;
    };

    class LContainer
    {
        public:
            LContainer(Container &data) {
                this->data = data;
            }
            LContainer() {
            }
            ~LContainer() {
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
            std::string getModel() const {
                return this->data.mModel;
            }
            std::string getScript() const {
                return this->data.mScript;
            }
            float getWeight() const {
                return this->data.mWeight;
            }
            int getFlags() const {
                return this->data.mFlags;
            }
            int getInventory(lua_State* L) {
                LuaRef table = newTable(L);
				std::vector<ContItem> vec = this->data.mInventory.mList;
				for (auto i = vec.begin(); i != vec.end(); i++) {
					table.append(RefCountedPtr<LContItem>(new LContItem(*i)));
				}
				push(L, table);
				return 1;
            }
            void load(LESMReader* esm, bool isDeleted) {
                this->data.load(*esm->getReader(), isDeleted);
            }
        private:
            Container data;
    };
}
