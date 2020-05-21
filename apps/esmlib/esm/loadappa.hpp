#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadappa.hpp>

#include "esm/esmreader.hpp"

namespace ESM
{

	/*
	 * Alchemist apparatus
	 */

	class LApparatus
	{
		public:
            LApparatus() {
			}
			~LApparatus() {
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
			std::string getIcon() const {
				return this->data.mIcon;
			}
			std::string getScript() const {
				return this->data.mScript;
			}
			int getType() const {
				return this->data.mData.mType;
			}
			float getQuality() const {
				return this->data.mData.mQuality;
			}
            float getWeight() const {
				return this->data.mData.mWeight;
			}
			int getValue() const {
				return this->data.mData.mValue;
			}
			void load(LESMReader* esm, bool isDeleted) {
				this->data.load(*esm->getReader(), isDeleted);
			}
		private:
			Apparatus data;
	};
}

