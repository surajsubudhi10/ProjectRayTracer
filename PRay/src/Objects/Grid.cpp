//
// Created by Suraj on 11-06-2018.
//

#include <Objects/Grid.h>
#include <cmath>
#include <Utils/Maths.h>
#include <iostream>

Grid::Grid() :
    Compound(),
    nx(0), ny(0), nz(0)
{}

Grid::Grid(const Grid &grid):
    Compound(grid),
    nx(grid.nx), ny(grid.ny), nz(grid.nz)
{}

Grid* Grid::clone() const
{
    return new Grid(*this);
}

BBox Grid::get_bounding_box() { return bbox;}

Point3D Grid::min_coordinates() const
{
    BBox object_box;
    Point3D p0(kHugeValue);

    for(auto obj : _objects)
    {
        object_box = obj->get_bounding_box();

        if(object_box.x0 < p0.x)
            p0.x = object_box.x0;

        if(object_box.y0 < p0.y)
            p0.y = object_box.y0;

        if(object_box.z0 < p0.z)
            p0.z = object_box.z0;
    }

    p0.x -= kEpsilon;
    p0.y -= kEpsilon;
    p0.z -= kEpsilon;

    return p0;
}

Point3D Grid::max_coordinates() const
{
    BBox object_box;
    Point3D p1(-kHugeValue);

    for(auto obj : _objects)
    {
        object_box = obj->get_bounding_box();

        if(object_box.x1 > p1.x)
            p1.x = object_box.x1;

        if(object_box.y1 > p1.y)
            p1.y = object_box.y1;

        if(object_box.z1 > p1.z)
            p1.z = object_box.z1;
    }

    p1.x -= kEpsilon;
    p1.y -= kEpsilon;
    p1.z -= kEpsilon;

    return p1;
}

