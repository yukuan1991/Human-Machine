#pragma once
#include <QGraphicsObject>
#include <base/lang/not_null.h>
#include <QFont>


namespace Balance
{
class Channel : public QGraphicsObject
{
    Q_OBJECT
signals:
    void fontChanged (const QFont &);
public:
    Channel(QGraphicsItem * parent = null);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = null) override;
    QRectF boundingRect () const override;

    //const QString & name () const noexcept { return name_; }
    //void setName (QString name) noexcept { name_ = std::move (name); nameChanged (name_); }

    /// 标题的字体
    const QFont & font () const noexcept {  return font_; }
    /// 设置标题的字体
    void setFont (const QFont & f) { font_ = f; fontChanged (font_); }
    void clearItems ();


    struct add_task { const QString & taskName; qreal time; qreal startAt = 0; };
    /// 增加任务 taskName -> 任务名称, time -> 任务用时, startAt -> 起始时间
    virtual void addTask (add_task) = 0;
private:
    QFont font_;
};

}

