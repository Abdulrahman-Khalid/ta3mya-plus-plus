#pragma once
#define YY_NO_UNPUT

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

#include "statements.h"

#include "operator.h"
#include "type.h"
#include "node.h"

extern bool disableDebug;

#define DEBUG(i) do { if (!disableDebug) { cerr << "DEBUG: " << (i) << endl; } } while(0)
