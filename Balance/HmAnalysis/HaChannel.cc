#include "Balance/HmAnalysis/HaChannel.h"
#include "Balance/HmAnalysis/HaBlock.h"
#include <QApplication>
#include <QFont>
#include <QFontMetricsF>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Balance/parameters.hpp"
#include "Balance/HmAnalysis/ChannelTitle.h"
#include <QDebug>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>

namespace Balance {
namespace HmAnalysis {
using namespace boost::adaptors;

HaChannel::HaChannel(QGraphicsObject *parent)
    :Channel (parent)
{
    auto lower = new QGraphicsRectItem (0, 0, channelWidth, channelGrayHeight, this);
    lower->setBrush (QColor (127, 127, 127, 100));
    lower->setPen (Qt::NoPen);
    lower->setZValue (3);
    lower->setPos (0, channelHeight - channelGrayHeight);

    auto upper = new QGraphicsRectItem (0, 0, channelWidth, channelGrayHeight, this);
    upper->setBrush (QColor (127, 127, 127, 100));
    upper->setPen (Qt::NoPen);
    upper->setZValue (3);
    upper->setPos (0, QFontMetricsF (qApp->font ()).height ());

    auto boundary = new QGraphicsRectItem (0, 0, channelWidth, 10000, this);
    boundary->setPen (Qt::NoPen);
    boundary->setZValue (3);
    boundary->setPos (0, channelHeight);
    boundary->setBrush (sceneBackground);

    auto title = new ChannelTitle (this);
    title->setTitle (objectName ());
    title->setZValue (4);
    title->setPos (0, 0);
    connect (this, &HaChannel::objectNameChanged, title, &ChannelTitle::setTitle);
}

void HaChannel::addTask(add_task params)
{
    const auto metrics = QFontMetricsF (qApp->font ());
    const auto h = metrics.height ();

    auto newTask = new HaBlock (this);
    newTask->setName (params.taskName);
    newTask->setTime (params.time);
    const auto y = HaBlock::timeToPos (params.startAt, totalTime (), h);
    newTask->setPos ({0, y});

    newTask->refreshRatio ();
    connect (this, &HaChannel::totalTimeChanged, newTask, &HaBlock::refreshRatio);
    connect (this, &HaChannel::fontChanged, newTask, &HaBlock::refreshRatio);
}

void HaChannel::importTask(const std::vector<std::pair<QString, qreal> > & data)
{
    qreal bottom = 0;
    for (auto & it : data)
    {
        addTask ({.taskName = it.first, .time = it.second, .startAt = bottom});
        bottom += it.second;
    }
}

bool HaChannel::intersect()
{
    QStringList names;
    for (auto block : childItems ()
         | transformed ([] (auto && c) { return dynamic_cast<HaBlock *> (c); })
         | filtered ([] (auto && c) { return c != nullptr; }))
    {
        auto items = block->collidingItems ();
        auto blockColided = items |
                filtered ([] (auto&&c) { return dynamic_cast<HaBlock*> (c) != nullptr; });

        if (not blockColided.empty ())
        {
            return true;
        }
    }

    return false;
}

} // namespace HmAnalysis
} // namespace Balance
