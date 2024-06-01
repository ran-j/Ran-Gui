#pragma once

#include <d2d1.h>

typedef D2D1_COLOR_F RAN_GUI_COLOR_F;

namespace ControlColor
{
    // Basic Colors
    const RAN_GUI_COLOR_F Black = D2D1::ColorF(D2D1::ColorF::Black);
    const RAN_GUI_COLOR_F White = D2D1::ColorF(D2D1::ColorF::White);

    // Additional Colors
    const RAN_GUI_COLOR_F Red = D2D1::ColorF(D2D1::ColorF::Red);
    const RAN_GUI_COLOR_F Green = D2D1::ColorF(D2D1::ColorF::Green);
    const RAN_GUI_COLOR_F Blue = D2D1::ColorF(D2D1::ColorF::Blue);
    const RAN_GUI_COLOR_F Yellow = D2D1::ColorF(D2D1::ColorF::Yellow);
    const RAN_GUI_COLOR_F Orange = D2D1::ColorF(D2D1::ColorF::Orange);
    const RAN_GUI_COLOR_F Purple = D2D1::ColorF(D2D1::ColorF::Purple);
    const RAN_GUI_COLOR_F Pink = D2D1::ColorF(D2D1::ColorF::Pink);

    // Shades of Gray
    const RAN_GUI_COLOR_F LightGray = D2D1::ColorF(0.9f, 0.9f, 0.9f, 1.0f);  // Light Gray
    const RAN_GUI_COLOR_F Gray = D2D1::ColorF(0.7f, 0.7f, 0.7f, 1.0f);       // Gray
    const RAN_GUI_COLOR_F DarkGray = D2D1::ColorF(0.5f, 0.5f, 0.5f, 1.0f);   // Dark Gray
    const RAN_GUI_COLOR_F BorderGray = D2D1::ColorF(0.3f, 0.3f, 0.3f, 1.0f); // Border Gray

    // Custom Colors
    const RAN_GUI_COLOR_F LightBlue = D2D1::ColorF(0.68f, 0.85f, 0.90f, 1.0f);       // Light Blue
    const RAN_GUI_COLOR_F DarkBlue = D2D1::ColorF(0.12f, 0.56f, 0.78f, 1.0f);        // Dark Blue
    const RAN_GUI_COLOR_F DarkSlateGray = D2D1::ColorF(D2D1::ColorF::DarkSlateGray); // Dark Slate Gray
    const RAN_GUI_COLOR_F LightGreen = D2D1::ColorF(0.56f, 0.93f, 0.56f, 1.0f); // Light Green
}
