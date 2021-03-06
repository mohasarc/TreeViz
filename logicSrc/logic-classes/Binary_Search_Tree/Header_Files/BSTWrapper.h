// The wrapper class for AVLTree class
#ifndef AVL_TREE_WRAPPER_H
#define AVL_TREE_WRAPPER_H
#include <napi.h>
#include "./BSTree.h"

class BSTWrapper : public Napi::ObjectWrap<BSTWrapper>{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    BSTWrapper(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value traverse(const Napi::CallbackInfo& info);
    Napi::Value insert(const Napi::CallbackInfo& info);
    Napi::Value toTreeString(const Napi::CallbackInfo& info);
    Napi::Value constructFromTreeString(const Napi::CallbackInfo& info);
    Napi::Value insertSequence(const Napi::CallbackInfo& info);
    Napi::Boolean search(const Napi::CallbackInfo& info);
    Napi::Value remove(const Napi::CallbackInfo& info);

    Napi::Value isEmpty(const Napi::CallbackInfo& info);
    Napi::Value setSequence(const Napi::CallbackInfo& info);
    Napi::Value getSequence(const Napi::CallbackInfo& info);
    Napi::Value generateInorderSequence(const Napi::CallbackInfo& info);
    Napi::Value getStepsNo(const Napi::CallbackInfo& info);
    Napi::Value getStepText(const Napi::CallbackInfo& info);
    Napi::Value getStepTreeStr(const Napi::CallbackInfo& info);
    Napi::Value getStepNote(const Napi::CallbackInfo& info);
    Napi::Value clearSteps(const Napi::CallbackInfo& info);

    Napi::Value setPrioritizePredecessor(const Napi::CallbackInfo& info);

    BSTree<int>* theBSTTree;
};

#endif