#include <Controls/ProgressBar.h>
#include <Render/Graphics.h>

namespace RanGui
{
    ProgressBar::ProgressBar(float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height), m_progress(0.0f)
    {
    }

    void ProgressBar::Initialize(Graphics &graphics)
    {
        Renderable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();

        renderTarget->CreateSolidColorBrush(ControlColor::LightGray, &m_pBackgroundBrush);
        renderTarget->CreateSolidColorBrush(ControlColor::Green, &m_pForegroundBrush);
    }

    void ProgressBar::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBackgroundBrush.Get());
        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_width * m_progress, m_y + m_height), m_pForegroundBrush.Get());
    }

    void ProgressBar::SetProgress(float progress)
    {
        m_progress = min(max(progress, 0.0f), 1.0f);
    }
}