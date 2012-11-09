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
