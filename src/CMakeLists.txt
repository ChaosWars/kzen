ADD_SUBDIRECTORY( icons )
ADD_SUBDIRECTORY( pics )
FIND_PACKAGE( libmtp REQUIRED )
INCLUDE_DIRECTORIES(${KDE4_INCLUDES}
                    ${LIBMTP_INCLUDE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR} )

SET( SRC main.cpp
        kzen.cpp
        kzensplash.cpp
        kzenwidget.cpp
        kzenmusicwidget.cpp
        kzendirnavbar.cpp
        kzendevice.cpp
        kzendevicethread.cpp
        kzenobject.cpp
        kzenalbum.cpp
        kzentrack.cpp
        kzenfile.cpp
        kzenplaylist.cpp
        kzenalbumview.cpp
        kzentrackview.cpp
        kzenalbumviewmodel.cpp
        kzentrackviewmodel.cpp
        devices.cpp )

QT4_ADD_RESOURCES( SRC kzen.qrc )
LINK_DIRECTORIES( ${KDE4_LIB_DIR} )
KDE4_ADD_EXECUTABLE( kzen ${SRC} )
ADD_DEFINITIONS( ${KDE4_DEFINITIONS} ${QT_DEFINITIONS} )
TARGET_LINK_LIBRARIES( kzen ${KDE4_KDECORE_LIBS}
                            ${KDE4_KDEUI_LIBS}
                            ${KDE4_UTIL_LIBS}
                            ${KDE4_KIO_LIBS}
                            ${KDE4_KFILE_LIBS}
                            ${QT_QTCORE_LIBS}
                            ${LIBMTP_LIBRARY} )
INSTALL(TARGETS kzen
        RUNTIME DESTINATION ${KDE4_BIN_INSTALL_DIR}
        LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
        ARCHIVE DESTINATION ${PLUGIN_INSTALL_DIR} )
INSTALL( FILES kzen.desktop DESTINATION ${KDE4_XDG_APPS_INSTALL_DIR} )
