#include <napi.h>
#include "./logic-classes/2_3_Search_Tree/Header_Files/Tree23Wrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Tree23Wrapper::Init(env, exports);
}

NODE_API_MODULE(logic, InitAll)
// NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)