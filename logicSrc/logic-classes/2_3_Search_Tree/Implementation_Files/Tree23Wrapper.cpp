// The wrapper class of tree23 class
#include "../Header_Files/Tree23Wrapper.h"

Napi::FunctionReference Tree23Wrapper::constructor;

Napi::Object Tree23Wrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Tree23", {
        InstanceMethod("traverse", &Tree23Wrapper::traverse),
        InstanceMethod("insert", &Tree23Wrapper::insert),
        InstanceMethod("toTreeString", &Tree23Wrapper::toTreeString),
        InstanceMethod("constructFromTreeString", &Tree23Wrapper::constructFromTreeString),
        // InstanceMethod("search", &Tree23Wrapper::search),
        // InstanceMethod("remove", &Tree23Wrapper::remove)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Tree23", func);
    return exports;
}

// The constructor wrapper
Tree23Wrapper::Tree23Wrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Tree23Wrapper>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    this->the23Tree = new Tree23<int>();
}

// Methods' wrappers
Napi::Value Tree23Wrapper::traverse(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->the23Tree->traverse();
    return Napi::String::New(info.Env(), output);
}

Napi::Value Tree23Wrapper::insert(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();
    // if (length < 1 || !info[0].IsNumber() || !info[0].IsString()){
    //     Napi::TypeError::New(env, "Number or String expected").ThrowAsJavaScriptException();
    // }

    if (info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        bool result = this->the23Tree->insert(val);
        return Napi::Boolean::New(info.Env(), result);
    } 
    // else if (info[0].IsString()){
    //     string val = info[0].As<Napi::String>();
    //     bool result = this->the23Tree->insert(val);
    //     return Napi::Boolean::New(info.Env(), result);
    // }
     else {
        Napi::Error::New(env, "unhandeled type to be inserted").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

Napi::Value Tree23Wrapper::toTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string output = this->the23Tree->toTreeString();
    return Napi::String::New(info.Env(), output);
}

Napi::Value Tree23Wrapper::constructFromTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1 || !info[0].IsString()){
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    }

    Napi::String treeString = info[0].As<Napi::String>();
    this->the23Tree->constructFromTreeString(treeString);
    return Napi::Number::New(info.Env(), 0);
}

// Napi::Boolean Tree23Wrapper::search(const Napi::CallbackInfo& info){

// }

// Napi::Boolean Tree23Wrapper::remove(const Napi::CallbackInfo& info){

// }