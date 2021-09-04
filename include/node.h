#pragma once
#include <vector>
#include <memory>
#include "util.h"

namespace gee {

class Node
{
public:
    int m_value;
    int m_id;
    int m_index;
public:
    Node(int id, int v) : m_id(id), m_value(v) {};       

    std::vector<Node> m_child;
    std::weak_ptr<Node> m_parent;

    Node& AddChild(const Node& node);
    Node& Add(const Node& node);
    
    int Calculate()
    {
        m_value = 50 - getRandomNumber(0,100);

        return m_value;
    };

    void PrintTree();
    void PrintNode();
};

Node& GetBestNode(Node& node);

} // gee