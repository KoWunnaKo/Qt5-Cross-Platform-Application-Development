#include "gameinterface.h"

GameInterface::GameInterface(QObject *parent) : QObject(parent)
{
    // create our player
    _this_player = new Player();
    // Now we need to add our player to the list of players.
    // Our list of players has a type of `QVariantList`
    // So in order to add to this list, we have to create a new QVariant

    // QVariant is a templated class. This means that we need
    // to let the class know what our type is
    _players.append(QVariant::fromValue<Player*>(_this_player));
    // Note the syntax `QVariant::fromValue<Player*>`
    // We're letting the templated function `fromValue` know
    // That it'll be ingesting the type `Player*`
    // Which is a pointer to our player instance.
}

QVariantList GameInterface::create_viruses()
{
    QVariantList result;
    int number = 5;
    for(int i=0; i<number; i++)
        result.append(QVariant::fromValue<Virus*>(new Virus()));
    return result;
}


QVariantList GameInterface::create_food(int game_width, int game_height, int number=500)
{
    QVariantList result;
    for(int i=0; i<number; i++)
        result.append(QVariant::fromValue<Food*>(new Food(game_width, game_height)));
    return result;
}

// howto handle collisions
// https://www.reddit.com/r/gamedev/comments/6aqu5x/how_do_games_like_agario_handle_collisions/
void GameInterface::check_interactions()
{
    // For each Player QVariant in our QVariantList `_players`...
    for(QVariant player_variant : _players)
    {
        // cast each player variant into into a `Player` pointer
        Player *player = player_variant.value<Player*>();

        // Now iterate through every food variant
        for(QVariant food_variant : _food)
        {
            // cast the food variant into into a `Food` pointer
            Food *food = food_variant.value<Food*>();
            if (food->is_disabled())
                continue;
            player->handle_touch(food);
        }

        // Now iterate through every virus variant
        for (QVariant virus_variant: _viruses)
        {
            // cast the virius variant into into a `Virus` pointer
            Virus *virus = virus_variant.value<Virus*>();
            player->handle_touch(virus);
        }

        // Now iterate through every other player variant
        for (QVariant other_player_variant : _players)
        {
            // cast the other player variant into into a `Virus` pointer
            Player *other_player = other_player_variant.value<Player*>();
            if (player == other_player)
                continue;
            player->handle_touch(other_player);
        }
    }
}
