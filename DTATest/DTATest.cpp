#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

class Events : public EventHandler
{
    void on_right_click()
    {
        std::cout << "ON RIGHT CLICK" << std::endl;
    }
};

int main()
{
    connect("localhost", DTA_PORT);
    register_artifact(1, new Events());

    loop();
}
