sfml-app : main.o Score.o Menu.o Game.o
	g++ main.o Score.o Menu.o Game.o -o sfml-app -L /home/pierre/SFML/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o : main.cpp Score.cpp Menu.cpp  Game.cpp
	g++ -c main.cpp Score.cpp Menu.cpp  Game.cpp -I /home/pierre/SFML/include

clean :
	rm sfml-app *.o
