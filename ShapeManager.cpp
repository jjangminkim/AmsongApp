#include "stdafx.h"
#include "ShapeManager.h"
#include "AppTypes.h"

using namespace Amsong;
using namespace Gdiplus;

#define DO_WORK_TO_ALL_SHAPES(func)     \
    unsigned int i;                     \
    for (i = 0; i < MAX_TRIS; ++i) {    \
        _triangles[i].func();           \
    }                                   \
    for (i = 0; i < MAX_PIES; ++i) {   \
        _pies[i].func();                \
    }                                   \
    for (i = 0; i < MAX_RECTS; ++i) {    \
        _rectangles[i].func();          \
    }

#define DO_WORK_TO_ALL_SHAPES_WITH_PARAM(func, param)   \
    unsigned int i;                                     \
    for (i = 0; i < MAX_TRIS; ++i) {                    \
        _triangles[i].func(param);                      \
    }                                                   \
    for (i = 0; i < MAX_PIES; ++i) {                   \
        _pies[i].func(param);                           \
    }                                                   \
    for (i = 0; i < MAX_RECTS; ++i) {                    \
        _rectangles[i].func(param);                     \
    }

#define DO_WORK_TO_ALL_SHAPES_WITH_KEY(func, param) \
    unsigned int i;                                 \
    CString key;                                    \
    for (i = 0; i < MAX_TRIS; ++i) {                \
        key.Format(_T("TRIANGLE%d"));               \
        _triangles[i].func(param, key);             \
    }                                               \
    for (i = 0; i < MAX_PIES; ++i) {               \
        key.Format(_T("PIE%d"));                    \
        _pies[i].func(param, key);                  \
    }                                               \
    for (i = 0; i < MAX_RECTS; ++i) {                \
        key.Format(_T("RECTANGLE%d"));              \
        _rectangles[i].func(param, key);            \
    }

ShapeManager::ShapeManager(CWinApp* app)
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

    initColors();

    // registry에 저장된 값이 있으면, 불러온다.
    CString key;
    key.Format(_T("RECTANGLE%d"), OUT_CENTER_RECT);
    _rectangles[OUT_CENTER_RECT].loadPoints(app, key);
    if (_rectangles[OUT_CENTER_RECT].allPointsAreZero()) {
        initPoints();
    }
    else {
        loadAllPositions(app);
    }
}

