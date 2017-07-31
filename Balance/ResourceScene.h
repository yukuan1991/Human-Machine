#pragma once

#include <QGraphicsScene>
#include <base/lang/not_null.h>


namespace Balance
{

class ResourceScene : public QGraphicsScene
{
public:
    ResourceScene(QObject * parent = null);
};

}

