#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int gameIsActive = 1;
    int hasPlayerWon = 0;

    int playerLocation = 0;
    int playerHealth = 100;

    int inventory[10] = {0};
    const int ITEM_TORCH = 0;
    const int ITEM_SWORD = 1;
    const int ITEM_SHIELD = 2;
    const int ITEM_KEY = 3;
    const int ITEM_POTION = 4;

    const char *itemNames[10] = {
        "a rusty torch",
        "a short sword",
        "a wooden shield",
        "an ornate key",
        "a healing potion"};

    int roomItems[10][10] = {{0}};
    int roomVisited[10] = {0};
    int puzzleSolved = 0;
    int exitUnlocked = 0;
    int hallwayTrapTriggered = 0;

    char playerInput[100] = {0};
    char command[50] = {0};
    char argument[50] = {0};
    int inputIsValid = 0;
    int i = 0;

    const int ROOM_CELL = 0;
    const int ROOM_HALLWAY = 1;
    const int ROOM_ARMORY = 2;
    const int ROOM_STUDY = 3;
    const int ROOM_CHAMBER = 4;
    const int ROOM_GATE = 5;

    const char *roomNames[10] = {
        "Starting Cell",
        "Echoing Hallway",
        "Ancient Armory",
        "Alchemist's Study",
        "Flooded Chamber",
        "The Grand Exit"};

    roomItems[ROOM_CELL][ITEM_TORCH] = 1;
    roomItems[ROOM_ARMORY][ITEM_SWORD] = 1;
    roomItems[ROOM_ARMORY][ITEM_SHIELD] = 1;
    roomItems[ROOM_STUDY][ITEM_POTION] = 1;

    printf("--- The Lost Labyrinth of Lumina ---\n");
    printf("You awaken on a cold, stone floor. It is pitch black.\n");
    printf("A faint, damp smell hangs in the air.\n");
    printf("What do you do? (Type 'help' for commands)\n\n");

    while (gameIsActive == 1)
    {
        command[0] = '\0';
        argument[0] = '\0';

        if (playerLocation == ROOM_CELL)
        {
            printf("You are in a small, damp cell. The walls are slick with moisture.\n");
            if (inventory[ITEM_TORCH] == 0)
            {
                printf("It is too dark to see much, but you can feel a wooden door to the NORTH.\n");
                if (roomItems[ROOM_CELL][ITEM_TORCH] == 1)
                {
                    printf("You fumble around on the floor and feel a TORCH.\n");
                }
            }
            else
            {
                printf("Your torch illuminates the cramped space. There is a single wooden door to the NORTH.\n");
            }
        }
        else if (playerLocation == ROOM_HALLWAY)
        {
            printf("You are in a long, echoing hallway. Torches in sconces cast flickering shadows.\n");
            printf("The hallway continues to the NORTH. The cell is to the SOUTH.\n");
            printf("There are doors to the EAST and WEST.\n");
        }
        else if (playerLocation == ROOM_ARMORY)
        {
            printf("You have entered an old armory. Racks of rusted weapons line the walls.\n");
            if (roomItems[ROOM_ARMORY][ITEM_SWORD] == 1 || roomItems[ROOM_ARMORY][ITEM_SHIELD] == 1)
            {
                printf("On a dusty table, you see a SWORD and a SHIELD.\n");
            }
            printf("The only exit is back to the hallway to the EAST.\n");
        }
        else if (playerLocation == ROOM_STUDY)
        {
            printf("This room is clearly an alchemist's study. Broken vials and strange powders litter the floor.\n");
            if (puzzleSolved == 0)
            {
                printf("A single SCROLL sits on a stone lectern in the center of the room.\n");
            }
            if (roomItems[ROOM_STUDY][ITEM_POTION] == 1)
            {
                printf("A small, corked POTION sits on a shelf.\n");
            }
            printf("The only way out is to the WEST.\n");
        }
        else if (playerLocation == ROOM_CHAMBER)
        {
            printf("This chamber is flooded with knee-deep, murky water. The air is heavy and cold.\n");
            if (puzzleSolved == 1 && roomItems[ROOM_CHAMBER][ITEM_KEY] == 1)
            {
                printf("You see the glint of a KEY at the bottom of the water.\n");
            }
            printf("The hallway lies to the SOUTH.\n");
        }
        else if (playerLocation == ROOM_GATE)
        {
            printf("You stand before a massive, iron-wrought gate. It is covered in intricate, ancient designs.\n");
            printf("It appears to be the only way out. It is firmly locked.\n");
            printf("The hallway is to the SOUTH.\n");
        }

        if (roomVisited[playerLocation] == 0)
        {
            roomVisited[playerLocation] = 1;
        }

        if (playerLocation == ROOM_HALLWAY && hallwayTrapTriggered == 0)
        {
            hallwayTrapTriggered = 1;
            printf("\n>> As you step into the center of the hall, you hear a *click*! <<\n");
            printf(">> Arrows shoot from hidden slits in the walls! <<\n");
            if (inventory[ITEM_SHIELD] == 1)
            {
                playerHealth = playerHealth - 15;
                printf(">> You raise your shield just in time, but one arrow gets through! You lose 15 health. <<\n");
            }
            else
            {
                playerHealth = playerHealth - 40;
                printf(">> With nothing to defend yourself, several arrows strike you! You lose 40 health. <<\n");
            }
            printf("Your health is now %d.\n\n", playerHealth);
        }

        inputIsValid = 0;
        while (inputIsValid == 0)
        {
            printf("> ");
            if (fgets(playerInput, sizeof(playerInput), stdin) != NULL)
            {
                for (i = 0; playerInput[i] != '\0'; i++)
                {
                    playerInput[i] = tolower(playerInput[i]);
                }
                if (sscanf(playerInput, "%s %s", command, argument) >= 1)
                {
                    inputIsValid = 1;
                }
                else
                {
                    printf("Please enter a valid command.\n");
                }
            }
        }

        printf("\n");

        if (strcmp(command, "quit") == 0)
        {
            gameIsActive = 0;
            printf("You give up and accept your fate in the darkness.\n");
        }
        else if (strcmp(command, "help") == 0)
        {
            printf("Commands:\n");
            printf("  go [north|south|east|west]\n");
            printf("  take [item]\n");
            printf("  use [item]\n");
            printf("  examine [object]\n");
            printf("  answer [solution]\n");
            printf("  inventory\n");
            printf("  health\n");
            printf("  quit\n\n");
        }
        else if (strcmp(command, "inventory") == 0)
        {
            printf("You are carrying:\n");
            int hasItems = 0;
            for (i = 0; i < 10; i++)
            {
                if (inventory[i] == 1)
                {
                    printf(" - %s\n", itemNames[i]);
                    hasItems = 1;
                }
            }
            if (hasItems == 0)
            {
                printf(" - Nothing.\n");
            }
            printf("\n");
        }
        else if (strcmp(command, "health") == 0)
        {
            printf("Your current health is: %d/100.\n\n", playerHealth);
        }
        else if (strcmp(command, "go") == 0)
        {
            int moved = 0;
            if (playerLocation == ROOM_CELL)
            {
                if (strcmp(argument, "north") == 0)
                {
                    playerLocation = ROOM_HALLWAY;
                    moved = 1;
                }
            }
            else if (playerLocation == ROOM_HALLWAY)
            {
                if (strcmp(argument, "north") == 0)
                {
                    playerLocation = ROOM_GATE;
                    moved = 1;
                }
                else if (strcmp(argument, "south") == 0)
                {
                    playerLocation = ROOM_CELL;
                    moved = 1;
                }
                else if (strcmp(argument, "east") == 0)
                {
                    playerLocation = ROOM_STUDY;
                    moved = 1;
                }
                else if (strcmp(argument, "west") == 0)
                {
                    playerLocation = ROOM_ARMORY;
                    moved = 1;
                }
            }
            else if (playerLocation == ROOM_ARMORY)
            {
                if (strcmp(argument, "east") == 0)
                {
                    playerLocation = ROOM_HALLWAY;
                    moved = 1;
                }
            }
            else if (playerLocation == ROOM_STUDY)
            {
                if (strcmp(argument, "west") == 0)
                {
                    playerLocation = ROOM_HALLWAY;
                    moved = 1;
                }
            }
            else if (playerLocation == ROOM_CHAMBER)
            {
                if (strcmp(argument, "south") == 0)
                {
                    playerLocation = ROOM_HALLWAY;
                    moved = 1;
                }
            }
            else if (playerLocation == ROOM_GATE)
            {
                if (strcmp(argument, "south") == 0)
                {
                    playerLocation = ROOM_HALLWAY;
                    moved = 1;
                }
            }

            if (moved == 0)
            {
                printf("You can't go that way.\n\n");
            }
        }
        else if (strcmp(command, "take") == 0)
        {
            int itemTaken = 0;
            if (playerLocation == ROOM_CELL && strcmp(argument, "torch") == 0)
            {
                if (roomItems[ROOM_CELL][ITEM_TORCH] == 1)
                {
                    inventory[ITEM_TORCH] = 1;
                    roomItems[ROOM_CELL][ITEM_TORCH] = 0;
                    itemTaken = 1;
                    printf("You now have a torch. The darkness recedes.\n\n");
                }
            }
            else if (playerLocation == ROOM_ARMORY)
            {
                if (strcmp(argument, "sword") == 0 && roomItems[ROOM_ARMORY][ITEM_SWORD] == 1)
                {
                    inventory[ITEM_SWORD] = 1;
                    roomItems[ROOM_ARMORY][ITEM_SWORD] = 0;
                    itemTaken = 1;
                    printf("You take the short sword.\n\n");
                }
                else if (strcmp(argument, "shield") == 0 && roomItems[ROOM_ARMORY][ITEM_SHIELD] == 1)
                {
                    inventory[ITEM_SHIELD] = 1;
                    roomItems[ROOM_ARMORY][ITEM_SHIELD] = 0;
                    itemTaken = 1;
                    printf("You pick up the wooden shield.\n\n");
                }
            }
            else if (playerLocation == ROOM_STUDY && strcmp(argument, "potion") == 0)
            {
                if (roomItems[ROOM_STUDY][ITEM_POTION] == 1)
                {
                    inventory[ITEM_POTION] = 1;
                    roomItems[ROOM_STUDY][ITEM_POTION] = 0;
                    itemTaken = 1;
                    printf("You took the healing potion.\n\n");
                }
            }
            else if (playerLocation == ROOM_CHAMBER && strcmp(argument, "key") == 0)
            {
                if (roomItems[ROOM_CHAMBER][ITEM_KEY] == 1)
                {
                    inventory[ITEM_KEY] = 1;
                    roomItems[ROOM_CHAMBER][ITEM_KEY] = 0;
                    itemTaken = 1;
                    printf("You reach into the cold water and retrieve the ornate key.\n\n");
                }
            }

            if (itemTaken == 0)
            {
                printf("You can't take that.\n\n");
            }
        }
        else if (strcmp(command, "examine") == 0 || strcmp(command, "read") == 0)
        {
            if (playerLocation == ROOM_STUDY && strcmp(argument, "scroll") == 0)
            {
                printf("The scroll is old and brittle. It reads:\n");
                printf("  'I have cities, but no houses.\n");
                printf("   I have mountains, but no trees.\n");
                printf("   I have water, but no fish.\n");
                printf("   What am I?'\n\n");
                printf("Type 'answer [your_guess]' to solve.\n\n");
            }
            else
            {
                printf("There is nothing special to examine.\n\n");
            }
        }
        else if (strcmp(command, "answer") == 0)
        {
            if (playerLocation == ROOM_STUDY)
            {
                if (strcmp(argument, "map") == 0)
                {
                    if (puzzleSolved == 0)
                    {
                        puzzleSolved = 1;
                        roomItems[ROOM_CHAMBER][ITEM_KEY] = 1;
                        printf("Correct! As you speak the word, you hear a faint *plink* from a room to the north.\n\n");
                    }
                    else
                    {
                        printf("You have already solved this riddle.\n\n");
                    }
                }
                else
                {
                    printf("That is not the correct answer.\n\n");
                }
            }
            else
            {
                printf("There is nothing to answer here.\n\n");
            }
        }
        else if (strcmp(command, "use") == 0)
        {
            if (strcmp(argument, "potion") == 0)
            {
                if (inventory[ITEM_POTION] == 1)
                {
                    playerHealth = playerHealth + 50;
                    if (playerHealth > 100)
                    {
                        playerHealth = 100;
                    }
                    inventory[ITEM_POTION] = 0;
                    printf("You drink the potion. You feel a warm, healing sensation. Your health is now %d.\n\n", playerHealth);
                }
                else
                {
                    printf("You don't have a potion.\n\n");
                }
            }
            else if (strcmp(argument, "key") == 0)
            {
                if (inventory[ITEM_KEY] == 1)
                {
                    if (playerLocation == ROOM_GATE)
                    {
                        exitUnlocked = 1;
                        printf("You insert the ornate key into the massive lock. With a deafening *CRACK*, the tumblers turn and the gate is unlocked!\n\n");
                    }
                    else
                    {
                        printf("This is not the place to use the key.\n\n");
                    }
                }
                else
                {
                    printf("You don't have a key.\n\n");
                }
            }
            else
            {
                printf("You can't use that.\n\n");
            }
        }
        else
        {
            printf("I don't understand that command. Type 'help' for a list of commands.\n\n");
        }

        if (playerHealth <= 0)
        {
            gameIsActive = 0;
            hasPlayerWon = 0;
        }
        if (exitUnlocked == 1 && playerLocation == ROOM_GATE)
        {
            gameIsActive = 0;
            hasPlayerWon = 1;
        }
    }

    if (hasPlayerWon == 1)
    {
        printf("With a final, heroic push, the grand gate swings open, revealing a path to sunlight and freedom.\n");
        printf("You have escaped the Labyrinth of Lumina!\n");
        printf("CONGRATULATIONS!\n");
    }
    else
    {
        printf("\nYour vision fades to black...\n");
        printf("The labyrinth has claimed another soul.\n");
        printf("GAME OVER\n");
    }

    return 0;
}
