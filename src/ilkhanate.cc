
// (c) oblong industries

#include "ilkhanate.hh"

#include <libLoam/c/ob-log.h>

namespace {
v8::Local<v8::Symbol> IlkSymbol() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(v8::Symbol::New(ctxt->GetIsolate(),
                              Nan::New("gelatin.ilk").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> ConsIlk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(v8::Symbol::New(ctxt->GetIsolate(),
                              Nan::New("gelatin.ilk.cons").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> V2Float64Ilk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(
        v8::Symbol::New(ctxt->GetIsolate(),
                        Nan::New("gelatin.ilk.v2float64").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> V2Int32Ilk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(v8::Symbol::New(
        ctxt->GetIsolate(), Nan::New("gelatin.ilk.v2int32").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> V2Int64Ilk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(v8::Symbol::New(
        ctxt->GetIsolate(), Nan::New("gelatin.ilk.v2int64").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> V3Float64Ilk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(
        v8::Symbol::New(ctxt->GetIsolate(),
                        Nan::New("gelatin.ilk.v3float64").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Symbol> V4Float64Ilk() {
  static Nan::Persistent<v8::Symbol> sym;
  Nan::EscapableHandleScope scope;
  if (sym.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    sym.Reset(
        v8::Symbol::New(ctxt->GetIsolate(),
                        Nan::New("gelatin.ilk.v4float64").ToLocalChecked()));
  }
  return scope.Escape(Nan::New(sym));
}

v8::Local<v8::Map> IlkCtorMap() {
  Nan::EscapableHandleScope scope;
  static v8::Persistent<v8::Map> m;
  if (m.IsEmpty()) {
    auto ctxt = Nan::GetCurrentContext();
    m.Reset(ctxt->GetIsolate(), v8::Map::New(ctxt->GetIsolate()));
  }
  v8::Local<v8::Map> lm = Nan::New(m);
  return scope.Escape(lm);
}

v8::Local<v8::Symbol> SymForIlk(gelatin::Ilkhanate::Ilk ilk) {
  using namespace gelatin::Ilkhanate;

  v8::Local<v8::Symbol> ilksym;
  // This is near the point where a lookup table would be better.
  switch (ilk) {
    case Ilk::Cons:
      ilksym = ConsIlk();
      break;
    case Ilk::V2Float64:
      ilksym = V2Float64Ilk();
      break;
    case Ilk::V2Int32:
      ilksym = V2Int32Ilk();
      break;
    case Ilk::V3Float64:
      ilksym = V3Float64Ilk();
      break;
    case Ilk::V4Float64:
      ilksym = V4Float64Ilk();
      break;
    case Ilk::Null:
      OB_FATAL_BUG("Somebody used the Null Ilk.");
      break;
  }
  return ilksym;
}

NAN_METHOD(RegisterIlkConstructor) {
  const auto ilkv = info[0];
  const auto ctorv = info[1];

  if (!ilkv->IsSymbol()) {
    Nan::ThrowTypeError("first argument must be a Symbol");
    return;
  }
  if (!ctorv->IsFunction()) {
    Nan::ThrowTypeError("second argument must be a function");
    return;
  }
  const auto ilk = v8::Local<v8::Symbol>::Cast(ilkv);
  const auto ctor = v8::Local<v8::Symbol>::Cast(ctorv);
  v8::Local<v8::Map> ilkmap = IlkCtorMap();
  // Urgh, this seems... gross?  What if we have multiple contexts?
  ilkmap->Set(Nan::GetCurrentContext(), ilk, ctor).ToLocalChecked();
}
}

namespace gelatin {
namespace Ilkhanate {
NAN_MODULE_INIT(Init) {
  auto obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("ILK").ToLocalChecked(), IlkSymbol());

  Nan::Set(obj, Nan::New("CONS").ToLocalChecked(), ConsIlk());
  Nan::Set(obj, Nan::New("V2FLOAT64").ToLocalChecked(), V2Float64Ilk());
  Nan::Set(obj, Nan::New("V2INT32").ToLocalChecked(), V2Int32Ilk());
  Nan::Set(obj, Nan::New("V2INT64").ToLocalChecked(), V2Int64Ilk());
  Nan::Set(obj, Nan::New("V3FLOAT64").ToLocalChecked(), V3Float64Ilk());
  Nan::Set(obj, Nan::New("V4FLOAT64").ToLocalChecked(), V4Float64Ilk());
  Nan::SetMethod(obj, "registerIlkConstructor", RegisterIlkConstructor);

  Nan::Set(target, Nan::New("ilkhanate").ToLocalChecked(), obj);
}

Ilk GetIlk(v8::Local<v8::Object> obj) {
  v8::Local<v8::Value> obilk = Nan::Get(obj, IlkSymbol()).ToLocalChecked();

  // This is near the point where a lookup table would be better.
  if (obilk->Equals(ConsIlk())) {
    return Ilk::Cons;
  } else if (obilk->Equals(V3Float64Ilk())) {
    return Ilk::V3Float64;
  } else if (obilk->Equals(V2Float64Ilk())) {
    return Ilk::V2Float64;
  } else if (obilk->Equals(V2Int32Ilk())) {
    return Ilk::V2Int32;
  } else if (obilk->Equals(V4Float64Ilk())) {
    return Ilk::V4Float64;
  } else {
    return Ilk::Null;
  }
}

bool HasIlk(v8::Local<v8::Object> obj, Ilk ilk) {
  v8::Local<v8::Value> obilk = Nan::Get(obj, IlkSymbol()).ToLocalChecked();
  v8::Local<v8::Symbol> ilksym = SymForIlk(ilk);
  return obilk->Equals(ilksym);
}

v8::Local<v8::Function> GetIlkConstructor(Ilk ilk) {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Symbol> ilksym = SymForIlk(ilk);
  v8::Local<v8::Map> symmap = IlkCtorMap();
  v8::Local<v8::Value> val =
      symmap->Get(Nan::GetCurrentContext(), ilksym).ToLocalChecked();
  if (!val->IsFunction()) {
    OB_LOG_BUG("retrieved value from ilk ctor map that was not a function");
    return {};
  }
  const auto ctor = v8::Local<v8::Function>::Cast(val);
  return scope.Escape(ctor);
}
}
}