void ShapeManager::initPoints()
{
    // 기본 값으로 position setting.
    clearAllPositions();

    // BIG_REV_TRI
    PointArray points;
    points.push_back(Point(240, 360));
    points.push_back(Point(1040, 360));
    points.push_back(Point(640, 700));
    _triangles[BIG_REV_TRI].setPoints(points);
    points.clear();

    // MID_REV_TRI
    points.push_back(Point(340, 360));
    points.push_back(Point(940, 360));
    points.push_back(Point(640, 600));
    _triangles[MID_REV_TRI].setPoints(points);
    points.clear();

    // SMALL_REV_TRI
    points.push_back(Point(440, 360));
    points.push_back(Point(840, 360));
    points.push_back(Point(640, 500));
    _triangles[SMALL_REV_TRI].setPoints(points);
    points.clear();

    // MINI_REV_TRI
    points.push_back(Point(404, 500));
    points.push_back(Point(876, 500));
    points.push_back(Point(640, 700));
    _triangles[MINI_REV_TRI].setPoints(points);
    points.clear();

    // MICRO_REV_TRI
    points.push_back(Point(514, 500));
    points.push_back(Point(764, 500));
    points.push_back(Point(640, 600));
    _triangles[MICRO_REV_TRI].setPoints(points);
    points.clear();

    // PIES
    points.push_back(Point(240, 20));
    points.push_back(Point(1040, 700));
    Angle angle;
    angle = std::make_pair(180.0F, 180.0F);
    _pies[BIG_CENTER_PIE].setPoints(points);
    _pies[BIG_CENTER_PIE].setAngle(angle);

    points.push_back(Point(240, 20));
    points.push_back(Point(1040, 700));
    angle = std::make_pair(180.0F, 40.0F);
    _pies[BIG_LEFT_PIE].setPoints(points);
    _pies[BIG_LEFT_PIE].setAngle(angle);
    points.clear();

    points.push_back(Point(240, 20));
    points.push_back(Point(1040, 700));
    angle = std::make_pair(320.0F, 40.0F);
    _pies[BIG_RIGHT_PIE].setPoints(points);
    _pies[BIG_RIGHT_PIE].setAngle(angle);
    points.clear();

    points.push_back(Point(340, 120));
    points.push_back(Point(940, 600));
    angle = std::make_pair(180.0F, 180.0F);
    _pies[MID_PIE].setPoints(points);
    _pies[MID_PIE].setAngle(angle);
    points.clear();

    points.push_back(Point(440, 220));
    points.push_back(Point(840, 500));
    angle = std::make_pair(180.0F, 180.0F);
    _pies[SMALL_PIE].setPoints(points);
    _pies[SMALL_PIE].setAngle(angle);
    points.clear();

    // RECTANGLES
    points = makeRectanglePoints(280, 160, 50, 50);
    _rectangles[OUT_LEFT_RECT].setPoints(points);

    points = makeRectanglePoints(615, 30, 50, 50);
    _rectangles[OUT_CENTER_RECT].setPoints(points);

    points = makeRectanglePoints(950, 160, 50, 50);
    _rectangles[OUT_RIGHT_RECT].setPoints(points);

    points = makeRectanglePoints(430, 180, 40, 40);
    _rectangles[MID_LEFT_RECT].setPoints(points);

    points = makeRectanglePoints(810, 180, 40, 40);
    _rectangles[MID_RIGHT_RECT].setPoints(points);

    points = makeRectanglePoints(480, 290, 40, 40);
    _rectangles[IN_LEFT_RECT].setPoints(points);

    points = makeRectanglePoints(800, 290, 40, 40);
    _rectangles[IN_RIGHT_RECT].setPoints(points);

    points = makeRectanglePoints(620, 550, 40, 40);
    _rectangles[BOTTOM_RECT].setPoints(points);

}

void ShapeManager::initColors()
{
    unsigned int i = 0;
    for (i = 0; i < MAX_TRIS; ++i) {
        _triangles[i].setColor(_triangleColors[i]);
    }
    for (i = 0; i < MAX_PIES; ++i) {
        _pies[i].setColor(_pieColors[i]);
    }
    for (i = 0; i < MAX_RECTS; ++i) {
        _rectangles[i].setColor(CLR_OUT);
    }
}

void ShapeManager::clearAllPositions()
{
    DO_WORK_TO_ALL_SHAPES(clearAllPoints)
}

void ShapeManager::loadAllPositions(CWinApp* app)
{
    DO_WORK_TO_ALL_SHAPES_WITH_KEY(loadPoints, app)
}

void ShapeManager::saveAllPositions(CWinApp* app)
{
    DO_WORK_TO_ALL_SHAPES_WITH_KEY(savePoints, app)
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
    Point point(x, y);
    _triangles[id].setPoint(pointIndex, point);
}

void ShapeManager::moveRetanglePoint(int id, int pointIndex, int x, int y)
{
    Point point(x, y);
    _rectangles[id].setPoint(pointIndex, point);
}

void ShapeManager::moveRectangle(int id, int widthStep, int heightStep)
{
    if (0 != widthStep) {
        _rectangles[id].moveHorizontally(widthStep);
    }
    if (0 != heightStep) {
        _rectangles[id].moveVertically(heightStep);
    }
}

void ShapeManager::moveTriangle(int id, int widthStep, int heightStep)
{
    if (0 != widthStep) {
        _triangles[id].moveHorizontally(widthStep);
    }
    if (0 != heightStep) {
        _triangles[id].moveVertically(heightStep);
    }
}

void ShapeManager::movePie(int id, int widthStep, int heightStep)
{
    if (0 != widthStep || 0 != heightStep) {
        PointArray piePoints = _pies[id].points();
        Point new0 = piePoints[0];
        Point new1 = piePoints[1];
        if (0 != widthStep) {
            new0.X += widthStep;
            new1.X += widthStep;
        }
        if (0 != heightStep) {
            new0.Y += heightStep;
            new1.Y += heightStep;
        }
        _pies[id].setPoint(0, new0);
        _pies[id].setPoint(1, new1);
    }
}

