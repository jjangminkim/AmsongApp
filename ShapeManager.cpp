#include "stdafx.h"
#include "ShapeManager.h"
#include "AppTypes.h"

using namespace Amsong;

ShapeManager::ShapeManager()
{
    // Set Color Defines
    _triangleColors[BIG_REV_TRI]    = CLR_BALL;
    _triangleColors[MID_REV_TRI]    = CLR_SECOND_BASE;
    _triangleColors[SMALL_REV_TRI]  = CLR_FIRST_BASE;
    _triangleColors[MINI_REV_TRI]   = CLR_STRIKE;
    _triangleColors[MICRO_REV_TRI]  = CLR_HP;

    _pieColors[BIG_CENTER_PIE]  = CLR_HOMERUN;
    _pieColors[BIG_LEFT_PIE]    = CLR_THIRD_BASE;
    _pieColors[BIG_RIGHT_PIE]   = CLR_THIRD_BASE;
    _pieColors[MID_PIE]         = CLR_SECOND_BASE;
    _pieColors[SMALL_PIE]       = CLR_FIRST_BASE;
}

void ShapeManager::setTriangle(int id, const PointArray& points)
{
    _triangles[id].init(points, _triangleColors[id]);
}

void ShapeManager::setRectangle(int id, const PointArray& points)
{
    _rectangles[id].init(points, CLR_OUT);
}

void ShapeManager::setPie(int id, const PointArray& points, const Angle& angle)
{
    _pies[id].init(points, _pieColors[id], angle);
}

void ShapeManager::moveTrianglePoint(int id, int pointIndex, int x, int y)
{
    Gdiplus::Point point(x, y);
    _triangles[id].setPoint(pointIndex, point);
}

void ShapeManager::moveRetanglePoint(int id, int pointIndex, int x, int y)
{
    Gdiplus::Point point(x, y);
    _rectangles[id].setPoint(pointIndex, point);
}

void ShapeManager::setPieSize(int id, int width, int height)
{
    _pies[id].setSize(width, height);
}

void ShapeManager::moveAllHorizontally(int step)
{
    unsigned int i;
    for (i = 0; i < MAX_TRIS; ++i) {
        _triangles[i].moveHorizontally(step);
    }
    for (i = 0; i < MAX_RECTS; ++i) {
        _rectangles[i].moveHorizontally(step);
    }
    for (i = 0; i < MAX_PIES; ++i) {
        _pies[i].moveHorizontally(step);
    }
}

void ShapeManager::moveAllVerically(int step)
{
    unsigned int i;
    for (i = 0; i < MAX_TRIS; ++i) {
        _triangles[i].moveHorizontally(step);
    }
    for (i = 0; i < MAX_RECTS; ++i) {
        _rectangles[i].moveHorizontally(step);
    }
    for (i = 0; i < MAX_PIES; ++i) {
        _pies[i].moveHorizontally(step);
    }
}

void ShapeManager::drawAllShapes(Gdiplus::Graphics* g)
{
    unsigned int i;
    for (i = 0; i < MAX_TRIS; ++i) {
        _triangles[i].drawShape(g);
    }
    for (i = 0; i < MAX_RECTS; ++i) {
        _rectangles[i].drawShape(g);
    }
    for (i = 0; i < MAX_PIES; ++i) {
        _pies[i].drawShape(g);
    }
}

void ShapeManager::fillAllShapes(Gdiplus::Graphics* g)
{
    // 색을 채우는 순서는..
    // 삼각형 -> 반원 -> 사각형 순으로 한다.
    // 위와 같이 색을 채우면, 경계선에 닿았을 때..
    // 무조건 진루타를 치는 방향으로 결정된다.
    unsigned int i;
    for (i = 0; i < MAX_TRIS; ++i) {
        _triangles[i].fillShape(g);
    }
    for (i = 0; i < MAX_PIES; ++i) {
        _pies[i].fillShape(g);
    }
    for (i = 0; i < MAX_RECTS; ++i) {
        _rectangles[i].fillShape(g);
    }
}