#include "Document.h"
#include "cmark.h"

namespace mdmodel
{
    Document::Document(cmark_node* root)  :
        Node(""), 
        m_root(root)
    {
        
    }

    Document::~Document()
    {
        if (m_root)
        {
            cmark_node_free(m_root);
        }
    }
}