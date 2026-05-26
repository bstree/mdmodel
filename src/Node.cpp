#include "mdmodel/Node.h"
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

    Node* Node::Child(std::string_view name) const
    {
        Node* child = nullptr;
        auto it = m_children.find(std::string(name));
        if (it != m_children.end())
        {
            child = it->second.get();
        }
        return child;
    }

    std::string_view Node::Name() const 
    {
        return m_name;
    }

    std::optional<std::string> Node::StringValue() const 
    {
        if (m_children.size() == 1)
        {
            return std::string(m_children.begin()->second->Name());
        }

        return std::nullopt;
    }


    std::optional<int> Node::IntValue() const
    {
        std::optional<int> value;
        if (m_children.size() == 1)
        {
            try 
            {
                value = std::stoi(std::string(m_children.begin()->second->Name()));
            }
            catch (const std::exception&)
            {
                // Not a valid integer, return empty optional
            }
        }

        return value;
    }

    std::optional<bool> Node::BoolValue() const
    {
        std::optional<bool> value;
        if (m_children.size() == 1)
        {
            std::string_view str_value = m_children.begin()->second->Name();
            if (str_value == "true")
            {
                value = true;
            }
            else if (str_value == "false")
            {
                value = false;
            }
        }

        return value;
    }

    std::optional<double> Node::DoubleValue() const
    {
        std::optional<double> value;
        if (m_children.size() == 1)
        {
            try 
            {
                value = std::stod(std::string(m_children.begin()->second->Name()));
            }
            catch (const std::exception&)
            {
                // Not a valid double, return empty optional
            }
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
    Node* Node::Find(std::string_view path) const
    {
        std::vector<std::string_view> path_parts = SplitPath(path);
        if (path_parts.empty())
        {
            return nullptr; // invalid path
        }

        // Start traversal from this node, then descend through each path part.
        Node* node = const_cast<Node*>(this);
        for (const auto& part : path_parts)
        {
            if (!node)
            {
                return nullptr; // path not found
            }
            node = node->Child(part);
        }

        return node;
    }

    void Node::ForEach(std::function<void(Node&)> function)
    {
        for (auto& pair : m_children)
        {
            function(*pair.second);
        }
    }
}