void Grid::setup_cells()
{
    Point3D p0 = min_coordinates();
    Point3D p1 = max_coordinates();

    bbox.x0 = p0.x;
    bbox.y0 = p0.y;
    bbox.z0 = p0.z;
    bbox.x1 = p1.x;
    bbox.y1 = p1.y;
    bbox.z1 = p1.z;

    const auto numOfObjects = _objects.size();
    const auto wx = p1.x - p0.x;
    const auto wy = p1.y - p0.y;
    const auto wz = p1.z - p0.z;
    const auto multiplier = 2.0f;

    const auto s = pow(wx * wy * wz / numOfObjects, 1.0f/ 3.0f);
    nx = (int)(multiplier * wx / s) + 1;
    ny = (int)(multiplier * wy / s) + 1;
    nz = (int)(multiplier * wz / s) + 1;

    const auto numOfCells = static_cast<unsigned int>(nx * ny * nz);
    _cells.reserve(numOfCells);

    for(auto i = 0; i < numOfCells; i++){
        _cells.push_back(nullptr);
    }

    std::vector<int> counts;
    counts.reserve(numOfCells);
    for (int i = 0; i < numOfCells; i++) {
        counts.push_back(0);
    }

    BBox obj_box;   // object bounding box
    int index;      // cells arrays index

    for(auto obj : _objects)
    {
        obj_box = obj->get_bounding_box();

        const auto ixmin = static_cast<int>(clamp((obj_box.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1));
        const auto iymin = static_cast<int>(clamp((obj_box.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1));
        const auto izmin = static_cast<int>(clamp((obj_box.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1));

        const auto ixmax = static_cast<int>(clamp((obj_box.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1));
        const auto iymax = static_cast<int>(clamp((obj_box.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1));
        const auto izmax = static_cast<int>(clamp((obj_box.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1));

        for(int iz = izmin; iz <= izmax; iz++){
            for(int iy = iymin; iy <= iymax; iy++){
                for(int ix = ixmin; ix <= ixmax; ix++)
                {
                    index = ix + nx * iy + nx * ny * iz;

                    if(counts[index] == 0){
                        _cells[index] = obj;
                        counts[index] += 1;
                    } else{
                        if(counts[index] == 1){
                            auto * compound_ptr = new Compound;
                            compound_ptr->add_object(_cells[index]);
                            compound_ptr->add_object(obj);

                            _cells[index] = compound_ptr;
                            counts[index] += 1;
                        } else{
                            _cells[index]->add_object(obj);
                            counts[index] += 1;
                        }
                    }
                }
            }
        }
    }

    _objects.erase(_objects.begin(), _objects.end());

    int num_zeroes 	= 0;
    int num_ones 	= 0;
    int num_twos 	= 0;
    int num_threes 	= 0;
    int num_greater = 0;

    for (int j = 0; j < numOfCells; j++) {
        if (counts[j] == 0)
            num_zeroes += 1;
        if (counts[j] == 1)
            num_ones += 1;
        if (counts[j] == 2)
            num_twos += 1;
        if (counts[j] == 3)
            num_threes += 1;
        if (counts[j] > 3)
            num_greater += 1;
    }

    std::cout << "num_cells =" << numOfCells << "\n";
    std::cout << "numZeroes = " << num_zeroes << "  numOnes = " << num_ones << "  numTwos = " << num_twos << "\n";
    std::cout << "numThrees = " << num_threes << "  numGreater = " << num_greater << "\n";

    counts.erase(counts.begin(), counts.end());
}

Grid::~Grid()
= default;

bool Grid::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    double ox = ray.o.x;
    double oy = ray.o.y;
    double oz = ray.o.z;

    double dx = ray.d.x;
    double dy = ray.d.y;
    double dz = ray.d.z;

    double x0 = bbox.x0;
    double y0 = bbox.y0;
    double z0 = bbox.z0;
    double x1 = bbox.x1;
    double y1 = bbox.y1;
    double z1 = bbox.z1;

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    }
    else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    }
    else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    }
    else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }

    double t0, t1;

    // find largest entering t value

    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;

    if (tz_min > t0)
        t0 = tz_min;

    // find smallest exiting t value
    if (tx_max < ty_max)
        t1 = tx_max;
    else {
        t1 = ty_max;
    }

    if (tz_max < t1)
        t1 = tz_max;

    if(t0 > t1)
        return false;

    // initial cell coordinates

    int ix, iy, iz;

    if (bbox.inside(ray.o)) {  			// does the ray start inside the grid?
        ix = static_cast<int>(clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1));
        iy = static_cast<int>(clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1));
        iz = static_cast<int>(clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1));
    }
    else {
        Point3D p = ray.o + t0 * ray.d;  // initial hit point with grid's bounding box
        ix = static_cast<int>(clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1));
        iy = static_cast<int>(clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1));
        iz = static_cast<int>(clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1));
    }

    auto dtx = (tx_max - tx_min) / nx;
    auto dty = (ty_max - ty_min) / ny;
    auto dtz = (tz_max - tz_min) / nz;

    double tx_next, ty_next, tz_next;
    int ix_stop, iy_stop, iz_stop;
    int ix_step, iy_step, iz_step;

    if (dx > 0) {
        tx_next = tx_min + (ix + 1) * dtx;
        ix_step = +1;
        ix_stop = nx;
    }
    else {
        tx_next = tx_min + (nx - ix) * dtx;
        ix_step = -1;
        ix_stop = -1;
    }

    if (dx == 0.0) {
        tx_next = kHugeValue;
        ix_step = -1;
        ix_stop = -1;
    }


    if (dy > 0) {
        ty_next = ty_min + (iy + 1) * dty;
        iy_step = +1;
        iy_stop = ny;
    }
    else {
        ty_next = ty_min + (ny - iy) * dty;
        iy_step = -1;
        iy_stop = -1;
    }

    if (dy == 0.0) {
        ty_next = kHugeValue;
        iy_step = -1;
        iy_stop = -1;
    }

    if (dz > 0) {
        tz_next = tz_min + (iz + 1) * dtz;
        iz_step = +1;
        iz_stop = nz;
    }
    else {
        tz_next = tz_min + (nz - iz) * dtz;
        iz_step = -1;
        iz_stop = -1;
    }

    if (dz == 0.0) {
        tz_next = kHugeValue;
        iz_step = -1;
        iz_stop = -1;
    }

    /// traverse the grid

    while(true)
    {
        auto index = ix + nx * iy + nx * ny * iz;
        auto* object_ptr = _cells[index];

        if(tx_next < ty_next && tx_next < tz_next){
            if(object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < tx_next){
                material_ptr = object_ptr->get_material();
                return true;
            }

            tx_next += dtx;
            ix += ix_step;

            if(ix == ix_stop){
                return false;
            }
        } else{
            if(ty_next < tz_next){
                if(object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < ty_next){
                    material_ptr = object_ptr->get_material();
                    return true;
                }

                ty_max += dty;
                iy += iy_step;

                if(iy == iy_stop){
                    return false;
                }
            } else{
                if(object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < tz_next){
                    material_ptr = object_ptr->get_material();
                    return true;
                }

                ty_max += dtz;
                iz += iz_step;

                if(iz == iz_stop){
                    return false;
                }
            }
        }
    }
}


