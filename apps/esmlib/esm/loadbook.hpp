#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadbook.hpp>

#include "esm/esmreader.hpp"

using namespace luabridge;

namespace ESM
{
/*
 * Books, magic scrolls, notes and so on
 */

class LBook
	{
	public:
        LBook() {
		}
		~LBook() {
		}
		unsigned int getRecordId() const {
			return this->data.sRecordId;
		}
		std::string getRecordType() const {
			return this->data.getRecordType();
		}
        float getWeight() const {
            return this->data.mData.mWeight;
        }
        int getValue() const {
            return this->data.mData.mValue;
        }
        int getIsScroll() const {
            return this->data.mData.mIsScroll;
        }
        int getSkillId() const {
            return this->data.mData.mSkillId;
        }
        int getEnchant() const {
            return this->data.mData.mEnchant;
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
        std::string getEnchantId() const {
            return this->data.mEnchant;
        }
        std::string getText() const {
            return this->data.mText;
        }
        std::string getId() const {
            return this->data.mId;
        }
		void load(LESMReader* esm, bool isDeleted) {
			this->data.load(*esm->getReader(), isDeleted);
		}
	private:
        Book data;
	};
}
