#ifndef SA_TRAVERSALTASKDRAWMACRONODE_H_
#define SA_TRAVERSALTASKDRAWMACRONODE_H_

#include "tree/binarytree/TraversalTask.h"

class Window;

class TraversalTaskDrawMacroNode : public TraversalTask {
public:
    TraversalTaskDrawMacroNode(Window *window);
    ~TraversalTaskDrawMacroNode();
    /*
    @Override
    */
    void doWhenTraversing(Node *node);

private:
    Window *window;
};

#endif