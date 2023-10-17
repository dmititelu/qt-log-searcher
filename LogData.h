#ifndef LOGDATA_H
#define LOGDATA_H

#include <QStringList>

struct LogData
{
    int m_LogTimestamp;
    int m_LogFieldNumber;
    QStringList m_LogLabelList;
    QStringList m_LogTypeList;
};

#endif // LOGDATA_H
