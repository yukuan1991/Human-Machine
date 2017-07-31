#include "HaBlock.h"
#include <QDebug>
#include "Balance/parameters.hpp"
#include "Balance/HmAnalysis/HaChannel.h"
#include <QFontMetricsF>
#include <assert.h>
#include <QPainter>
#include <QApplication>


namespace Balance {
namespace HmAnalysis {

HaBlock::HaBlock(QGraphicsItem * parent)
    :TaskBlock (parent)
{
    connect (this, &HaBlock::selectedChanged, this, &HaBlock::onSelected);
}

QVariant HaBlock::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &input)
{
    if (change == GraphicsItemChange::ItemPositionChange)
    {
        const auto pItem = dynamic_cast<Channel *> (parentItem ());
        assert (pItem);
        auto rect = pItem->boundingRect ();
        rect.setBottom (rect.bottom () - channelGrayHeight);
        const auto metrics = QFontMetricsF (pItem->font ());
        rect.setTop (rect.top () + metrics.height () + channelGrayHeight);

        const auto rectHeight = TaskBlock::boundingRect ().height ();

        const auto top = rect.top () - rectHeight;
        const auto bottom = rect.bottom ();

        const auto p1 = input.toPointF ();
        const auto p2 = p1 - QPointF (p1.x (), 0);

        const auto p3 = QPointF (p2.x (), p2.y () > bottom ? bottom : p2.y ());
        const auto p4 = QPointF (p3.x (), p3.y () < top ? top : p3.y ());

        return p4;
    }

    if (change == GraphicsItemChange::ItemSelectedHasChanged)
    {
        emit selectedChanged (input.toBool ());
    }

    return QGraphicsObject::itemChange (change, input);
}

void HaBlock::onSelected(bool b)
{
    setZValue (b ? 2 : 1);
}

void HaBlock::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->save ();
    paintBlock (painter, option, widget);

    const auto totalHeight = channelHeight - 2 * channelGrayHeight - textHeight ();
    paintBlock (painter, option, widget, QPointF (0, 0 - totalHeight));
    paintBlock (painter, option, widget, QPointF (0, 0 + totalHeight));
    painter->restore ();
    painter->drawPath (shape ());
}

QPainterPath HaBlock::shape () const
{
    const auto rect = TaskBlock::boundingRect ();

    QPainterPath path;
    path.addRect (rect);

    const auto totalHeight = channelHeight - 2 * channelGrayHeight - textHeight ();
    const auto upperRect = QRectF (rect.topLeft () - QPointF (0, totalHeight), rect.bottomRight () - QPointF (0, totalHeight));
    const auto lowerRect = QRectF (rect.topLeft () + QPointF (0, totalHeight), rect.bottomRight () + QPointF (0, totalHeight));

    path.addRect (upperRect);
    path.addRect (lowerRect);

    return path;
}

QRectF HaBlock::boundingRect() const
{
    return shape ().boundingRect ();
}

QRectF HaBlock::singleBoundingRect() const
{
    return TaskBlock::boundingRect ();
}

qreal HaBlock::startTime()
{
    not_null<HaChannel*> pItem = dynamic_cast<HaChannel *> (parentItem ());
    const auto totalTime = pItem->totalTime ();
    const auto y = pos ().y ();
    const auto fontOffset = QFontMetricsF (qApp->font ()).height ();

    return posToTime (y, totalTime, fontOffset);
}

qreal HaBlock::posToTime(qreal y, qreal totalTime, qreal fontOffset)
{
    const auto start = fontOffset + channelGrayHeight;

    const auto end = channelHeight - channelGrayHeight;

    const auto span = end - start;
    const auto relativeY = y - start;

    const auto absoluteTime = relativeY / span * totalTime;
    const auto inBoundTime = absoluteTime < 0 ? absoluteTime + totalTime :
                                                absoluteTime > totalTime ? absoluteTime - totalTime :
                                                                           absoluteTime;
    return inBoundTime;
}

qreal HaBlock::timeToPos(qreal startTime, qreal totalTime, qreal fontOffset)
{
    const auto start = fontOffset + channelGrayHeight;

    const auto end = channelHeight - channelGrayHeight;

    const auto span = end - start;

    const auto relativeY = startTime * span / totalTime;
    const auto y = relativeY + start;

    return y;
}


void HaBlock::refreshRatio ()
{
    const auto pItem = dynamic_cast<HaChannel *> (parentItem ());
    pItem->font ();
    auto metrics = QFontMetricsF (pItem->font ());
    const auto h = metrics.height ();

    const auto totalHeight = channelHeight - 2 * channelGrayHeight - h;
    const auto totalTime = pItem->totalTime ();

    setRatio (totalHeight / totalTime);
}

}
}
