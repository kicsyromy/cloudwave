TEMPLATE = app

QT += qml quick widgets network xml multimedia

INCLUDEPATH += \
    backend \
    backend/network \
    backend/structure \
    backend/adapter \
    backend/model \
    backend/playback \
    backend/data

HEADERS += \
    backend/logger.h \
    backend/common.h \
    backend/structure/album.h \
    backend/structure/artist.h \
    backend/structure/track.h \
    backend/adapter/artistretriever.h \
    backend/adapter/genreretriever.h \
    backend/model/artistlistmodel.h \
    backend/model/albumlistmodel.h \
    backend/model/genrelistmodel.h \
    backend/model/tracklistmodel.h \
    backend/playback/playlist.h \
    backend/model/pageid.h \
    backend/model/albumdetailsmodel.h \
    backend/model/artistdetailsmodel.h \
    backend/model/playlistmodel.h \
    backend/playback/nowplaying.h \
    backend/adapter/albumretriever.h \
    backend/adapter/trackretriever.h \
    backend/network/plexconnection.h \
    backend/data/artistthumbprovider.h \
    backend/data/localimagecache.h \
    backend/data/albumthumbprovider.h

SOURCES += \
    main.cpp \
    backend/adapter/artistretriever.cpp \
    backend/adapter/genreretriever.cpp \
    backend/model/artistlistmodel.cpp \
    backend/model/albumlistmodel.cpp \
    backend/model/genrelistmodel.cpp \
    backend/model/tracklistmodel.cpp \
    backend/playback/playlist.cpp \
    backend/model/albumdetailsmodel.cpp \
    backend/model/artistdetailsmodel.cpp \
    backend/model/playlistmodel.cpp \
    backend/playback/nowplaying.cpp \
    backend/adapter/albumretriever.cpp \
    backend/adapter/trackretriever.cpp \
    backend/network/plexconnection.cpp \
    backend/data/artistthumbprovider.cpp \
    backend/data/localimagecache.cpp \
    backend/data/albumthumbprovider.cpp

RESOURCES += qml.qrc

include(deployment.pri)

