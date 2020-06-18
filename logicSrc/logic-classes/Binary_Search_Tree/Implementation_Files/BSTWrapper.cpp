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
        InstanceMethod("remove", &BSTWrapper::remove),
        InstanceMethod("isEmpty", &BSTWrapper::isEmpty),
        InstanceMethod("setSequence", &BSTWrapper::setSequence),
        InstanceMethod("getSequence", &BSTWrapper::getSequence),
        InstanceMethod("generateInorderSequence", &BSTWrapper::generateInorderSequence),
        InstanceMethod("getStepsNo", &BSTWrapper::getStepsNo),
        InstanceMethod("getStepText", &BSTWrapper::getStepText),
        InstanceMethod("getStepTreeStr", &BSTWrapper::getStepTreeStr),
        InstanceMethod("getStepNote", &BSTWrapper::getStepNote),
        InstanceMethod("clearSteps", &BSTWrapper::clearSteps),
        InstanceMethod("setPrioritizePredecessor", &BSTWrapper::setPrioritizePredecessor),
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

    if (info.Length() > 0 && info[0].IsNumber()){
        int val = info[0].As<Napi::Number>();
        this->theBSTTree->remove(val);
        bool result = true;
        return Napi::Boolean::New(info.Env(), result);
    } 
     else {
        Napi::Error::New(env, "unhandeled type to be removed").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), env.Undefined());
    }
}

Napi::Value BSTWrapper::isEmpty(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool empty = this->theBSTTree->isEmpty();
    return Napi::Boolean::New(info.Env(), empty);
}

Napi::Value BSTWrapper::setSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsString())
        theBSTTree->setSequence(info[0].As<Napi::String>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BSTWrapper::getSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string sequence = this->theBSTTree->getSequence();
    return Napi::String::New(info.Env(), sequence);
}

Napi::Value BSTWrapper::generateInorderSequence(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    string generatedSequence = this->theBSTTree->generateInorderSequence();
    return Napi::String::New(info.Env(), generatedSequence);
}

Napi::Value BSTWrapper::getStepsNo(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int stepsNo = this->theBSTTree->getStepsNo();
    return Napi::Number::New(info.Env(), stepsNo);
}

Napi::Value BSTWrapper::getStepText(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string stepText;

    if (info.Length() > 0 && info[0].IsNumber())
        stepText = theBSTTree->getStepText(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::String::New(info.Env(), stepText);
}

Napi::Value BSTWrapper::getStepTreeStr(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string stepTreeStr;

    if (info.Length() > 0 && info[0].IsNumber())
        stepTreeStr = theBSTTree->getStepTreeStr(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::String::New(info.Env(), stepTreeStr);
}

Napi::Value BSTWrapper::getStepNote(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    string stepNote;

    if (info.Length() > 0 && info[0].IsNumber())
        stepNote = theBSTTree->getStepNote(info[0].As<Napi::Number>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::String::New(info.Env(), stepNote);
}

Napi::Value BSTWrapper::clearSteps(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    theBSTTree->clearSteps();
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

Napi::Value BSTWrapper::setPrioritizePredecessor(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsBoolean())
        theBSTTree->setPrioritizePredecessor(info[0].As<Napi::Boolean>());
    else
        Napi::Error::New(env, "arguments number or type is not correct").ThrowAsJavaScriptException();
    
    return Napi::Boolean::New(info.Env(), env.Undefined());
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    BSTWrapper::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)