run:
	g++ Enemy.cpp Bullet.cpp main.cpp -lsfml-graphics -lsfml-system -lsfml-window  -o SpaceInvaders
	./SpaceInvaders