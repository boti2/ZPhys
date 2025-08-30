#pragma once
#include <ZPhys/shapes.h>

namespace ZPhys {
    bool circleCircleCollision(Circle &a, Circle &b);
    bool circleTriangleCollision(Circle &c, const Triangle &t);
    bool triangleTriangleCollision(const Triangle &a, const Triangle &b);
}
