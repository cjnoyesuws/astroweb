#include <iostream>
#include <stdio.h>
#include "astro.h"
#include "julian.h"
#include "datetime.fns"


int main(int argc, char *argv[]) {
    DATES date = {3,29,1958};
    DATES noon = {0,0,0};
    TIM time = { 17,45, 0 };
    TIM tnoon = {0, 0, 0};
    TIM side = {0,0,0};
    DEG_MIN lat = {42,50,'N'};
    DEG_MIN lng = { 71,50,'W'};
    JULIAN jul;


    int v1 = noon_date( &date, &noon, &tnoon, &time, -5, 0 );
    printf("noon hours %d, date %d/%d/%d time %d:%d\n", v1, noon.day, noon.month, noon.year, tnoon.hours, tnoon.minutes);
    julian_calc(&noon,v1,tnoon.minutes, &jul);
    std::cout << "base " << jul.jd_base << " 1900 " << jul.jd_1900 << " 1989 " << jul.jd_1989 << " cent " << jul.jd_cent << " centsq " << jul.jd_cent_sq;
    printf("base %f, 1900 %f, 1989 %f, 1900 cent %f, 1900 centsq %f\n", jul.jd_base,jul.jd_1900,jul.jd_1989,jul.jd_cent,jul.jd_cent_sq);
    sidereal_time(&noon, v1, tnoon.minutes,  &lng, &side, 'N' );
    printf("sidereal %d:%d:%d\n", side.hours, side.minutes, side.seconds);

    }



