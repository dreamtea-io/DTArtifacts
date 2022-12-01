#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

class Events : public EventHandler
{
    void on_right_click(Player* player)
    {
        player->fix_position();

        player->send_message("Starting...");
        player->set_velocity(Vector3(0, 1, 0));

        for (int y = 0; y < 5; y++)
        {
            for (int x = 2; x < 12; x++)
            {
                for (int z = 0; z < 10; z++)
                {
                    if ((x > 2 && x < 11) && (z > 0 && z < 9))
                    {
                        continue;
                    }

                    player->world->set_block(x, y, z, "OAK_PLANKS");
                }
            }
        }
    }
};

int main()
{
    connect("localhost", DTA_PORT);
    register_artifact(1, new Events());

    loop();
}
