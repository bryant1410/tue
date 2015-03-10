//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "../mat.hpp"
#include "../math.hpp"
#include "../pose2d.hpp"
#include "../pose3d.hpp"
#include "../quat.hpp"
#include "../vec.hpp"

namespace tue {

namespace math
{
  template<typename T>
  inline mat<T, 2, 3> translation_mat(const T& x, const T& y) noexcept {
    return {
      { T(1), T(0), x },
      { T(0), T(1), y },
    };
  }

  template<typename T>
  inline mat<T, 2, 3> translation_mat(const vec2<T>& xy) noexcept {
    return translation_mat(xy.x(), xy.y());
  }

  template<typename T>
  inline mat<T, 3, 4> translation_mat(
      const T& x, const T& y, const T& z) noexcept {
    return {
      { T(1), T(0), T(0), x },
      { T(0), T(1), T(0), y },
      { T(0), T(0), T(1), z },
    };
  }

  template<typename T>
  inline mat<T, 3, 4> translation_mat(const vec3<T>& xyz) noexcept {
    return translation_mat(xyz.x(), xyz.y(), xyz.z());
  }

  template<typename T>
  inline auto rotation_mat(const T& angle) noexcept {
    using U = decltype(math::sin(angle));
    U s, c;
    math::sincos(angle, s, c);
    return mat<U, 2, 2>{
      { c, -s },
      { s,  c },
    };
  }

  template<typename T>
  inline auto rotation_mat(
      const T& axis_x,
      const T& axis_y,
      const T& axis_z,
      const T& angle) noexcept {
    using U = decltype(math::sin(angle));
    const U x = static_cast<U>(axis_x);
    const U y = static_cast<U>(axis_y);
    const U z = static_cast<U>(axis_z);

    U s, c;
    math::sincos(angle, s, c);
    const U omc = U(1) - c;

    const U xx = x * x;
    const U xy = x * y;
    const U xz = x * z;
    const U xs = x * s;
    const U yy = y * y;
    const U yz = y * z;
    const U ys = y * s;
    const U zz = z * z;
    const U zs = z * s;
    const U xxomc = xx * omc;
    const U xyomc = xy * omc;
    const U xzomc = xz * omc;
    const U yyomc = yy * omc;
    const U yzomc = yz * omc;
    const U zzomc = zz * omc;

    return mat<U, 3, 3>{
      { xxomc + c, xyomc - zs, xzomc + ys },
      { xyomc + zs, yyomc + c, yzomc - xs },
      { xzomc - ys, yzomc + xs, zzomc + c },
    };
  }

  template<typename T>
  inline auto rotation_mat(const vec3<T>& axis, const T& angle) noexcept {
    return rotation_mat(axis.x(), axis.y(), axis.z(), angle);
  }

  template<typename T>
  inline auto rotation_mat(const vec4<T>& v) noexcept {
    return rotation_mat(v.x(), v.y(), v.z(), v.w());
  }

  template<typename T>
  inline auto rotation_mat(const T& x, const T& y, const T& z) noexcept {
    return math::rotation_mat(math::axis_angle(x, y, z));
  }

  template<typename T>
  inline auto rotation_mat(const vec3<T>& v) noexcept {
    return math::rotation_mat(v.x(), v.y(), v.z());
  }

  template<typename T>
  inline mat<T, 3, 3> rotation_mat(const quat<T>& q) noexcept {
    const T x = q.x();
    const T y = q.y();
    const T z = q.z();
    const T w = q.w();
    const T xx2 = x * x * T(2);
    const T xy2 = x * y * T(2);
    const T xz2 = x * z * T(2);
    const T xw2 = x * w * T(2);
    const T yy2 = y * y * T(2);
    const T yz2 = y * z * T(2);
    const T yw2 = y * w * T(2);
    const T zz2 = z * z * T(2);
    const T zw2 = z * w * T(2);
    return {
      { T(1) - yy2 - zz2, xy2 - zw2, xz2 + yw2 },
      { xy2 + zw2, T(1) - xx2 - zz2, yz2 - xw2 },
      { xz2 - yw2, yz2 + xw2, T(1) - xx2 - yy2 },
    };
  }

  template<typename T>
  inline mat<T, 2, 2> scale_mat(const T& x, const T& y) noexcept {
    return {
      { x, T(0) },
      { T(0), y },
    };
  }

  template<typename T>
  inline mat<T, 2, 2> scale_mat(const vec2<T>& xy) noexcept {
    return scale_mat(xy.x(), xy.y());
  }

