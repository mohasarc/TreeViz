// The wrapper class of tree23 class
#include "../Header_Files/AVLTreeWrapper.h"

Napi::FunctionReference AVLTreeWrapper::constructor;

Napi::Object AVLTreeWrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "AVLTree", {
        InstanceMethod("traverse", &AVLTreeWrapper::traverse),
        InstanceMethod("insert", &AVLTreeWrapper::insert),
        InstanceMethod("toTreeString", &AVLTreeWrapper::toTreeString),
        InstanceMethod("constructFromTreeString", &AVLTreeWrapper::constructFromTreeString),
        // InstanceMethod("search", &AVLTreeWrapper::search),
        // InstanceMethod("remove", &AVLTreeWrapper::remove)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("AVLTree", func);
    return exports;
}

// The constructor wrapper
AVLTreeWrapper::AVLTreeWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<AVLTreeWrapper>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    this->theAVLTree = new AVLTree<int>();
}

// Methods' wrappers
Napi::Value AVLTreeWrapper::traverse(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->theAVLTree->traverse();
    return Napi::String::New(info.Env(), output);
}

Napi::Value AVLTreeWrapper::insert(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    // if (length < 1 || !info[0].IsNumber() || !info[0].IsString()){
    //     Napi::TypeError::New(env, "Number or String expected").ThrowAsJavaScriptException();
    // }

    if (info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        bool result = this->theAVLTree->insert(val);
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->theAVLTree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type to be inserted").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

Napi::Value AVLTreeWrapper::toTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->theAVLTree->toTreeString();
    return Napi::String::New(info.Env(), output);
}

Napi::Value AVLTreeWrapper::constructFromTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsString()){
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String treeString = info[0].As<Napi::String>();
    this->theAVLTree->constructFromTreeString(treeString);
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

// Napi::Boolean AVLTreeWrapper::search(const Napi::CallbackInfo& info){

// }

// Napi::Boolean AVLTreeWrapper::remove(const Napi::CallbackInfo& info){

// }

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    AVLTreeWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)