/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */


#include "Junk.h"
#include "constants.h"

Junk::Junk() : Robot() {}
Junk::Junk(const Unit& u) : Robot(u) {}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Unit& u){}

bool Junk::attacks(const Unit& u) const{}

bool Junk::isJunk() const {return true;}
