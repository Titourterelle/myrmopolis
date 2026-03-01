#include "ant.hpp"
#include "colony.hpp"
#include "environment/tile.hpp"
#include "environment/board.hpp"

#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

Ant::Ant(Colony &colony, Tile &spawn_tile) noexcept :
    colony(&colony),
    board(&colony.getBoard()),
    actual_tile(&spawn_tile)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return is_transporting_food;
}

void Ant::act() noexcept
{
    Tile* next_tile = nullptr;

    const std::vector<Tile*> adjacent_tiles = board->getAdjacentTiles(*actual_tile);

    if(isTransportingFood())
    {
        std::set<const Tile::Coordinates*> anthills_coordinates;
        for(const auto& anthill : colony->getAnthills())
        {
            anthills_coordinates.insert(&anthill->getCoordinates());
        }

        std::map<int, Tile*> pheromones_on_tiles;
        for(const auto& tile : adjacent_tiles)
        {
            if(anthills_coordinates.contains(&tile->getCoordinates()))
            {
                next_tile = tile;
                break;
            }
            else
            {
                pheromones_on_tiles[tile->getPheromones().home] = tile;
            }
        }
        if(!next_tile)
        {
            next_tile = pheromones_on_tiles.rbegin()->second;
        }
    }
    else
    {
        std::map<int, Tile*> pheromones_on_tiles;
        for(const auto& tile : adjacent_tiles)
        {
            pheromones_on_tiles[tile->getPheromones().food] = tile;
        }
        next_tile = pheromones_on_tiles.rbegin()->second;
    }

    move(*next_tile);
    actual_tile->interact(*this);

    std::cout << "La fourmi se deplace vers la tuile de coordonnées " << actual_tile->getCoordinates().x << "|" << actual_tile->getCoordinates().y << std::endl;
}

void Ant::pickFood()
{
    if(isTransportingFood())
    {
        throw std::runtime_error("The ant is already transporting food");
    }

    is_transporting_food = true;
}

void Ant::dropFood() noexcept
{
    is_transporting_food = false;
}


void Ant::move(Tile &next_tile) noexcept
{
    actual_tile = &next_tile;
}