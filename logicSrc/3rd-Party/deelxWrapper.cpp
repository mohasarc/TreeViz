// The wrapper class of tree23 class
#include "./deelxWrapper.h"

Napi::FunctionReference deelxWrapper::constructor;

Napi::Object deelxWrapper::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Deelx", {
        InstanceMethod("isValidTreeString", &deelxWrapper::isValidTreeString),
        InstanceMethod("isValidTreeSequence", &deelxWrapper::isValidTreeSequence),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Deelx", func);
    return exports;
}

// The constructor wrapper
deelxWrapper::deelxWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<deelxWrapper>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    // string regExpStr = "";

    // if (info.Length() > 0 && info[0].IsString()){
    //     regExpStr = info[0].As<Napi::String>();
    // }

    // this->regexpPtr = new CRegexpT<char>(regExpStr.c_str());
}

Napi::Value deelxWrapper::isValidTreeString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string treeStr;
    bool isMatched;
    static CRegexpT<char> regexp(R"(\{\d+(,\d+)*\}(\(((?R),?)+\))*)");

    if (info.Length() > 0 && info[0].IsString()){
        treeStr = info[0].As<Napi::String>();
        MatchResult result = regexp.MatchExact(treeStr.c_str());
        isMatched = result.IsMatched();
    }
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();

    return Napi::Boolean::New(info.Env(), isMatched);
}

Napi::Value deelxWrapper::isValidTreeSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string treeSequence;
    bool isMatched;
    static CRegexpT<char> regexp(R"(\d(,?d?-?(?R))*)");

    if (info.Length() > 0 && info[0].IsString()){
        treeSequence = info[0].As<Napi::String>();
        MatchResult result = regexp.MatchExact(treeSequence.c_str());
        isMatched = result.IsMatched();
    }
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();

    return Napi::Boolean::New(info.Env(), isMatched);
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    deelxWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)