#include "stdafx.h"
#include "Shapes.h"
#include "AppTypes.h"

#include <boost/foreach.hpp>

using namespace Amsong;
using namespace Gdiplus;

void Shape::setPoint(int i, const Gdiplus::Point& point)
{
    ASSERT(static_cast<unsigned int>(i) < _points.size());
    _points[i] = point;
}

bool Shape::allPointsAreZero()
{
    bool allZero = true;
    for (unsigned int i = 0; i < _points.size(); ++i) {
        if (0 != _points[i].X || 0 != _points[i].Y) {
            allZero = false;
            break;
        }
    }

    return allZero;
}

void Shape::loadPoints(CWinApp* app, const CString& keyName)
{
    CString keyNameX, keyNameY;
    for (unsigned int i = 0; i < _points.size(); ++i) {
        keyNameX = keyName;
        keyNameX.AppendFormat(_T("_P%d_X"));
        _points[i].X = app->GetProfileInt(APP_NAME, keyNameX, 0);

        keyNameY = keyName;
        keyNameY.AppendFormat(_T("_P%d_Y"));
        _points[i].Y = app->GetProfileInt(APP_NAME, keyNameY, 0);
    }
}

void Shape::savePoints(CWinApp* app, const CString& keyName)
{
    CString keyNameX, keyNameY;
    for (unsigned int i = 0; i < _points.size(); ++i) {
        keyNameX = keyName;
        keyNameX.AppendFormat(_T("_P%d_X"));
        app->WriteProfileInt(APP_NAME, keyNameX, _points[i].X);

        keyNameY = keyName;
        keyNameY.AppendFormat(_T("_P%d_Y"));
        app->WriteProfileInt(APP_NAME, keyNameY, _points[i].Y);
    }
}

void Shape::moveHorizontally(int step)
{
    for (unsigned int i = 0; i < _points.size(); ++i) {
        _points[i].X += step;
    }
}

void Shape::moveVertically(int step)
{
    for (unsigned int i = 0; i < _points.size(); ++i) {
        _points[i].Y += step;
    }
}

///////////////////////////////////////////////////////////////////////////

void Polygon::drawShape(Gdiplus::Graphics* g)
{
    if (!allPointsAreZero()) {
        Pen pen(Color(255, 0, 0, 0), 2.0F);
        g->DrawPolygon(&pen, &_points[0], _points.size());
    }
}

void Polygon::fillShape(Gdiplus::Graphics* g)
{
    if (!allPointsAreZero()) {
        SolidBrush brush(_color);
        g->FillPolygon(&brush, &_points[0], _points.size());
    }
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

void Pie::drawShape(Gdiplus::Graphics* g)
{
    if (!allPointsAreZero()) {
        Rect rect(_points[0].X, _points[0].Y, width(), height());
        Pen pen(Color(255, 0, 0, 0), 2.0F);
        g->DrawPie(&pen, rect, _angle.first, _angle.second);
    }
}

void Pie::fillShape(Gdiplus::Graphics* g)
{
    if (!allPointsAreZero()) {
        Rect rect(_points[0].X, _points[0].Y,
                  (_points[1].X - _points[0].X), (_points[1].Y - _points[0].Y));
        SolidBrush brush(_color);
        g->FillPie(&brush, rect, _angle.first, _angle.second);
    }
}
