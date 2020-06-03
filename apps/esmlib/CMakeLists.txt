set(ESMLIB
  esmlibmain.cpp esmlib.h esmlib.cpp
)

option(BUILD_WITH_LUA "Enable Lua language" ON)
if(BUILD_WITH_LUA)

    find_package(LuaJit REQUIRED)

    MESSAGE(STATUS "Found LuaJit_LIBRARIES: ${LuaJit_LIBRARIES}")
    MESSAGE(STATUS "Found LuaJit_INCLUDE_DIRS: ${LuaJit_INCLUDE_DIRS}")

    set(LuaScript_Sources
            Script/LangLua/LangLua.cpp
            Script/LangLua/LuaFunc.cpp)
    set(LuaScript_Headers ${LUA_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/extern/LuaBridge ${CMAKE_SOURCE_DIR}/extern/LuaBridge/detail
            Script/LangLua/LangLua.hpp)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_LUA")
    include_directories(SYSTEM ${LuaJit_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/extern/LuaBridge)
endif(BUILD_WITH_LUA)

set(ESMPROXY ./esm/esmreader.hpp ./esm/esmcommon.hpp ./esm/loadtes3.hpp ./esm/loadtes3.cpp ./esm/loadalch.hpp ./esm/effectlist.hpp ./esm/loadacti.hpp
            ./esm/loadappa.hpp ./esm/loadarmo.hpp ./esm/loadland.hpp ./esm/loadmgef.hpp ./esm/loaddoor.hpp ./esm/loadbook.hpp ./esm/cellid.hpp
			 ./esm/variant.hpp ./esm/loadstat.hpp ./esm/loadspel.hpp ./esm/loadskil.hpp ./esm/loadmisc.hpp ./esm/loadltex.hpp ./esm/loadingr.hpp
			 ./esm/loadglob.hpp ./esm/loadench.hpp ./esm/loadcrea.hpp ./esm/loadcont.hpp ./esm/loadclot.hpp ./esm/loadclas.hpp ./esm/loadbsgn.hpp
			 ./esm/loadbody.hpp ./esm/transport_dest.hpp ./esm/landutils.hpp)

source_group(apps\\esmlib\\esm FILES ${ESMPROXY})
source_group(apps\\esmlib FILES ${ESMLIB} ${LuaScript_Headers} ${LuaScript_Sources})

include_directories("./")
include_directories(${CMAKE_SOURCE_DIR}/extern)

set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library(esmlib SHARED ${ESMLIB} ${ESMPROXY})

target_link_libraries(esmlib
  components
  ${OSG_LIBRARIES}
  ${OSGUTIL_LIBRARIES}
  ${LuaJit_LIBRARIES}
)

	

if (BUILD_WITH_CODE_COVERAGE)
  add_definitions (--coverage)
  target_link_libraries(bsatool gcov)
endif()
