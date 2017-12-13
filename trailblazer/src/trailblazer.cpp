// elila090 and andpa149

#include <queue>
#include <iostream> //PURELY DEBUG

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
using namespace std;


// Recursively get path from Node
vector<Node *> getPathFromNode(Vertex*& currentNode, Vertex*& start)
{
    if (currentNode == start)
    {
        vector<Node *> path;
        path.push_back(start);
        return path;
    }
    else
    {
        vector<Node *> path = getPathFromNode(currentNode->previous, start);
        path.push_back(currentNode);
        return path;
    }
}


/* Recursive Depth-First-Search from $start to $end in $graph
 *
 * Builds the path as it goes, removes nodes to dead-ends and backs up
 * to last branch.
 */
bool recDepthFirstSearch(BasicGraph& graph, vector<Vertex*>& path, Vertex*& currentSquare, Vertex*& end)
{
    currentSquare->visited = true;
    currentSquare->setColor(GREEN);

    path.push_back(currentSquare);
    if ( currentSquare == end ) { return true; }
    // USE NODE ITERATOR
    for (Edge *edge : graph.getEdgeSet(currentSquare))
    {
        if ( !edge->finish->visited && recDepthFirstSearch(graph, path, edge->finish, end) )
            return true;
    }

    currentSquare->setColor(GRAY);
    path.pop_back();
    return false;
}

// Calls upon recDepthFirstSearch and returns it's results.
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    recDepthFirstSearch(graph, path, start, end);

    // Set node.visited=false for all nodes in the graph
    for (Node *node : graph.getNodeSet() )
    {
        node->resetData();
    }

    return path;
}



// Breadth-First-Search implementation

// Reverse order comparison struct for two Node pointers
struct DPSComp
{
public:
    DPSComp() { }
    bool operator() (const Node* lhs, const Node* rhs)
    {
        return lhs->cost > rhs->cost;
    }
};

//
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;

    priority_queue<Node *, vector<Node *>, DPSComp> prioritisedNodeList;
    start->visited = true;
    prioritisedNodeList.push(start);

    while( !prioritisedNodeList.empty() )
    {
        Node * currentNode = prioritisedNodeList.top();

        currentNode->setColor(GREEN);

        for ( Node *node : graph.getNeighbors(currentNode) )
        {
            if ( !node->visited)
            {
                node->cost = 1 + currentNode->cost;
                node->visited = true;
                node->previous = currentNode;

                if (node == end) // Found full path
                {
                    path = getPathFromNode(node, start);

                    for (Node *node : graph.getNodeSet() )
                    {
                        node->resetData();
                    }
                    return path;
                }

                node->setColor(YELLOW);
                prioritisedNodeList.push(node);
            }
        }

        prioritisedNodeList.pop();
    }

    for (Node *node : graph.getNodeSet() )
    {
        node->resetData();
    }
    return path;
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;

    PriorityQueue<Node *> prioritisedNodeList;
    start->visited = true;
    prioritisedNodeList.enqueue(start, 0);

    cout << "First node: " << start << endl;

    while( !prioritisedNodeList.isEmpty() )
    {
        Node * currentNode = prioritisedNodeList.dequeue();

        currentNode->setColor(GREEN);

        for ( Edge *edge : graph.getEdgeSet(currentNode) )
        {
            Node * nextNode = edge->finish;
            if ( !(nextNode)->visited)
            {
                nextNode->cost = edge->cost + currentNode->cost;
                nextNode->visited = true;
                nextNode->previous = currentNode;

                if (nextNode == end) // Found full path
                {
                    path = getPathFromNode(nextNode, start);

                    for (Node *node : graph.getNodeSet() )
                    {
                        node->resetData();
                    }
                    return path;
                }

                nextNode->setColor(YELLOW);
                prioritisedNodeList.enqueue(nextNode, nextNode->cost);
            }
        }
    }

    // Reset graph and return empty path
    for (Node *node : graph.getNodeSet() )
    {
        node->resetData();
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;

    PriorityQueue<Node *> prioritisedNodeList;
    start->visited = true;
    start->cost = 0;
    prioritisedNodeList.enqueue(start, 0);

    cout << "First node: " << start << endl;

    while( !prioritisedNodeList.isEmpty() )
    {
        Node * currentNode = prioritisedNodeList.dequeue();

        currentNode->setColor(GREEN);

        for ( Edge *edge : graph.getEdgeSet(currentNode) )
        {
            Node * nextNode = edge->finish;
            if ( !(nextNode)->visited)
            {
                double newCost = edge->cost + currentNode->cost;

                if (nextNode->cost == 0)
                {
                    nextNode->previous = currentNode;
                    nextNode->cost = edge->cost + currentNode->cost;
                    nextNode->setColor(YELLOW);
                    prioritisedNodeList.enqueue(nextNode, newCost);
                }
                else if (newCost < nextNode->cost)
                {
                    nextNode->previous = currentNode;
                    nextNode->cost = edge->cost + currentNode->cost;
                    nextNode->setColor(YELLOW);
                    prioritisedNodeList.changePriority(nextNode, newCost);
                }


                if (nextNode == end) // Found full path
                {
                    path = getPathFromNode(nextNode, start);

                    for (Node *node : graph.getNodeSet() )
                    {
                        node->resetData();
                    }
                    return path;
                }


            }
        }
    }

    // Reset graph and return empty path
    for (Node *node : graph.getNodeSet() )
    {
        node->resetData();
    }
    return path;
}
