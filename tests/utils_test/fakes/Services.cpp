#include "Services.h"

int Service1::instancesCount = 0;

Service1::Service1(int id)
    : IService(id)
{
    ++instancesCount;
}

Service1::~Service1()
{
    --instancesCount;
}




