#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadacti.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
	class LActivator
	{
		public:
            LActivator() {
			}
			~LActivator() {
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
			void load(LESMReader* esm, bool isDeleted) {
				this->data.load(*esm->getReader(), isDeleted);
			}
		private:
			Activator data;
	};
}
