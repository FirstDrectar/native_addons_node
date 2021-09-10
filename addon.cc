
#include <napi.h>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

Napi::Value SayHello(const Napi::CallbackInfo& info) {
  cout << "hello MMDSMART ";
}

Napi::Value Loop(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  double arg2 = info[2].As<Napi::Number>().DoubleValue();

  std::vector<double> vector;
  auto start_time = std::chrono::steady_clock::now();
  while (arg0 < arg1) {
    arg0 += arg2;
    vector.push_back(arg0);
  }
  auto end_time = std::chrono::steady_clock::now();
  auto result = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  Napi::Number num = Napi::Number::New(env, result.count());

  return num;
}

Napi::Boolean Math(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  double arg2 = info[2].As<Napi::Number>().DoubleValue();

  Napi::Boolean result = Napi::Boolean::New(env, arg0 + arg1 == arg2);
  return result;
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "sayHello"),
              Napi::Function::New(env, SayHello));
  exports.Set(Napi::String::New(env, "loop"), Napi::Function::New(env, Loop));
  exports.Set(Napi::String::New(env, "math"), Napi::Function::New(env, Math));
  return exports;
}

NODE_API_MODULE(addon, Init)
