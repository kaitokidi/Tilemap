/************************************TILEMAP********************************/

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>

int main(){

    std::ifstream mapFile("Map.txt");

    sf::Texture tileTexture;
    sf::Sprite tile;

    sf::Vector2i map[100][100];
    sf::Vector2i source;
    source.x = 0;
    source.y = 0;

    std::string str;
    int spritew, spriteh;
    int width, heigth;

    if(mapFile.is_open()){

        std::string tileset;
        mapFile >> tileset;
        if(!tileTexture.loadFromFile(tileset)){
            std::cout << "failed on loading tileset" << std::endl;
        }
        tile.setTexture(tileTexture);

        //Sprite size
        mapFile >> str;
        spritew = atoi(str.c_str());
        mapFile >> str;
        spriteh = atoi(str.c_str());

        //Map size
        mapFile >> str;
        width = str[0] - '0';
        mapFile >> str;
        heigth = str[0] - '0';

        while(!mapFile.eof()){
            mapFile >> str;
//              std::cout << " -> " << str << std::endl;
            char x = str[0]; char y = str[2];
            if(x == 'n' || y == 'n')
                map[source.x][source.y] = sf::Vector2i(-1,-1);
            else{
                map[source.x][source.y] = sf::Vector2i(x - '0', y - '0');
//                std::cout << source.x << " " << source.y << " -> " << x - '0' << "." << y - '0' << std::endl;
            }

            if(mapFile.peek() == '\n'){
                source.x = 0;
                ++source.y;
            }
            else
                ++source.x;
        }
    }
   std::cout << width*spritew << std::endl;
    sf::RenderWindow window(sf::VideoMode(width*spritew+1,heigth*spriteh+1), "title");

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color(250,250,250));
        for(int i = 0; i < width; ++i){
            for(int j = 0; j < heigth; ++j){
                tile.setPosition(i*spritew, j*spriteh);
                tile.setTextureRect(sf::IntRect(map[i][j].x*spritew,
                    map[i][j].y*spriteh,spritew,spriteh));

                window.draw(tile);
            }
        }

        window.display();
    }

}

/*
g++ -c tileMap.cpp
g++ -o tilemap tileMap.o -lsfml-graphics -lsfml-window -lsfml-system
 */

