#include "Balance/Channel.h"
#include <QPainter>
#include "Balance/parameters.hpp"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsScene>
#include <QFontMetricsF>
#include "Balance/HmAnalysis/HaBlock.h"
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

using namespace boost::adaptors;

Balance::Channel::Channel(QGraphicsItem *parent)
    :QGraphicsObject (parent)
{
    setZValue (0);
    setAcceptHoverEvents (true);
    connect (this, &Channel::objectNameChanged, [this] { update (); });
    connect (this, &Channel::fontChanged, [this] { update (); });
}

void Balance::Channel::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget *widget)
{
    Q_UNUSED (widget);
    Q_UNUSED (option);
    painter->setFont (font_);

    const auto rect = boundingRect ();
    const auto & textName = objectName ();
    const auto metrics = QFontMetricsF (painter->font ());
    const auto h = metrics.height ();
    const auto w = metrics.width (objectName ());

    auto finalText = QString ();
    //auto realW = qreal {};

    if (w > rect.width ())
    {
        finalText = metrics.elidedText (textName, Qt::ElideMiddle, rect.width ());
        //realW = metrics.width (finalText);
    }
    else
    {
        finalText = textName;
        //realW = w;
    }

    const auto color = QColor (Qt::white);

    painter->setBrush (color);

    painter->save ();
    painter->setPen (Qt::NoPen);

    auto r = rect;
    r.setTop (h);
    painter->drawRect (r);
    painter->restore ();

    //painter->drawText (QRectF (QPointF ((rect.width ()- realW) / 2, rect.top ()), QSizeF (realW, h)), finalText);
}

QRectF Balance::Channel::boundingRect() const
{
    return QRectF (0, 0, channelWidth, channelHeight);
}

void Balance::Channel::clearItems()
{
    for (auto block : childItems ()
         | transformed ([] (auto && child) { return dynamic_cast<TaskBlock*> (child); })
         | filtered ([](auto && child) { return child != null; }))
    {
        block->deleteLater ();
    }
}

