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

    BTree<int> *theBTree;
};

#endif