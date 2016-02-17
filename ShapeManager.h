#ifndef _SHAPE_CONTROLLER_H
#define _SHAPE_CONTROLLER_H

#include "Shapes.h"

namespace Amsong {  

    class ShapeManager {
    public:
        ShapeManager(CWinApp* app);
        ~ShapeManager() {}

    public:
        enum TRIANGLE_ID {
            BIG_REV_TRI = 0,    // Ball
            MID_REV_TRI,        // 2nd base
            SMALL_REV_TRI,      // 1st base
            MINI_REV_TRI,       // Strike
            MICRO_REV_TRI,      // hit by pitch (H.P.)

            MAX_TRIS
        };

        enum PIE_ID {
            BIG_CENTER_PIE = 0, // homerun
            BIG_LEFT_PIE,       // 3rd base    
            BIG_RIGHT_PIE,      // 3rd base
            MID_PIE,            // 2nd base
            SMALL_PIE,          // 1st base

            MAX_PIES,
        };

        // Fill with WHITE color (out)
        enum RECTANGLE_ID {
            OUT_LEFT_RECT = 0,
            OUT_CENTER_RECT,
            OUT_RIGHT_RECT,
            MID_LEFT_RECT,
            MID_RIGHT_RECT,
            IN_LEFT_RECT,
            IN_RIGHT_RECT,
            BOTTOM_RECT,

            MAX_RECTS,
        };

    private:
        Polygon _triangles[MAX_TRIS];
        Polygon _rectangles[MAX_RECTS];
        Pie     _pies[MAX_PIES];

        // COLOR DEFINES
        Gdiplus::Color _triangleColors[MAX_TRIS];
        Gdiplus::Color _pieColors[MAX_PIES];

    private:
        void initPoints();
        void initColors();

    public:
        void clearAllPositions();
        void loadAllPositions(CWinApp* app);
        void saveAllPositions(CWinApp* app);

    public:
        void setTriangle(int id, const PointArray& points);
        void setRectangle(int id, const PointArray& points);
        void setPie(int id, const PointArray& points, const Angle& angle);

    public:
        void moveTrianglePoint(int id, int pointIndex, int x, int y);
        void moveRetanglePoint(int id, int pointIndex, int x, int y);

        void moveRectangle(int id, int widthStep, int heightStep);
        void moveTriangle(int id, int widthStep, int heightStep);
        void movePie(int id, int widthStep, int heightStep);

        void resizeRectangle(int id, int widthStep, int heightStep);
        void resizeTriangle(int id, int widthStep, int heightStep);
        void resizePie(int id, int widthStep, int heightStep, int angleStep);

    public:
        PointArray makeRectanglePoints(int x, int y, int width, int height);
        void setPieSize(int id, int width, int height);

    public:
        void moveAllHorizontally(int step);
        void moveAllVerically(int step);

    public:
        void drawAllShapes(Gdiplus::Graphics* g);
        void fillAllShapes(Gdiplus::Graphics* g);


    };

}   // Amsong

#endif // _SHAPE_CONTROLLER_H