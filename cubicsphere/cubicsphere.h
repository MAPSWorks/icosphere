#ifndef ICOSPHERE_H
#define ICOSPHERE_H
#include <iostream>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Rhumb.hpp>
#include <vector>
#include <forward_list>
#include <list>
#include <map>
#include "geometry.h"




namespace Halifirien {



class CubicSphere {
public:

    static constexpr double X = 0.525731112119133606;
    static constexpr double Z = 0.850650808352039932;

    CubicSphere (const unsigned int& depth);
    CubicSphere();
    ~CubicSphere();

    unsigned long vertexCount ();
    Vertex* operator [] (const uint32_t& id);
    void visit (Vertex* vertex);
    Vertex* walkTowards (const Geolocation& target, const unsigned int& depth);
    Vertex* walkTowards (const Cartesian& target, const unsigned int& depth) const;
    Vertex* nearest (const Geolocation& target, const unsigned int& depth = 0);

    void toGeolocation (const Cartesian& c, Geolocation& g);
    void toCartesian (const Geolocation& g, Cartesian& c);
    static double distSquared (const Cartesian& a, const Cartesian& b);


    inline void divideTriangle (Triangle* t);

    std::pair<std::vector<Triangle*>::iterator, std::vector<Triangle*>::iterator> triangles (const unsigned& level);
    std::pair<std::vector<Vertex*>::iterator, std::vector<Vertex*>::iterator> vertices();

protected:
    unsigned _depth;
    uint32_t _count;

    inline void subdivide (const unsigned int &level);

    // mesh data structures

    std::vector<Vertex*> _vertices;
    std::vector<std::vector<Triangle*>> _triangles;


    mutable Vertex* _lastVisited;
    inline void makeTriangle (Vertex* a, Vertex* b, Vertex* c, Triangle* parent);
    inline void makeNeighbours (Vertex* p, Vertex* q);

    inline Vertex* addVertex (const Cartesian& c, int level);
    inline void mid (const Cartesian& c1, const Cartesian& c2, Cartesian& c);
    GeographicLib::Geocentric* _gc;

    // these are working variables for triangle subdivision
    uint32_t k;
    Vertex* e1;
    uint64_t edgeKey;
    bool _initial;
    std::unordered_map<uint64_t, Vertex*> edgeMap;
    std::unordered_map<uint64_t, Vertex*>::iterator it;

    Vertex* ids0 [3];  // triangles of outer vertices
    Vertex* ids1 [3];  // triangles of edge vertices

    Cartesian c;
    unsigned level;

    inline uint64_t makeKey (const uint32_t& v1, const uint32_t& v2);


    // data for "fast" icosphere


};
} // namespace
#endif // ICOSPHERE_H
