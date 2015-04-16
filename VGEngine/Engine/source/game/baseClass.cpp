#include "engine\game\baseClass.h"
using namespace vg;
int BaseClass::memoryCount = 0;
BaseClass::BaseClass(){ memoryCount++; }
BaseClass::~BaseClass(){ memoryCount--; }
