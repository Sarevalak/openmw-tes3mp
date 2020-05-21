#pragma once

#include <components/esm/esmcommon.hpp>

namespace ESM
{
	 /* This struct defines a file 'context' which can be saved and later
       restored by an ESMReader instance. It will save the position within
       a file, and when restored will let you read from that position as
       if you never left it.
     */
    class LESM_Context
    {
        public:
            LESM_Context(ESM_Context ctx) {
                this->ctx = ctx;
            }
            LESM_Context() {
                this->ctx = {};
            }
            ~LESM_Context() {
            }
            std::string getFilename() const {
                return this->ctx.filename;
            }
            uint32_t getLeftRec() const {
                return this->ctx.leftRec;
            }
            uint32_t getLeftSub() const {
                return this->ctx.leftSub;
            }
            uint32_t getLeftFile() const {
                return this->ctx.leftFile;
            }
            std::string getRecName() const {
                return this->ctx.recName.toString();
            }
            std::string getSubName() const {
                return this->ctx.subName.toString();
            }
            int getIndex() const {
                return this->ctx.index;
            }
            int getSubCached() const {
                return this->ctx.subCached;
            }
            int getFilePos() const {
                return this->ctx.filePos;
            }
            ESM_Context* getContext() {
                return &this->ctx;
            }
        private:
            ESM_Context ctx;
    };
}

