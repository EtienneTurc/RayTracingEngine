#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"

struct camera
{
    point3d  position, look_at;
    vector3d direction, right, up;
    real_t fov;

    camera( const point3d& pos, const point3d& target, const vector3d& cam_right = {0.,1.,0.});
    camera( const point3d& pos, const vector3d& dir, const vector3d& cam_right = { 0., 1., 0.});
    camera( const camera & ) = default;
    camera( camera&& ) = default;
    ~camera() = default;

    matrix44 camera2world() const
    {
        return {right.x, up.x, direction.x, look_at.x,
                right.y, up.y, direction.y, look_at.y,
                right.z, up.z, direction.z, look_at.z};
    }

    void move( real_t step_forward, real_t theta, real_t phi );
};

#endif
