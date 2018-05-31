

#include "Utils/Maths.h"
#include <cmath>

//#define     EQN_EPS     1e-9  
//#define     EQN_EPS     1e-30
//#define     EQN_EPS     1e-60
#define     EQN_EPS     1e-90

#define	IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

int SolveQuadric(double c[3], double s[2])
{
	double p, q, D;

	/* normal form: x^2 + px + q = 0 */

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];

	D = p * p - q;

	if (IsZero(D)) {
		s[0] = -p;
		return 1;
	}
	else if (D > 0) {
		double sqrt_D = sqrt(D);

		s[0] = sqrt_D - p;
		s[1] = -sqrt_D - p;
		return 2;
	}
	else /* if (D < 0) */
		return 0;
}


int SolveCubic(double c[4], double s[3])
{
	int     i, num;
	double  sub;
	double  A, B, C;
	double  sq_A, p, q;
	double  cb_p, D;

	/* normal form: x^3 + Ax^2 + Bx + C = 0 */

	A = c[2] / c[3];
	B = c[1] / c[3];
	C = c[0] / c[3];

	/*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

	sq_A = A * A;
	p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
	q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

	/* use Cardano's formula */

	cb_p = p * p * p;
	D = q * q + cb_p;

	if (IsZero(D)) {
		if (IsZero(q)) { /* one triple solution */
			s[0] = 0;
			num = 1;
		}
		else { /* one single and one double solution */
			double u = cbrt(-q);
			s[0] = 2 * u;
			s[1] = -u;
			num = 2;
		}
	}
	else if (D < 0) { /* Casus irreducibilis: three real solutions */
		double phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
		double t = 2 * sqrt(-p);

		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + PI / 3);
		s[2] = -t * cos(phi - PI / 3);
		num = 3;
	}
	else { /* one real solution */
		double sqrt_D = sqrt(D);
		double u = cbrt(sqrt_D - q);
		double v = -cbrt(sqrt_D + q);

		s[0] = u + v;
		num = 1;
	}

	/* resubstitute */

	sub = 1.0 / 3 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}


int SolveQuartic(double c[5], double s[4])
{
	double  coeffs[4];
	double  z, u, v, sub;
	double  A, B, C, D;
	double  sq_A, p, q, r;
	int     i, num;

	/* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	A = c[3] / c[4];
	B = c[2] / c[4];
	C = c[1] / c[4];
	D = c[0] / c[4];

	/*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

	sq_A = A * A;
	p = -3.0 / 8 * sq_A + B;
	q = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
	r = -3.0 / 256 * sq_A*sq_A + 1.0 / 16 * sq_A*B - 1.0 / 4 * A*C + D;

	if (IsZero(r)) {
		/* no absolute term: y(y^3 + py + q) = 0 */

		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;

		num = SolveCubic(coeffs, s);

		s[num++] = 0;
	}
	else {
		/* solve the resolvent cubic ... */

		coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2 * p;
		coeffs[3] = 1;

		(void)SolveCubic(coeffs, s);

		/* ... and take the one real solution ... */

		z = s[0];

		/* ... to build two quadric equations */

		u = z * z - r;
		v = 2 * z - p;

		if (IsZero(u))
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return 0;

		if (IsZero(v))
			v = 0;
		else if (v > 0)
			v = sqrt(v);
		else
			return 0;

		coeffs[0] = z - u;
		coeffs[1] = q < 0 ? -v : v;
		coeffs[2] = 1;

		num = SolveQuadric(coeffs, s);

		coeffs[0] = z + u;
		coeffs[1] = q < 0 ? v : -v;
		coeffs[2] = 1;

		num += SolveQuadric(coeffs, s + num);
	}

	/* resubstitute */

	sub = 1.0 / 4 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}


int SolveQuarticV2(double coeff[5], double roots[4])
{
    if (coeff[0] == 0)
    {
        double cubic_coeff[4] = {coeff[1], coeff[2], coeff[3], coeff[4]};
        auto num = SolveCubic(cubic_coeff, roots);
        return num;
    }

    // See "Summary of Ferrari's Method" in http://en.wikipedia.org/wiki/Quartic_function

    // Without loss of generality, we can divide through by 'a'.
    // Anywhere 'a' appears in the equations, we can assume a = 1.
    coeff[1] /= coeff[0];
    coeff[2] /= coeff[0];
    coeff[3] /= coeff[0];
    coeff[4] /= coeff[0];

    auto b2 = coeff[1] * coeff[1];
    auto b3 = coeff[1] * b2;
    auto b4 = b2 * b2;

    auto alpha = (-3.0 / 8.0) * b2 + coeff[2];
    auto beta  = b3 / 8.0 - coeff[1] * coeff[2] / 2.0 + coeff[3];
    auto gamma = (-3.0 / 256.0) * b4 + b2 * coeff[2] / 16.0 - coeff[1] * coeff[3]/4.0 + coeff[4];

    auto alpha2 = alpha * alpha;
    auto t = -coeff[1] / 4.0;

    if (IsZero(beta))
    {
        auto rad = sqrt(alpha2 - 4.0*gamma);
        auto r1 = sqrt((-alpha + rad) / 2.0);
        auto r2 = sqrt((-alpha - rad) / 2.0);

        roots[0] = t + r1;
        roots[1] = t - r1;
        roots[2] = t + r2;
        roots[3] = t - r2;
    }
    else
    {
        auto alpha3 = alpha * alpha2;
        auto P = -(alpha2 / 12.0 + gamma);
        auto Q = -alpha3 / 108.0 + alpha * gamma / 3.0 - beta * beta / 8.0;
        auto R = -Q/2.0 + sqrt(Q * Q / 4.0 + P * P * P / 27.0);
        auto U = pow(R, 1 / 3);
        auto y = (-5.0/6.0)*alpha + U;
        if (IsZero(U))
        {
            y -= pow(Q, 1 / 3);//cbrt(Q,0);
        }
        else
        {
            y -= P/(3.0 * U);
        }
        auto W = sqrt(alpha + 2.0*y);

        auto r1 = sqrt(-(3.0 * alpha + 2.0 * y + 2.0 * beta / W));
        auto r2 = sqrt(-(3.0 * alpha + 2.0 * y - 2.0 * beta / W));

        roots[0] = t + ( W - r1) / 2.0;
        roots[1] = t + ( W + r1) / 2.0;
        roots[2] = t + (-W - r2) / 2.0;
        roots[3] = t + (-W + r2) / 2.0;
    }

    return 4;
}
