#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

class Events : public EventHandler
{
    void on_right_click(Player* player)
    {
        player->send_message("Hello world!");
        std::cout << "ON RIGHT CLICK" << std::endl;
    }
};

int main()
{
    connect("localhost", DTA_PORT);
    register_artifact(1, new Events());

    loop();
}
