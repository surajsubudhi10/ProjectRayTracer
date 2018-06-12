//
// Created by Suraj on 11-06-2018.
//

#ifndef PRAY_GRID_H
#define PRAY_GRID_H

#include "Compound.h"

class Grid : public Compound
{
public:
    Grid();
    Grid(const Grid& grid);
    Grid* clone() const override;
    ~Grid() override ;

    BBox get_bounding_box() const override;
    void setup_cells();
    bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
    //bool shadow_hit(const Ray& ray, float& tmin) const override;

private:
    std::vector<GeometricObject*> _cells;
    //BBox bbox;
    int nx, ny, nz; // Number of cells in x, y and z directions

    Point3D min_coordinates() const;
    Point3D max_coordinates() const;

}; // End of Class Grid

#endif //PRAY_GRID_H
