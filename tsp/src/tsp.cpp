/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Tour.h"

int main(int argc, char *argv[]) {
    QApplication abc(argc, argv);

    string filename = "tsp10.txt";
    ifstream input;
    input.open(filename);

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    // run insertion heuristic
    /*
    Tour tour;
    double x;
    double y;
    while (input >> x >> y) {
        Point p(x, y);
        tour.insertNearest(p);
        //uncomment the 4 lines below to animate
        //tour.draw(scene);
        //std::chrono::milliseconds dura(50);
        //std::this_thread::sleep_for(dura);
        //a.processEvents();
    }
    input.close();
    */

    /*
    Point p(100.0, 100.0);
    Point q(500.0, 100.0);
    Point r(500.0, 500.0);
    Point s(100.0, 500.0);
    Tour tour(p,q,r,s);
    Point o(500.0, 300.0);
    */
    Tour tour;
    Point a(110.0, 225.0);
    Point b(161.0, 280.0);
    Point c(325.0, 554.0);
    Point d(490.0, 284.0);
    Point e(157.0, 443.0);
    Point f(283.0, 379.0);
    Point g(397.0, 566.0);
    Point h(306.0, 360.0);
    Point i(343.0, 110.0);
    Point j(552.0, 199.0);
    tour.insertSmallest(a);
    tour.insertSmallest(b);
    tour.insertSmallest(c);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(d);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(e);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(f);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(g);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(h);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(i);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.insertSmallest(j);
    cout << "dist: " << tour.distance() << endl;
    tour.show();
    tour.draw(scene);
    std::chrono::milliseconds dura(50);
    std::this_thread::sleep_for(dura);
    abc.processEvents();


    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    cout << "Number of points: " << tour.size() << endl;

    tour.show();

    // draw tour
    tour.draw(scene);
    return abc.exec(); // start Qt event loop
}
