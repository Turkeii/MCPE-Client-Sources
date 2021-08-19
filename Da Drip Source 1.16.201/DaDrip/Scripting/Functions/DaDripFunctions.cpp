#include "DaDripFunctions.h"

JsValueRef CALLBACK DaDripFunctions::getCommandManager(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argumentCount, void* callbackState) {
	return reinterpret_cast<ContextObjects*>(callbackState)->commandManager;
}

JsValueRef CALLBACK DaDripFunctions::getModuleManager(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argumentCount, void* callbackState) {
	return reinterpret_cast<ContextObjects*>(callbackState)->moduleManager;
}

JsValueRef CALLBACK DaDripFunctions::getDrawUtils(JsValueRef callee, bool isConstructCall, JsValueRef* arguments, unsigned short argumentCount, void* callbackState) {
	return reinterpret_cast<ContextObjects*>(callbackState)->drawUtils;
}