#pragma once
#include <vector>
#include <ZLib/vec.h>
#include <cassert>

namespace ZPhys {
    struct Triangle {
        Vec2 verts[3];
    };

    struct Circle {
        Vec2 pos;
        double radius;
    };

    struct Polygon {
        std::vector<Vec2> verts;
        std::vector<Triangle> triangles;

        void addLoop(const std::vector<Vec2> &loop);
    };
}
