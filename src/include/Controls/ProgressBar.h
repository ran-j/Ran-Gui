#pragma once
#include <Controls/Control.h>

namespace RanGui
{
    class ProgressBar : public Control
    {
    public:
        ProgressBar(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        // Set the progress of the progress bar (0.0f - 1.0f)
        void SetProgress(float progress);

    private:
        float m_progress;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pForegroundBrush;
    };
}