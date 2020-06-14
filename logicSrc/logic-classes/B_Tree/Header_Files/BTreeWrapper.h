#ifndef BTree_WRAPPER_H
#define BTree_WRAPPER_H

// The wrapper class for BTree class
#include <napi.h>
#include "BTree.h"

class BTreeWrapper : public Napi::ObjectWrap<BTreeWrapper>{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    BTreeWrapper(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value traverse(const Napi::CallbackInfo& info);
    Napi::Value insert(const Napi::CallbackInfo& info);
    Napi::Value toTreeString(const Napi::CallbackInfo& info);
    Napi::Value constructFromTreeString(const Napi::CallbackInfo& info);
    // Napi::Boolean search(const Napi::CallbackInfo& info);
    Napi::Value remove(const Napi::CallbackInfo& info);

    Napi::Value setOrder(const Napi::CallbackInfo& info);
    Napi::Value getOrder(const Napi::CallbackInfo& info);
    Napi::Value setPropagateS(const Napi::CallbackInfo& info);
    Napi::Value getPropagateS(const Napi::CallbackInfo& info);
    Napi::Value setPrioritizeInorderPredecessor(const Napi::CallbackInfo& info);
    Napi::Value getPrioritizeInorderPredecessor(const Napi::CallbackInfo& info);
    Napi::Value setPrioritizeRotateLeft(const Napi::CallbackInfo& info);
    Napi::Value getPrioritizeRotateLeft(const Napi::CallbackInfo& info);

    Napi::Value insertSequence(const Napi::CallbackInfo& info);
    Napi::Value setSequence(const Napi::CallbackInfo& info);
    Napi::Value getSequence(const Napi::CallbackInfo& info);
    Napi::Value generateInorderSequence(const Napi::CallbackInfo& info);

    Napi::Value getStepsNo(const Napi::CallbackInfo& info);
    Napi::Value getStepText(const Napi::CallbackInfo& info);
    Napi::Value getStepTreeStr(const Napi::CallbackInfo& info);

    BTree<int> *theBTree;
};

#endif