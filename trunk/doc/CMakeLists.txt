FIND_PACKAGE( docbook )

IF( DOCBOOK_FOUND )
    kde3_create_handbook(index.docbook INSTALL_DESTINATION ${KDE3PREFIX}/share/doc/HTML/en/kzen )
ENDIF( DOCBOOK_FOUND )