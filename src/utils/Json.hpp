#pragma once

#include "Utility.hpp"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QVariant>

#include "details/JsonImpl.hpp"

#define JSON_KEY_VALUE(key, value) static constexpr auto const key = value
#define JSON_KEY(key)              JSON_KEY_VALUE(key, #key)

namespace Utility
{
    bool loadAndConvertFileToJson(const QString & filename, QJsonObject & json,
                                                         QString * errorString = nullptr);
    bool loadAndConvertFileToJson(const QString & filename, QJsonArray & json,
                                                         QString * errorString = nullptr);
    bool loadAndConvertFileToJson(const QString & filename, QJsonValue & json,
                                                         QString * errorString = nullptr);

    bool convertFileToJson(QFile & file, QJsonObject & json,
                                                  QString * errorString = nullptr);
    bool convertFileToJson(QFile & file, QJsonArray & json,
                                                  QString * errorString = nullptr);
    bool convertFileToJson(QFile & file, QJsonValue & json,
                                                  QString * errorString = nullptr);

    bool convertByteArrayToJson(const QByteArray & array, QJsonObject & json,
                                                       QString * errorString = nullptr);
    bool convertByteArrayToJson(const QByteArray & array, QJsonArray & json,
                                                       QString * errorString = nullptr);
    bool convertByteArrayToJson(const QByteArray & array, QJsonValue & json,
                                                       QString * errorString = nullptr);

    QByteArray jsonToArray(const QJsonValue & json, bool emptyReturnOnEmptyJson = false,
                           QJsonDocument::JsonFormat format = QJsonDocument::Compact);

    QJsonArray sumArray(const QJsonArray & array1, const QJsonArray & array2);

    QString jsonTypeToString(QJsonValue::Type type);

    /* *************************************************************************
     * CONVERTION CHECKS
     * ************************************************************************/

    template<typename T>
    inline bool canConvertJsonValue(const QJsonValue &)
    { return false; }

#define CAN_CONVERT_TO(type, func) \
    template<> \
    inline bool canConvertJsonValue<type>(const QJsonValue & value) \
    { Q_UNUSED(value) return func; }

    CAN_CONVERT_TO(bool,        value.isBool());
    CAN_CONVERT_TO(int,         value.isDouble());
    CAN_CONVERT_TO(double,      value.isDouble());
    CAN_CONVERT_TO(QString,     value.isString());
    CAN_CONVERT_TO(QJsonArray,  value.isArray());
    CAN_CONVERT_TO(QJsonObject, value.isObject());
    CAN_CONVERT_TO(QVariant,    true);
    CAN_CONVERT_TO(QJsonValue,  true);
    CAN_CONVERT_TO(QStringList,
        QVariant(value.toArray().toVariantList()).convert(QMetaType::QStringList));

#undef CAN_CONVERT_TO

    /* *************************************************************************
     * CONVERTION
     * ************************************************************************/

    /**
     * @brief Convert a QJsonValue to the type of the template
     */
    template<typename T>
    T convertJsonValue(const QJsonValue & value, const T & defaultValue = T()) = delete;

#define CONVERT_TO(type, func) \
    template<> \
    inline type convertJsonValue(const QJsonValue & value, const type & defaultValue) \
    { Q_UNUSED(value) Q_UNUSED(defaultValue) return func; }

    CONVERT_TO(bool,        value.toBool(defaultValue));
    CONVERT_TO(int,         value.toInt(defaultValue));
    CONVERT_TO(double,      value.toDouble(defaultValue));
    CONVERT_TO(QString,     value.toString(defaultValue));
    CONVERT_TO(QJsonArray,  value.toArray(defaultValue));
    CONVERT_TO(QJsonObject, value.toObject(defaultValue));
    CONVERT_TO(QVariant,    value.toVariant());
    CONVERT_TO(QJsonValue,  value);
    CONVERT_TO(QStringList, QVariant(value.toArray().toVariantList()).toStringList());

#undef CONVERT_TO

    /**
     * @brief Convert a QString to the type of the template
     */
    template<typename T>
    T convertJsonValue(const QString & value, const T & defaultValue = T()) = delete;

#define CONVERT_TO(type, func) \
    template<> \
    inline type convertJsonValue(const QString & value, const type & defaultValue) \
    { Q_UNUSED(defaultValue) return func; }

    CONVERT_TO(bool,        Utility::stringToBool(value));
    CONVERT_TO(int,         value.toInt());
    CONVERT_TO(double,      value.toDouble());
    CONVERT_TO(QString,     value);
    CONVERT_TO(QJsonArray,  QJsonDocument::fromJson(value.toUtf8()).array());
    CONVERT_TO(QJsonObject, QJsonDocument::fromJson(value.toUtf8()).object());
    CONVERT_TO(QVariant,    QVariant(value));
    CONVERT_TO(QJsonValue,  QJsonValue(value));
    CONVERT_TO(QStringList, QVariant(QJsonDocument::fromJson(value.toUtf8()).array().toVariantList()).toStringList());

#undef CONVERT_TO

/**
 * @brief This namespace contains a lot of tools to help you manipulate QJsonObject
 */
namespace Json
{
    template<typename T = QJsonObject>
    inline std::pair<T, QString> fromByteArray(QByteArray const & array)
    {
        T json;
        QString error;
        convertByteArrayToJson(array, json, &error);
        return { json, error };
    }

