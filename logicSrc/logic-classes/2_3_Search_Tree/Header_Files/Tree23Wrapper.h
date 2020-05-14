// The wrapper class for Tree23 class
#include <napi.h>
#include "Tree23.h"

class Tree23Wrapper : public Napi::ObjectWrap<Tree23Wrapper>{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Tree23Wrapper(const Napi::CallbackInfo& info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value traverse(const Napi::CallbackInfo& info);
    Napi::Value insert(const Napi::CallbackInfo& info);
    Napi::Value toTreeString(const Napi::CallbackInfo& info);
    Napi::Value constructFromTreeString(const Napi::CallbackInfo& info);
    // Napi::Boolean search(const Napi::CallbackInfo& info);
    // Napi::Boolean remove(const Napi::CallbackInfo& info);

    Tree23<int> *the23Tree;
};
