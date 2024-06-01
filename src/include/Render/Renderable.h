#pragma once

#include <Render/Graphics.h>

namespace RanGui
{
    class Renderable
    {
    protected:
        bool m_isVisible = true;
        Graphics *m_graphics = nullptr;
        float m_x, m_y, m_width, m_height;

    public:
        Renderable() = default;
        Renderable(float pos_x, float pos_y, float width, float height)
            : m_x(pos_x), m_y(pos_y), m_width(width), m_height(height) {}

        virtual ~Renderable() = default;

    public:
        virtual void Render(Graphics &graphics) = 0;
        virtual void Initialize(Graphics &graphics)
        {
            m_graphics = &graphics;
        };

    public:
        virtual bool IsVisible() const { return m_isVisible; }
        virtual void SetVisible(bool visible) { m_isVisible = visible; }

    public:
        virtual void SetPosition(float x, float y)
        {
            m_x = x;
            m_y = y;
        }
        virtual void SetSize(float width, float height)
        {
            m_width = width;
            m_height = height;
        }
        virtual void SetRelativePosition(float x, float y)
        {
            m_x += x;
            m_y += y;
        }
        virtual void SetRelativeSize(float width, float height)
        {
            m_width += width;
            m_height += height;
        }

        virtual float GetX() const { return m_x; }
        virtual float GetY() const { return m_y; }
        virtual float GetWidth() const { return m_width; }
        virtual float GetHeight() const { return m_height; }

    public:
        virtual bool Intersect(float x, float y) const
        {
            return x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height;
        }
    };
}