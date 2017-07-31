#include "Balance/ResourceScene.h"
#include <QPainter>
#include "Balance/parameters.hpp"

namespace Balance
{

ResourceScene::ResourceScene(QObject *parent)
    :QGraphicsScene (parent)
{
    setBackgroundBrush (sceneBackground);
}

}
