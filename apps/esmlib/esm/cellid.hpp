#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/cellid.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{

class LCellId
	{
	public:
        LCellId(CellId& data) {
            this->data = data;
        }
        LCellId() {
		}
		~LCellId() {
		}
        std::string getWorldspace() const {
            return this->data.mWorldspace;
        }
        int getX() const {
            return this->data.mIndex.mX;
        }
        int getY() const {
            return this->data.mIndex.mY;
        }
        bool getPaged() const {
            return this->data.mPaged;
        }
        std::string getDefaultWorldspace() const {
            return this->data.sDefaultWorldspace;
        }
		void load(LESMReader* esm) {
			this->data.load(*esm->getReader());
		}
	private:
        CellId data;
	};
}
