//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tue/mat.hpp>
#include "test_case.hpp"

#include <tue/math.hpp>
#include <tue/unused.hpp>
#include <tue/vec.hpp>

namespace
{
	using namespace tue;

	constexpr auto u2 = 2U;

	constexpr fmat4x2 fm421 = {
		{ 1.1f, 1.2f },
		{ 2.1f, 2.2f },
		{ 3.1f, 3.2f },
		{ 4.1f, 4.2f },
	};

	constexpr dmat4x2 dm421 = {
		{ 1.1, 1.2 },
		{ 2.1, 2.2 },
		{ 3.1, 3.2 },
		{ 4.1, 4.2 },
	};

	constexpr mat4x2<int> im421 = {
		{ 111, 222 },
		{ 333, 444 },
		{ 555, 666 },
		{ 777, 888 },
	};

	constexpr mat4x2<unsigned int> um422 = {
		{ 2U, 3U },
		{ 4U, 5U },
		{ 6U, 7U },
		{ 8U, 9U },
	};

	TEST_CASE(default_constructor)
	{
		fmat4x2 m;
		unused(m);
	}

	TEST_CASE(scalar_constructor)
	{
		constexpr fmat4x2 m1(1.1f);
		test_assert(m1[0] == fvec2(1.1f, 0.0f));
		test_assert(m1[1] == fvec2(0.0f, 1.1f));
		test_assert(m1[2] == fvec2(0.0f, 0.0f));
		test_assert(m1[3] == fvec2(0.0f, 0.0f));

		constexpr fmat4x3 m2(2.2f);
		test_assert(m2[0] == fvec3(2.2f, 0.0f, 0.0f));
		test_assert(m2[1] == fvec3(0.0f, 2.2f, 0.0f));
		test_assert(m2[2] == fvec3(0.0f, 0.0f, 2.2f));
		test_assert(m2[3] == fvec3(0.0f, 0.0f, 0.0f));

		constexpr fmat4x4 m3(3.3f);
		test_assert(m3[0] == fvec4(3.3f, 0.0f, 0.0f, 0.0f));
		test_assert(m3[1] == fvec4(0.0f, 3.3f, 0.0f, 0.0f));
		test_assert(m3[2] == fvec4(0.0f, 0.0f, 3.3f, 0.0f));
		test_assert(m3[3] == fvec4(0.0f, 0.0f, 0.0f, 3.3f));
	}

	TEST_CASE(column_constructor)
	{
		constexpr fmat4x2 m = {
			{ 1.1f, 1.2f },
			{ 2.1f, 2.2f },
			{ 3.1f, 3.2f },
			{ 4.1f, 4.2f },
		};
		test_assert(m[0] == fvec2(1.1f, 1.2f));
		test_assert(m[1] == fvec2(2.1f, 2.2f));
		test_assert(m[2] == fvec2(3.1f, 3.2f));
		test_assert(m[3] == fvec2(4.1f, 4.2f));
	}

	TEST_CASE(extend_and_truncate_constructors)
	{
		// TODO
	}

	TEST_CASE(explicit_conversion_constructor)
	{
		constexpr fmat4x2 m(dm421);
		test_assert(m[0] == fvec2(dm421[0]));
		test_assert(m[1] == fvec2(dm421[1]));
		test_assert(m[2] == fvec2(dm421[2]));
		test_assert(m[3] == fvec2(dm421[3]));
	}

	TEST_CASE(implicit_conversion_operator)
	{
		CONST_OR_CONSTEXPR dmat4x2 m = fm421;
		test_assert(m[0] == dvec2(fm421[0]));
		test_assert(m[1] == dvec2(fm421[1]));
		test_assert(m[2] == dvec2(fm421[2]));
		test_assert(m[3] == dvec2(fm421[3]));
	}

	TEST_CASE(identity)
	{
		CONST_OR_CONSTEXPR auto m1 = fmat4x2::identity();
		CONST_OR_CONSTEXPR auto m2 = fmat4x3::identity();
		CONST_OR_CONSTEXPR auto m3 = fmat4x4::identity();
		test_assert(m1 == fmat4x2(1.0f));
		test_assert(m2 == fmat4x3(1.0f));
		test_assert(m3 == fmat4x4(1.0f));
	}

