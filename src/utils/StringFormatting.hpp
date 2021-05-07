#pragma once

// Project includes ------------------------------------------------------------
#include "details/StringFormatting.hpp"
#include "Json.hpp"
#include "StringLitterals.hpp"

/* If you got a mysterious error about the operator % being deleted, you
 * probably forgot to convert your string to a QString with _s :P
 */
template<typename T>
inline void operator%(char const *s, T other) = delete;

template<typename T>
inline QString operator%(const QString & s, const T & value)
{ return Utility::Details::_moduloHelper(s, value); }

inline QString operator%(const QString & s, const std::string & str)
{ return s.arg(str.c_str()); }

inline QString operator%(const QString & s, const QByteArray & data)
{ return s.arg(data.constData()); }

inline QString operator%(const QString & s, const QJsonObject & json)
{ return s % Utility::jsonToArray(json, false, QJsonDocument::Indented); }

inline QString operator%(const QString & s, const QJsonArray & json)
{ return s % Utility::jsonToArray(json, false, QJsonDocument::Indented); }

inline QString operator%(const QString & s, const QJsonValue & json)
{ return s % Utility::jsonToArray(json, false, QJsonDocument::Indented); }
