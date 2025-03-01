#include <iostream>
#include <cstring>
#include <string>
#include <Windows.h>

int main()
{
    struct Entity {
        ULONG pEnt;
        char placeholder[10];
    };

    struct EspStorage {
        Entity entities[32];
    } espstorage;
    memset(&espstorage, 0, sizeof(espstorage));
    std::cout << espstorage.entities[0].pEnt << std::endl;
    memset(&espstorage.entities[0].pEnt, (ULONG)5, 1);
    //espstorage.entities[0].pEnt = 5;
    std::cout << std::to_string((int)espstorage.entities[0].pEnt) << std::endl;
}
