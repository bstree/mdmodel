#pragma once
#include "Node.h"

struct cmark_node;

namespace mdmodel
{
    class Document : public Node
    {
    public:
        Document(cmark_node* root);
        ~Document();
        
    private:
        cmark_node* m_root;
    };
}