#ifndef PLEXCONNECTION_H
#define PLEXCONNECTION_H

#include <QObject>

#include <QString>
#include <QSet>

class QNetworkAccessManager;
class QNetworkReply;

typedef unsigned long RequestId;

namespace backend
{
    namespace network
    {
        class PlexConnection: public QObject
        {
            Q_OBJECT

        public:
            enum RequestStatus
            {
                NoError = 0,

                // network layer errors [relating to the destination server] (1-99):
                ConnectionRefusedError = 1,
                RemoteHostClosedError,
                HostNotFoundError,
                TimeoutError,
                OperationCanceledError,
                SslHandshakeFailedError,
                TemporaryNetworkFailureError,
                NetworkSessionFailedError,
                BackgroundRequestNotAllowedError,
                UnknownNetworkError = 99,

                // proxy errors (101-199):
                ProxyConnectionRefusedError = 101,
                ProxyConnectionClosedError,
                ProxyNotFoundError,
                ProxyTimeoutError,
                ProxyAuthenticationRequiredError,
                UnknownProxyError = 199,

                // content errors (201-299):
                ContentAccessDenied = 201,
                ContentOperationNotPermittedError,
                ContentNotFoundError,
                AuthenticationRequiredError,
                ContentReSendError,
                ContentConflictError,
                ContentGoneError,
                UnknownContentError = 299,

                // protocol errors
                ProtocolUnknownError = 301,
                ProtocolInvalidOperationError,
                ProtocolFailure = 399,

                // Server side errors (401-499)
                InternalServerError = 401,
                OperationNotImplementedError,
                ServiceUnavailableError,
                UnknownServerError = 499
            };

        public:
            static QString hostname;

        public:
            explicit PlexConnection();
            ~PlexConnection();

        public:
            RequestId get(const QString &path);

        signals:
            void dataReady(RequestId id, const QByteArray &data, RequestStatus status, const QString &errorString);

        private slots:
            void onRequestFinished(QNetworkReply *reply);

        private:
            QNetworkAccessManager *mNAManager;
            QSet<QNetworkReply *> mRequests;

        private:
            Q_DISABLE_COPY(PlexConnection)
        };
    }
}

#endif // PLEXCONNECTION_H
