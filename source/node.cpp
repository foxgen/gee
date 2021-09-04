#include "node.h"
#include <iostream>

namespace gee {

Node& Node::Add(const Node& node)
{
    return *this;
}

Node& Node::AddChild(const Node& node)
{
    m_child.push_back(node);

    return *this;
}

void Node::PrintNode()
{
    std::cout << m_value ;
}

int Calculate(Node& node)
{
    if (node.m_child.size() == 0)
        return node.m_value;

    int best = node.m_child[0].m_value;

    for (auto n : node.m_child)
    {
        int v = Calculate(n);
        if (v > best)
            best = v;        
    }

    node.m_value = best;
    return best;
}

Node& GetBestNode(Node& node)
{
    Node& best = node.m_child[0];

    for (auto n : node.m_child)
    {
        int v = Calculate(n);
        if (v > best.m_value)
            best = n;     
    }

    return best;
}

void Node::PrintTree()
{
    std::cout << "[";
    
    std::cout << "(" << m_value << ")";
    for (auto n = m_child.begin(); n != m_child.end(); n++)
    {
        n->PrintTree();

        if (m_child.end() != n+1)
            std::cout << ",";
    }

    std::cout << "]";
}

} // gee