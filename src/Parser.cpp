#include "Parser.h"
#include "Document.h"
#include <cmark.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace mdmodel
{
    static std::string_view GetNodeText(cmark_node* node)
    {
        std::string_view text;

        for (cmark_node* child = cmark_node_first_child(node);
             child != nullptr;
             child = cmark_node_next(child))
        {
            auto type = cmark_node_get_type(child);
            if (type == CMARK_NODE_TEXT)
            {
                if (const char* literal = cmark_node_get_literal(child))
                {
                    text = literal;
                    break;
                }
            }
        }
        return text;
    }

    NodePtr Parser::Parse(const std::string& markdown)
    {
        auto native = cmark_parse_document(
            markdown.data(),
            markdown.length(),
            CMARK_OPT_DEFAULT);
        if (native == nullptr)
        {
            throw std::runtime_error("Failed to parse markdown document.");
        }

        auto doc = std::make_unique<Document>(native);
        m_parseQueue.push({ native, *doc });
        while (!m_parseQueue.empty())
        {
            Parse();
        }
        return std::move(doc);
    }

    void Parser::Parse()
    {
        auto [native, parent] = m_parseQueue.front();
        m_parseQueue.pop();

        Node* lastHeadingNode = nullptr;

        for (cmark_node* child = cmark_node_first_child(native);
             child != nullptr;
             child = cmark_node_next(child))
        {            
            auto type = cmark_node_get_type(child);
            std::cout << "Processing node type: " << cmark_node_get_type_string(child) << std::endl;

            switch (type)
            {                
                case CMARK_NODE_HEADING:
                case CMARK_NODE_PARAGRAPH:
                {
                    auto text = GetNodeText(child);
                    auto pos = text.find_first_of(": ");
                    if (pos == std::string_view::npos)
                    {
                        auto node = std::make_unique<Node>(text);
                        lastHeadingNode = node.get();
                        parent.AddChild(std::move(node));
                        std::cout << "Parsed heading: " << parent.Name() << "/" << text << std::endl;
                        continue;
                    }

                    auto node = std::make_unique<Node>(text.substr(0, pos));
                    auto& field = *node;
                    parent.AddChild(std::move(node));
                    field.AddChild(std::make_unique<Node>(text.substr(pos + 2)));

                    std::cout << "Parsed heading: " << parent.Name() << "/" << text << std::endl;
                    break;
                }

                case CMARK_NODE_LIST:
                {
                    if (lastHeadingNode)
                    {
                        m_parseQueue.push({ child, *lastHeadingNode });
                    }
                    else
                    {
                        std::cout << parent.Name() << ": List found without preceding heading, adding to parent node." << std::endl;
                        //m_parseQueue.push({ child, parent });
                    }
                    break;
                }

                case CMARK_NODE_ITEM:
                {
                    m_parseQueue.push({ child, parent });
                    break;
                }

                default:
                    std::cout << "Unhandled node type: " << cmark_node_get_type_string(child) << " (" << type << ")" << std::endl;
                    break;
            }
        }
    }
}