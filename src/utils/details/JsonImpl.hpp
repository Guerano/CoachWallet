#pragma once

#include <QJsonValue>
#include <QString>

namespace Utility::Json::Details
{
QStringList splitPath(const QString & path);
QRegularExpressionMatch keyMatchArray(const QString & key);

bool get(QJsonValue & value, const QString & path);
void set(QJsonValue & json, QStringList keys, QJsonValue value);
void merge(const QString & path, QJsonObject & dest, const QJsonValue & value);
bool contains(QJsonObject const & json, QStringList paths);
} // !namespace Utility::Json::Details
