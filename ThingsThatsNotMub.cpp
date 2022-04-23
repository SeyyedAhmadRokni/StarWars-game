#include <bits/stdc++.h>
#include <StarWars.hpp>
#include "Classes.cpp"

Arrow::Arrow(int x, int y, int damage = 100, int rate = 6):
    Box(x, y, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate){
    this->damage = damage;
}
Arrow::Arrow(Point p, int damage = 100, int rate = 6):
    Box(p, FIRE_WIDHT, FIRE_HEIGHT, 
        imageAddress, rate){
    this->damage = damage;
}
void Arrow::draw(Window* window){
    window->draw_img(imageAddress,
        Rectangle(x, y, width, height));
}
