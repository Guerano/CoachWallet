#pragma once

// Qt includes
#include <QString>

// C++ includes
#include <initializer_list>
#include <algorithm>

namespace Utility
{
QString byteToHRSize(qint64 bytes, bool addUnit = true, int precision = 2);

template<typename T, typename C = std::initializer_list<T>>
bool isInList(const T & val, const C & container)
{
    return std::find(std::begin(container), std::end(container), val) != std::end(container);
}

QString boolToString(bool b);
bool    stringToBool(const QString & str, bool * ok = nullptr);
} // !namespace Utility
