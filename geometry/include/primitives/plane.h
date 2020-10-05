#pragma once

#include "general.h"

namespace ivkg {

    class plane_t {
    public:
        plane_t();

        plane_t(const plane_t &) = default;

        plane_t(std::initializer_list<long double> coefficients);

        long double &operator[](std::size_t idx);

        const long double &operator[](std::size_t idx) const;

        vector_t<3> normal() const;

        line_t<3> intersect(const plane_t &rhs) const;

    private:
        std::array<long double, 4> coefficients_;
    };

    bool operator==(const plane_t &lhs, const plane_t &rhs);

    bool parallel(const plane_t &lhs, const plane_t &rhs);

}
/* ------------------------------------------------
                REALIZATION_PLANE_CLASS
-------------------------------------------------*/

ivkg::plane_t::plane_t() {
    for(coordinate_t& elem : coefficients_) {
        elem = std::numeric_limits<double>::quiet_NaN();
    }
}

ivkg::plane_t::plane_t(std::initializer_list<long double> coefficients) {
    if(coefficients.size() != coefficients_.size()) {
        return;
    }

    typename std::array<coordinate_t, 4>::iterator obj_iter  = coefficients_.begin();
    typename std::initializer_list<coordinate_t>::iterator init_iter = coefficients.begin();
    while (obj_iter != coefficients_.end()) {
        *obj_iter = *init_iter;
        obj_iter++;
        init_iter++;
    }
}

long double& ivkg::plane_t::operator[](std::size_t idx) {
    return coefficients_[idx];
}

const long double& ivkg::plane_t::operator[](std::size_t idx) const {
    return coefficients_[idx];
}

ivkg::vector_t<3> ivkg::plane_t::normal() const {
    return ivkg::vector_t<3>({coefficients_[0], coefficients_[1], coefficients_[3]});
}

ivkg::line_t<3> ivkg::plane_t::intersect(const ivkg::plane_t &rhs) const {
    vector_t<3> lhs_normal = normal();
    vector_t<3> rhs_normal = rhs.normal();
    vector_t<3> crs = ivkg::cross(lhs_normal, rhs_normal);
    if(equal(crs.len(), 0.0)) {
        return ivkg::line_t<3>();
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