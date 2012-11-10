project(krunner_flickr)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})


# Dependencies
find_package(KDE4 ${KDE_MIN_VERSION} REQUIRED)
include(KDE4Defaults)
find_package(KDE4Workspace REQUIRED)
find_package(QJSON REQUIRED)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-std=c++0x)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

# package/



include_directories(${QJSON_INCLUDE_DIR})

set(krunner_flickr_SRCS
    imageiconengine.cpp
    flickr.cpp
    flickjob.cpp
)

#add_subdirectory(icons)

kde4_add_plugin(krunner_flickr ${krunner_flickr_SRCS})
target_link_libraries(krunner_flickr ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS} ${QJSON_LIBRARIES})

install(TARGETS krunner_flickr DESTINATION ${PLUGIN_INSTALL_DIR} )

install(FILES plasma-runner-flickr.desktop DESTINATION ${SERVICES_INSTALL_DIR})
