#pragma once

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>
#include <components/esm/loadland.hpp>
#include <components/esm/esmcommon.hpp>
#include <components/misc/constants.hpp>

#include "esm/esmreader.hpp"
#include "esm/esmcommon.hpp"


namespace ESM
{

    /*
     * Landscape data.
     */

    class LLandData
    {
    public:
        LLandData(const Land::LandData* data) {
            this->data = data;
        }
        LLandData() {
            this->data = NULL;
        }
        ~LLandData() {
            this->data = NULL;
        }
        float getHeightOffset() const {
            return this->data->mHeightOffset;
        }
        int getHeights(lua_State* L) {
            LuaRef table = newTable(L);
            for (int i = 0; i < Land::LAND_NUM_VERTS; i++) {
                table.append(this->data->mHeights[i]);
            }
            push(L, table);
            return 1;
        }
        float getMinHeight() const {
            return this->data->mMinHeight;
        }
        float getMaxHeight() const {
            return this->data->mMaxHeight;
        }
        /*
         * void getNormals() const {
         *     return this->data->mNormals;
         * }
        */
        // 2D array of texture indices. An index can be used to look up an ESM::LandTexture,
        // but to do so you must subtract 1 from the index first!
        // An index of 0 indicates the default texture.
        int getTextures(lua_State* L) {
            LuaRef table = newTable(L);
            for (int i = 0; i < Land::LAND_NUM_TEXTURES; i++) {
                table.append(this->data->mTextures[i]);
            }
            push(L, table);
            return 1;
        }
        /*
         * void getColours() const {
         *     return this->data->mColours;
         * }
        */
        int getDataLoaded() const {
            return this->data != NULL && this->data->mDataLoaded;
        }

        const Land::LandData* getLandData() const {
            return this->data;
        }
    private:
        const Land::LandData* data;
    };

    class LLand
    {
    public:
        LLand() {
        }
        ~LLand() {
        }
        unsigned int getRecordId() const {
            return this->data.sRecordId;
        }
        std::string getRecordType() const {
            return this->data.getRecordType();
        }
        int getFlags() const {
            return this->data.mFlags;
        }
        int getX() const {
            return this->data.mX;
        }
        int getY() const {
            return this->data.mY;
        }
        int getPlugin() const {
            return this->data.mPlugin;
        }
        RefCountedPtr<LESM_Context> getContext() {
            return RefCountedPtr<LESM_Context>(new LESM_Context(this->data.mContext));
        }
        void setContext(RefCountedPtr<LESM_Context> rc) {
            this->data.mContext = *rc.get()->getContext();
        }
        int getDataTypes() const {
            return this->data.mDataTypes;
        }

        void load(LESMReader* esm, bool isDeleted) {
            this->data.load(*esm->getReader(), isDeleted);
        }

        /**
         * Actually loads data into target
         * If target is nullptr, assumed target is mLandData
         */
        void loadData(int flags) const {
            this->data.loadData(flags);
        }

        /**
         * Frees memory allocated for mLandData
         */
        void unloadData() const {
            this->data.unloadData();
        }

        /// Check if given data type is loaded
        bool isDataLoaded(int flags) {
            return this->data.isDataLoaded(flags);
        }

        /// Sets the flags and creates a LandData if needed
        // void setDataLoaded(int flags) {
        //     this->data.setDataLoaded(flags);
        // }

        /// Return land data with at least the data types specified in \a flags loaded (if they
        /// are available). Will return a 0-pointer if there is no data for any of the
        /// specified types.
        RefCountedPtr<LLandData> getLandData(int flags) const {
            return RefCountedPtr<LLandData>(new LLandData(this->data.getLandData(flags)));
        }

        int getAvailableData(int flags) const {
            return flags & this->getDataTypes();
        }

        const Land* getLand() {
            return &this->data;
        }
    private:
        Land data;
    };

}
