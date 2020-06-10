// The wrapper class of tree23 class
#include "../Header_Files/BTreeWrapper.h"

Napi::FunctionReference BTreeWrapper::constructor;

Napi::Object BTreeWrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "BTree", {
        InstanceMethod("traverse", &BTreeWrapper::traverse),
        InstanceMethod("insert", &BTreeWrapper::insert),
        InstanceMethod("toTreeString", &BTreeWrapper::toTreeString),
        InstanceMethod("constructFromTreeString", &BTreeWrapper::constructFromTreeString),
        // InstanceMethod("search", &BTreeWrapper::search),
        InstanceMethod("remove", &BTreeWrapper::remove)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("BTree", func);
    return exports;
}

// The constructor wrapper
BTreeWrapper::BTreeWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<BTreeWrapper>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    int order = 3;

    if (length > 0 && info[0].IsNumber()){
        order = info[0].As<Napi::Number>();
    } 

    this->theBTree = new BTree<int>(order);
}

// Methods' wrappers
Napi::Value BTreeWrapper::traverse(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    this->theBTree->traverse();
    // return Napi::String::New(info.Env(), output);
    return Napi::Boolean::New(info.Env(), env.Undefined());

}

Napi::Value BTreeWrapper::insert(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    // if (length < 1 || !info[0].IsNumber() || !info[0].IsString()){
    //     Napi::TypeError::New(env, "Number or String expected").ThrowAsJavaScriptException();
    // }

    if (length > 0 && info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        this->theBTree->insert(val);
        bool result = true;
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->theBTree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type to be inserted").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

Napi::Value BTreeWrapper::toTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->theBTree->toTreeString();
    return Napi::String::New(info.Env(), output);
}

Napi::Value BTreeWrapper::constructFromTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsString()){
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }else {
        Napi::String treeString = info[0].As<Napi::String>();
        this->theBTree->constructFromTreeString(treeString);
    }

    return Napi::Number::New(info.Env(), 0);
}

// Napi::Boolean BTreeWrapper::search(const Napi::CallbackInfo& info){

// }

Napi::Value BTreeWrapper::remove(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        this->theBTree->remove(val);
        bool result = true;
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->theBTree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type to be removed").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    BTreeWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)