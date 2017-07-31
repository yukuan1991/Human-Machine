#include "Balance/TaskBlock.h"
#include <base/lang/not_null.h>
#include <stdexcept>
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QFontMetricsF>
#include <QApplication>
#include "Balance/parameters.hpp"

namespace Balance {

using namespace std;

TaskBlock::TaskBlock (QGraphicsItem *parent)
    :QGraphicsObject (parent)
{
    if (parent == null)
    {
        throw logic_error ("TaskBlock created with a null parent");
    }

    setAcceptHoverEvents (true);
    setZValue (1);

    connect (this, &TaskBlock::timeChanged, [this] { update (); });
    connect (this, &TaskBlock::nameChanged, [this] { update (); });
    setFlags (ItemSendsGeometryChanges | ItemIsMovable | ItemIsSelectable);
}

void TaskBlock::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBlock (painter, option, widget);
}

void TaskBlock::paintBlock(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *, QPointF offset)
{
    auto rect = TaskBlock::boundingRect ();
    rect.moveTo (offset);
    painter->setFont (qApp->font ());

    {
        auto pen = option->state & QStyle::State_Selected ? QPen (blockSelectedBorder) : QPen (blockBorder);
        pen.setWidthF (2.0);
        painter->setPen (pen);
    }

    const auto metrics = QFontMetricsF (painter->font ());
    const auto h = metrics.height ();
    const auto w = metrics.width (name ());

    auto final_text = QString ();
    auto real_w = qreal {};

    if (w > rect.width ())
    {
        final_text = metrics.elidedText (name (), Qt::ElideMiddle, rect.width ());
        real_w = metrics.width (final_text);
    }
    else
    {
        final_text = name ();
        real_w = w;
    }

    painter->setBrush (option->state & QStyle::State_Selected ? blockSelectedArea :
                        option->state & QStyle::State_MouseOver ? blockHoveredArea :
                                                                blockArea);

    rect.setLeft (rect.left () + 2);
    rect.setRight (rect.right () - 2);
    painter->drawRect (rect);

    painter->setPen (option->state & QStyle::State_Selected ? blockArea.darker (): blockSelectedArea.darker ());

    painter->drawText (QRectF (QPointF (rect.left () + (rect.width () - real_w) / 2, rect.top () + (rect.height () - h) / 2), QSizeF (real_w, h)), final_text);
}

QRectF TaskBlock::boundingRect () const
{
    auto p = parentItem ();
    if (p == null)
    {
        return {};
    }

    return QRectF (0, 0, p->boundingRect ().width (), time_ * ratio_);
}

qreal TaskBlock::textHeight() const noexcept
{
    return QFontMetricsF (qApp->font ()).height ();
}

} // namespace HmAnalysis
