#include <ZPhys/shapes.h>
#include <algorithm>

namespace ZPhys {
    double polygonArea(const std::vector<Vec2> &verts){
        double area = 0;
        int n = verts.size();
        for(int i=0;i<n;i++){
            const Vec2 &a = verts[i];
            const Vec2 &b = verts[(i+1)%n];
            area += a.x*b.y - b.x*a.y;
        }
        return 0.5*area;
    }

    void ensureCW(std::vector<Vec2> &verts){
        if(polygonArea(verts) > 0) std::reverse(verts.begin(), verts.end());
    }

    bool isDegenerate(const std::vector<Vec2> &verts){
        if(verts.size() < 3) return true;
        if(std::abs(polygonArea(verts)) < 1e-12) return true;
        for(size_t i=0;i<verts.size();i++)
            for(size_t j=i+1;j<verts.size();j++)
                if(verts[i].x==verts[j].x && verts[i].y==verts[j].y) return true;
        return false;
    }

    static bool segmentsIntersect(const Vec2 &p1,const Vec2 &p2,const Vec2 &q1,const Vec2 &q2){
        auto cross = [](const Vec2 &u,const Vec2 &v){ return u.x*v.y - u.y*v.x; };
        Vec2 r = p2 - p1;
        Vec2 s = q2 - q1;
        double denom = cross(r,s);
        if(denom==0) return false;
        Vec2 qp = q1 - p1;
        double t = cross(qp,s)/denom;
        double u = cross(qp,r)/denom;
        return t>0 && t<1 && u>0 && u<1;
    }

    bool isSelfIntersecting(const std::vector<Vec2> &verts){
        int n = verts.size();
        for(int i=0;i<n;i++){
            Vec2 a1 = verts[i], a2 = verts[(i+1)%n];
            for(int j=i+1;j<n;j++){
                if(j==(i+1)%n || (i==0 && j==n-1)) continue;
                Vec2 b1 = verts[j], b2 = verts[(j+1)%n];
                if(segmentsIntersect(a1,a2,b1,b2)) return true;
            }
        }
        return false;
    }

    void Polygon::addLoop(const std::vector<Vec2> &loop){
        assert(!isDegenerate(loop) && !isSelfIntersecting(loop));
        verts = loop;
        ensureCW(verts);
        triangles.clear();
        auto vertsCopy = verts;
        while(vertsCopy.size()>=3){
            bool earFound=false;
            int n = vertsCopy.size();
            for(int i=0;i<n;i++){
                Vec2 prev=vertsCopy[(i+n-1)%n], curr=vertsCopy[i], next=vertsCopy[(i+1)%n];
                Vec2 ab=curr-prev, ac=next-prev;
                if(ab.x*ac.y - ab.y*ac.x >=0){
                    bool inside=false;
                    for(int j=0;j<n;j++){
                        if(j==i || j==(i+1)%n || j==(i+n-1)%n) continue;
                        Vec2 p=vertsCopy[j];
                        Vec2 v0=next-prev,v1=curr-prev,v2=p-prev;
                        double dot00=v0*v0, dot01=v0*v1, dot02=v0*v2, dot11=v1*v1, dot12=v1*v2;
                        double invDenom=1/(dot00*dot11-dot01*dot01);
                        double u=(dot11*dot02-dot01*dot12)*invDenom;
                        double v=(dot00*dot12-dot01*dot02)*invDenom;
                        if(u>=0 && v>=0 && u+v<=1){ inside=true; break; }
                    }
                    if(inside) continue;
                    Triangle t; t.verts[0]=prev; t.verts[1]=curr; t.verts[2]=next;
                    triangles.push_back(t);
                    vertsCopy.erase(vertsCopy.begin()+i);
                    earFound=true;
                    break;
                }
            }
            if(!earFound) break;
        }
    }
}
