//
// Created by Suraj on 29-05-2018.
//

#include <Objects/Torus.h>
#include <cmath>
#include <Utils/Maths.h>

Torus::Torus() :
        GeometricObject(),
        _center(Point3D(0.0)),
        _inner_radius(0.5f),
        _outer_radius(1.0f)
{}


Torus::Torus(const Torus &torus) :
    GeometricObject(torus),
    _center(torus._center),
    _inner_radius(torus._inner_radius),
    _outer_radius(torus._outer_radius)
{}

Torus::Torus(const Point3D &cen, float innerRad, float outerRad) :
    GeometricObject(),
    _center(cen),
    _inner_radius(innerRad),
    _outer_radius(outerRad)
{}


Torus* Torus::clone() const
{
    return (new Torus(*this));
}
//
//bool Torus::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
//{
////    if(!bBox.hit(ray))
////        return false;
//
//    auto dx = ray.d.x; auto dy = ray.d.y; auto dz = ray.d.z;
//    auto ox = ray.o.x; auto oy = ray.o.y; auto oz = ray.o.z;
//
//    double coeffs[5];       // Coefficient Array
//    double roots[4];        // Solutions Array
//
//    auto sum_d_sqrd = dx * dx + dy * dy + dz * dz;
//    auto e = ox * ox + oy * oy + oz * oz - (_outer_radius * _outer_radius) - (_inner_radius * _inner_radius);
//    auto f = dx * ox + oy * dy + oz * dz;
//    auto four_a_sqrd = 4.0 * _outer_radius * _outer_radius;
//
//
//    coeffs[0] =  4 * e * e - (four_a_sqrd * (powf(_inner_radius, 2) - pow(oy, 2)));
//    coeffs[1] = (4 * e * f) + 2 * four_a_sqrd * oy * dy;
//    coeffs[2] =  2 * sum_d_sqrd * e + 4 * f * f + four_a_sqrd * dy * dy;
//    coeffs[3] = 4 * sum_d_sqrd * f;
//    coeffs[4] = sum_d_sqrd * sum_d_sqrd;
//
//    // Find roots
//    auto num_of_real_roots = SolveQuarticV2(coeffs, roots);
//    auto intersected = false;
//    auto t = kHugeValue;
//
//    if(num_of_real_roots == 0)
//        return false;
//
//    for(int j = 0; j < num_of_real_roots; j++)
//    {
//        if(roots[j] > kEpsilon)
//        {
//            intersected = true;
//            if(roots[j] < t)
//                t = roots[j];
//        }
//    }
//
//    if(!intersected)
//        return false;
//
//    tmin = t;
//    sr.hit_point = ray.o + t * ray.d;
//    sr.normal = get_normal(sr.hit_point);
//    return true;
//}
//
//


BBox Torus::get_bounding_box() const
{
    double delta = 0.0001;

    return (BBox(Point3D(_center.x - _outer_radius - _inner_radius - delta, _center.y - _inner_radius - delta, _center.z - _outer_radius - _inner_radius - delta),
                 Point3D(_center.x + _outer_radius + _inner_radius + delta, _center.y + _inner_radius + delta, _center.z + _outer_radius + _inner_radius + delta)));
}

Normal Torus::get_normal(const Point3D &p) const
{

    auto square_val = (p.x * p.x + p.y * p.y + p.z * p.z + (pow(_outer_radius, 2) - pow(_inner_radius, 2)));
    auto nx = 4 * p.x *  (square_val - 2 * pow(_outer_radius, 2));
    auto ny = 4 * p.y *   square_val;
    auto nz = 4 * p.z *  (square_val - 2 * pow(_outer_radius, 2));

    return Normal(nx, ny, nz);
}

bool Torus::shadow_hit(const Ray &ray, float &tmin) const
{
    if(!shadows)
        return false;

    auto origin = ray.o;
    auto direction = ray.d;
    auto origin_to_center = origin - _center;
    auto A = _outer_radius;
    auto B = _inner_radius;
    auto direction_len_sq = direction.len_squared();

    auto K1 = 2.0 * origin_to_center * direction;
    auto K2 = origin_to_center.len_squared() + pow(A, 2) - pow(B, 2);
    auto K4 = pow(origin_to_center.x , 2) + pow(origin_to_center.z, 2);
    auto K5 = pow(direction.x, 2) + pow(direction.z, 2);
    auto K6 = 2.0 * origin_to_center.x * direction.x + 2.0 * origin_to_center.z * direction.z;

    double coeff[5];
    double roots[4];

    coeff[0] = pow(direction_len_sq, 2);
    coeff[1] = 2.0 * direction_len_sq * K1;
    coeff[2] = 2.0 * direction_len_sq * K2 + K1 * K1 - 4 * A * A * K5;
    coeff[3] = 2.0 * K1 * K2 - 4 * A * A * K6;
    coeff[4] = K2 * K2 - 4 * A * A * K4;

    auto num_of_roots = SolveQuarticV2(coeff, roots);

    // Find roots
    auto num_of_real_roots = SolveQuarticV2(coeff, roots);
    auto intersected = false;
    auto t = kHugeValue;

    if(num_of_real_roots == 0)
        return false;

    for(int j = 0; j < num_of_real_roots; j++)
    {
        if(roots[j] > kEpsilon)
        {
            intersected = true;
            if(roots[j] < t)
                t = roots[j];
        }
    }

    return intersected;
}

