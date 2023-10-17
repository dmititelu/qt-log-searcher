#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QtCore/QObject>
#include <QString>
#include <memory>

class LogSystemModel;

class LogSystemController : public QObject
{
    Q_OBJECT

    Q_PROPERTY (bool logError READ getLogError NOTIFY logErrorChanged)
    Q_PROPERTY (QObject *logModel READ getLogModel NOTIFY logModelChanged)
    Q_PROPERTY (QString filterBy WRITE setFilterBy NOTIFY filterByChanged)
public:
    LogSystemController(QObject *parent = nullptr);
    virtual ~LogSystemController() override;

    QObject *getLogModel() const;
    Q_SIGNAL void logModelChanged();

    bool getLogError() const;

    Q_SIGNAL void logErrorChanged();

    void setFilterBy(const QString &value);
    Q_SIGNAL void filterByChanged();
private:
    bool m_bLogError;
    std::unique_ptr<LogSystemModel> m_pLogModel;
};
#endif // LOGCONTROLLER_H
