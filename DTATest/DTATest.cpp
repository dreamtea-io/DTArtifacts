#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

class Events : public EventHandler
{
    void on_right_click(Player* player)
    {
        player->fix_position();

        player->send_message("Starting...");
        //player->set_velocity(Vector3(0, 1, 0));

        auto direction = player->get_direction();
        auto color = Color(0, 0, 0);

        for (int i = 0; i < 30; i++)
        {
            color.r = (255 / 30) * i;
            color.g = (255 / 40) * i;
            color.b = (255 / 50) * i;

            player->world->add_particle(
                direction.x * i,
                direction.y * i + 1.0,
                direction.z * i,
                Particle::DUST,
                color
            );
        }
    }
};

int main()
{
    connect("localhost", DTA_PORT);
    register_artifact(1, new Events());

    loop();
}
