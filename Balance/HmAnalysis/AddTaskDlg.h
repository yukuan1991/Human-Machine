#pragma once

#include <QDialog>
#include <base/lang/not_null.h>

namespace Balance {
namespace HmAnalysis {

namespace Ui {
class AddTaskDlg;
}

class AddTaskDlg : public QDialog
{
    Q_OBJECT
public:
    explicit AddTaskDlg(QWidget *parent = null);
    ~AddTaskDlg() override;
    void setTaskName (const QString & name);
    void setTaskTime (qreal time);

    QString taskName () const noexcept;
    qreal taskTime () const noexcept;
private:
    Ui::AddTaskDlg *ui;
};


} // namespace HmAnalysis
} // namespace Balance