	TEST_CASE(zero)
	{
		CONST_OR_CONSTEXPR auto m1 = fmat4x2::zero();
		CONST_OR_CONSTEXPR auto m2 = fmat4x3::zero();
		CONST_OR_CONSTEXPR auto m3 = fmat4x4::zero();
		test_assert(m1 == fmat4x2(0.0f));
		test_assert(m2 == fmat4x3(0.0f));
		test_assert(m3 == fmat4x4(0.0f));
	}

	TEST_CASE(column)
	{
		CONST_OR_CONSTEXPR fvec2 column0 = fm421.column(0);
		CONST_OR_CONSTEXPR fvec2 column1 = fm421.column(1);
		CONST_OR_CONSTEXPR fvec2 column2 = fm421.column(2);
		CONST_OR_CONSTEXPR fvec2 column3 = fm421.column(3);
		test_assert(column0 == fm421[0]);
		test_assert(column1 == fm421[1]);
		test_assert(column2 == fm421[2]);
		test_assert(column3 == fm421[3]);
	}

	TEST_CASE(set_column)
	{
		fmat4x2 m;
		m.set_column(0, fvec2(1.1f, 1.2f));
		m.set_column(1, fvec2(2.1f, 2.2f));
		m.set_column(2, fvec2(3.1f, 3.2f));
		m.set_column(3, fvec2(4.1f, 4.2f));
		test_assert(m[0] == fvec2(1.1f, 1.2f));
		test_assert(m[1] == fvec2(2.1f, 2.2f));
		test_assert(m[2] == fvec2(3.1f, 3.2f));
		test_assert(m[3] == fvec2(4.1f, 4.2f));
	}

	TEST_CASE(row)
	{
		CONST_OR_CONSTEXPR fvec4 row0 = fm421.row(0);
		CONST_OR_CONSTEXPR fvec4 row1 = fm421.row(1);
		test_assert(row0 == fvec4(fm421[0][0], fm421[1][0], fm421[2][0], fm421[3][0]));
		test_assert(row1 == fvec4(fm421[0][1], fm421[1][1], fm421[2][1], fm421[3][1]));
	}

	TEST_CASE(set_row)
	{
		fmat4x2 m;
		m.set_row(0, fvec4(1.1f, 2.1f, 3.1f, 4.1f));
		m.set_row(1, fvec4(1.2f, 2.2f, 3.2f, 4.2f));
		test_assert(m[0] == fvec2(1.1f, 1.2f));
		test_assert(m[1] == fvec2(2.1f, 2.2f));
		test_assert(m[2] == fvec2(3.1f, 3.2f));
		test_assert(m[3] == fvec2(4.1f, 4.2f));
	}

	TEST_CASE(subscript_operator)
	{
		constexpr fmat4x2 cem = {
			{ 1.1f, 1.2f },
			{ 2.1f, 2.2f },
			{ 3.1f, 3.2f },
			{ 4.1f, 4.2f },
		};
		CONST_OR_CONSTEXPR fvec2 cem0 = cem[0];
		CONST_OR_CONSTEXPR fvec2 cem1 = cem[1];
		CONST_OR_CONSTEXPR fvec2 cem2 = cem[2];
		CONST_OR_CONSTEXPR fvec2 cem3 = cem[3];
		test_assert(cem0 == fvec2(1.1f, 1.2f));
		test_assert(cem1 == fvec2(2.1f, 2.2f));
		test_assert(cem2 == fvec2(3.1f, 3.2f));
		test_assert(cem3 == fvec2(4.1f, 4.2f));

		fmat4x2 m = cem;
		fvec2& m0 = m[0];
		fvec2& m1 = m[1];
		fvec2& m2 = m[2];
		fvec2& m3 = m[3];
		test_assert(static_cast<void*>(&m0) == static_cast<void*>(&m));
		test_assert(&m1 == &m0 + 1);
		test_assert(&m2 == &m0 + 2);
		test_assert(&m3 == &m0 + 3);

		const fmat4x2& cm = m;
		const fvec2& cm0 = cm[0];
		const fvec2& cm1 = cm[1];
		const fvec2& cm2 = cm[2];
		const fvec2& cm3 = cm[3];
		test_assert(&cm0 == &m0);
		test_assert(&cm1 == &m1);
		test_assert(&cm2 == &m2);
		test_assert(&cm3 == &m3);
	}

