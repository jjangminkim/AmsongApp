#ifndef _SHAPES_H
#define _SHAPES_H

#include <Gdiplus.h>
#include <GdiPlusBrush.h>
#include <vector>

namespace Amsong {

    typedef std::vector<Gdiplus::Point> PointArray;
    typedef std::pair<float, float> Angle;

    class Shape {
    public:
        Shape() {}
        ~Shape() {}

    protected:
        PointArray _points;
        Gdiplus::Color _color;

    public:
        void init(const PointArray& points, const Gdiplus::Color& color);

        void addPoint(const Gdiplus::Point& point) { _points.push_back(point); }
        void setPoint(int i, const Gdiplus::Point& point);
        void setColor(const Gdiplus::Color& color) { _color = color; }

    public:
        virtual void moveHorizontally(int step) = 0;
        virtual void moveVertically(int step) = 0;
        virtual void drawShape(Gdiplus::Graphics* g) = 0;
        virtual void fillShape(Gdiplus::Graphics* g) = 0;
    };

    inline void Shape::init(const PointArray& points, const Gdiplus::Color& color)
    {
        _points = points;
        _color = color;
    }

    ///////////////////////////////////////////////////////////////////////////
    class Polygon : public Shape {
    public:
        Polygon() {}
        Polygon(const PointArray& points, const Gdiplus::Color& color)
        { Shape::init(points, color); }
        virtual ~Polygon() {}

    public:
        virtual void moveHorizontally(int step);
        virtual void moveVertically(int step);
        virtual void drawShape(Gdiplus::Graphics* g);
        virtual void fillShape(Gdiplus::Graphics* g);

    };

    ///////////////////////////////////////////////////////////////////////////
    class Pie : public Shape {
    public:
        Pie() {}
        Pie(const PointArray& points, const Gdiplus::Color& color, const Angle& angle);
        virtual ~Pie() {}

    protected:
        enum { MAX_POINTS = 2 };

        Angle _angle;

    public:
        void init(const PointArray& points, const Gdiplus::Color& color, const Angle& angle);
        void setAngle(const Angle& angle) { _angle = angle; }
        void setSize(int width, int height);

    public:
        int width() const;
        int height() const;

    public:
        virtual void moveHorizontally(int step);
        virtual void moveVertically(int step);
        virtual void drawShape(Gdiplus::Graphics* g);
        virtual void fillShape(Gdiplus::Graphics* g);

    };

}   // namespace Amsong

#endif  // _SHAPES_H