#include "JsonImpl.hpp"

#include "../Json.hpp"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
# define QT_SKIP_EMPTY_PARTS Qt::SkipEmptyParts
#else
# define QT_SKIP_EMPTY_PARTS QString::SkipEmptyParts
#endif

using namespace Utility::Json;

QStringList Details::splitPath(const QString & path)
{
    // "root.obj[4].val\\.s" -> "root", "obj", "[4]", "val.s"
    static const QRegularExpression re(R"(^(.*)(\[\d+\])$)");
    static const QRegularExpression reDot(R"((?<!\\)\.)");

    QStringList keys;
    const auto split = path.split(reDot, QT_SKIP_EMPTY_PARTS);
    for (auto s : split)
    {
        s.replace("\\.", ".");
        const auto match = re.match(s);
        if (!match.hasMatch())
            keys.append(s);
        else
        {
            if (!match.captured(1).isEmpty())
                keys.append(match.captured(1));
            keys.append(match.captured(2));
        }
    }

    return keys;
}

QRegularExpressionMatch Details::keyMatchArray(const QString & key)
{
    static const QRegularExpression reIsArray(R"(^\[(\d+)\]$)");
    return reIsArray.match(key);
}

bool Details::get(QJsonValue & value, const QString & path)
{
    const auto keys = splitPath(path);
    for (const auto & key : keys)
    {
        const auto isArray = keyMatchArray(key);
        if (isArray.hasMatch())
        {
            if (!value.isArray())
                return false;
            value = value.toArray().at(isArray.captured(1).toInt());
        }
        else
        {
            if (!value.isObject())
                return false;
            value = value.toObject().value(key);
        }
    }

    return true;
}

void Details::set(QJsonValue & json, QStringList keys, QJsonValue value)
{
    if (keys.isEmpty())
    {
        json = value;
        return ;
    }

    const auto key   = keys.takeFirst();
    const auto match = keyMatchArray(key);
    if (match.hasMatch())
    {
        const auto idx = match.captured(1).toInt();
        auto array = json.toArray();
        for (int i = array.size(); i <= idx; ++i)
            array.append(QJsonValue{});

        auto j = array.at(idx);
        set(j, keys, value);
        array[idx] = j;
        json = array;
    }
    else
    {
        auto obj = json.toObject();
        auto j   = obj.value(key);
        set(j, keys, value);
        obj[key] = j;
        json = obj;
    }
}

void Details::merge(const QString & path, QJsonObject & dest, const QJsonValue & value)
{
    if (value.type() != QJsonValue::Object || !Utility::Json::contains(dest, path))
        Utility::Json::set(dest, path, value);
    else
    {
        const auto obj = value.toObject();
        for (auto itr = obj.begin(); itr != obj.end(); ++itr)
            merge(path + "." + itr.key(), dest, itr.value());
    }
}

bool Details::contains(QJsonObject const & json, QStringList paths)
{
    if (json.isEmpty() || paths.isEmpty())
        return true;

    auto const key = paths.takeFirst();
    return json.contains(key) ? Details::contains(json[key].toObject(), paths) : false;
}
