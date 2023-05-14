#pragma once
#ifndef ETCFUNCTION_H
#define ETCFUNCTION_H

#include <cmath>

#define max(a,b)	(((a) > (b)) ? (a) : (b))
#define min(a,b)	(((a) < (b)) ? (a) : (b))

#define sqrt2(a,b)				(sqrt(a+b))
#define dis_cal(a,b)			((a-b)*(a-b))
#define dis_vector(a,b)		80-(abs(a.IDE[0]-b->IDE[0])+abs(a.IDE[1]-b->IDE[1])+abs(a.IDE[2]-b->IDE[2]) + abs(a.IDE[3] - b->IDE[3]))

#endif