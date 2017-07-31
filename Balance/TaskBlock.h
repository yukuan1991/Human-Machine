#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>
#include <base/lang/move.hpp>

namespace Balance {

class TaskBlock : public QGraphicsObject
{
    Q_OBJECT
signals:
    void timeChanged (qreal);
    void nameChanged (const QString &);
    void ratioChanged (qreal);
public:
    //struct make_TaskBlock1 { qreal time_ = 0; const QString& name_ = {}; QGraphicsItem * parent = nullptr; };

    TaskBlock(QGraphicsItem * parent);

    void setTime (qreal time) { time_ = time; emit timeChanged (time_); }
    qreal taskSpan () const noexcept { return time_; }

    void setName (QString name) { name_ = ::move (name); emit nameChanged (name_); }
    const QString & name () const noexcept { return name_; }

    void setRatio (qreal r) { ratio_ = r; ratioChanged (ratio_); }
    qreal ratio () const noexcept { return ratio_; }

    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = null) override;
    void paintBlock (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * = null, QPointF offset = QPointF (0, 0));
    QRectF boundingRect () const override;

    qreal textHeight () const noexcept;
protected:
private:
    qreal time_ = 0;
    QString name_;
    qreal ratio_;
};

} // namespace HmAnalysis

