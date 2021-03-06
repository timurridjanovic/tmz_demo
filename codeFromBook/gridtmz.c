#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g) {

    // x
    double imp0 = 377.0;
    int mm, nn;

    Type = tmZGrid;

    // x size of domain
    SizeX = 101;
    // y size of domain
    SizeY = 81;
    // duration of simulation
    MaxTime = 300;

    // Courant number
    Cdtds = 1.0 / sqrt(2.0);

    ALLOC_2D(g->hx, SizeX, SizeY - 1, double);
    ALLOC_2D(g->chxh, SizeX, SizeY - 1, double);
    ALLOC_2D(g->chxe, SizeX, SizeY - 1, double);
    ALLOC_2D(g->hy, SizeX - 1, SizeY, double);
    ALLOC_2D(g->chyh, SizeX - 1, SizeY, double);
    ALLOC_2D(g->chye, SizeX - 1, SizeY, double);
    ALLOC_2D(g->ez, SizeX, SizeY, double);
    ALLOC_2D(g->ceze, SizeX, SizeY, double);
    ALLOC_2D(g->cezh, SizeX, SizeY, double);

    /*set electric-field update coefficients*/
    for (mm = 0; mm < SizeX; mm++) {
        for (nn = 0; nn < SizeY; nn++) {
            Ceze(mm, nn) = 1.0;
            Cezh(mm, nn) = Cdtds*imp0;
        }
    }

    /*set magnetic-field update coefficients*/
    for (mm = 0; mm < SizeX; mm++) {
        for (nn = 0; nn < SizeY - 1; nn++) {
            Chxh(mm, nn) = 1.0;
            Chxe(mm, nn) = Cdtds / imp0;
        }
    }

    for (mm = 0; mm < SizeX - 1; mm++) {
        for (nn = 0; nn < SizeY; nn++) {
            Chyh(mm, nn) = 1.0;
            Chye(mm, nn) = Cdtds / imp0;
        }
    }
    return;
}
