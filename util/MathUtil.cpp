#include "MathUtil.h"

int MathUtil::compare(double d1, double d2, double dEsp)
{
    if (d1 > d2 + dEsp)
        return 1;
    else if (d2 > d1 + dEsp)
        return -1;
    return 0;
}
