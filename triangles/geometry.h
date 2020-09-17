#pragma once

#include <iostream>
#include <limits>
#include <cmath>

#define TOLERANCE 1e-5

/* ------------------------------------------------
                START POINT_METHODS
 -------------------------------------------------*/
struct point3D_t {
    double x, y, z;

    explicit point3D_t();
    explicit point3D_t(double x_, double y_, double z_);

    bool valid() const;
};

bool operator==(const point3D_t& lhs, const point3D_t& rhs);
std::istream& operator>>(std::istream& in, point3D_t& point);
std::ostream& operator<<(std::ostream& out, const point3D_t& point);
double distance(const point3D_t& rhs, const point3D_t& lhs);
/* ------------------------------------------------
                END POINT_METHODS
 -------------------------------------------------*/



/* ------------------------------------------------
                START VECTOR_METHODS
 -------------------------------------------------*/
struct vector3D_t {
    double x, y, z;

    explicit vector3D_t();
    explicit vector3D_t(double x_, double y_, double z_);
    explicit vector3D_t(const point3D_t& lhs, const point3D_t& rhs);

    vector3D_t& operator +=(const vector3D_t& rhs);
    vector3D_t& operator *=(double lambda);

    bool valid() const;
    double len() const;
    bool is_zero() const;
};

bool operator==(const vector3D_t& lhs, const vector3D_t& rhs);
const vector3D_t operator+(const vector3D_t& lhs, const vector3D_t& rhs);
const vector3D_t operator*(double lambda, const vector3D_t& rhs);
const vector3D_t operator*(const vector3D_t& lhs, double lambda);

double dot(const vector3D_t& lhs, const vector3D_t& rhs);
vector3D_t cross(const vector3D_t& lhs, const vector3D_t& rhs);
bool is_parallel(const vector3D_t& lhs, const vector3D_t& rhs);
/* ------------------------------------------------
                END VECTOR_METHODS
 -------------------------------------------------*/




/* ------------------------------------------------
                START LINE_METHODS
 -------------------------------------------------*/
struct line_t {
    vector3D_t start;
    vector3D_t direction;

    explicit line_t();
    explicit line_t(const point3D_t& lhs, const point3D_t& rhs);
};
/* ------------------------------------------------
                END LINE_METHODS
 -------------------------------------------------*/




/* ------------------------------------------------
                START TRIANGLE_METHODS
 -------------------------------------------------*/
struct triangle_t {
    point3D_t A, B, C;

    explicit triangle_t();
    explicit triangle_t(const point3D_t& A_, const point3D_t& B_, const point3D_t& C_);

    bool valid();
};

std::istream& operator>>(std::istream& in, triangle_t& triangle);
std::ostream& operator<<(std::ostream& out, const triangle_t& triangle);
/* ------------------------------------------------
                END TRIANGLE_METHODS
 -------------------------------------------------*/




/* ------------------------------------------------
                START PLANE_METHODS
 -------------------------------------------------*/
struct plane_t {
    double a, b, c, d;

    explicit plane_t(double a_, double b_, double c_, double d_);
    explicit plane_t(const point3D_t& x1, const point3D_t& x2, const point3D_t& x3);

    vector3D_t normal() const;
};

bool is_parallel(const plane_t& lhs, const plane_t& rhs);
line_t intersection_of_2planes(const plane_t& lhs, const plane_t& rhs);
/* ------------------------------------------------
                 END PLANE_METHODS
 -------------------------------------------------*/

