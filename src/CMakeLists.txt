ADD_SUBDIRECTORY( icons )
FIND_PACKAGE( libmtp REQUIRED )
INCLUDE_DIRECTORIES(${KDE4_INCLUDES}
                    ${LIBMTP_INCLUDE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR} )

SET( SRC devices.cpp
         kzen.cpp
         kzenalbum.cpp
         kzenalbumview.cpp
         kzenalbumviewmodel.cpp
         kzendevice.cpp
         kzendevicethread.cpp
         kzendevicewidget.cpp
         kzendirnavbar.cpp
         kzenfile.cpp
         kzenfiletransferview.cpp
         kzenfiletransferviewmodel.cpp
         kzenfiletransferwidget.cpp
         kzenfolder.cpp
         kzenmusicwidget.cpp
         kzenobject.cpp
         kzenphotowidget.cpp
         kzenplaylist.cpp
         kzenplaylistview.cpp
         kzenplaylistviewmodel.cpp
         kzensplash.cpp
         kzentrack.cpp
         kzentrackview.cpp
         kzentrackviewmodel.cpp
         kzenvideowidget.cpp
         kzenwidget.cpp
         main.cpp )

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
INSTALL(TARGETS kzen DESTINATION ${KDE4_BIN_INSTALL_DIR} )
INSTALL( FILES kzen.desktop DESTINATION ${KDE4_XDG_APPS_INSTALL_DIR} )
INSTALL( FILES kzenui.rc DESTINATION ${DATA_INSTALL_DIR}/kzen )
