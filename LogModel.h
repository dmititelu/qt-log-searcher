#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMap>
#include <QList>

#include "LogData.h"

class LogSystemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DataRoles
    {
        LogFieldNumberRole = 0,
        LogTypeRole = 1,
        LogLabelRole = 2,
        LogSessionCountRole = 3
    };

    explicit LogSystemModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<LogData> getDisplayedLogList() const;

    void appendRow(const int timestamp, const QString &logLine);
    void populateDisplayList();
    void filterBy(const QString &value);

private:
    bool _isExpectedType(const QString &value);
    QMap<std::pair<int,int>, LogData> m_FullLogList;
    QList<LogData> m_DisplayedLogList;
};

#endif // LOGMODEL_H