	TEST_CASE(pre_increment_operator)
	{
		fmat4x2 m = fm421;
		test_assert(&(++m) == &m);
		test_assert(m == fm421 + 1);
	}

	TEST_CASE(pre_decrement_operator)
	{
		fmat4x2 m = fm421;
		test_assert(&(--m) == &m);
		test_assert(m == fm421 - 1);
	}

	TEST_CASE(post_increment_operator)
	{
		fmat4x2 m = fm421;
		test_assert(m++ == fm421);
		test_assert(m == fm421 + 1);
	}

	TEST_CASE(post_decrement_operator)
	{
		fmat4x2 m = fm421;
		test_assert(m-- == fm421);
		test_assert(m == fm421 - 1);
	}

	TEST_CASE(addition_assignment_operator)
	{
		fmat4x2 m1 = fm421;
		test_assert(&(m1 += u2) == &m1);
		test_assert(m1 == fm421 + u2);

		fmat4x2 m2 = fm421;
		test_assert(&(m2 += um422) == &m2);
		test_assert(m2 == fm421 + um422);
	}

	TEST_CASE(subtraction_assignment_operator)
	{
		fmat4x2 m1 = fm421;
		test_assert(&(m1 -= u2) == &m1);
		test_assert(m1 == fm421 - u2);

		fmat4x2 m2 = fm421;
		test_assert(&(m2 -= um422) == &m2);
		test_assert(m2 == fm421 - um422);
	}

	TEST_CASE(multiplication_assignment_operator)
	{
		fmat4x2 m1 = fm421;
		test_assert(&(m1 *= u2) == &m1);
		test_assert(m1 == fm421 * u2);

		// TODO
		//fmat4x2 m2 = fm421;
		//test_assert(&(m2 *= um422) == &m2);
		//test_assert(m2 == fm421 * um422);
	}

	TEST_CASE(division_assignment_operator)
	{
		fmat4x2 m1 = fm421;
		test_assert(&(m1 /= u2) == &m1);
		test_assert(m1 == fm421 / u2);

		fmat4x2 m2 = fm421;
		test_assert(&(m2 /= um422) == &m2);
		test_assert(m2 == fm421 / um422);
	}

	TEST_CASE(modulo_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 %= u2) == &m1);
		test_assert(m1 == im421 % u2);

		mat4x2<int> m2 = im421;
		test_assert(&(m2 %= um422) == &m2);
		test_assert(m2 == im421 % um422);
	}

	TEST_CASE(bitwise_and_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 &= u2) == &m1);
		test_assert(m1 == (im421 & u2));

		mat4x2<int> m2 = im421;
		test_assert(&(m2 &= um422) == &m2);
		test_assert(m2 == (im421 & um422));
	}

	TEST_CASE(bitwise_or_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 |= u2) == &m1);
		test_assert(m1 == (im421 | u2));

		mat4x2<int> m2 = im421;
		test_assert(&(m2 |= um422) == &m2);
		test_assert(m2 == (im421 | um422));
	}

	TEST_CASE(bitwise_xor_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 ^= u2) == &m1);
		test_assert(m1 == (im421 ^ u2));

		mat4x2<int> m2 = im421;
		test_assert(&(m2 ^= um422) == &m2);
		test_assert(m2 == (im421 ^ um422));
	}

	TEST_CASE(bitwise_shift_left_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 <<= u2) == &m1);
		test_assert(m1 == (im421 << u2));

		mat4x2<int> m2 = im421;
		test_assert(&(m2 <<= um422) == &m2);
		test_assert(m2 == (im421 << um422));
	}

	TEST_CASE(bitwise_shift_right_assignment_operator)
	{
		mat4x2<int> m1 = im421;
		test_assert(&(m1 >>= u2) == &m1);
		test_assert(m1 == (im421 >> u2));

		mat4x2<int> m2 = im421;
		test_assert(&(m2 >>= um422) == &m2);
		test_assert(m2 == (im421 >> um422));
	}
}
