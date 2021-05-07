#pragma once

#include <QRegularExpression>
#include <QString>

#include <string>

inline QString operator"" _s(const char * str,       std::size_t size)
{ return QString::fromLatin1(str, size); }

inline QString operator"" _s(const wchar_t * wstr,   std::size_t size)
{ return QString::fromWCharArray(wstr, size); }

inline QString operator"" _s(const char16_t * str16, std::size_t size)
{ return QString::fromUtf16(str16, size); }

inline QString operator"" _s(const char32_t * str32, std::size_t size)
{ return QString::fromUcs4(str32, size); }

inline QRegularExpression operator"" _r(const char * str,       std::size_t size)
{ return QRegularExpression(QString::fromLatin1(str, size)); }

inline QRegularExpression operator"" _r(const wchar_t * wstr,   std::size_t size)
{ return QRegularExpression(QString::fromWCharArray(wstr, size)); }

inline QRegularExpression operator"" _r(const char16_t * str16, std::size_t size)
{ return QRegularExpression(QString::fromUtf16(str16, size)); }

inline QRegularExpression operator"" _r(const char32_t * str32, std::size_t size)
{ return QRegularExpression(QString::fromUcs4(str32, size)); }
