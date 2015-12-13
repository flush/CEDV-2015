project (myguiship)
set(CMAKE_BUILDTYPE Release)
set(MYGUI_INSTALL $ENV{MYGUI_INSTALL})
set (HEADER_FILES ./inc)
set (SOURCE_FILES src/GuiShip.cpp ../records/src/records.cpp)
set(MYGUI_SOURCE_DIR $ENV{MYGUI_SOURCE_DIR})
set(OGRE_INCLUDE_DIR "/usr/include/OGRE")
set(OIS_INCLUDE_DIR "/usr/include/ois")
set(RECORDS_INCLUDE_DIR "../records/inc")
set(TARGET="SHARED")
       include_directories(
                .
                ${MYGUI_SOURCE_DIR}/Common
                ${MYGUI_SOURCE_DIR}/MyGUIEngine/include
                ${MYGUI_INSTALL}/Common/Base/Ogre
                ${MYGUI_SOURCE_DIR}/Platforms/Ogre/OgrePlatform/include
                ${OGRE_INCLUDE_DIR}
		${MYGUI_INSTALL}/Common/Input/OIS
                ${OIS_INCLUDE_DIR}
                ${RECORDS_INCLUDE_DIR}
        )

                add_definitions("-DMYGUI_OGRE_PLATFORM")

include_directories(${HEADER_FILES})
add_library (myguiship SHARED ${SOURCE_FILES})

link_directories("/usr/lib/i386-linux-gnu/")
target_link_libraries(myguiship OgreMain)

link_directories("./")
link_directories(${MYGUI_INSTALL}/lib)
add_executable(tester ./test/main.cpp)
target_link_libraries(tester myguiship)
target_link_libraries(tester boost_system)
target_link_libraries(tester pthread)
target_link_libraries(tester Common)
target_link_libraries(tester X11)
target_link_libraries(tester MyGUIEngine)
target_link_libraries(tester OIS)
target_link_libraries(tester libMyGUI.OgrePlatform.a)


