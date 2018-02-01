#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QString>
#include <QDataStream>

#define LOG_ERROR   qCritical() << qPrintable(QString(__FILE__).section('/', -1, -1)) << __LINE__ << Q_FUNC_INFO << "\nERROR   :"
#define LOG_WARNING qWarning()  << qPrintable(QString(__FILE__).section('/', -1, -1)) << __LINE__ << Q_FUNC_INFO << "\nWARNING :"
#define LOG_INFO    qDebug()    << qPrintable(QString(__FILE__).section('/', -1, -1)) << __LINE__ << Q_FUNC_INFO << "\nINFO    :"
#define LOG_DEBUG   qDebug()    << qPrintable(QString(__FILE__).section('/', -1, -1)) << __LINE__ << Q_FUNC_INFO << "\nDEBUG   :"

#endif // LOGGER_H
