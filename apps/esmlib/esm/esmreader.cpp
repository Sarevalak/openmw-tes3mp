#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <LuaBridge.h>
#include <RefCountedPtr.h>

#include <components/esm/esmreader.hpp>

#include "esm/esmreader.hpp"
#include "esm/esmcommon.hpp"
#include "esm/loadtes3.hpp"

using namespace luabridge;

namespace ESM {
    class LESMReader {
        public:
            LESMReader() {
                this->reader = new ESMReader();
            }
            ~LESMReader()
            {
                delete this->reader;
            }

            /*************************************************************************
            *
            *  Information retrieval
            *
            *************************************************************************/

            int getVer() {
                return this->reader->getVer();
            }
            int getRecordCount() {
                return this->reader->getRecordCount();
            }
            float getFVer() {
                return this->reader->getFVer();
            }
            std::string getAuthor() {
                return this->reader->getAuthor();
            }
            std::string getDesc() {
                return this->reader->getDesc();
            }
            LuaRef getGameFiles(lua_State* L) {
                LuaRef table = newTable(L);
                std::vector<Header::MasterData> vec = this->reader->getGameFiles();
                for (auto i = vec.begin(); i != vec.end(); i++) {
                    table.append(RefCountedPtr<LMasterData>(new LMasterData(*i)));
                }
                return table;
            }

            RefCountedPtr<LHeader> getHeader() {
                return RefCountedPtr<LHeader>(new LHeader(this->reader->getHeader()));
            }
            int getFormat() {
                return this->reader->getFormat();
            };
            std::string retSubName() {
                return this->reader->retSubName().toString();
            }
            unsigned int getSubSize() {
                return this->reader->getSubSize();
            }
            std::string getName() {
                return this->reader->getName();
            }

            /*************************************************************************
            *
            *  Opening and closing
            *
            *************************************************************************/

            /** Save the current file position and information in a ESM_Context
                struct
            */
            RefCountedPtr<LESM_Context> getContext() {
                return RefCountedPtr<LESM_Context>(new LESM_Context(this->reader->getContext()));
            }

            /** Restore a previously saved context */
            void restoreContext(RefCountedPtr<LESM_Context> rc) {
                return this->reader->restoreContext(*rc.get()->getContext());
            }

            /** Close the file, resets all information. After calling close()
                the structure may be reused to load a new file.
            */
            void close() {
                return this->reader->close();
            }

            /// Raw opening. Opens the file and sets everything up but doesn't
            /// parse the header.
            // void openRaw(Files::IStreamPtr _esm, const std::string& name);

            /// Load ES file from a new stream, parses the header. Closes the
            /// currently open file first, if any.
            // void open(Files::IStreamPtr _esm, const std::string& name);

            void open(const std::string file) {
                return this->reader->open(file);
            }

            // void openRaw(const std::string& filename);

            /// Get the current position in the file. Make sure that the file has been opened!
            size_t getFileOffset() {
                return this->reader->getFileOffset();
            }

            // This is a quick hack for multiple esm/esp files. Each plugin introduces its own
            //  terrain palette, but ESMReader does not pass a reference to the correct plugin
            //  to the individual load() methods. This hack allows to pass this reference
            //  indirectly to the load() method.

            void setIndex(const int index) {
                return this->reader->setIndex(index);
            }
            int getIndex() {
                return this->reader->getIndex();
            }

            void setGlobalReaderList(std::vector<ESMReader>* list) {
                return this->reader->setGlobalReaderList(list);
            }

            std::vector<ESMReader>* getGlobalReaderList() {
                return this->reader->getGlobalReaderList();
            }

            /*************************************************************************
            *
            *  Low level record methods
            *
            *************************************************************************/

            // Get the next record name
            std::string getRecName() {
                return this->reader->getRecName().toString();
            }

            // Skip the rest of this record. Assumes the name and header have
            // already been read
            void skipRecord() {
                return this->reader->skipRecord();
            }

            /* Read record header. This updatesleftFile BEYOND the data that
               follows the header, ie beyond the entire record. You should use
               leftRec to orient yourself inside the record itself.
            */
            // void getRecHeader() { getRecHeader(mRecordFlags); }
            void getRecHeader(lua_State* L) {
                int argc = lua_gettop(L);
                if (argc == 0) {
                    return this->reader->getRecHeader();
                }
                else {
                    uint32_t flags = luaL_checkinteger(L, 1);
                    return this->reader->getRecHeader(flags);
                }
            }

            bool hasMoreRecs() {
                return this->reader->hasMoreRecs();
            }

            bool hasMoreSubs() {
                return this->reader->hasMoreSubs();
            }

            ESMReader* getReader() {
                return this->reader;
            }
        private:
            ESMReader* reader;
    };
}
