#include "HaView.h"
#include "Balance/HmAnalysis/HaBlock.h"
#include "Balance/HmAnalysis/HaChannel.h"
#include "Balance/Channel.h"
#include "Balance/ResourceScene.h"
#include "Balance/parameters.hpp"
#include <QMouseEvent>
#include <QToolTip>
#include <QMenu>
#include "Balance/HmAnalysis/AddTaskDlg.h"
#include <QMessageBox>
#include <QInputDialog>
#include <boost/range/algorithm.hpp>

namespace Balance {
namespace HmAnalysis {

using std::make_unique;

HaView::HaView(QWidget *parent)
    :QGraphicsView (parent)
    ,scene_ ([this] {auto s = make_unique<ResourceScene> (); this->setScene (s.get ()); return s; } ())
{
    scene_->setSceneRect (0, 0, 1024, 768);
    setRenderHint (QPainter::Antialiasing);
    setMouseTracking (true);
    setViewportUpdateMode (QGraphicsView::FullViewportUpdate);

    int i = 0;

    {
        auto item = new HaChannel;
        scene_->addItem (item);
        item->setObjectName ("人");
        human_ = item;
        item->setPos ((channelWidth + channelGap) * i, 10);
        connect (this, &HaView::totalTimeChanged, item, &HaChannel::setTotalTime);
        i++;
    }

    for ( ;i < 4; i ++)
    {
        auto item = new HaChannel; scene_->addItem (item);
        machines_.emplace_back (item);
        item->setObjectName ("机器" + QString::number (i));
        connect (this, &HaView::totalTimeChanged, item, &HaChannel::setTotalTime);
        item->setPos ((channelWidth + channelGap) * i, 10);
    }
}


HaView::~HaView()
{

}

void HaView::mouseMoveEvent(QMouseEvent *event)
{
    SCOPE_EXIT {  QGraphicsView::mouseMoveEvent (event); };
    auto item = itemAt (event->pos ());
    const auto casted_item = dynamic_cast<HaBlock *> (item);
    if (casted_item == null)
    {
        return;
    }

    const auto tip = casted_item->name () + "\n" "任务用时:" +
            QString::number (casted_item->taskSpan ()) + "\n"
            "起始时间:" + QString::number (casted_item->startTime ());
            ;

    QToolTip::showText (QCursor::pos (), tip);
}

void HaView::mouseReleaseEvent (QMouseEvent *event)
{
    SCOPE_EXIT {  QGraphicsView::mouseReleaseEvent (event); };
    const auto button = event->button ();
    if (button != Qt::RightButton)
    {
        return;
    }

    const auto item = itemAt (event->pos ());

    if (auto bar = dynamic_cast<Channel *> (item); bar != null)
    {
        barClicked (bar);
        return;
    }

    if (auto block = dynamic_cast<HaBlock *> (item); block != null)
    {
        blockClicked (block);
    }
}

void HaView::taskSetting()
{
    if (const auto s = scene (); s)
    {
        if (const auto items = s->selectedItems (); items.size () == 1)
        {
            if (auto item = dynamic_cast<HaBlock * > (items.at (0)); item)
            {
                setTaskAttribute (item);
            }
        }
        else
        {
            QMessageBox::information (this, "作业设置", "请选中单个作业");
        }
    }
    else
    {
        QMessageBox::information (this, "作业设置", "scene -> null");
    }
}

void HaView::setTitle ()
{
    //QDialog dlg (this);
}

QStringList HaView::intersectedChannels()
{
    return {};
    //QStringList list;
    //if (human_->intersect ())
    //{
    //    list << human_->name ();
    //}
    //for ()
}

QStringList HaView::machines() const
{
    QStringList list;
    for (auto it : machines_)
    {
        list << it->objectName ();
    }

    return list;
}

void HaView::importData(const QString &channel, const std::vector<std::pair<QString, qreal> > &data)
{
    using namespace boost::range;
    const auto found = find_if (machines_, [&] (auto & it) { return it->objectName () == channel; });
    if (found == end (machines_))
    {
        return;
    }

    (*found)->importTask (data);
}


void HaView::barClicked(Channel * bar)
{
    QMenu menu;
    auto addTask = menu.addAction ("增加作业");
    auto setHeader = menu.addAction ("设置表头");
    auto clearItems = menu.addAction ("清空任务");

    connect (addTask, &QAction::triggered, [&]
    {
        AddTaskDlg dlg (this);
        const auto res = dlg.exec ();

        if (QDialog::Accepted != res)
        {
            return;
        }

        const auto time = dlg.taskTime ();
        const auto name = dlg.taskName ();

        if (time < 0.1)
        {
            QMessageBox::information (this, "增加作业", "作业时间为" + QString::number (time) + " 时间太小 无法添加");
            return;
        }

        bar->addTask ({.taskName = name, .time = time});
    });

    connect (setHeader, &QAction::triggered, [&]
    {
        bool isOk = false;
        const auto text = QInputDialog::getText (this, "表头", "新表头", QLineEdit::Normal, bar->objectName (), &isOk);
        if (isOk)
        {
            bar->setObjectName (text);
        }
    });

    connect (clearItems, &QAction::triggered, [&]
    {
        bar->clearItems ();
    });

    menu.exec (QCursor::pos ());
}

void HaView::blockClicked(HaBlock *block)
{
    QMenu menu (this);
    connect (menu.addAction ("删除作业"), &QAction::triggered, [this, block] {
        block->deleteLater ();
    });

    connect (menu.addAction ("设置作业名"), &QAction::triggered, [this, block] {
        bool isOk = false;
        const auto text = QInputDialog::getText (this, "表头", "新表头", QLineEdit::Normal, block->name (), &isOk);
        if (isOk)
        {
            block->setName (text);
        }
    });

    connect (menu.addAction ("设置作业时间"), &QAction::triggered, [this, block] {
        bool isOk = false;
        const auto time = QInputDialog::getDouble (this, "表头", "新表头", block->taskSpan (), 0.1, 1000, 2, &isOk);
        if (isOk)
        {
            block->setTime (time);
        }
    });

    menu.exec (QCursor::pos ());
}


void HaView::setTaskAttribute(not_null<HaBlock *> block)
{
    AddTaskDlg dlg (this);

    const auto oldName = block->name ();
    const auto oldTime = block->taskSpan ();
    dlg.setTaskName (oldName);
    dlg.setTaskTime (oldTime);

    const auto res = dlg.exec ();

    if (QDialog::Accepted != res)
    {
        return;
    }

    const auto time = dlg.taskTime ();
    const auto name = dlg.taskName ();

    if (time < 0.1)
    {
        QMessageBox::information (this, "作业", "作业时间为" + QString::number (time) + " 时间太短");
        return;
    }
    block->setName (name);
    block->setTime (time);
}

void HaView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent (event);
    fitInView (scene ()->sceneRect ());
}

} // namespace AmAnalysis
} // namespace Balance
