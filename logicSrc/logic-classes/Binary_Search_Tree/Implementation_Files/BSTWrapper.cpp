// The wrapper class of tree23 class
#include "../Header_Files/BSTWrapper.h"

Napi::FunctionReference BSTWrapper::constructor;

Napi::Object BSTWrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "BSTree", {
        InstanceMethod("traverse", &BSTWrapper::traverse),
        InstanceMethod("insert", &BSTWrapper::insert),
        InstanceMethod("toTreeString", &BSTWrapper::toTreeString),
        InstanceMethod("constructFromTreeString", &BSTWrapper::constructFromTreeString),
        InstanceMethod("insertSequence", &BSTWrapper::insertSequence),
        // InstanceMethod("search", &BSTWrapper::search),
        InstanceMethod("remove", &BSTWrapper::remove)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("BSTree", func);
    return exports;
}

// The constructor wrapper
BSTWrapper::BSTWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<BSTWrapper>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    this->theBSTTree = new BSTree<int>();
}

// Methods' wrappers
Napi::Value BSTWrapper::traverse(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->theBSTTree->traverse();
    return Napi::String::New(info.Env(), output);
}

Napi::Value BSTWrapper::insert(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    // if (length < 1 || !info[0].IsNumber() || !info[0].IsString()){
    //     Napi::TypeError::New(env, "Number or String expected").ThrowAsJavaScriptException();
    // }

    if (info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        bool result = this->theBSTTree->insert(val);
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->theBSTTree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type is to be inserted").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

Napi::Value BSTWrapper::toTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->theBSTTree->toTreeString();
    return Napi::String::New(info.Env(), output);
}

Napi::Value BSTWrapper::constructFromTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsString()){
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String treeString = info[0].As<Napi::String>();
    this->theBSTTree->constructFromTreeString(treeString);
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BSTWrapper::insertSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsString()){
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String sequence = info[0].As<Napi::String>();
    bool success = this->theBSTTree->insertSequence(sequence);

    if (!success){
        Napi::TypeError::New(env, "Not a valid sequence").ThrowAsJavaScriptException();
    }

    return Napi::Boolean::New(info.Env(), env.Undefined());
}

// Napi::Boolean BSTWrapper::search(const Napi::CallbackInfo& info){

// }

Napi::Value BSTWrapper::remove(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 1 && info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        string type = info[1].As<Napi::String>();
        this->theBSTTree->remove(val, type[0]);
        bool result = true;
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->theBSTTree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type to be removed").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    BSTWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)