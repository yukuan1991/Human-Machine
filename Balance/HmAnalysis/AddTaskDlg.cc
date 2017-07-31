#include "AddTaskDlg.h"
#include "ui_AddTaskDlg.h"
#include <QDoubleValidator>

namespace Balance {
namespace HmAnalysis {

AddTaskDlg::AddTaskDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskDlg)
{
    ui->setupUi(this);
    ui->editTime->setValidator (new QDoubleValidator (0.1, 10000, 2, ui->editTime));
}

AddTaskDlg::~AddTaskDlg()
{
    delete ui;
}

void AddTaskDlg::setTaskName(const QString &name)
{
    ui->editTask->setText (name);
}

void AddTaskDlg::setTaskTime(qreal time)
{
    ui->editTime->setText (QString::number (time));
}


QString AddTaskDlg::taskName() const noexcept
{
    return ui->editTask->text ();
}

qreal AddTaskDlg::taskTime() const noexcept
{
    return ui->editTime->text ().toDouble ();
}

} // namespace HmAnalysis
} // namespace Balance
