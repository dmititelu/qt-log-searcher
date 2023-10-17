#include "LogController.h"
#include "LogModel.h"

#include <QTextStream>
#include <QFile>

LogSystemController::LogSystemController(QObject *parent):
    QObject(parent)
  , m_bLogError(false)
  , m_pLogModel(std::make_unique<LogSystemModel>())
{
    QFile file(":/logs.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        m_bLogError = true;
        Q_EMIT logErrorChanged();
    }

    if (!m_bLogError)
    {
        QTextStream in(&file);

        int timestamp = 0;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line == ".")
            {
                ++timestamp;
            }
            m_pLogModel->appendRow(timestamp, line);
        }

        m_pLogModel->populateDisplayList();
    }

    file.close();
}

LogSystemController::~LogSystemController() = default;

QObject *LogSystemController::getLogModel() const
{
    return m_pLogModel.get();
}

void LogSystemController::setFilterBy(const QString &value)
{
    m_pLogModel->filterBy(value);
}

bool LogSystemController::getLogError() const
{
    return m_bLogError;
}
