import QtQuick 2.4
import Material 0.1
import "../views" as Views

import Constants 1.0 as Constants

Page {
    id: page

    property bool optimalWidthAvail: width > Units.dp(510)
    property bool search: false
    property QtObject visibleModel: {
        var model

        switch (tabView.currentIndex)
        {
        case 0: // Artists
            model = artistListModel
            break;
        case 1: // Albums
            model = albumListModel
            break;
        case 2: // Genres
            model = genreListModel
            break;
        case 3: // Songs
            model = trackListModel
            break;
        }

        return model
    }

    signal requestPage(var pageId, var data)

    actionBar.customContent: Loader {
        id: searchLoader
        anchors.fill: parent
        sourceComponent: page.search ? searchField : null
        onSourceComponentChanged: {
            if (searchLoader.sourceComponent === null)
                page.visibleModel.search("")
        }
    }

    Component {
        id: searchField
        Item {
            anchors.fill: parent
            TextField {
                id: textField
                anchors.fill: parent
                anchors.leftMargin: Units.dp(40)
                anchors.topMargin: Units.dp(20)
                anchors.bottomMargin: Units.dp(20)

                textColor: "white"

                onTextChanged: {
                    visibleModel.search(textField.text)
                }

                Component.onCompleted: {
                    textField.forceActiveFocus()
                }
            }
        }
    }

    actions: [
        Action {
            iconName: page.search ? "navigation/cancel" : "action/search"
            name: "Search"
            onTriggered: {
                page.search = !page.search
            }
        },

        Action {
            iconName: "action/settings"
            name: "Settings"
        }
    ]

    tabs: [
        {
            text: optimalWidthAvail ? "Artists" : "",
            icon: "social/person"
        },
        {
            text: optimalWidthAvail ? "Albums" : "",
            icon: "av/album"
        },
        {
            text: optimalWidthAvail ? "Genres": "",
            icon: "action/view_agenda"
        },
        {
            text: optimalWidthAvail ? "Songs" : "",
            icon: "av/my_library_music"
        }
    ]

    TabView {
        id: tabView
        anchors.fill: parent
        currentIndex:  page.selectedTab
        model: tabs
    }

    VisualItemModel {
        id: tabs

        Views.ArtistsView {
            width: tabView.width
            height: tabView.height
            inView: tabView.currentIndex == 0
            onItemClicked: {
                page.requestPage(Constants.Page.ArtistDetails, item)
            }
        }

        Views.AlbumsView {
            width: tabView.width
            height: tabView.height
            inView: tabView.currentIndex == 1
            onItemClicked: {
                page.requestPage(Constants.Page.AlbumDetails, item)
            }
        }

        Views.GenresView {
            width: tabView.width
            height: tabView.height
            inView: tabView.currentIndex == 2
        }

        Views.TracksView {
            width: tabView.width
            height: tabView.height
            inView: tabView.currentIndex == 3
        }
    }
}
