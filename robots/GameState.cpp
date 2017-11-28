/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"

//DEBUG
#include <iostream>
using std::cout;
using std::endl;
//DEBUG



GameState::GameState(){}
GameState::~GameState()
{
    for (size_t i = 0; i < robots.size(); i++) {
        delete robots[i];
    }
}

GameState::GameState(int numberOfRobots) {
    for (unsigned int i = 0; i < numberOfRobots; i++) {
        Robot * robot;
        do
        {
            robot = new Robot();
        }
        while (!isEmpty (*robot));
        robots.push_back(robot);
        cout << "New R-n: " << i << endl;
    }
    teleportHero();
}

GameState::GameState( const GameState& other)
{
    hero = other.hero;
    for (size_t i = 0; i < other.robots.size(); i++) {
        this->robots[i] = new Robot(*other.robots[i]);
    }
}

GameState& GameState::operator =(const GameState& other)
{
    this->hero = other.hero;

    while ( !this->robots.empty() ) {
        delete this->robots[this->robots.size() - 1];
        this->robots.pop_back();
    }
    for (size_t i = 0; i < other.robots.size(); i++) {
        this->robots.push_back( new Robot(*other.robots[i]) );
    }
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); i++)
    {
        robots[i]->draw(scene);
    }
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;

    unsigned int i = 0;
    while (i < robots.size()) {
        bool noJunk = noJunkAt(*robots[i], i);
        bool collision = (countRobotsAt (*robots[i]) > 1);
        if (collision) {
            if (noJunk)
            {
                Unit * uTmp = robots[i];
                robots[i] = new Junk(*robots[i]);
                delete uTmp;
                numberDestroyed++;
                i++;
            }
            else
            {
                delete robots[i];
                robots[i] = robots[robots.size()-1];
                robots.pop_back();
                numberDestroyed++;
            }
        } else i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (size_t i = 0; i < robots.size(); i++)
    {
        if (!robots[i]->isJunk()) return true;
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (!robots[i]->isJunk())
        {
            if (robots[i]->attacks(unit) || robots[i]->at(unit)) return false;
        }
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}


bool GameState::noJunkAt(const Unit& unit, const int index)
{
    for (size_t i = 0; i < robots.size(); i++)
    {
        if (robots[i]->at(unit) && robots[i]->isJunk() && i != index)
        {
            return false;
        }
    }
    return true;
}


/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;

    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}



//DEBUG
int GameState::getSize() const
{
    return robots.size();
}
