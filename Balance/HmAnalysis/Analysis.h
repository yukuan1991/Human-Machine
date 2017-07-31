#pragma once

#include <QWidget>
#include <base/lang/not_null.h>

namespace Balance {
namespace HmAnalysis {

namespace Ui {
class Analysis;
}
class HaView;
class HaChannel;

class Analysis : public QWidget
{
    Q_OBJECT
public:
    explicit Analysis(QWidget *parent = 0);
    ~Analysis();
    void taskSetting ();
    void setTotalTime (qreal totalTime);
    qreal totalTime () const;
    void intersect ();
    not_null<HaView *> view () noexcept;
private:
    Ui::Analysis *ui;
};


} // namespace HmAnalysis
} // namespace Balance
