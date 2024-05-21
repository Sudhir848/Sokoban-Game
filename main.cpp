/* Copyright [2023] <Sudhir Gunaseelan> */

#include <iostream>
#include "sokoban.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, const char* argv[]) {
    sf::Texture wall_texture, empty_texture, box_texture,
    storage_texture, player_texture, box_in_storage_texture;
    if (!wall_texture.loadFromFile("block_06.png") ||
        !box_texture.loadFromFile("crate_03.png") ||
        !empty_texture.loadFromFile("ground_01.png") ||
        !storage_texture.loadFromFile("ground_04.png") ||
        !player_texture.loadFromFile("player_05.png") ||
        !player_texture.loadFromFile("player_08.png") ||
        !player_texture.loadFromFile("player_17.png") ||
        !player_texture.loadFromFile("player_20.png")) {
        std::cout << "Error: could not load tile textures" << std::endl;
    }

    // Loading the level from a file
    std::string filename = argv[1];

    std::ifstream input(filename);
    if (!input) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    Sokoban game;
    input >> game;
    sf::RenderWindow window(sf::VideoMode(game.width *
    player_texture.getSize().x, game.height * player_texture.getSize().y),
    "Sokoban");
    bool flag = false;
    while (window.isOpen()) {
        // Creating the tile sprites
        std::vector<sf::Sprite> sprites;
        for (int y = 0; y < game.height; y++) {
            for (int x = 0; x < game.width; x++) {
                sf::Sprite sprite;
                switch (game.grid[game.index(x, y)]) {
                    case Sokoban::Wall:
                    sprite.setTexture(wall_texture);
                    break;

                    case Sokoban::Empty:
                    sprite.setTexture(empty_texture);
                    break;

                    case Sokoban::Box:
                    sprite.setTexture(box_texture);
                    break;

                    case Sokoban::Storage:
                    sprite.setTexture(storage_texture);
                    break;

                    case Sokoban::BoxInStorage:
                    sprite.setTexture(box_in_storage_texture);
                    break;

                    case Sokoban::Player:
                    sprite.setTexture(player_texture);
                    break;

                    default:
                    break;
                }
                sf::Sprite playerSprite(player_texture);
                sprite.setPosition(x * sprite.getLocalBounds().width,
                            y * sprite.getLocalBounds().height);
                sprites.push_back(sprite);
                player_texture.loadFromFile("player_05.png");
                playerSprite.setPosition((x + 0.5) * 64, (y + 0.5) * 64);
            }
        }
        sf::Event event;
        // Display a congratulatory message
        sf::Texture font;
        if (!font.loadFromFile("congrats.png")) {
            std::cout << "Error: could not load congratulatory "
                << "message" << std::endl;
        }
        sf::Sprite sprite1(font);
        sprite1.setPosition(60.f + 54.f, 64.f + 40.f);
        while (window.pollEvent(event)) {
            int dx = 0, dy = 0;
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Up) {
                    dy = -1;
                } else if (event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::Left) {
                    dx = -1;
                } else if (event.key.code == sf::Keyboard::S ||
                    event.key.code == sf::Keyboard::Down) {
                    dy = 1;
                } else if (event.key.code == sf::Keyboard::D ||
                    event.key.code == sf::Keyboard::Right) {
                    dx = 1;
                } else if (event.key.code == sf::Keyboard::R) {
                    // Reset the level
                    game = Sokoban(filename);
                }
            }

            // Move the player
            if (dx != 0 || dy != 0) {
                game.movePlayer(dx, dy);
                if (game.isWon()) {
                    // Disable player movement
                    dx = 0;
                    dy = 0;
                    flag = true;
                    if (event.key.code == sf::Keyboard::R) {
                        // Reset the level
                        game = Sokoban(filename);
                    }
                }
            }
        }
        // Draw the updated sprite
        window.clear();
        for (sf::Sprite sprite : sprites) {
            window.draw(sprite);
        }
        if (flag == true) {
            window.draw(sprite1);
        }
        window.display();
    }
    return 0;
}
