﻿#pragma once

#include <base/lang/not_null.h>
#include "Ribbon.h"

class HmRibbon : public Ribbon
{
    Q_OBJECT
signals:
    void taskSetting ();
    void timeSetting ();
    void titleSetting ();
    void importHuman ();
    void importMachine ();
    void insertHuman ();
    void insertMachine ();
public:
    HmRibbon(QWidget * parent = null);
    void initConn ();
private:
    RibbonTool * taskSetting_ = null;
    RibbonTool * timeSetting_ = null;
    RibbonTool * titleSetting_ = null;
    RibbonTool * importHuman_ = null;
    RibbonTool * importMachine_ = null;
    RibbonTool * insertHuman_ = null;
    RibbonTool * insertMachine_ = null;
};

