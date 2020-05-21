#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loaddoor.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{

class LDoor
	{
	public:
        LDoor() {
		}
		~LDoor() {
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
		std::string getOpenSound() const {
			return this->data.mOpenSound;
		}
		std::string getCloseSound() const {
			return this->data.mCloseSound;
		}
		void load(LESMReader* esm, bool isDeleted) {
			this->data.load(*esm->getReader(), isDeleted);
		}
	private:
		Door data;
	};
}

