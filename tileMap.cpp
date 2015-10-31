/**************************************TILEMAP********************************/
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>

int main(){

    //WITH THIS WE ASSOCIATE THE FILE Map.txt TO mapFile
    std::ifstream mapFile("Map.txt");

    sf::Texture tileMapTexture;
    sf::Sprite tile;

    std::vector < std::vector < sf::Vector2i> > map;
    sf::Vector2i source(0,0);

    std::string str;
    int spritew, spriteh;
    int sourceTailWidth, sourceTailHeigh;
    int qttyCol, qttyRow;

    //WITH THIS WE OPPEN THE FILE AND IF SUCCEEDS CONTINUE
    if(mapFile.is_open()){

        std::string tileMapImageName;
        //THE OPERATOR   ">>"   MEANS PUT THE NEXT STRING ON THE mapFile ON THE STRING NEXT TO IT (in  this case tileMapImageName)
        mapFile >> tileMapImageName;
        if(!tileMapTexture.loadFromFile(tileMapImageName)){
            std::cout << "failed on loading tileset" << std::endl;
        }
        tile.setTexture(tileMapTexture);

        //Sprite size
        mapFile >> str;
        //.c_str() converts a C++ string to a C string
        //I did it to aply atoi on it which is a C function that converts strings to integers
        sourceTailWidth = atoi(str.c_str());
        mapFile >> str;
        sourceTailHeigh = atoi(str.c_str());

        //ARBITRARY VALUES (the values we want our tiles to have on the screen)
	    spritew = 64;	    spriteh = 64;
	
        //Map size
        //WITH THIS IMPLEMENTATION YOU CAN ONLY USE MAPS WITH A MAXIMUM SIZE OF 9X9
        //a better implementation would take the first characters of the string str before the ','
        //and the characters after it and use the function .c_str() and atoi like we did  above
        mapFile >> str;
        qttyCol = str[0] - '0';
        mapFile >> str;
        qttyRow = str[0] - '0';
                
        //initialization of the map definig the size so we can set values
        map = std::vector < std::vector < sf::Vector2i> > (qttyRow, std::vector < sf::Vector2i> (qttyCol));

	//THIS MEAND WHILE THERE ARE STRINGS TO READ ON THE mapFile (eof -> end of file)
        while(!mapFile.eof()){
            mapFile >> str;
            //again we are working with 9x9 as the maximum number of different tiles
            char x = str[0]; char y = str[2];
            if(x == 'n' || y == 'n')
                map[source.x][source.y] = sf::Vector2i(-1,-1);
            else{
                map[source.x][source.y] = sf::Vector2i(x - '0', y - '0');
            }
	//IF THE NEXT CHAR OF THE mapFile IS A \n (return)
            if(mapFile.peek() == '\n'){
                source.x = 0;
                ++source.y;
            }
            else
                ++source.x;
        }
    }
    else {
        std::cout << "Can't Open the file" << std::endl;
    }
    
    sf::RenderWindow window(sf::VideoMode(qttyCol*spritew,qttyRow*spriteh), "tilemap <0(O:");

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
	
        for(int i = 0; i < qttyCol; ++i){
            for(int j = 0; j < qttyRow; ++j){
            	if(map[i][j].x != -1 && map[i][j].y != -1) {
	                tile.setPosition(i*spritew, j*spriteh);
	                tile.setTextureRect(sf::IntRect(map[i][j].x*sourceTailWidth, map[i][j].y*sourceTailHeigh,sourceTailWidth,sourceTailHeigh);
	                tile.setScale(spritew/sourceTailWidth,spriteh/sourceTailHeigh);
	        	window.draw(tile);
            	}
            }
        }
        window.display();	
    }

}

/*
g++ -c tileMap.cpp
g++ -o tilemap tileMap.o -lsfml-graphics -lsfml-window -lsfml-system
./tilemap
 */
