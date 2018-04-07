#ifndef __FX_POINT_H__
#define __FX_POINT_H__

#include <algorithm>

namespace fx
{
#define PI (3.1415926535897932384626433832795028841971693993751)

	template<class Type>
	float a2r(Type a)
	{
		return (float)a * (float)PI / 180.0f;
	}

	template<class Type>
	double d_a2r(Type a)
	{
		return (double)a * PI / 180.0;
	}

	template<class Type>
	float r2a(Type r)
	{
		return (float)r * 180.0f / (float)PI;
	}

	template<class Type>
	double d_r2a(Type r)
	{
		return (double)r * 180.0 / PI;
	}

	template<class Type>
	float sinr(Type r)
	{
		return (float)std::sin(r);
	}

	template<class Type>
	float sin(Type a)
	{
		return sinr(a2r(a));
	}

	template<class Type>
	double dsinr(Type r)
	{
		return (double)std::sin(r);
	}

	template<class Type>
	double dsin(Type a)
	{
		return (double)dsinr(d_a2r(a));
	}

	template<class Type>
	float cosr(Type r)
	{
		return (float)std::cos(r);
	}

	template<class Type>
	float cos(Type a)
	{
		return cosr(a2r(a));
	}

	template<class Type>
	double dcosr(Type r)
	{
		return (double)std::cos(r);
	}

	template<class Type>
	double dcos(Type a)
	{
		return (double)dcosr(d_a2r(a));
	}

	struct point
	{
		point()
			: x(0), y(0)
		{ }

		point(int _x, int _y)
			: x(_x), y(_y)
		{ }

		~point()
		{ }

		point operator+(const point & p)
		{
			return point(x + p.x, y + p.y);
		}

		point operator+=(const point & p)
		{
			return point(x += p.x, y += p.y);
		}

		point operator-(const point & p)
		{
			return point(x - p.x, y - p.y);
		}

		point operator-=(const point & p)
		{
			return point(x -= p.x, y -= p.y);
		}

		bool operator==(const point & p)
		{
			return x == p.x && y == p.y;
		}

		bool operator!=(const point & p)
		{
			return x != p.x || y != p.y;
		}

		int operator[](int idx)
		{
			switch (idx)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				return -1;
			}
		}

// 		float _x = x * cos(a) - y * sin(a);
// 		float _y = x * sin(a) + y * cos(a);

// 		float _x = x * cos(a) + y * sin(a);
// 		float _y = y * cos(a) - x * sin(a);

		point rotate(const float & a)
		{
			return point((int)std::lroundf(x * cos(a) + y * sin(a)),
				(int)std::lroundf(y * cos(a) - x * sin(a)));
		}

		point rotate(const float & a, const point & c)
		{
			point t = *this - c;
			return t.rotate(a) + c;
		}

		point rotate_self(const float & a)
		{
			*this = rotate(a);
			return *this;
		}

		point rotate_self(const float & a, const point & c)
		{
			*this = rotate(a, c);
			return *this;
		}

		point rotate_rv(const float & a)
		{
			return point((int)std::lroundf(x * cos(a) - y * sin(a)),
				(int)std::lroundf(x * sin(a) + y * cos(a)));
		}

		point rotate_rv(const float & a, const point & c)
		{
			point t = *this - c;
			return t.rotate_rv(a) + c;
		}

		point rotate_self_rv(const float & a)
		{
			*this = rotate_rv(a);
			return *this;
		}

		point rotate_self_rv(const float & a, const point & c)
		{
			operator-=(c);
			rotate_self_rv(a);
			return operator+=(c);
		}

	public:
		int x;
		int y;
	};

}

#endif // !__FX_POINT_H__
