/* Copyright [2023] <Sudhir Gunaseelan> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "sokoban.hpp"
#include <SFML/Graphics.hpp>

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream level_file(filename);

    if (!level_file) {
        std::cout << "Error: could not open level file "
            << filename << std::endl;
        return;
    }

    level_file >> width >> height;
    grid.resize(width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char cell;
            level_file >> cell;

            switch (cell) {
                case '.':
                grid[index(x, y)] = Empty;
                break;

                case 'A':
                grid[index(x, y)] = Box;
                break;

                case '#':
                grid[index(x, y)] = Wall;
                break;

                case 'a':
                grid[index(x, y)] = Storage;
                break;

                case '1':
                grid[index(x, y)] = BoxInStorage;
                break;

                case '@':
                player_position = { x, y };
                grid[index(x, y)] = Player;
                break;

                default:
                std::cout << "Error: invalid cell character "
                    << cell << std::endl;
                break;
            }
        }
    }

    // Creating the tile sprites
    wall_sprite.setTexture(wall_texture);
    empty_sprite.setTexture(empty_texture);
    box_sprite.setTexture(box_texture);
    storage_sprite.setTexture(storage_texture);
    player_sprite.setTexture(player_texture);
    player_sprite.setOrigin(32, 32);
    player_sprite.setPosition((player_position.x + 0.5f) * 64,
    (player_position.y + 0.5f) * 64);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Set the texture and sprite to the empty texture and sprite
    sf::Sprite sprite(empty_sprite);

    // Draw each tile in the grid
    std::for_each(grid.begin(), grid.end(), [this, &target, &sprite, &states](const Cell& cell) {
        switch (cell) {
            case Wall:
                sprite.setTexture(wall_texture);
                break;

            case Box:
                sprite.setTexture(box_texture);
                break;

            case Storage:
                sprite.setTexture(storage_texture);
                break;

            case BoxInStorage:
                sprite.setTexture(box_texture);
                break;

            case Player:
                sprite.setTexture(player_texture);
                break;

            default:
                break;
        }

        // Get the x and y coordinates of the current cell
        int index = &cell - &grid[0];
        int x = index % width;
        int y = index / width;

        sprite.setPosition(position + sf::Vector2f(x * 64, y * 64));
        target.draw(sprite, states);
    });
}


void Sokoban::movePlayer(int x, int y) {
    int new_player_x = player_position.x + x;
    int new_player_y = player_position.y + y;
    int new_box_x = new_player_x + x;
    int new_box_y = new_player_y + y;
    int player_index = index(player_position.x, player_position.y);
    int new_player_index = index(new_player_x, new_player_y);
    int new_box_index = index(new_box_x, new_box_y);

    // Player is moving outside the play area
    if (new_player_x < 0 || new_player_x >= width ||
        new_player_y < 0 || new_player_y >= height) {
        return;
    }

    // Player is trying to move into a wall
    if (grid[new_player_index] == Wall) {
        return;
    }

    // Player is trying to move into a box
    if (grid[new_player_index] == Box) {
        if (new_box_x < 0 || new_box_x >= width ||
            new_box_y < 0 || new_box_y >= height) {
            // Box is moving outside the play area
            return;
        }

        if (grid[new_box_index] == Wall || grid[new_box_index] == Box) {
            // Box is moving into a wall or another box
            return;
        }

        // Move the box
        grid[new_box_index] = Box;
        grid[new_player_index] = Player;
        grid[player_index] = Empty;
        player_position = { new_player_x, new_player_y };
    } else {
        // Move the player
        grid[new_player_index] = Player;
        grid[player_index] = Empty;
        player_position = { new_player_x, new_player_y };
    }
}

bool Sokoban::isWon() const {
    int numbox = 0;
    int numbox_storage = storage_array.size();

    int storage_area = 0;
    uint64_t size = grid.size();
    int s = size;
    for (int i = 0; i < s; i++) {
        if (grid[i] == Box) {
            numbox++;
            for (int j = 0; j < numbox_storage; j++) {
                if (i == storage_array[j]) {
                    storage_area++;
                }
            }
        }
    }
    if (numbox == numbox_storage && numbox == storage_area) {
        return true;
    } else {
        return false;
    }
}

std::istream& operator>>(std::istream& in, Sokoban& sokoban) {
    in >> sokoban.width >> sokoban.height;

    sokoban.grid.resize(sokoban.width * sokoban.height);

    for (int y = 0; y < sokoban.height; y++) {
        for (int x = 0; x < sokoban.width; x++) {
            char cell;
            in >> cell;
            switch (cell) {
                case '@':
                sokoban.player_position = { x, y };
                sokoban.grid[sokoban.index(x, y)] = Sokoban::Player;
                break;

                case '.':
                sokoban.grid[sokoban.index(x, y)] = Sokoban::Empty;
                break;

                case 'A':
                sokoban.grid[sokoban.index(x, y)] = Sokoban::Box;
                break;

                case '#':
                sokoban.grid[sokoban.index(x, y)] = Sokoban::Wall;
                break;

                case 'a':
                sokoban.grid[sokoban.index(x, y)] = Sokoban::Storage;
                sokoban.storage_array.push_back(sokoban.index(x, y));
                break;

                case '1':
                sokoban.grid[sokoban.index(x, y)] = Sokoban::BoxInStorage;
                break;

                default:
                std::cout << "Error: invalid cell character " << cell
                << std::endl;
                break;
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& sokoban) {
    out << sokoban.width << " " << sokoban.height << "\n";
    return out;
}

int Sokoban::index(int x, int y) const {
       return x + y * width;
}
