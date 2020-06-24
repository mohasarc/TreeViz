#ifndef DEELX_WRAPPER_H
#define DEELX_WRAPPER_H

// The wrapper class for BTree class
#include "../logic-classes/B_Tree/Header_Files/BTree.h"
#include <napi.h>
// #include <string>

class deelxWrapper : public Napi::ObjectWrap<deelxWrapper>{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    deelxWrapper(const Napi::CallbackInfo& info);
    
private:
    static Napi::FunctionReference constructor;
    Napi::Value isValidTreeString(const Napi::CallbackInfo& info);
    Napi::Value isValidTreeSequence(const Napi::CallbackInfo& info);
    CRegexpT<char> * regexpPtr = NULL;
};

#endif