#pragma once
#ifndef TES_HEADER_UTIL_GEOMETRY_GEOMETRY_HPP_
#define TES_HEADER_UTIL_GEOMETRY_GEOMETRY_HPP_
#include <utility>
#ifndef DEBUG_WITHOUT_LLAPI
#include <llapi/mc/Vec3.hpp>
#endif
namespace tes::geometry {

struct Point2D {
    int x;
    int z;

    constexpr Point2D(int x_, int z_) : x(x_),z(z_) {}
    Point2D() = delete;

#ifndef DEBUG_WITHOUT_LLAPI
    Point2D(const Vec3& vec) : x((int)vec.x), z((int)vec.z) {
    }
#endif
};


struct Area2D {
public:
    const int max_x;
    const int min_x;
    const int max_z;
    const int min_z;
    constexpr Area2D(int x1, int z1, int x2, int z2)
        : max_x(std::max(x1,x2)), min_x(std::min(x1,x2)), max_z(std::max(z1,z2)), min_z(std::min(z1,z2)){}

    constexpr Area2D(Point2D p1, Point2D p2) : Area2D({p1.x, p1.z, p2.x, p2.z}){}

    [[nodiscard]] constexpr bool contains(int x,int z) const noexcept {
        return (min_x <= x && x <= max_x && min_z <= z && z <= max_z );
    }

    [[nodiscard]] constexpr bool contains(const Area2D& area) const noexcept {
        if (min_x >= area.max_x || max_x <= area.min_x ||  min_z >= area.max_z || max_z <= area.min_z){
            return false;
        } else {
            return true;
        }
    }

    [[nodiscard]] constexpr int getAreaSize() const noexcept {
        return (max_x - min_x) * (max_z - min_z);
    }

    [[nodiscard]] constexpr int getWidth() const noexcept {
        return (max_x - min_x);
    }
    [[nodiscard]] constexpr int getHeight() const noexcept {
        return (max_z - min_z);
    }

    [[nodiscard]] constexpr Point2D getStartPos() const noexcept {
        return Point2D(min_x,min_z);
    }

    [[nodiscard]] constexpr Point2D getEndPos() const noexcept {
        return Point2D(max_x,max_z);
    }

    auto operator<=>(const Area2D&) const = default;

    [[nodiscard]]
    constexpr Area2D getDuplicateArea(Area2D area) const {
        return  {{
                std::max(area.min_x, min_x),
                std::max(area.min_z, min_z)
            },
            {
                std::min(area.max_x, max_x),
                std::min(area.max_z, max_z)
            }
        };
    }

};
}

#endif //TES_HEADER_UTIL_GEOMETRY_GEOMETRY_HPP_
