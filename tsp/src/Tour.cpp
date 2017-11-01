// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <math.h>
#include "Tour.h"
#include "Node.h"
#include "Point.h"


Tour::Tour()
{
    front = nullptr;
    numberPoints = 0;
}

Tour::Tour(Point a, Point b, Point c, Point d)
{
    front = new Node(a, nullptr);
    Node * tmp = new Node(d, front);

    Node * tmpNodePointer = tmp;
    tmp = new Node(c, tmpNodePointer);

    tmpNodePointer = tmp;
    tmp = new Node(b, tmpNodePointer);
    front->next = tmp;

    numberPoints = 4;
}

Tour::~Tour()
{
    if (0 < numberPoints)
    {
        Node * it = front->next;
        Node * nextNode;
        while (it != front)
        {
            nextNode = it->next;

            delete it;

            it = nextNode;
        }
        delete front;
    }
}

void Tour::show()
{
    Node * it = front->next;
    cout << "(" << front->point.x << ", " << front->point.y << ")" << endl;
    while (it != front && 1 < numberPoints)
    {
        cout << "(" << it->point.x << ", " << it->point.y << ")" << endl;
        it = it->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    Node * it = front->next;
    front->point.draw(scene);
    while (it != front && 1 < numberPoints)
    {
        it->point.draw(scene);
        it = it->next;
    }
}

int Tour::size()
{
    return numberPoints;
}

double Tour::distance()
{
    double distance = 0;
    Node * it = front->next;

    int i = 0;
    while (it != front)
    {
        distance += (it->point).distanceTo(((it->next)->point));
        it = it->next;
        i++;
    }
    distance += it->point.distanceTo(it->next->point);

    return distance;
}

void Tour::insertNearest(Point p)
{
    if (1 < numberPoints)
    {
        Node * it = front->next;
        Node * nearest = front;
        double rainbow = p.distanceTo(front->next->point);

        while (it != front)
        {
            if (p.distanceTo(it->next->point) < rainbow )
            {
                nearest = it;
                rainbow = p.distanceTo(it->next->point);
            }
            it = it->next;
        }
        if (p.distanceTo(it->next->point) < rainbow )
        {
            nearest = it;
            rainbow = p.distanceTo(it->next->point);
        }

        Node * addedNode = new Node(p, nearest->next);
        nearest->next = addedNode;
    }
    else if (numberPoints == 1)
    {
        Node * addedNode = new Node(p, front);
        front->next = addedNode;
    }
    else
    {
        front = new Node(p, nullptr);
    }
    numberPoints++;
}

void Tour::insertSmallest(Point p)
{
    if (1 < numberPoints)
    {
        Node * it = front->next;
        Node * nearest = front;
        double shortestDistance = p.distanceTo(front->point) + p.distanceTo(front->next->point) - (front->point).distanceTo(front->next->point);
        double curDist;

        while (it != front)
        {
            curDist = p.distanceTo(it->point) + p.distanceTo(it->next->point)  - (it->point).distanceTo(it->next->point);
            if (curDist < shortestDistance)
            {
                nearest = it;
                shortestDistance = curDist;
            }
            it = it->next;
        }

        curDist = p.distanceTo(it->point) + p.distanceTo(it->next->point)  - (it->point).distanceTo(it->next->point);
        if (curDist < shortestDistance)
        {
            nearest = it;
            shortestDistance = curDist;
        }


        Node * addedNode = new Node(p, nearest->next);
        nearest->next = addedNode;

    }
    else if (numberPoints == 1)
    {
        Node * addedNode = new Node(p, front);
        front->next = addedNode;
    }
    else
    {
        front = new Node(p, front);
    }
    numberPoints++;
}
