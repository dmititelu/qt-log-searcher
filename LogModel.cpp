#include "LogModel.h"
#include <utility>

static const QString C_UNDEFINED_TYPE_LABEL = " - undefined";
static const QString C_INFO_TYPE_LABEL = " - info";
static const QString C_ERROR_TYPE_LABEL = " - error";
static const QString C_WARNING_TYPE_LABEL = " - warning";

static const QString C_UNDEFINED_TYPE_NUMBER = "0x00";
static const QString C_INFO_TYPE_NUMBER = "0x01";
static const QString C_WARNING_TYPE_NUMBER = "0x02";
static const QString C_ERROR_TYPE_NUMBER = "0x03";

LogSystemModel::LogSystemModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_FullLogList()
    , m_DisplayedLogList()
{

}

QHash<int, QByteArray> LogSystemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[LogFieldNumberRole] = "logFieldNumber";
    roles[LogTypeRole] = "logType";
    roles[LogLabelRole] = "logLabel";
    roles[LogSessionCountRole] = "logSessionCount";

    return roles;
}

int LogSystemModel::rowCount(const QModelIndex &) const
{
    return m_DisplayedLogList.size();
}

QVariant LogSystemModel::data(const QModelIndex &idx,int role) const
{
    if (idx.row() < 0 || idx.row() >= rowCount() || idx.row() >= m_DisplayedLogList.size())
       return QVariant();

    LogData logData = m_DisplayedLogList.at(idx.row());

    switch (role)
    {
        case LogSessionCountRole:
        {
            return logData.m_LogTimestamp + 1;
        }
        case LogFieldNumberRole:
        {
            return logData.m_LogFieldNumber;
        }
        case LogTypeRole:
        {
            QString logTypeString;
            for (auto type : logData.m_LogTypeList)
            {
                logTypeString += type;
                if (logData.m_LogTypeList.size() > 1)
                {
                    logTypeString += "\n";
                }

            }
            return logTypeString;
        }
        case LogLabelRole:
        {
            QString logLabelString;
            for (auto label : logData.m_LogLabelList)
            {
                logLabelString += label;
                if (logData.m_LogLabelList.size() > 1)
                {
                    logLabelString += "\n";
                }
            }
            return logLabelString;
        }

        default:
            return QVariant();
    }
}

// function was added in order avoid displaying messages with unexpected types
// 213, garbage, garbage message
bool LogSystemModel::_isExpectedType(const QString &value)
{
    return value == C_UNDEFINED_TYPE_NUMBER || value == C_INFO_TYPE_NUMBER || value == C_WARNING_TYPE_NUMBER || value == C_ERROR_TYPE_NUMBER;
}

void LogSystemModel::populateDisplayList()
{
    beginResetModel();
    for (auto logData : m_FullLogList)
    {
        m_DisplayedLogList.push_back(logData);
    }
    endResetModel();
}

void LogSystemModel::appendRow(const int timestamp, const QString &logLine)
{
    QStringList fields = logLine.split(",");
    bool isLogLine(false);

    // isLogLine ensures that the log line begins with an integer
    // . is not displayed
    // garbageString, garbageType, garbageMessage is not displayed
    fields[LogFieldNumberRole].toInt(&isLogLine);

    if (isLogLine && _isExpectedType(fields[LogTypeRole]))
    {
        auto it = m_FullLogList.find(std::make_pair(timestamp, fields[LogFieldNumberRole].toInt()));
        if(it != m_FullLogList.end() && it.value().m_LogTimestamp == timestamp)
        {
            it->m_LogTypeList.append(fields[LogTypeRole] + C_ERROR_TYPE_LABEL);
            it->m_LogLabelList.append(fields[LogLabelRole]);
        }

        else
        {
            LogData logData;
            logData.m_LogTimestamp = timestamp;
            logData.m_LogFieldNumber = fields[LogFieldNumberRole].toInt();

            if (fields[LogTypeRole] == C_INFO_TYPE_NUMBER)
            {
                logData.m_LogTypeList.append(fields[LogTypeRole] + C_INFO_TYPE_LABEL);
            }
            else if (fields[LogTypeRole] == C_ERROR_TYPE_NUMBER)
            {
                logData.m_LogTypeList.append(fields[LogTypeRole] + C_ERROR_TYPE_LABEL);
            }
            else if (fields[LogTypeRole] == C_WARNING_TYPE_NUMBER)
            {
                logData.m_LogTypeList.append(fields[LogTypeRole] + C_WARNING_TYPE_LABEL);
            }
            else
            {
                logData.m_LogTypeList.append(fields[LogTypeRole] + C_UNDEFINED_TYPE_LABEL);
            }
            logData.m_LogLabelList.append(fields[LogLabelRole]);

            m_FullLogList.insert(std::make_pair(timestamp, logData.m_LogFieldNumber), logData);
        }
    }
}

void LogSystemModel::filterBy(const QString &value)
{
    beginResetModel();
    m_DisplayedLogList.clear();
    for(auto logLine : m_FullLogList)
    {
        bool wasLogLineFound = false;
        for (auto logLabel : logLine.m_LogLabelList)
        {
            if (logLabel.toLower().contains(value.toLower()) && !wasLogLineFound)
            {
                m_DisplayedLogList.append(logLine);
                wasLogLineFound = true;
            }
        }
        if(!wasLogLineFound)
        {
            for (auto logType : logLine.m_LogTypeList)
            {
                if (logType.toLower().contains(value.toLower()))
                {
                    m_DisplayedLogList.append(logLine);
                }
            }
        }
    }
    endResetModel();
}

QList<LogData> LogSystemModel::getDisplayedLogList() const
{
    return m_DisplayedLogList;
}
