FIND_PATH( LIBMTP_INCLUDE_DIR libmtp.h /usr/include/libmtp/ /usr/local/include/libmtp )
FIND_LIBRARY( LIBMTP_LIBRARY NAMES mtp PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )

IF( LIBMTP_INCLUDE_DIR AND LIBMTP_LIBRARY )
   SET( LIBMTP_FOUND TRUE )
ENDIF( LIBMTP_INCLUDE_DIR AND LIBMTP_LIBRARY )


IF( LIBMTP_FOUND )
   IF( NOT libmtp_FIND_QUIETLY )
      MESSAGE( STATUS "Found libmtp: ${LIBMTP_LIBRARY}" )
   ENDIF( NOT libmtp_FIND_QUIETLY )
ELSE( LIBMTP_FOUND )
   IF( libmtp_FIND_REQUIRED )
      MESSAGE( FATAL_ERROR "Could not find libmtp" )
   ENDIF( libmtp_FIND_REQUIRED )
ENDIF( LIBMTP_FOUND )