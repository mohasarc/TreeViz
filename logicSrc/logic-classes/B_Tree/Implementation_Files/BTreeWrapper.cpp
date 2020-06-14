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
        InstanceMethod("remove", &BTreeWrapper::remove),
        InstanceMethod("setOrder", &BTreeWrapper::setOrder),
        InstanceMethod("getOrder", &BTreeWrapper::getOrder),
        InstanceMethod("setPropagateS", &BTreeWrapper::setPropagateS),
        InstanceMethod("getPropagateS", &BTreeWrapper::getPropagateS),
        InstanceMethod("setPrioritizeInorderPredecessor", &BTreeWrapper::setPrioritizeInorderPredecessor),
        InstanceMethod("getPrioritizeInorderPredecessor", &BTreeWrapper::getPrioritizeInorderPredecessor),
        InstanceMethod("setPrioritizeRotateLeft", &BTreeWrapper::setPrioritizeRotateLeft),
        InstanceMethod("getPrioritizeRotateLeft", &BTreeWrapper::getPrioritizeRotateLeft),
        InstanceMethod("insertSequence", &BTreeWrapper::insertSequence),
        InstanceMethod("setSequence", &BTreeWrapper::setSequence),
        InstanceMethod("getSequence", &BTreeWrapper::getSequence),
        InstanceMethod("generateInorderSequence", &BTreeWrapper::generateInorderSequence),
        InstanceMethod("getStepsNo", &BTreeWrapper::getStepsNo),
        InstanceMethod("getStepText", &BTreeWrapper::getStepText),
        InstanceMethod("getStepTreeStr", &BTreeWrapper::getStepTreeStr),
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

Napi::Value BTreeWrapper::setOrder(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsNumber())
        theBTree->setOrder(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BTreeWrapper::getOrder(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int order = this->theBTree->getOrder();
    return Napi::Number::New(info.Env(), order);
}

Napi::Value BTreeWrapper::setPropagateS(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsBoolean())
        theBTree->setPropagateS(info[0].As<Napi::Boolean>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());

}

Napi::Value BTreeWrapper::getPropagateS(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool propagateS = this->theBTree->getPropagateS();
    return Napi::Boolean::New(info.Env(), propagateS);
}

Napi::Value BTreeWrapper::setPrioritizeInorderPredecessor(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsBoolean())
        theBTree->setPrioritizeInorderPredecessor(info[0].As<Napi::Boolean>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BTreeWrapper::getPrioritizeInorderPredecessor(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool prioritizeInorderPredecessor = this->theBTree->getPrioritizeInorderPredecessor();
    return Napi::Boolean::New(info.Env(), prioritizeInorderPredecessor);
}

Napi::Value BTreeWrapper::setPrioritizeRotateLeft(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsBoolean())
        theBTree->setPrioritizeRotateLeft(info[0].As<Napi::Boolean>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BTreeWrapper::getPrioritizeRotateLeft(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool prioritizeRotateLeft = this->theBTree->getPrioritizeRotateLeft();
    return Napi::Boolean::New(info.Env(), prioritizeRotateLeft);
}


Napi::Value BTreeWrapper::insertSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    bool success = false;

    if (info.Length() > 0 && info[0].IsString())
        success = theBTree->insertSequence(info[0].As<Napi::String>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), success);
}

Napi::Value BTreeWrapper::setSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsString())
        theBTree->setSequence(info[0].As<Napi::String>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BTreeWrapper::getSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string sequence = this->theBTree->getSequence();
    return Napi::String::New(info.Env(), sequence);
}

Napi::Value BTreeWrapper::generateInorderSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string generatedSequence = this->theBTree->generateInorderSequence();
    return Napi::String::New(info.Env(), generatedSequence);
}


Napi::Value BTreeWrapper::getStepsNo(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int stepsNo = this->theBTree->getStepsNo();
    return Napi::Number::New(info.Env(), stepsNo);
}

Napi::Value BTreeWrapper::getStepText(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string stepText;

    if (info.Length() > 0 && info[0].IsNumber())
        stepText = theBTree->getStepText(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::String::New(info.Env(), stepText);
}

Napi::Value BTreeWrapper::getStepTreeStr(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string stepTreeStr;

    if (info.Length() > 0 && info[0].IsNumber())
        stepTreeStr = theBTree->getStepTreeStr(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::String::New(info.Env(), stepTreeStr);
}

Napi::Value BTreeWrapper::clearSteps(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    theBTree->clearSteps();
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    BTreeWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)