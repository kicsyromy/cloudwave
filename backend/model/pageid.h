#ifndef PAGEID_H
#define PAGEID_H

#include <QObject>

namespace backend
{
    namespace model
    {
        class PageId: public QObject
        {
            Q_OBJECT
            Q_ENUMS(Page)

        public:
            enum Page
            {
                MainPage,
                AlbumDetails,
                ArtistDetails,
                GenreDetails
            };
        };
    }
}

#endif // PAGEID_H