bool Torus::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
//    if(!bBox.hit(ray))
//        return false;

    auto origin = ray.o;
    auto direction = ray.d;
    auto origin_to_center = origin - _center;
    auto A = _outer_radius;
    auto B = _inner_radius;
    auto direction_len_sq = direction.len_squared();

    auto K1 = 2.0 * origin_to_center * direction;
    auto K2 = origin_to_center.len_squared() + pow(A, 2) - pow(B, 2);
    auto K4 = pow(origin_to_center.x , 2) + pow(origin_to_center.z, 2);
    auto K5 = pow(direction.x, 2) + pow(direction.z, 2);
    auto K6 = 2.0 * origin_to_center.x * direction.x + 2.0 * origin_to_center.z * direction.z;

    double coeff[5];
    double roots[4];

    coeff[0] = pow(direction_len_sq, 2);
    coeff[1] = 2.0 * direction_len_sq * K1;
    coeff[2] = 2.0 * direction_len_sq * K2 + K1 * K1 - 4 * A * A * K5;
    coeff[3] = 2.0 * K1 * K2 - 4 * A * A * K6;
    coeff[4] = K2 * K2 - 4 * A * A * K4;

    auto num_of_roots = SolveQuarticV2(coeff, roots);

    auto intersected = false;
    auto t = kHugeValue;

    if(num_of_roots == 0)
        return false;

    for (int i = 0; i < num_of_roots; i++) {
        if(roots[i] > kEpsilon){
            intersected = true;

            if(roots[i] < t){
                t = roots[i];
            }
        }
    }

    if(!intersected)
        return false;

    tmin = t;
    sr.hit_point = origin + tmin * direction;
    sr.normal = get_normal(sr.hit_point);
    return true;
}

//bool Torus::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
//{
//    // Set up the coefficients of a quartic equation for the intersection
//    // of the parametric equation P = vantage + u*direction and the
//    // surface of the torus.
//    // There is far too much algebra to explain here.
//    // See the text of the tutorial for derivation.
//
//    auto vantage = ray.o;
//    auto direction = ray.d;
//
//    auto R = _outer_radius;
//    auto S = _inner_radius;
//
//    const double T = 4.0 * R * R;
//    const double G = T * (direction.x*direction.x + direction.y*direction.y);
//    const double H = 2.0 * T * (vantage.x*direction.x + vantage.y*direction.y);
//    const double I = T * (vantage.x*vantage.x + vantage.y*vantage.y);
//    const double J = direction.len_squared();
//    const double K = 2.0 * Vector3D(vantage) * direction;
//    const double L = Vector3D(vantage).len_squared() + R*R - S*S;
//
//
//    double coeff[5] = {J*J, 2.0 * J * K, 2.0 * J * L + K * K - G, 2.0 * K * L - H, L * L - I};
//    double uArray[4];
//
//    const int numRealRoots = SolveQuarticV2(coeff, uArray);
////            J*J,                    // coefficient of u^4
////            2.0*J*K,                // coefficient of u^3
////            2.0*J*L + K*K - G,      // coefficient of u^2
////            2.0*K*L - H,            // coefficient of u^1 = u
////            L*L - I,                // coefficient of u^0 = constant term
////            uArray                  // receives 0..4 real solutions
////    );
//
//    // We need to keep only the real roots.
//    // There can be significant roundoff error in quartic solver,
//    // so we have to tolerate more slop than usual.
//    const double SURFACE_TOLERANCE = 1.0e-4;
//    int numPositiveRoots = 0;
//    for (int i=0; i < numRealRoots; ++i)
//    {
//        // Compact the array...
//        if (uArray[i] > SURFACE_TOLERANCE)
//        {
//            uArray[numPositiveRoots++] = uArray[i];
//        }
//    }
//
//    auto intersected = false;
//    auto t = kHugeValue;
//    if(numRealRoots == 0)
//        return false;
//    for(int j = 0; j < numRealRoots; j++)
//    {
//        if(uArray[j] > kEpsilon)
//        {
//            intersected = true;
//            if(uArray[j] < t)
//                t = uArray[j];
//        }
//    }
//    if(!intersected)
//        return false;
//
//    tmin = t;
//    sr.hit_point = ray.o + t * ray.d;
//    sr.normal = get_normal(sr.hit_point);
//
//    return true;
//
//    //return numPositiveRoots;
//}

void Torus::set_center(const Point3D &cen) { _center = cen; }
void Torus::set_inner_radius(float rad) {_inner_radius = rad; }
void Torus::set_outer_radius(float rad) {_outer_radius = rad; }

Point3D Torus::get_center() const { return _center;}
float Torus::get_outer_radius() const { return _outer_radius;}
float Torus::get_inner_radius() const { return _inner_radius;}

Torus::~Torus()
= default;
