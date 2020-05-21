#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/loadtes3.hpp>

using namespace luabridge;

namespace ESM
{
    class LESMReader;

	class LMasterData {
        public:
            LMasterData(Header::MasterData &data);
            LMasterData();
            ~LMasterData();
            std::string getName() const;
            uint64_t getSize() const;
            // Position of the parent file in the global list of loaded files
            int getIndex() const;
        private:
            Header::MasterData data;
    };

    class LHeader {
        public:
            LHeader(const Header &header);
            LHeader();
            ~LHeader();
            int getCurrentFormat() const;
            const Header* getHeader();
        private:
            Header header;
    };
}
