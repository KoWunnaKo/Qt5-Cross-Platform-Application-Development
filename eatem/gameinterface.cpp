#include "gameinterface.h"


GameInterface::GameInterface(QObject *parent)
    : QObject(parent)
    , _game_size(new QRect())
{
    // create our player
    _this_player = new Player(_game_size);
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

    emit update_this_player();

    connect(this, &GameInterface::create_game_objects, this, &GameInterface::slot_game_object_creation);
    _game_interval.setInterval(100);
    connect(&_game_interval, &QTimer::timeout, this, &GameInterface::increment_game_step);
    _game_interval.start();
}

void GameInterface::set_game_size(int width, int height)
{
    _game_size->setHeight(height);
    _game_size->setWidth(width);
    // FIXME: change naming
    slot_game_object_creation();
}

void GameInterface::create_viruses()
{
    int number = 5;
    for(int i=0; i<number; i++)
        _viruses.append(QVariant::fromValue<Virus*>(new Virus(_game_size)));
}

void GameInterface::slot_game_object_creation()
{
    create_food(1000);
    create_viruses();
    emit update_food();
    emit update_viruses();
}


void GameInterface::create_food(int number)
{
    for(int i=0; i<number; i++)
        _food.append(QVariant::fromValue<Food*>(new Food(_game_size)));
}

QVariantList GameInterface::get_food()
{
    return _food;
}

QVariantList GameInterface::get_viruses()
{
    return _viruses;
}

Player* GameInterface::get_this_player()
{
    return _this_player;
}

QVariantList GameInterface::get_players()
{
    return _players;
}

void GameInterface::increment_game_step()
{
    check_game_object_interactions();
}

// howto handle collisions
// https://www.reddit.com/r/gamedev/comments/6aqu5x/how_do_games_like_agario_handle_collisions/
void GameInterface::check_game_object_interactions()
{
    for (QVariant virus_variant : _viruses)
    {
        Virus *virus = virus_variant.value<Virus *>();
        for (QVariant food_variant : _food)
        {
            Food *food = food_variant.value<Food *>();
            // FIXME: need to actually clean up if players shoot food here
            // and below as well
            virus->handle_touch(food);
        }

    }
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

void GameInterface::set_game_height(int height)
{
    _game_size->setHeight(height);
}

void GameInterface::set_game_width(int width)
{
    _game_size->setWidth(width);
    // NOTE: Slight hack
    emit create_game_objects();
}
