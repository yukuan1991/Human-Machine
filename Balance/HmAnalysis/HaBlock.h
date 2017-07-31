#pragma once
#include "Balance/TaskBlock.h"

namespace Balance {
namespace HmAnalysis {

class HaBlock : public TaskBlock
{
    Q_OBJECT
signals:
    void selectedChanged (bool);
public:
    HaBlock (QGraphicsItem * parent);
    QVariant itemChange (GraphicsItemChange change, const QVariant & input) override;
    void onSelected (bool b);
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = null) override;
    QPainterPath shape () const override;
    QRectF boundingRect () const override;
    QRectF singleBoundingRect () const;
    qreal startTime ();
    static qreal posToTime (qreal pos, qreal totalTime, qreal fontOffset);
    static qreal timeToPos (qreal startTime, qreal totalTime, qreal fontOffset);
public slots:
    void refreshRatio ();
};

}
}
