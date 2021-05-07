#include "Json.hpp"

#include "StringLitterals.hpp"
#include "Utility.hpp"

#include <QMap>
#include <QFile>
#include <QJsonParseError>

using namespace Utility;

bool Utility::loadAndConvertFileToJson(const QString & filename,
                                       QJsonObject &   json,
                                       QString *       errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        errString = QString("File '%1' cannot be opened for reading: %2")
                .arg(filename).arg(file.errorString());
        return false;
    }

    return convertFileToJson(file, json, errorString);
}

bool Utility::loadAndConvertFileToJson(const QString & filename,
                                       QJsonArray &    json,
                                       QString *       errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        errString = QString("File '%1' cannot be opened for reading: %2")
                .arg(filename).arg(file.errorString());
        return false;
    }

    return convertFileToJson(file, json, errorString);
}

bool Utility::loadAndConvertFileToJson(const QString & filename,
                                       QJsonValue &    json,
                                       QString *       errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        errString = QString("File '%1' cannot be opened for reading: %2")
                .arg(filename).arg(file.errorString());
        return false;
    }

    return convertFileToJson(file, json, errorString);
}

bool Utility::convertFileToJson(QFile & file, QJsonObject & json, QString * errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    if (!file.isReadable())
    {
        errString = QString("File '%1' is not readable").arg(file.fileName());
        return false;
    }

    return convertByteArrayToJson(file.readAll(), json, errorString);
}

bool Utility::convertFileToJson(QFile & file, QJsonArray & json, QString * errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    if (!file.isReadable())
    {
        errString = QString("File '%s' is not readable").arg(file.fileName());
        return false;
    }

    return convertByteArrayToJson(file.readAll(), json, errorString);
}

bool Utility::convertFileToJson(QFile & file, QJsonValue & json, QString * errorString)
{
    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    if (!file.isReadable())
    {
        errString = QString("File '%s' is not readable").arg(file.fileName());
        return false;
    }

    return convertByteArrayToJson(file.readAll(), json, errorString);
}

bool Utility::convertByteArrayToJson(const QByteArray & array,
                                     QJsonObject &      json,
                                     QString *          errorString)
{
    if (array.isEmpty())
        return true;

    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QJsonParseError jsonParseError;
    auto const jsonDocument = QJsonDocument::fromJson(array, &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError)
    {
        errString = "Unable to parse JSON: " + jsonParseError.errorString();
        return false;
    }

    if (!jsonDocument.isObject())
    {
        errString = "JSON must start with an object";
        return false;
    }

    json = jsonDocument.object();
    return true;
}

bool Utility::convertByteArrayToJson(const QByteArray & array,
                                     QJsonArray &       json,
                                     QString *          errorString)
{
    if (array.isEmpty())
        return true;

    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QJsonParseError jsonParseError;
    auto const jsonDocument = QJsonDocument::fromJson(array, &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError)
    {
        errString = "Unable to parse JSON: " + jsonParseError.errorString();
        return false;
    }

    if (!jsonDocument.isArray())
    {
        errString = "JSON must start with an array";
        return false;
    }

    json = jsonDocument.array();
    return true;
}

bool Utility::convertByteArrayToJson(const QByteArray & array,
                                     QJsonValue &       json,
                                     QString *          errorString)
{
    if (array.isEmpty())
        return true;

    QString dummy;
    QString & errString = errorString == nullptr ? dummy : *errorString;

    QJsonParseError jsonParseError;
    auto const doc = QJsonDocument::fromJson(array, &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError)
    {
        errString = "Unable to parse JSON: " + jsonParseError.errorString();
        return false;
    }

    if (doc.isArray())
        json = doc.array();
    else
        json = doc.object();

    return true;
}

QByteArray Utility::jsonToArray(const QJsonValue & json,
                                bool emptyReturnOnEmptyJson,
                                QJsonDocument::JsonFormat format)
{
    QByteArray result;

    auto fromContainer = [&] (auto const & c)
    {
        QByteArray tmp;

        if (!c.isEmpty() || !emptyReturnOnEmptyJson)
            tmp = QJsonDocument(c).toJson(format);

        return tmp;
    };

    switch (json.type())
    {
    case QJsonValue::Array:  result = fromContainer(json.toArray());        break;
    case QJsonValue::Object: result = fromContainer(json.toObject());       break;
    case QJsonValue::Bool:   result = boolToString(json.toBool()).toUtf8(); break;
    case QJsonValue::Double: result = QByteArray::number(json.toDouble());  break;
    case QJsonValue::String: result = json.toString().toUtf8();             break;
    default: break;
    }

    if (!result.isEmpty() && format == QJsonDocument::Indented)
    {
        result = QString(result).replace(R"(\[\s+\])"_r, "[]")
                .replace(R"({\s+})"_r,   "{}")
                .toUtf8();
    }
    return result;
}

QJsonArray Utility::sumArray(const QJsonArray & array1, const QJsonArray & array2)
{
    return std::accumulate(array2.cbegin(), array2.cend(), array1,
                           [](QJsonArray array, const QJsonValue & val)
    { return array + val; });
}

QString Utility::jsonTypeToString(QJsonValue::Type type)
{
    static const QMap<QJsonValue::Type, QString> map = {
        { QJsonValue::Null,   "null"   },
        { QJsonValue::Bool,   "bool"   },
        { QJsonValue::Double, "double" },
        { QJsonValue::String, "string" },
        { QJsonValue::Array,  "array"  },
        { QJsonValue::Object, "object" }
    };
    return map.value(type, "unknown");
}