void ShapeManager::resizeRectangle(int id, int widthStep, int heightStep)
{
    if (0 != widthStep || 0 != heightStep) {
        PointArray rectPoints = _rectangles[id].points();
        if (0 != widthStep) {
            Point new1 = rectPoints[1];
            new1.X += widthStep;
            Point new2 = rectPoints[2];
            new2.X += widthStep;
            _rectangles[id].setPoint(1, new1);
            _rectangles[id].setPoint(2, new2);
        }
        if (0 != heightStep) {
            Point new2 = rectPoints[2];
            new2.Y += heightStep;
            Point new3 = rectPoints[3];
            new3.Y += heightStep;
            _rectangles[id].setPoint(2, new2);
            _rectangles[id].setPoint(3, new3);
        }
    }
}

void ShapeManager::resizeTriangle(int id, int widthStep, int heightStep)
{
    if (0 != widthStep || 0 != heightStep) {
        PointArray triPoints = _triangles[id].points();
        if (0 != widthStep) {
            Point new0 = triPoints[0];
            new0.X += widthStep;
            Point new1 = triPoints[1];
            new1.X += widthStep;
            _triangles[id].setPoint(0, new0);
            _triangles[id].setPoint(1, new1);
        }
        if (0 != heightStep) {
            Point new2 = triPoints[2];
            new2.Y += heightStep;
            _triangles[id].setPoint(2, new2);
        }
    }
}

void ShapeManager::resizePie(int id, int widthStep, int heightStep, int angleStep)
{
    if (0 != widthStep || 0 != heightStep) {
        PointArray piePoints = _pies[id].points();
        Point new0 = piePoints[0];
        Point new1 = piePoints[1];
        if (0 != widthStep) {
            new0.X -= widthStep;
            new1.X += widthStep;
        }
        if (0 != heightStep) {
            new0.Y -= heightStep;
            new1.Y += heightStep;
        }
        _pies[id].setPoint(0, new0);
        _pies[id].setPoint(1, new1);
    }
    if (0 != angleStep &&
        (BIG_LEFT_PIE == id ||
         BIG_RIGHT_PIE == id)) {
        Angle angle = _pies[id].angle();
        if (BIG_LEFT_PIE == id) {
            angle.second += angleStep;
        }
        else if (BIG_RIGHT_PIE == id) {
            angle.first -= angleStep;
            angle.second += angleStep;
        }
        _pies[id].setAngle(angle);
    }
}

PointArray ShapeManager::makeRectanglePoints(int x, int y, int width, int height)
{
    PointArray points;
    points.push_back(Point(x, y));
    points.push_back(Point(x + width, y));
    points.push_back(Point(x + width, y + height));
    points.push_back(Point(x, y + height));

    return points;
}

void ShapeManager::setPieSize(int id, int width, int height)
{
    _pies[id].setSize(width, height);
}

void ShapeManager::moveAllHorizontally(int step)
{
    DO_WORK_TO_ALL_SHAPES_WITH_PARAM(moveHorizontally, step)
}

void ShapeManager::moveAllVerically(int step)
{
    DO_WORK_TO_ALL_SHAPES_WITH_PARAM(moveVertically, step)
}

void ShapeManager::drawAllShapes(Gdiplus::Graphics* g)
{
    DO_WORK_TO_ALL_SHAPES_WITH_PARAM(drawShape, g)
}

void ShapeManager::fillAllShapes(Gdiplus::Graphics* g)
{
    // 색을 채우는 순서는..
    // 삼각형 -> 반원 -> 사각형 순으로 한다.
    // 위와 같이 색을 채우면, 경계선에 닿았을 때..
    // 무조건 진루타를 치는 방향으로 결정된다.
    DO_WORK_TO_ALL_SHAPES_WITH_PARAM(fillShape, g)

/*    unsigned int i;                    
    for (i = 1; i < 2; ++i) {   
        _triangles[i].fillShape(g);     
    }                                  
    for (i = 1; i < 2; ++i) {   
        _pies[i].fillShape(g);          
    }  */                                
    /*for (i = 0; i < MAX_RECTS; ++i) {  
        _rectangles[i].func(param);    
    }*/
}