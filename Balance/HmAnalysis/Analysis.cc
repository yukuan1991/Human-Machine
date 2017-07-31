#include "Analysis.h"
#include "ui_Analysis.h"
#include "HaChannel.h"

namespace Balance {
namespace HmAnalysis {

Analysis::Analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analysis)
{
    ui->setupUi(this);
}

Analysis::~Analysis()
{
    delete ui;
}

void Analysis::taskSetting()
{
    ui->view->taskSetting ();
}

void Analysis::setTotalTime(qreal totalTime)
{
    ui->view->setTotalTime (totalTime);
}

qreal Analysis::totalTime() const
{
    return ui->view->totalTime ();
}

not_null<HaView *> Analysis::view() noexcept
{
    return ui->view;
}


} // namespace HmAnalysis
} // namespace Balance
