#pragma once
#include "Node.h"
#include <queue>
#include <memory>

struct cmark_node;

namespace mdmodel
{
    class Parser
    {
    public:
        NodePtr Parse(const std::string& markdown);

    private:
        void Parse();
        //void Parse(cmark_node* native, Node& parent);
        NodePtr ParseHeaderNode(cmark_node* node);

    private:
        std::queue<std::pair<cmark_node*, Node&>> m_parseQueue;
    };
}