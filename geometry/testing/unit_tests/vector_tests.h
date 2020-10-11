#pragma once

#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "../../include/geometry.h"

TEST(GeometryVectorTest, Arithmetic) {
    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> b{0.0, 4.0, 3.0};
        ivkg::vector_t<3> expected{1.0, 6.0, 6.0};
        ASSERT_EQ(a + b, expected);
        ASSERT_EQ(a += b, expected);
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> b{0.0, 4.0, 3.0};
        ivkg::vector_t<3> expected{1.0, -2.0, 0.0};
        ASSERT_EQ(a - b, expected);
        ASSERT_EQ(a -= b, expected);
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> a_copy{1.0, 2.0, 3.0};
        ivkg::vector_t<3> expected{-1.0, -2.0, -3.0};
        ASSERT_EQ(-a, expected);
        ASSERT_EQ(a, a_copy) << "unary sub modify vector";
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        double lambda = 4.0;
        ivkg::vector_t<3> expected{4.0, 8.0, 12.0};
        ASSERT_EQ(a * lambda, expected) << "mult by positive lambda";
        ASSERT_EQ(a *= lambda, expected) << "mult by positive lambda";
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 0.0};
        double lambda = 0.0;
        ivkg::vector_t<3> expected{0.0, 0.0, 0.0};
        ASSERT_EQ(a * lambda, expected) << "mult by zero lambda";
        ASSERT_EQ(a *= lambda, expected) << "mult by zero lambda";
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 0.0};
        double lambda = -1.0;
        ivkg::vector_t<3> expected{-1.0, -2.0, 0.0};
        ASSERT_EQ(a * lambda, expected) << "mult by negative lambda";
        ASSERT_EQ(a *= lambda, expected) << "mult by negative lambda";
    }
}

TEST(GeometryVectorTest, Valid) {
    {
        ivkg::vector_t<10> x;
        ASSERT_FALSE(x.valid()) << "default construct";
    }

    {
        ivkg::point_t<3> x1{1.0, 2.0, 3.0};
        ivkg::point_t<3> x2{1.0, 3.0, 5.0};
        ivkg::vector_t<3> x{x1, x2};
        ASSERT_TRUE(x.valid()) << "construct from 2 valid points";
    }

    {
        ivkg::point_t<3> x1;
        ivkg::point_t<3> x2{1.0, 3.0, 5.0};
        ivkg::vector_t<3> x{x1, x2};
        ASSERT_FALSE(x.valid()) << "construct from 1 invalid and 1 valid points";
    }

    {
        ivkg::point_t<3> x1;
        ivkg::point_t<3> x2;
        ivkg::vector_t<3> x(x1, x2);
        ASSERT_FALSE(x.valid()) << "construct from 2 invalid points";
    }

    {
        ivkg::vector_t<3> x{1.0, 2.0, 3.0};
        ASSERT_TRUE(x.valid()) << "construct doubles vector";
    }

}

TEST(GeometryVectorTest, Len) {
    {
        ivkg::vector_t<3> v{3.0, 4.0, 0.0};
        ASSERT_DOUBLE_EQ(v.len(), 5.0);
    }

    {
        ivkg::vector_t<3> v{0.0, 0.0, 0.0};
        ASSERT_DOUBLE_EQ(v.len(), 0.0);
    }

    {
        ivkg::vector_t<3> v{16.0, 0.0, 0.0};
        ASSERT_DOUBLE_EQ(v.len(), 16.0);
    }
}

TEST(GeometryVectorTest, IsZero) {
    {
        ivkg::vector_t<3> v{3.0, 4.0, 0.0};
        ASSERT_FALSE(v.zero());
    }

    {
        ivkg::vector_t<3> v{0.0, 0.0, 0.0};
        ASSERT_TRUE(v.zero());
    }

    {
        ivkg::vector_t<3> v;
        ASSERT_FALSE(v.zero());
    }
}

TEST(GeometryVectorTest, Equal) {
    {
        ivkg::vector_t<3> v1{0.0, 4.0, 0.0};
        ivkg::vector_t<3> v2{0.0, 4.0, 0.0};
        ASSERT_TRUE(v1 == v2);
    }

    {
        ivkg::vector_t<3> v1{0.0, 4.0, 0.0};
        ivkg::vector_t<3> v2;
        ASSERT_FALSE(v1 == v2) << "1 invalid vector";
    }
}


TEST(GeometryVectorTest, IsParallel) {
    {
        ivkg::vector_t<3> v1{3.0, 4.0, 0.0};
        ivkg::vector_t<3> v2{6.0, 8.0, 0.0};
        ASSERT_TRUE(parallel(v1, v2));
    }

    {
        ivkg::vector_t<3> v1{3.0, 4.0, 0.0};
        ivkg::vector_t<3> v2{1.0, 8.0, 0.0};
        ASSERT_FALSE(parallel(v1, v2));
    }

    {
        ivkg::vector_t<3> v2;
        ivkg::vector_t<3> v1;
        ASSERT_FALSE(parallel(v1, v2)) << "2 vectors invalid";
    }

    {
        ivkg::vector_t<3> v1{3.0, 4.0, 0.0};
        ivkg::vector_t<3> v2;
        ASSERT_FALSE(parallel(v1, v2)) << "v2 vector invalid";
    }
}


TEST(GeometryVectorTest, Dot) {
    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> b{0.0, 4.0, 3.0};
        ASSERT_DOUBLE_EQ(17.0, dot(a, b));
    }
}

TEST(GeometryVectorTest, Cross) {
    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> b{-2.0, 0.0, 4.0};
        ivkg::vector_t<3> expected{8.0, -10.0, 4.0};
        ASSERT_EQ(expected, cross(a, b));
    }

    {
        ivkg::vector_t<3> a{1.0, 2.0, 3.0};
        ivkg::vector_t<3> b{2.0, 4.0, 6.0};
        ivkg::vector_t<3> expected{0.0, 0.0, 0.0};
        ASSERT_EQ(expected, cross(a, b)) << "parallel vectors";
    }
}