#include <node.h>
#include <node_buffer.h>
#include <algorithm>
#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include "dlt645_api_07.h"

namespace dlt645_07 {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Exception;

void StringToHex(const char *src, char *dest, int len) {
  int i = 0, j = 0;
  char *end;
  char buffer[5];
  
  for (i = 0; i < len; i += 2) {
    std::memset(buffer, '\0', sizeof(buffer));
    std::memcpy(buffer, src + i, 2);
    dest[j] = strtol(buffer, &end, 16);
    j++;
  }
}

void HexToString(const char *src, char *dest, int len) {
  int i = 0, j = 0;
  char buffer[5];
  
  for (i = 0; i < len; i++) {
    std::memset(buffer, '\0', sizeof(buffer));
    sprintf(buffer, "%02x", src[i]);
    std::memcpy(dest + j, buffer, 2);
    j += 2;
  }
}

void EchoMethod(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Echo !!"));
}

void UnPacket07Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 1) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }
  
	String::Utf8Value utf_payload(args[0]);
	std::string str_payload = *utf_payload;
  char* readData   = (char *)std::malloc(str_payload.length());
  std::memset(readData, 0x00, str_payload.length());
  StringToHex(str_payload.c_str(), readData, str_payload.length());
  size_t readLength = str_payload.length() / 2;
  
  S_D07_UNPACK stUnPack = {0};
  std::memset((unsigned char *)&stUnPack, 0x00, sizeof(S_D07_UNPACK));
  int ret = 0;
  
  ret = unpack_d07_frame(readData, readLength, &stUnPack);
  if(ret != E_D07_OK) {
    switch (ret)
    {
      case E_D07_ERRO_UNKOWN_ID:
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Unknown ID")));
        break;
      case E_D07_ERRO_FRAME_UNCOMP:
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Frame is not complete")));
        break;
      case E_D07_ERRO_FRAME_0x68:
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Start with 0x68 error")));
        break;
      case E_D07_ERRO_FRAME_CHECK_SUM:
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Check sum error")));
        break;
      case E_D07_ERRO_FRAME_END_0x16:
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "End with 0x16 error")));
        break;
      default:
        std::cout << "Wrong format:"<< ret << std::endl;
        isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Default format error")));
        break;
    }
    return;
  }

/*
  std::cout << "Buffer length:" << readLength << std::endl;
  std::cout << "frame info:"<< ret << std::endl;
  std::cout << "ctrl_code:" << stUnPack.ctrl_c << std::endl;
  std::cout << "data_len:"<< stUnPack.data_len << std::endl;
  std::cout << "frame_len:"<< stUnPack.frame_len << std::endl;
  std::cout << "0xFE_num:"<< stUnPack.lead_num << std::endl;
  std::cout << "Address:"<< stUnPack.address << std::endl;
  std::cout << "Ruler ID:"<< stUnPack.ruler_id << std::endl;
*/
  
  S_D07_RULER_INFO info;
  std::memset((unsigned char *)&info, 0x00, sizeof(S_D07_RULER_INFO));
  ret = get_d07_ruler_info(stUnPack.ruler_id, &info);
	if(ret != E_D07_OK)	{
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Ruler ID error")));
		return;
	}
	
	S_D07_CTRL_CODE stCtrl;
	std::memset((unsigned char *)&stCtrl, 0x00, sizeof(S_D07_CTRL_CODE));
	S_D07_PACK_FRAME pack_frame = {0};
	F_D07_RULER_TRANS func = NULL;
  char* writeData   = (char *)std::malloc(1024);
  char* strWriteData   = (char *)std::malloc(1024);
  int writeLength = 0;
  char data[256] = {0x70, 0x00, 0x00, 0x00};
  unsigned char ucCtrl = 0;
	
	stCtrl.direct = E_D07_CTRL_DIR_S2M;
	func = info.func;
	stCtrl.funcode = E_D07_CTRL_READ_DATA;
	pack_frame.data = data;
	pack_frame.data_len = info.len + 4;
	
	ret = trans_d07ctrl_struct2char(&ucCtrl, &stCtrl);
	if(ret != E_D07_OK)
	{
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Trans 07 failed")));
		return;
	}
	
	pack_frame.ruler_id = stUnPack.ruler_id;
	pack_frame.ctrl_code = ucCtrl;
	std::memcpy(pack_frame.address, stUnPack.address, 13);
	
	ret = pack_d07_frame_by_data(&pack_frame, writeData, &writeLength);
	if(ret != E_D07_OK)
	{
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Pack frame failed")));
		return;
	}
	
	std:memset(strWriteData, '\0', 1024);
	std::strcpy(strWriteData, "fefefefe");
	HexToString(writeData, &strWriteData[8], writeLength);
/*
	std::cout << "Write frame:"<< writeData << writeLength << std::endl;
*/
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, strWriteData));
	
	std::free(strWriteData);
	std::free(writeData);
	std::free(readData);
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "echo", EchoMethod);
    NODE_SET_METHOD(exports, "unpacket07", UnPacket07Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace dlt645_07