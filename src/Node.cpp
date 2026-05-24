#include "Node.h"
#include <vector>


namespace mdmodel 
{
    Node::Node(std::string_view name) : 
        m_name(name) 
    {
    }

    void Node::AddChild(NodePtr&& child) 
    {
        m_children.emplace(std::string(child->Name()), std::move(child));
    }

    NodeIter Node::Child(std::string_view name) 
    {
        return m_children.find(std::string(name));
    }

    std::string_view Node::Name() const 
    {
        return m_name;
    }

    std::string_view Node::Value() const 
    {
        std::string_view value;
        if (m_children.size() == 1)
        {
            value = m_children.begin()->second->Name();
        }

        return value;
    }

    std::vector<std::string_view> SplitPath(std::string_view path)
    {
        std::vector<std::string_view> path_parts;
        size_t start = 0;
        size_t end = path.find('/');
        while (end != std::string_view::npos)
        {
            if (end != start) // avoid empty parts
            {
                path_parts.push_back(path.substr(start, end - start));
            }
            start = end + 1;
            end = path.find('/', start);
        }

        if (start < path.size()) // add the last part        
        {
            path_parts.push_back(path.substr(start));
        }
        
        return path_parts;
    }

    // path is expected to be in the format of "/child1/child2/child3"
    NodeIter Node::Find(std::string_view path)
    {
        std::vector<std::string_view> path_parts = SplitPath(path);
        if (path_parts.empty())
        {
            return ChildrenEnd(); // invalid path
        }

        NodeIter it = Child(path_parts[0]);
        for (size_t i = 1; i < path_parts.size() && it != ChildrenEnd(); ++i)
        {
            it = it->second->Child(path_parts[i]);
        }

        return it;
    }
}