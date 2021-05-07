#include "Utility.hpp"

namespace Utility
{
QString byteToHRSize(qint64 bytes, bool addUnit, int precision)
{
    if (bytes > 1024 * 1024 * 1024)
        return QString("%1%2").arg(bytes / (1024. * 1024. * 1024.), 0, 'f', precision).arg(addUnit ? " GiB" : "");
    else if (bytes > 1024 * 1024)
        return QString("%1%2").arg(bytes / (1024. * 1024.), 0, 'f', precision).arg(addUnit ? " MiB" : "");
    else if (bytes > 1024)
        return QString("%1%2").arg(bytes / 1024., 0, 'f', precision).arg(addUnit ? " kiB" : "");
    return QString("%1%2").arg(bytes).arg(addUnit ? " B" : "");
}

QString boolToString(bool b)
{
    return b ? "true" : "false";
}

bool stringToBool(const QString & str, bool * ok)
{
    bool dummy;
    bool & valid = ok == nullptr ? dummy : *ok;

    if (str.isEmpty())
    {
        valid = false;
        return false;
    }

    valid = true;

    {
        bool conversionOk;
        qint32 val = str.toInt(&conversionOk);
        if (conversionOk)
            return val != 0;
    }

    if (str.compare("true", Qt::CaseInsensitive) == 0
            || str.compare("yes", Qt::CaseInsensitive) == 0)
        return true;
    else if (str.compare("false", Qt::CaseInsensitive) == 0
             || str.compare("no", Qt::CaseInsensitive) == 0)
        return false;

    valid = false;
    return false;
}
} // !namespace Utility
