#ifndef HACHANNEL_H
#define HACHANNEL_H
#include "Balance/Channel.h"
#include <QDebug>
#include <vector>
#include <utility>
#include <QString>


namespace Balance {
namespace HmAnalysis {

class HaChannel final : public Balance::Channel
{
    Q_OBJECT
signals:
    void totalTimeChanged (qreal);
public:
    HaChannel(QGraphicsObject * parent = null);
    /// 增加任务 taskName -> 任务名称, time -> 任务用时, startAt -> 起始时间
    void addTask(add_task t) override;
    void importTask (const std::vector<std::pair<QString, qreal>> & data);

    qreal totalTime () const noexcept { return totalTime_; }
    void setTotalTime (qreal t) { totalTime_ = t; totalTimeChanged (totalTime_); }
    bool intersect();
private:
    qreal totalTime_;
};

} // namespace HmAnalysis
} // namespace Balance

#endif // HACHANNEL_H
