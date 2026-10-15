#ifndef TNCG15_RAYTRACER_INTERVAL_H
#define TNCG15_RAYTRACER_INTERVAL_H
#include <utilities.h>

class interval {
public:
    float min, max;

    interval() : min(+infinity), max(-infinity) {}
    interval(float min, float max) : min(min), max(max) {}

    float size() const {
        return max - min;
    }

    bool contains(float x) const {
        return min <= x && x <= max;
    }

    bool surrounds(float x) const {
        return min < x && x < max;
    }

    float clamp(float x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

inline const interval interval::empty    = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);

#endif //TNCG15_RAYTRACER_INTERVAL_H