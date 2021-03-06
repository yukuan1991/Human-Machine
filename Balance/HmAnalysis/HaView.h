﻿#pragma once
#include <QGraphicsView>
#include <memory>
#include <base/lang/scope.hpp>
#include <vector>
#include <base/lang/not_null.h>



namespace Balance {
class ResourceScene;
class Channel;
namespace HmAnalysis {
class HaChannel;
class HaBlock;

class HaView : public QGraphicsView
{
    Q_OBJECT
signals:
    void totalTimeChanged (qreal);
public:
    explicit HaView (QWidget *parent = 0);
    ~HaView () override;
    void mouseMoveEvent (QMouseEvent * event) override;
    void mouseReleaseEvent (QMouseEvent * event) override;
    void onHumanAddTask();
    void onMachineAddTask(const QString &name);
    void taskSetting ();
    void setTotalTime (qreal totalTime) { totalTime_ = totalTime; totalTimeChanged (totalTime_); }
    qreal totalTime () const noexcept { return totalTime_; }
    void setTitle ();
    QStringList intersectedChannels ();
    QStringList machines () const;
    void importHuman (const std::vector<std::pair<QString, qreal>> & data);
    void importData (const QString & channel, const std::vector<std::pair<QString, qreal>> & data);

protected:
    void barClicked (Channel *bar);
    void blockClicked (HaBlock * block);

    void setTaskAttribute (not_null<HaBlock *> block);
    void resizeEvent (QResizeEvent * event) override;
    void resetTitle (Channel * bar);
    HaChannel* selectedMachine(const QString & channel);
private:
    std::unique_ptr<Balance::ResourceScene> scene_;
    HaChannel * human_ = nullptr;
    std::vector<not_null<HaChannel*>> machines_;
    qreal totalTime_;
};

} // namespace AmAnalysis
} // namespace Balance

