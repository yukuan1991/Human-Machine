﻿#include "HmMain.h"
#include <Balance/HmAnalysis/HaView.h>
#include <QMdiSubWindow>
#include <QDebug>
#include "Balance/HmAnalysis/Analysis.h"
#include "ui_HmMain.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "Balance/HmAnalysis/HaView.h"
#include <base/io/file/file.hpp>
#include <base/utils/charset.hpp>
#include "openvaf.h"


using namespace Balance::HmAnalysis;

HmMain::HmMain(QWidget *parent) :
    QWidget(parent),
    ui(new ::Ui::HmMain)
{
    ui->setupUi(this);
    initConn ();
    ui->mdi->setViewMode (QMdiArea::TabbedView);
    set_button_enabled();
}

void HmMain::initConn()
{
    connect (ui->rib, &Ribbon::fileNew, this, &HmMain::onFileNew);
    connect (ui->rib, &Ribbon::fileExit, this, &HmMain::close);
    connect (ui->rib, &HmRibbon::taskSetting, this, &HmMain::onTaskSetting);
    connect (ui->rib, &HmRibbon::timeSetting, this, &HmMain::onTimeSetting);
    connect (ui->rib, &HmRibbon::fileSave, this, &HmMain::onFileSave);
    connect (ui->rib, &HmRibbon::importHuman, this, &HmMain::onImportHuman);
    connect (ui->rib, &HmRibbon::importMachine, this, &HmMain::onImportMachine);
    connect (ui->rib, &HmRibbon::HumanAddTask, this, &HmMain::onHumanAddTask);
    connect (ui->rib, &HmRibbon::MachineAddTask, this, &HmMain::onMachineAddTask);


    connect (ui->rib, &HmRibbon::titleSetting, this, &HmMain::onTitleSetting);
    connect (ui->mdi, &QMdiArea::subWindowActivated, this, &HmMain::set_button_enabled);
}

HmMain::~HmMain()
{
    delete ui;
}

Balance::HmAnalysis::Analysis *HmMain::activeWindow()
{
    if (auto s = ui->mdi->activeSubWindow (); s)
    {
        if (auto w = dynamic_cast<Analysis *> (s->widget ()); w)
        {
            return w;
        }
    }

    return null;
}

void HmMain::set_button_enabled()
{
    const auto state = (activeWindow() != nullptr);
    ui->rib->subwindowActive(state);
}

void HmMain::onFileNew ()
{
    bool isOk = false;
    auto totalTime = QInputDialog::getDouble (this, "总时间", "请输入总时间", 10, 0, 100000, 2, &isOk);
    if (isOk)
    {
        createWindow ({.totalTime = totalTime, .title = "未命名"});
    }
}

void HmMain::onTaskSetting()
{
    if (auto w = activeWindow (); w)
    {
        w->taskSetting ();
    }
}

void HmMain::onTimeSetting()
{
    if (auto w = activeWindow (); w)
    {
        bool isOk = false;
        auto totalTime = QInputDialog::getDouble (this, "总时间", "请输入总时间", w->totalTime (), 0, 100000, 2, &isOk);
        w->setTotalTime (totalTime);
    }
}

void HmMain::onTitleSetting()
{
    if (auto w = activeWindow (); w)
    {
        w->view ()->setTitle ();
    }
}

void HmMain::onFileSave()
{
    if (auto w = activeWindow (); w)
    {
        //w->view ()->checkIntersect ();
    }
}

void HmMain::onImportHuman()
{
    if(auto w = activeWindow(); w)
    {
        auto view = w->view ();

        if (const auto fileName = QFileDialog::getOpenFileName(this, "导入", ".", "视频分析结果 (*.vaf)").toStdString ();
                not fileName.empty ())
        {
            if (auto content = file::read_all (::utf_to_sys (fileName).data ());
                    content)
            {
                if (const auto vafContent = readVaf (content.value ());
                        not vafContent.empty ())
                {
                    std::vector<std::pair<QString, qreal>> data;
                    for (auto & it : vafContent)
                    {
                        data.emplace_back (it.name, it.stdTime);
                    }
                    view->importHuman (data);
                }
                else
                {
                    QMessageBox::information (this, "文件", "文件信息无法读取");
                }
            }
            else
            {
                QMessageBox::information (this, "文件", "系统错误,无法读取文件");
            }
        }

    }
}

void HmMain::onImportMachine()
{
    auto w = activeWindow ();
    if (w == null)
    {
        return;
    }

    auto view = w->view ();
    const auto list = view->machines ();

    QInputDialog dlg (this);
    dlg.setComboBoxEditable (false);
    dlg.setComboBoxItems (list);
    dlg.setLabelText ("选择机器");
    dlg.setWindowTitle ("导入机器任务");

    const auto res = dlg.exec ();

    if (res != QInputDialog::Accepted)
    {
        return;
    }

    const auto fileName = QFileDialog::getOpenFileName(this, "导入", ".", "视频分析结果 (*.vaf)").toStdString ();
    if (fileName.empty ())
    {
        return;
    }

    auto content = file::read_all (::utf_to_sys (fileName).data ());
    if (!content)
    {
        QMessageBox::information (this, "文件", "系统错误,无法读取文件");
        return;
    }

    const auto vafContent = readVaf (content.value ());
    if (vafContent.empty ())
    {
        QMessageBox::information (this, "文件", "文件信息无法读取");
        return;
    }

    std::vector<std::pair<QString, qreal>> data;
    for (auto & it : vafContent)
    {
        data.emplace_back (it.name, it.stdTime);
    }
    view->importData (dlg.textValue (), data);
}

void HmMain::onHumanAddTask()
{
    if (auto w = activeWindow(); w)
    {
        auto view = w->view();
        view->onHumanAddTask();
    }
}

void HmMain::onMachineAddTask ()
{
    if(auto w = activeWindow(); w)
    {
        auto view = w->view();
        const auto list = view->machines();
        QInputDialog dlg (this);
        dlg.setComboBoxEditable (false);
        dlg.setComboBoxItems (list);
        dlg.setLabelText ("选择机器");
        dlg.setWindowTitle ("增加作业任务");

        if (const auto res = dlg.exec (); res == QInputDialog::Accepted)
        {
            view->onMachineAddTask(dlg.textValue ());
        }
    }
}

not_null<Balance::HmAnalysis::Analysis *> HmMain::createWindow(HmMain::_createWindow param)
{
    auto view = new Analysis (this);
    view->setAttribute (Qt::WA_DeleteOnClose, true);

    auto sub = ui->mdi->addSubWindow (view);
    sub->setWindowTitle (param.title);
    view->setTotalTime (param.totalTime);

    view->setWindowState (Qt::WindowMaximized);
    return view;
}

