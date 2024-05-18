#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(Point center, Point velocity, Color color, double radius, bool isCollidable);
    
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;

private:
    Point center_;
    Velocity velocity_;
    Color color_;
    double radius_;
    bool isCollidable_;
    double red_, green_, blue_;

};
