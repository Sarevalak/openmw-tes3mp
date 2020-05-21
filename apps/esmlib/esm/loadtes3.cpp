#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/loadtes3.hpp>

#include "esm/esmreader.hpp"
#include "esm/loadtes3.hpp"

using namespace luabridge;

namespace ESM
{
    // LMasterData

    LMasterData::LMasterData(Header::MasterData &data) {
        this->data = data;
    }
    LMasterData::LMasterData() {
        this->data = {};
    }
    LMasterData::~LMasterData() {
    }
    std::string LMasterData::getName() const {
        return this->data.name;
    }
    uint64_t LMasterData::getSize() const {
        return this->data.size;
    }
    // Position of the parent file in the global list of loaded files
    int LMasterData::getIndex() const {
        return this->data.index;
    }

    // LHeader

    LHeader::LHeader(const Header &header) {
        this->header = header;
    }
    LHeader::LHeader() {
        this->header = {};
    }
    LHeader::~LHeader() {
    }
    int LHeader::getCurrentFormat() const {
        return Header::CurrentFormat;
    }
    const Header* LHeader::getHeader() {
        return &this->header;
    }
 
}
