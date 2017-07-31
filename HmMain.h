#ifndef HMMAIN_H
#define HMMAIN_H

#include <QWidget>
#include <base/lang/not_null.h>

namespace Ui {
class HmMain;
}

namespace Balance::HmAnalysis {
class Analysis;
}

class HmMain : public QWidget
{
    Q_OBJECT
public:
    explicit HmMain(QWidget *parent = 0);
    void initConn ();
    ~HmMain();
    Balance::HmAnalysis::Analysis * activeWindow ();
private:
    void set_button_enabled();
private:
    void onFileNew ();
    void onTaskSetting ();
    void onTimeSetting ();
    void onTitleSetting ();
    void onFileSave ();
    void onImportHuman ();
    void onImportMachine ();
    void onHumanAddTask ();
    void onMachineAddTask ();

    struct _createWindow { qreal totalTime; const QString & title; };
    not_null<Balance::HmAnalysis::Analysis *> createWindow(_createWindow para);

private:
    Ui::HmMain *ui;
};

#endif // HMMAIN_H
