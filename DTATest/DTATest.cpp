#include <iostream>

#include "DTArtifacts.h"

using namespace dreamtea;

Vector3 direction;

class Events : public EventHandler
{
    void on_right_click(Player* player)
    {
        player->fix_position();

        player->send_message("Starting...");
        //player->set_velocity(Vector3(0, 1, 0));

        direction = player->get_direction();

        auto color = Color(0, 0, 0);

        bool ask_nearby = false;

        for (int i = 0; i < 30; i++)
        {
            color.r = (255 / 30) * i;
            color.g = (255 / 40) * i;
            color.b = (255 / 50) * i;

            Vector3 position(
                direction.x * i,
                direction.y * i + 1.0,
                direction.z * i
            );
            player->world->add_particle(
                position.x,
                position.y,
                position.z,
                Particle::DUST,
                ParticleOptions(color, true)
            );

            if (ask_nearby)
            {
                player->world->get_nearby_entities(position.x, position.y, position.z, 1, [player](Entity entity) {
                    player->world->add_particle(
                        entity.position.x,
                        entity.position.y + 2.0,
                        entity.position.z,
                        Particle::HEART
                    );
                    player->attack(entity, 5);
                    player->burn(entity, 100);
                });
            }
            ask_nearby = !ask_nearby;
        }

        //get_scheduler()->run_task(20 * 10, 20);
    }
};

int main()
{
    connect("localhost", DTA_PORT);
    register_artifact(1, new Events());

    loop();
}
