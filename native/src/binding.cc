#include <napi.h>

class Example : public Napi::ObjectWrap<Example> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Example(const Napi::CallbackInfo &info);

  private:
    static Napi::FunctionReference constructor;
    double _value;
    Napi::Value GetValue(const Napi::CallbackInfo &info);
    void SetValue(const Napi::CallbackInfo &info, const Napi::Value &value);
};

Napi::Object Example::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Example", {
        // Register a class instance accessor with getter and setter functions.
        InstanceAccessor<&Example::GetValue, &Example::SetValue>("value"),
        // We can also register a readonly accessor by omitting the setter.
        InstanceAccessor<&Example::GetValue>("readOnlyProp")
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Example", func);

    return exports;
}

Example::Example(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Example>(info) {
    Napi::Env env = info.Env();
    // ...
    Napi::Number value = info[0].As<Napi::Number>();
    this->_value = value.DoubleValue();
}

Napi::FunctionReference Example::constructor;

Napi::Value Example::GetValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_value);
}

void Example::SetValue(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    // ...
    Napi::Number arg = value.As<Napi::Number>();
    this->_value = arg.DoubleValue();
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    Example::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
