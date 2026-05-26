#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>

namespace mdmodel 
{
    class Node;
    using NodePtr = std::unique_ptr<Node>;

    class Node 
    {
    public:
        Node(std::string_view name);
        virtual ~Node() = default;

        void AddChild(NodePtr&& child);
        Node* Child(std::string_view name) const;
        Node* Find(std::string_view path) const;
        void ForEach(std::function<void(Node&)> function);

        std::string_view Name() const;
        std::optional<std::string> StringValue() const;
        std::optional<int> IntValue() const;
        std::optional<bool> BoolValue() const;
        std::optional<double> DoubleValue() const;

    private:
        std::string_view m_name;
        std::unordered_map<std::string, NodePtr> m_children;
    };
}