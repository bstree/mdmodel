#pragma once
#include <string>
#include <memory>
#include <unordered_map>

namespace mdmodel 
{
    class Node;
    using NodePtr = std::unique_ptr<Node>;
    using NodeIter = std::unordered_map<std::string, NodePtr>::iterator;

    class Node 
    {
    public:
        Node(std::string_view name);
        ~Node() = default;

        void AddChild(NodePtr&& child);
        NodeIter Child(std::string_view name);

        NodeIter Find(std::string_view path);
        NodeIter ChildrenBegin() { return m_children.begin(); }
        NodeIter ChildrenEnd() { return m_children.end(); }

        std::string_view Name() const;
        std::string_view Value() const;

    private:
        std::string_view m_name;
        std::unordered_map<std::string, NodePtr> m_children;
    };
}