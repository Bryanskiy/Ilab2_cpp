#include "../include/primitives/point.h"
#include "../include/primitives/vect.h"
#include "../include/primitives/line.h"
#include "../include/primitives/plane.h"

/* ------------------------------------------------
                REALIZATION_PLANE_CLASS
-------------------------------------------------*/

lingeo::plane_t::plane_t() {
    for(coordinate_t& elem : coefficients_) {
        elem = std::numeric_limits<double>::quiet_NaN();
    }
}

lingeo::plane_t::plane_t(std::initializer_list<long double> coefficients) {
    if(coefficients.size() != coefficients_.size()) {
        return;
    }

    auto obj_iter  = coefficients_.begin();
    auto init_iter = coefficients.begin();
    while (obj_iter != coefficients_.end()) {
        *obj_iter = *init_iter;
        obj_iter++;
        init_iter++;
    }
}

lingeo::plane_t::plane_t(const lingeo::point_t<3> &x1, const lingeo::point_t<3> &x2, const lingeo::point_t<3> &x3) {
    coefficients_[0] = (x2[1] - x1[1]) * (x3[2] - x1[2]) - (x2[2] - x1[2]) * (x3[1] - x1[1]);
    coefficients_[1] = -((x2[0] - x1[0]) * (x3[2] - x1[2]) - (x2[2] - x1[2]) * (x3[0] - x1[0]));
    coefficients_[2] = ((x2[0] - x1[0]) * (x3[1] - x1[1]) - (x2[1] - x1[1]) * (x3[0] - x1[0]));
    coefficients_[3] = -(x1[0] * coefficients_[0] + x1[1] * coefficients_[1] + x1[2] * coefficients_[2]);
}


long double& lingeo::plane_t::operator[](std::size_t idx) {
    return coefficients_[idx];
}

const long double& lingeo::plane_t::operator[](std::size_t idx) const {
    return coefficients_[idx];
}

lingeo::vector_t<3> lingeo::plane_t::normal() const {
    return lingeo::vector_t<3>({coefficients_[0], coefficients_[1], coefficients_[2]});
}

lingeo::line_t<3> lingeo::plane_t::intersect(const lingeo::plane_t &rhs) const {
    vector_t<3> lhs_normal = normal();
    vector_t<3> rhs_normal = rhs.normal();
    vector_t<3> crs = lingeo::cross(lhs_normal, rhs_normal);
    if(equal(crs.len(), 0.0)) {
        return lingeo::line_t<3>();
    }

    long double s1, s2, a, b;
    s1 = coefficients_[3];
    s2 = rhs[3];

    long double n1n2dot = dot(lhs_normal, rhs_normal);
    long double n1sqr = dot(lhs_normal, lhs_normal);
    long double n2sqr = dot(rhs_normal, rhs_normal);

    long double denominator = -std::pow(n1n2dot, 2) + n1sqr * n2sqr;
    a = (s2 * n1n2dot - s1 * n2sqr) / denominator;
    b = (s1 * n1n2dot - s2 * n1sqr) / denominator;

    return line_t<3>(a * lhs_normal + b * rhs_normal, crs);
}

bool lingeo::plane_t::valid() const {
    return lingeo::valid(coefficients_[0]) && lingeo::valid(coefficients_[1]) &&
           lingeo::valid(coefficients_[2]) && lingeo::valid(coefficients_[3]);
}

lingeo::point_t<3> lingeo::plane_t::get_point() const{
    lingeo::vector_t<3> plane_normal = normal();
    lingeo::vector_t<3> tmp = -this->coefficients_[3] / std::pow(plane_normal.len(), 2) * plane_normal;
    return {tmp[0], tmp[1], tmp[2]};
}

bool lingeo::plane_t::intersect(const lingeo::point_t<3>& point) const {
    return equal(coefficients_[0] * point[0] + coefficients_[1] * point[1] + coefficients_[2] * point[2] + coefficients_[3], 0.0);
}

bool lingeo::operator==(const plane_t &lhs, const plane_t &rhs) {
    return parallel(lhs, rhs) && rhs.intersect(lhs.get_point());
}

bool lingeo::parallel(const plane_t &lhs, const plane_t &rhs) {
    return parallel(lhs.normal(), rhs.normal());
}