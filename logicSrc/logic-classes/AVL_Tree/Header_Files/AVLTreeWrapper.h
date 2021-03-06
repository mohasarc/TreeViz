// The wrapper class for AVLTree class
#ifndef AVL_TREE_WRAPPER_H
#define AVL_TREE_WRAPPER_H
#include <napi.h>
#include "AVLTree.h"

class AVLTreeWrapper : public Napi::ObjectWrap<AVLTreeWrapper>{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    AVLTreeWrapper(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value traverse(const Napi::CallbackInfo& info);
    Napi::Value insert(const Napi::CallbackInfo& info);
    Napi::Value toTreeString(const Napi::CallbackInfo& info);
    Napi::Value constructFromTreeString(const Napi::CallbackInfo& info);
    // Napi::Boolean search(const Napi::CallbackInfo& info);
    // Napi::Boolean remove(const Napi::CallbackInfo& info);

    AVLTree<int>* theAVLTree;
};

#endif