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
        b.set_title ("导入分析文件");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "导入");
    }

    {
        std::array<UiGroup, 1> tab_content;

        ButtonCell b;

        b.add ("人", QPixmap ("png/作业员.png"), insertHuman_);
        b.add ("机器", QPixmap ("png/导出.png"), insertMachine_);
        b.set_title ("插入作业内容");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "插入");
    }

    {
        std::array<UiGroup, 1> tab_content;

        ButtonCell b;

        b.add ("作业设置", QPixmap ("png/作业员.png"), taskSetting_);
        b.add ("时间设置", QPixmap ("png/单位.png"), timeSetting_);
        b.add ("表头设置", QPixmap ("png/搜索.png"), titleSetting_);
        b.set_title ("");
        tab_content.at (0) = ::move (b);

        this->setupTab (tab_content, "设置");
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
    connect (insertHuman_, &RibbonTool::clicked, this, &HmRibbon::insertHuman);
    connect (insertMachine_, &RibbonTool::clicked, this, &HmRibbon::insertMachine);


    connect (this, &HmRibbon::subwindowActive, taskSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, timeSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, titleSetting_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, importHuman_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, importMachine_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, insertHuman_, &RibbonTool::setEnabled);
    connect (this, &HmRibbon::subwindowActive, insertMachine_, &RibbonTool::setEnabled);


}
