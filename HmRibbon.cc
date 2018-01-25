#include "HmRibbon.h"
#include <base/lang/move.hpp>
#include <QDebug>


HmRibbon::HmRibbon(QWidget *parent)
    :Ribbon (parent)
{

    {
        std::array<UiGroup, 1> tab_content;

        ButtonCell b;

        b.add ("人", QPixmap ("png/作业员.png"), importHuman_);
        b.add ("机器", QPixmap ("png/导出.png"), importMachine_);
        b.set_title ("导入(vaf file)");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "编辑");
    }

    {
        std::array<UiGroup, 1> tab_content;

        ButtonCell b;

        b.add ("作业员", QPixmap ("png/作业员.png"), taskSetting_);
        b.add ("时间", QPixmap ("png/单位.png"), timeSetting_);
        b.add ("表头", QPixmap ("png/搜索.png"), titleSetting_);
        b.set_title ("属性设置");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "设置");
    }

    {
        std::array<UiGroup, 1> tab_content;

        ButtonCell b;

        b.add ("人", QPixmap ("png/作业员.png"), HumanAddTask_);
        b.add ("机器", QPixmap ("png/导出.png"), MachineAddTask_);
        b.set_title ("作业内容");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "插入");
    }

    initConn ();
}

void HmRibbon::initConn()
{
    connect (taskSetting_, &RibbonTool::clicked, this, &HmRibbon::taskSetting);
    connect (timeSetting_, &RibbonTool::clicked, this, &HmRibbon::timeSetting);
    connect (titleSetting_, &RibbonTool::clicked, this, &HmRibbon::titleSetting);
    connect (importHuman_, &RibbonTool::clicked, this, &HmRibbon::importHuman);
    connect (importMachine_, &RibbonTool::clicked, this, &HmRibbon::importMachine);
    connect (HumanAddTask_, &RibbonTool::clicked, this, &HmRibbon::HumanAddTask);
    connect (MachineAddTask_, &RibbonTool::clicked, this, &HmRibbon::MachineAddTask);


    connect (this, &HmRibbon::subwindowActive, taskSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, timeSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, titleSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, importHuman_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, importMachine_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, HumanAddTask_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, MachineAddTask_, &RibbonTool::setEnabled);


}
