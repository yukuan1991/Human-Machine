#pragma once
#include <QColor>

namespace Balance
{
constexpr auto channelWidth = 240;
constexpr auto channelHeight = 750;
constexpr auto channelGap = 10;
constexpr auto channelGrayHeight = 100;
inline const auto blockBorder = QColor (236, 135, 14);
inline const auto blockArea = QColor (239, 244, 0);
inline const auto blockHoveredArea = QColor (254, 248, 134);
inline const auto blockSelectedBorder = QColor (91, 189, 43);
inline const auto blockSelectedArea = QColor (200, 226, 177);
inline const auto sceneBackground = QColor (0xDD, 0xDD, 0xDD);
}

