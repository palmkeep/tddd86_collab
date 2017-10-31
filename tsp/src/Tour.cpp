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
/*
Tour::Tour()
{
    // TODO: write this member
}
*/
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
    // TODO: write this member
}

void Tour::show()
{
    Node * it = front->next;
    cout << "(" << front->point.x << ", " << front->point.y << ")" << endl;
    while (it != front)
    {
        cout << "(" << it->point.x << ", " << it->point.y << ")" << endl;
        it = it->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    Node * it = front->next;
    front->point.draw(scene);
    while (it != front)
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
    cout << 1 << endl;
    distance += it->point.distanceTo(it->next->point);

    return distance;
}

void Tour::insertNearest(Point p)
{
    Node * it = front->next;
    Node * nearest = front;
    double rainbow = p.distanceTo(front->next->point);

    while (it != front)
    {
        cout << it->point.toString() << endl;
        if (p.distanceTo(it->next->point) < rainbow )
        {
            cout << 0 << endl;
            nearest = it;
            rainbow = p.distanceTo(it->next->point);
        }

        it = it->next;
    }
    cout << it->point.toString() << endl;
    if (p.distanceTo(it->next->point) < rainbow )
    {
        nearest = it;
        rainbow = p.distanceTo(it->next->point);
    }

    Node addedNode(p,it->next);
    nearest->next = &addedNode;
    cout << "N: " << nearest->point.toString() << endl;
    cout << nearest->next->point.toString() << endl;
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