  template<typename T>
  inline mat<T, 3, 3> scale_mat(const T& x, const T& y, const T& z) noexcept {
    return {
      { x, T(0), T(0) },
      { T(0), y, T(0) },
      { T(0), T(0), z },
    };
  }

  template<typename T>
  inline mat<T, 3, 3> scale_mat(const vec3<T>& xyz) noexcept {
    return scale_mat(xyz.x(), xyz.y(), xyz.z());
  }

  template<typename T>
  inline auto pose_mat(
      const vec2<T>& translation,
      const T& rotation) noexcept {
    const auto r = rotation_mat(rotation);
    return mat3x3<typename decltype(r)::component_type>(r)
        * translation_mat(translation);
  }

  template<typename T>
  inline auto pose_mat(const pose2d<T>& pose) noexcept {
    return pose_mat(pose.translation(), pose.rotation());
  }

  template<typename T>
  inline auto pose_mat(
      const vec3<T>& translation,
      const vec3<T>& rotation_axis,
      const T& rotation_angle) noexcept {
    const auto r = rotation_mat(rotation_axis, rotation_angle);
    return mat4x4<typename decltype(r)::component_type>(r)
        * translation_mat(translation);
  }

  template<typename T>
  inline auto pose_mat(
      const vec3<T>& translation,
      const vec4<T>& rotation) noexcept {
    return pose_mat(translation, rotation.xyz(), rotation.w());
  }

  template<typename T>
  inline auto pose_mat(
      const vec3<T>& translation,
      const vec3<T>& rotation) noexcept {
    const auto r = rotation_mat(rotation);
    return mat4x4<typename decltype(r)::component_type>(r)
        * translation_mat(translation);
  }

  template<typename T>
  inline auto pose_mat(
      const vec3<T>& translation,
      const quat<T>& rotation) noexcept {
    const auto r = rotation_mat(rotation);
    return mat4x4<typename decltype(r)::component_type>(r)
        * translation_mat(translation);
  }

  template<typename T>
  inline auto pose_mat(const pose3d<T>& pose) noexcept {
    return pose_mat(pose.translation(), pose.rotation());
  }

  template<typename T>
  inline auto view_mat(
      const vec2<T>& translation,
      const T& rotation) noexcept {
    return translation_mat(-translation)
        * rotation_mat(-rotation);
  }

  template<typename T>
  inline auto view_mat(const pose2d<T>& pose) noexcept {
    return view_mat(pose.translation(), pose.rotation());
  }

  template<typename T>
  inline auto view_mat(
      const vec3<T>& translation,
      const vec3<T>& rotation_axis,
      const T& rotation_angle) noexcept {
    return translation_mat(-translation)
        * rotation_mat(rotation_axis, -rotation_angle);
  }

  template<typename T>
  inline auto view_mat(
      const vec3<T>& translation,
      const vec4<T>& rotation) noexcept {
    return view_mat(translation, rotation.xyz(), rotation.w());
  }

  template<typename T>
  inline auto view_mat(
      const vec3<T>& translation,
      const vec3<T>& rotation) noexcept {
    return translation_mat(-translation)
        * rotation_mat(-rotation);
  }

  template<typename T>
  inline auto view_mat(
      const vec3<T>& translation,
      const quat<T>& rotation) noexcept {
    return translation_mat(-translation)
        * rotation_mat(math::conjugate(rotation));
  }

  template<typename T>
  inline auto view_mat(const pose3d<T>& pose) noexcept {
    return view_mat(pose.translation(), pose.rotation());
  }

  template<typename T>
  inline auto perspective_mat(
      const T& fovy,
      const T& aspect,
      const T& near,
      const T& far) {
    using U = decltype(math::sin(fovy));
    U s, c;
    math::sincos(U(fovy) / U(2), s, c);
    const U f = c / s;
    const U nmf = U(near - far);
    return mat<U, 4, 4>{
      { f / U(aspect),                             U(0), U(0), U(0) },
      { U(0), f,                                         U(0), U(0) },
      { U(0), U(0), U(near + far) / nmf, U(2) * U(near * far) / nmf },
      { U(0), U(0), U(-1),                                     U(0) },
    };
  }

  template<typename T>
  inline auto ortho_mat(
      const T& width,
      const T& height,
      const T& near,
      const T& far) {
    using U = decltype(math::sin(width));
    const U fmn = U(far - near);
    return mat<U, 4, 4>{
      { U(2) / U(width),           U(0), U(0), U(0) },
      { U(0), U(2) / U(height),          U(0), U(0) },
      { U(0), U(0), U(2) / fmn, (far + near) / fmn  },
      { U(0), U(0), U(0),                      U(1) },
    };
  }
}

}
