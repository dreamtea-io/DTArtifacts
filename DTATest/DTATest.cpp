#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

int main()
{
    connect("localhost", DTA_PORT);

    loop();
}
