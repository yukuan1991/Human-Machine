#include <mutex>
#include <thread>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <QApplication>
#include "Balance/HmAnalysis/HaView.h"
#include <QStyleFactory>
#include <QStyle>
#include <boost/filesystem.hpp>
#include <base/io/file/file.hpp>
#include <boost/range/adaptors.hpp>
#include "HmMain.h"
#include "verification/verification.h"
#include <QMessageBox>
#include <QTimer>

using namespace std;

void setStyle ()
{
    using namespace boost::filesystem;

    auto rng = boost::make_iterator_range (directory_iterator ("."), directory_iterator ());

    std::string qss;
    for (auto & it : rng)
    {
        if (it.path ().extension ().string () == ".css")
        {
            auto res = file::read_all (it.path ().string ().data ());
            if (res)
            {
                qss += res.value ();
            }
        }
    }
    qApp->setStyleSheet (QString::fromStdString (qss));
    qApp->setFont (QFont ("宋体", 11));
}

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    if(!verification_process())
    {
        return -1;
    }

    app.setStyle (QStyleFactory::create ("fusion"));
    setStyle ();

    HmMain m;
    m.resize (1440, 900);
    m.setWindowTitle("Human-Machine Operation Study");
    m.show ();

    QTimer timer;
    timer.setInterval (1000);
    timer.setSingleShot (true);
    QObject::connect (&timer, &QTimer::timeout, [&] { check_date (); timer.start (); });
    timer.start ();

    app.exec ();

    return 0;
}
