#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>


namespace Balance::HmAnalysis {

class ChannelTitle : public QGraphicsObject
{
    Q_OBJECT
signals:
    void titleChanged (const QString &);
public:

    ChannelTitle(QGraphicsItem * parent = null);
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = null) override;
    QRectF boundingRect () const override;
    const QString & title () const noexcept { return title_; }
    void setTitle (const QString & title) { title_ = title; titleChanged (title_); }
private:
    QString title_;
};

}

