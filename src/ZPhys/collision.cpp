#include <ZPhys/collision.h>
#include <ZLib/vec.h>

namespace ZPhys {
    bool circleCircleCollision(Circle &a, Circle &b) {
        Vec2 d = b.pos - a.pos;
        double dist = d.len();
        if(dist < a.radius + b.radius) {
            Vec2 n = d / d.len();
            double overlap = a.radius + b.radius - dist;
            a.pos -= n * 0.5 * overlap;
            b.pos += n * 0.5 * overlap;
            std::swap(a.vel, b.vel);
            return true;
        }
        return false;
    }

    bool circleTriangleCollision(Circle &c, const Triangle &t) {
        for(int i=0; i<3; i++) {
            Vec2 p0 = t.verts[i], p1 = t.verts[(i+1)%3];
            Vec2 edge = p1 - p0;
            double tparam = ((c.pos - p0) * edge) / (edge * edge);
            tparam = std::clamp(tparam, 0.0, 1.0);
            Vec2 proj = p0 + edge * tparam;
            if((proj - c.pos).len() < c.radius) {
                Vec2 n = (c.pos - proj).norm();
                double overlap = c.radius - (c.pos - proj).len();
                c.pos += n * overlap;
                c.vel -= n * (c.vel * n);
                return true;
            }
        }
        return false;
    }

    bool triangleTriangleCollision(const Triangle &a, const Triangle &b) {
        Vec2 axes[6] = {
            normal(a.verts[1] - a.verts[0]),
            normal(a.verts[2] - a.verts[1]),
            normal(a.verts[0] - a.verts[2]),
            normal(b.verts[1] - b.verts[0]),
            normal(b.verts[2] - b.verts[1]),
            normal(b.verts[0] - b.verts[2])
        };

        for(auto &axis : axes) {
            double minA, maxA, minB, maxB;
            projectTriangle(a, axis, minA, maxA);
            projectTriangle(b, axis, minB, maxB);
            if(!overlapProjections(minA, maxA, minB, maxB)) {
                return false;
            }
        }
        return true;
    }
}
