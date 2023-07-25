CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all:starwars.out

starwars.out: main.o rsdl.o Bullet.o Player.o Game_Characters.o Enemy.o Moving_Enemy.o Hostage.o Game.o Power_Up.o
	$(CC) main.o rsdl.o Bullet.o Player.o Game_Characters.o Enemy.o Moving_Enemy.o Hostage.o Game.o Power_Up.o $(CCFLAGS) -o starwars.out

main.o: rsdl.hpp main.cpp Bullet.hpp Player.hpp Game_Characters.hpp Enemy.hpp Moving_Enemy.hpp Hostage.hpp Game.hpp Power_Up.hpp
	$(CC) -c main.cpp -o main.o

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

Bullet.o: rsdl.hpp Bullet.hpp Bullet.cpp
	$(CC) -c Bullet.cpp -o Bullet.o

Player.o: rsdl.hpp Game_Characters.hpp Player.hpp Player.cpp Bullet.hpp Power_Up.hpp
	$(CC) -c Player.cpp -o Player.o

Game_Characters.o: rsdl.hpp Bullet.hpp Game_Characters.hpp Game_Characters.cpp
	$(CC) -c Game_Characters.cpp -o Game_Characters.o

Enemy.o: rsdl.hpp Game_Characters.hpp Enemy.hpp Enemy.cpp Bullet.hpp
	$(CC) -c Enemy.cpp -o Enemy.o

Moving_Enemy.o: rsdl.hpp Game_Characters.hpp Enemy.hpp Moving_Enemy.hpp Moving_Enemy.cpp Bullet.hpp
	$(CC) -c Moving_Enemy.cpp -o Moving_Enemy.o

Hostage.o: rsdl.hpp Game_Characters.hpp Hostage.hpp Hostage.cpp
	$(CC) -c Hostage.cpp -o Hostage.o

Game.o: rsdl.hpp Game.cpp Game.hpp Bullet.hpp Player.hpp Game_Characters.hpp Enemy.hpp Moving_Enemy.hpp Hostage.hpp
	$(CC) -c Game.cpp -o Game.o

Power_Up.o: rsdl.hpp Power_Up.hpp Power_Up.cpp
	$(CC) -c Power_Up.cpp -o Power_Up.o



.PHONY: clean
clean:
	rm  *.o starwars.out