QJsonObject & Json::removeExcept(QJsonObject & dest, Json::CStringInitList keys)
{
    QJsonObject newDest;
    for (auto && field : keys)
    {
        if (dest.contains(field))
            newDest.insert(field, dest[field]);
    }
    dest = newDest;
    return dest;
}

QJsonObject & Json::removeFields(QJsonObject & dest, Json::CStringInitList fields)
{
    for (auto && field : fields)
        dest.remove(field);

    return dest;
}

QJsonObject & Json::removeFields(QJsonObject & dest, QRegularExpression const & keyRegExp)
{
    QStringList fieldsToRemove;
    for (auto it = dest.begin() ; it != dest.end() ; ++it)
    {
        if (keyRegExp.match(it.key()).hasMatch())
            fieldsToRemove << it.key();
    }
    for (auto && field : fieldsToRemove)
        dest.remove(field);
    return dest;
}

QJsonObject Json::copyAndStrip(QJsonObject dest, Json::CStringInitList fields)
{
    return removeFields(dest, fields);
}

QJsonObject Json::copyAndStrip(QJsonObject dest, QRegularExpression const & keyRegExp)
{
    return removeFields(dest, keyRegExp);
}

QJsonObject Json::copyOnly(QJsonObject dest, Json::CStringInitList keys)
{
    return removeExcept(dest, keys);
}

QJsonObject Json::copyOnly(QJsonObject dest, QStringList keys)
{
    QJsonObject newDest;
    for (auto && field : keys)
    {
        if (dest.contains(field))
            newDest.insert(field, dest[field]);
    }
    return newDest;
}

QJsonObject & Json::append(QJsonObject & dest, QJsonObject const & source)
{
    return append(dest, source, source.keys());
}

QJsonObject & Json::append(QJsonObject & dest, QJsonObject const & source,
                           QStringList const & keys)
{
    for (auto const & key : keys)
    {
        if (source.contains(key))
            dest.insert(key, source.value(key));
    }
    return dest;
}

QJsonObject Json::concat(QJsonObject dest, QJsonObject const & source)
{
    return concat(dest, source, source.keys());
}

QJsonObject Json::concat(QJsonObject dest, QJsonObject const & source,
                         QStringList const & keys)
{
    return append(dest, source, keys);
}

QJsonObject & Json::merge(QJsonObject & dest, const QJsonObject & source)
{
    for (auto itr = source.begin(); itr != source.end(); ++itr)
        Details::merge(itr.key(), dest, itr.value());

    return dest;
}

void Json::set(QJsonValue & json, const QString & path, QJsonValue value)
{
    Details::set(json, Details::splitPath(path), value);
}

void Json::set(QJsonObject & json, const QString & path, QJsonValue value)
{
    QJsonValue j = json;
    set(j, path, value);
    json = j.toObject();
}

void Json::set(QJsonArray & json, const QString & path, QJsonValue value)
{
    QJsonValue j = json;
    set(j, path, value);
    json = j.toArray();
}

bool Json::contains(QJsonObject const & dest, QString const & path)
{
    return Details::contains(dest, Details::splitPath(path));
}

Json::Comparison<QJsonValue> Json::compare(const QJsonValue & a, const QJsonValue & b)
{
    if (a.isObject() && b.isObject())
        return compare(a.toObject(), b.toObject());
    else if (a.isArray() && b.isArray())
        return compare(a.toArray(), b.toArray());

    const bool val = a.type() == b.type() && a == b;
    return Comparison<QJsonValue>(val,  val ? std::pair<QJsonValue, QJsonValue>()
                                  : std::make_pair(a, b));
}

Json::Comparison<QJsonObject> Json::compare(const QJsonObject & a, const QJsonObject & b)
{
    Comparison<QJsonObject> res;

    const auto aKeys = a.keys();
    const auto bKeys = b.keys();

    QStringList commonKeys;
    for (auto key : bKeys)
    {
        if (!aKeys.contains(key) || b[key].type() != a[key].type())
            res.second.second.insert(key, b[key]);
        else
            commonKeys.push_back(key);
    }

    for (auto key : aKeys)
    {
        if (!bKeys.contains(key) || b[key].type() != a[key].type())
            res.second.first.insert(key, a[key]);
    }

    for (auto key : commonKeys)
    {
        auto tmpRes = compare(a[key], b[key]);
        if (!tmpRes.first)
        {
            res.second.first.insert(key, tmpRes.second.first);
            res.second.second.insert(key, tmpRes.second.second);
        }
    }

    res.first = res.second.first.empty() && res.second.second.empty();
    return res;
}

Json::Comparison<QJsonArray> Json::compare(const QJsonArray & a, const QJsonArray & b)
{
    Comparison<QJsonArray> res;

    QJsonArray aCopy = a;
    QJsonArray bCopy = b;

    auto ita = aCopy.begin();
    for (; ita != aCopy.end();)
    {
        auto itb = bCopy.begin();
        const auto itbEnd = bCopy.end();
        for (; itb != itbEnd; ++itb)
        {
            if (compare(*ita, *itb).first)
                break;
        }

        if (itb != itbEnd)
        {
            ita = aCopy.erase(ita);
            bCopy.erase(itb);
        }
        else
        {
            res.second.first.push_back(*ita);
            ++ita;
        }
    }

    res.second.second = bCopy;
    res.first = !res.second.first.size() && !res.second.second.size();
    return res;
}
