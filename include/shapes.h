#pragma once
#include <vector>
#include <ZLib/vec.h>

namespace ZPhys {
    struct Circle { Vec2 pos, vel; double radius; };
    struct Triangle { Vec2 verts[3]; Vec2 vel; };
    struct Polygon {
        std::vector<Vec2> verts;
        Vec2 vel;
        std::vector<Triangle> triangles;
    };
    
    double polygonArea(const std::vector<Vec2>& verts);
    void ensureCCW(std::vector<Vec2>& verts);
    bool isDegenerate(const std::vector<Vec2>& verts);
    bool isSelfIntersecting(const std::vector<Vec2>& verts);
}
