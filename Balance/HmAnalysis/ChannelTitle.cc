#include "Balance/HmAnalysis/ChannelTitle.h"
#include "Balance/parameters.hpp"
#include <QPainter>
#include "Balance/HmAnalysis/HaChannel.h"
#include <QFontMetrics>
#include <QApplication>

namespace Balance {
namespace HmAnalysis {

ChannelTitle::ChannelTitle(QGraphicsItem *parent)
    :QGraphicsObject (parent)
{

}

void ChannelTitle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);

    painter->setFont (qApp->font ());
    painter->save ();
    painter->setBrush (sceneBackground);
    painter->setPen (Qt::NoPen);
    painter->drawRect (boundingRect ());
    painter->restore ();

    painter->drawText (QRectF (0, 0, parentItem ()->boundingRect ().width (), QFontMetricsF (qApp->font ()).height ()), Qt::AlignCenter, title_);
}

QRectF ChannelTitle::boundingRect() const
{
    auto pItem = dynamic_cast<HaChannel *> (parentItem ());
    if (pItem == null)
    {
        return {};
    }
    return QRectF (pItem->boundingRect ().left (), -1000, pItem->boundingRect ().width (), 1000 + QFontMetricsF (qApp->font ()).height ());
}

}
}
