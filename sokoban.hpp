/* Copyright [2023] <Sudhir Gunaseelan> */

#ifndef _HOME_VBOXUSER_PS2B_SOKOBAN_HPP_
#define _HOME_VBOXUSER_PS2B_SOKOBAN_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


class Sokoban : public sf::Drawable {
 public:
    int width, height;
    enum Cell {
        Wall,
        Empty,
        Box,
        Storage,
        BoxInStorage,
        Player
    };
    std::vector<Cell> grid;
    Sokoban() : width(0), height(0), player_position({0, 0}) {}
    explicit Sokoban(const std::string& filename);
    void movePlayer(int x, int y);
    bool isWon() const;
    int index(int x, int y) const;
     std::vector<int> storage_array;
    friend std::istream& operator>>(std::istream& in, Sokoban& sokoban);
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& sokoban);

 private:
    sf::Vector2f position;
    sf::Texture texture;
    sf::Vector2i player_position;
    sf::Texture wall_texture, empty_texture, box_texture,
    storage_texture, player_texture;
    sf::Sprite wall_sprite, empty_sprite, box_sprite,
    storage_sprite, player_sprite;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif  // _HOME_VBOXUSER_PS2B_SOKOBAN_HPP_
