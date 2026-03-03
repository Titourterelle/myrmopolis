#include "ant.hpp"
#include "colony.hpp"
#include "environment/anthill_tile.hpp"
#include "environment/pheromones.hpp"
#include "environment/tile.hpp"
#include "environment/board.hpp"

#include <cstddef>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <vector>
#include <algorithm>

Ant::Ant(Colony &colony, Tile &spawn_tile) noexcept :
    colony(&colony),
    board(&colony.getBoard()),
    actual_tile(&spawn_tile),
    previous_tile(actual_tile)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return is_transporting_food;
}

void Ant::act() noexcept
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    Tile* next_tile = nullptr;

    std::vector<Tile*> adjacent_tiles = board->getAdjacentTiles(*actual_tile);

    if(isTransportingFood())
    {
        std::vector<AnthillTile*> nearby_anthills = searchAnthills(adjacent_tiles);
        if(!nearby_anthills.empty())
        {
            std::uniform_int_distribution<size_t> uni_dist(0, nearby_anthills.size() - 1);
            next_tile = nearby_anthills.at(uni_dist(gen));
            std::cout << "&" << std::endl;
        }
        else
        {
            removeTile(adjacent_tiles, *actual_tile);
            sortTilesByPheromones(adjacent_tiles, PheromoneType::Home);
            next_tile = adjacent_tiles[0];
            std::cout << "&&" << std::endl;
        }
    }
    else
    {
        removeTile(adjacent_tiles, *previous_tile);
        sortTilesByPheromones(adjacent_tiles, PheromoneType::Food);
        
        std::geometric_distribution<> geo_dist(pheromone_sensitivity);
        int index = geo_dist(gen);
        if(index >= adjacent_tiles.size())
        {
            std::uniform_int_distribution<size_t> uni_dist(0, adjacent_tiles.size() - 1);
            index = uni_dist(gen);
        }

        next_tile = adjacent_tiles.at(index);
        std::cout << "@" << std::endl;
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
    previous_tile = actual_tile;
    actual_tile = &next_tile;
}

const std::vector<AnthillTile*> Ant::searchAnthills(const std::vector<Tile*> &tiles_list) const noexcept
{
    std::vector<AnthillTile*> anthills_found;

    std::map<const Tile::Coordinates*, AnthillTile*> coordinates_anthills;
    for(const auto& anthill : colony->getAnthills())
    {
        coordinates_anthills[&anthill->getCoordinates()] = anthill;
    }
    
    for(const auto& tile : tiles_list)
    {
        if(coordinates_anthills.contains(&tile->getCoordinates()))
        {
            anthills_found.push_back(coordinates_anthills.at(&tile->getCoordinates()));
        }
    }

    return anthills_found;
}

void Ant::sortTilesByPheromones(std::vector<Tile*> &tiles_list, const PheromoneType pheromone) const noexcept
{
    std::sort(tiles_list.begin(), tiles_list.end(),
        [&pheromone](const Tile *left_tile, const Tile *right_tile)
        {
            if(pheromone == PheromoneType::Home) {return (left_tile->getPheromones().home > right_tile->getPheromones().home);}
            else if(pheromone == PheromoneType::Food) {return (left_tile->getPheromones().food > right_tile->getPheromones().food);}
            else {return true;}
        }
    );
}

void Ant::removeTile(std::vector<Tile*> &tiles_list, const Tile &tile_to_remove) const noexcept
{
    for(auto i = 0; i < tiles_list.size(); ++i)
    {
        if(*tiles_list.at(i) == tile_to_remove)
        {
            tiles_list.erase(tiles_list.begin() + i);
        }
    }
}
