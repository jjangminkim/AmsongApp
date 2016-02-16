#include "stdafx.h"
#include "Shapes.h"

#include <boost/foreach.hpp>

using namespace Amsong;
using namespace Gdiplus;

void Shape::setPoint(int i, const Gdiplus::Point& point)
{
    ASSERT(_points.size() <= static_cast<unsigned int>(i));
    _points[i] = point;
}

///////////////////////////////////////////////////////////////////////////

void Polygon::moveHorizontally(int step)
{
    for (unsigned int i = 0; i < _points.size(); ++i) {
        _points[i].X += step;
    }
}

void Polygon::moveVertically(int step)
{
    for (unsigned int i = 0; i < _points.size(); ++i) {
        _points[i].Y += step;
    }
}

void Polygon::drawShape(Gdiplus::Graphics* g)
{
    Pen pen(Color(255, 0, 0, 0));
    g->DrawPolygon(&pen, &_points[0], _points.size());
}

void Polygon::fillShape(Gdiplus::Graphics* g)
{
    SolidBrush brush(_color);
    g->FillPolygon(&brush, &_points[0], _points.size());
}

///////////////////////////////////////////////////////////////////////////

Pie::Pie(const PointArray& points, const Gdiplus::Color& color, const Angle& angle)
{
    // FIXME : Pie에 입력가능한 Point는 2개뿐이다.
    init(points, color, angle);
}

void Pie::init(const PointArray& points, const Gdiplus::Color& color, const Angle& angle)
{
    Shape::init(points, color);
    _angle = angle;
}

void Pie::setSize(int width, int height)
{
    int centerX = _points[0].X + (this->width() / 2);
    int centerY = _points[0].Y + (this->height() / 2);

    int halfWidth = width / 2;
    int halfHeight = height / 2;

    _points[0].X = centerX - halfWidth;
    _points[0].Y = centerY - halfHeight;
    _points[1].X = centerX + halfWidth;
    _points[1].Y = centerY + halfHeight;
}

int Pie::width() const
{
    return (_points[1].X - _points[0].X);
}

int Pie::height() const
{
    return (_points[1].Y - _points[0].Y);
}

void Pie::moveHorizontally(int step)
{
    for (unsigned int i = 0; i < MAX_POINTS; ++i) {
        _points[i].X += step;
    }
}

void Pie::moveVertically(int step)
{
    for (unsigned int i = 0; i < MAX_POINTS; ++i) {
        _points[i].Y += step;
    }
}

void Pie::drawShape(Gdiplus::Graphics* g)
{
     Rect rect(_points[0].X, _points[0].Y, width(), height());
     Pen pen(Color(255, 0, 0, 0));
     g->DrawPie(&pen, rect, _angle.first, _angle.second);
}

void Pie::fillShape(Gdiplus::Graphics* g)
{
    Rect rect(_points[0].X, _points[0].Y,
              (_points[1].X - _points[0].X), (_points[1].Y - _points[0].Y));
    SolidBrush brush(_color);
    g->FillPie(&brush, rect, _angle.first, _angle.second);
}