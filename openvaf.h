#pragma once
#include <QString>
#include <vector>
#include <string_view>
#include <QStringList>

enum class workType
{
    Processing = 0, Checking = 1, Moving = 2, Waiting = 3
};

struct taskInfo
{
    QString name;
    qreal stdTime;
    workType type;
};

/// 传入一个JSON的字符串然后会解析出一个文件中的所有任务信息
std::vector<taskInfo> readVaf (std::string_view data);
QStringList findAll (const QString & path, const QStringList & filter);
QMap<QString, std::vector<taskInfo>> collectVaf (const QString & folder);

