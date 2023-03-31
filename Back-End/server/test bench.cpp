std::string path = info[0].As<Napi::String>();
    int property = info[1].As<Number>();
    int dataSize = info[2].As<Number>();
    Array b = info[3].As<Array>();
    for(int i = 0; i<b.Length(); i++)
    {
      Napi::Value v = b[i];
      if (v.IsNumber())
      {
        int value = (int)v.As<Napi::Number>();
        ...
        ...
      }
    }



void args(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    int i = 0;
    while (i < info.Length()) {
        if (info[i]->IsBoolean()) {
            printf("boolean = %s", info[i]->BooleanValue() ? "true" : "false");
        } else if (info[i]->IsInt32()) {
            printf("int32 = %ld", info[i]->IntegerValue());
        } else if (info[i]->IsNumber()) {
            printf("number = %f", info[i]->NumberValue());
        } else if (info[i]->IsString()) {
            printf("string = %s", *v8::String::Utf8Value(info[i]->ToString()));
        } else if (info[i]->IsObject()) {
            printf("[object]");
            v8::Local<v8::Object> obj = info[i]->ToObject();
            v8::Local<v8::Array> props = obj->GetPropertyNames();
            for (unsigned int j = 0; j < props->Length(); j++) {
                printf("%s: %s",
                       *v8::String::Utf8Value(props->Get(j)->ToString()),
                       *v8::String::Utf8Value(obj->Get(props->Get(j))->ToString())
                      );
            }
        } else if (info[i]->IsUndefined()) {
            printf("[undefined]");
        } else if (info[i]->IsNull()) {
            printf("[null]");
        }
        i += 1;
    }
}



NAN_METHOD(func1) {
        if (info.Length() > 0) {
                Local<Object> obj = info[0]->ToObject();
                Local<String> x = Nan::New<String>("x").ToLocalChecked();
                Local<String> y = Nan::New<String>("y").ToLocalChecked();

                Local<String> sum  = Nan::New<String>("sum").ToLocalChecked();
                Local<String> prod  = Nan::New<String>("prod").ToLocalChecked();

                Local<Object> ret = Nan::New<Object>();

                double x1 = Nan::Get(obj, x).ToLocalChecked()->NumberValue();
                double y1 = Nan::Get(obj, y).ToLocalChecked()->NumberValue();

                Nan::Set(ret, sum, Nan::New<Number>(x1 + y1));
                Nan::Set(ret, prod, Nan::New<Number>(x1 * y1));

                info.GetReturnValue().Set(ret);

        }
}


NAN_METHOD(func1) {
        if (info.Length() > 0) {
                Local<Object> obj = info[0]->ToObject();
                Local<String> x = Nan::New<String>("x").ToLocalChecked();
                Local<String> y = Nan::New<String>("y").ToLocalChecked();

                Local<String> sum  = Nan::New<String>("sum").ToLocalChecked();
                Local<String> prod  = Nan::New<String>("prod").ToLocalChecked();

                Local<Object> ret = Nan::New<Object>();

                double x1 = Nan::Get(obj, x).ToLocalChecked()->NumberValue();
                double y1 = Nan::Get(obj, y).ToLocalChecked()->NumberValue();

                Nan::Set(ret, sum, Nan::New<Number>(x1 + y1));
                Nan::Set(ret, prod, Nan::New<Number>(x1 * y1));

                info.GetReturnValue().Set(ret);

        }
}



if (args[0]->IsArray()) {
Local<Array> a = Array::Cast(*args[0]);
for (int index = 0, size = a->Length(); index < size; index++) {
Local<Value> element = a->Get(index);
if (element->IsArray()) {
Local<Array> b = Array::Cast(*element);
// do useful stuff with b
}
}
}



if (info.Length() <= 0 || !info[0].IsArray()) {
        Napi::TypeError::New(env, "array expected").ThrowAsJavaScriptException();
    }

    Napi::Array array = info[0].As<Napi::Array>();
    uint32_t len = array.Length();
    cout<<"array length="<<len<<endl;
    for(uint32_t i=0;i<len;i++) {
        Napi::Array subArray = static_cast<Napi::Value>(array[i]).As<Napi::Array>();
        uint32_t lenj = subArray.Length();
        for(uint32_t j=0;j<lenj;j++) {
            string element = static_cast<Napi::Value>(subArray[j]).As<Napi::String>().ToString();
                cout<<"i="<<i<<" j="<<j<<" element ="<<element<<endl;
        }
    }