    using CStringInitList = std::initializer_list<char const *>;

    /**
     * @brief Remove all the fields of a @c QJsonObject except the ones specified
     * @param dest Object to remove the fields from.
     * @param keys List of fields to keep
     */
    QJsonObject & removeExcept(QJsonObject & dest, CStringInitList keys);

    /**
     * @brief Remove multiple fields of a @c QJsonObject at the same time.
     * @param dest  Object to remove the fields from.
     * @param keys  List of fields to remove.
     * @note        Unknown fields are ignored.
     */
    QJsonObject & removeFields(QJsonObject & dest, CStringInitList keys);

    /**
     * @brief Remove multiple fields of a @c QJsonObject at the same time.
     * @param dest  Object to remove the fields from.
     * @param keyRegExp Regex to match the keys to be removed
     * @note        Unknown fields are ignored.
     */
    QJsonObject & removeFields(QJsonObject & dest,
                                                      QRegularExpression const & keyRegExp);

    /**
     * @brief Duplicate the object and strip some fields before returning it.
     * @param dest  Object to be duplicated.
     * @param keys  List of fields to remove.
     * @note        Unknown fields are ignored.
     */
    QJsonObject copyAndStrip(QJsonObject dest, CStringInitList keys);

    /**
     * @brief Duplicate the object and strip some fields before returning it.
     * @param dest  Object to be duplicated.
     * @param keyRegExp Regex to match the keys to be removed
     * @note        Unknown fields are ignored.
     */
    QJsonObject copyAndStrip(QJsonObject dest,
                                                    QRegularExpression const & keyRegExp);

    /**
     * @brief Duplicate the object and keep only specified fields.
     * @param dest  Object to be duplicated.
     * @param keys  List of fields to keep.
     */
    QJsonObject copyOnly(QJsonObject dest, CStringInitList keys);

    /**
     * @brief Duplicate the object and keep only specified fields.
     * @param dest  Object to be duplicated.
     * @param keys  List of fields to keep.
     */
    QJsonObject copyOnly(QJsonObject dest, QStringList keys);

    /**
     * @brief   Append all @p source keys and values into @p dest.
     * @warning Already existing fields will be updated.
     */
    QJsonObject & append(QJsonObject & dest, QJsonObject const & source);

    /**
     * @brief   Append specified @p source keys and values into @p dest.
     * @warning Already existing fields will be updated.
     */
    QJsonObject & append(QJsonObject & dest, QJsonObject const & source,
                                                QStringList const & keys);

    /**
     * @brief Take two objects and concatenate them into a third one.
     */
    QJsonObject concat(QJsonObject dest, QJsonObject const & source);

    /**
     * @brief Take two objects and concatenate them into a third one, only
     *        selecting specified fields from the source.
     */
    QJsonObject concat(QJsonObject dest, QJsonObject const & source,
                                              QStringList const & keys);

    /**
     * @brief Recursively override all values from @p source
     *        into @p dest. Non-existing values are created.
     */
    QJsonObject & merge(QJsonObject & dest, const QJsonObject & source);

    template<typename T = QJsonValue>
    T get(QJsonValue value, const QString & path, const T & defaultValue = T())
    {
        if (!Details::get(value, path))
            return defaultValue;

        return convertJsonValue(value, defaultValue);
    }

    void set(QJsonValue  & json, const QString & path, QJsonValue value);
    void set(QJsonObject & json, const QString & path, QJsonValue value);
    void set(QJsonArray  & json, const QString & path, QJsonValue value);

    /**
     * @brief Recursively check if @p path exists inside @p json.
     */
    bool contains(QJsonObject const & json, QString const & path);

    template<class T>
    using Comparison = std::pair<bool, std::pair<T, T>>;

    /**
     * @brief Recursively compare @p a tp @p b QJsonvalues and generate differences
     */
    Comparison<QJsonValue>  compare(const QJsonValue  & a,
                                                           const QJsonValue  & b);

    /**
     * @brief Recursively compare @p a tp @p b QJsonObjects and generate differences
     */
    Comparison<QJsonObject> compare(const QJsonObject & a,
                                                           const QJsonObject & b);

    /**
     * @brief Recursively compare @p a tp @p b QJsonArrays and generate differences
     */
    Comparison<QJsonArray>  compare(const QJsonArray  & a,
                                                           const QJsonArray  & b);

} // !namespace Json
} // !namespace Utility
