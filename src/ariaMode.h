#pragma once

#include <iostream>
#include "aria.h"

void byteXOR(Byte* a, Byte* b, Byte* t, int size);
void ECB_ENC(Byte* key, Byte* pt, Byte* ct, int dataSize, int keySize);
void ECB_DEC(Byte* key, Byte* ct, Byte* pt, int dataSize, int keySize);
void CBC_ENC(Byte* key, Byte* pt, Byte* prect, Byte* ct, int keySize);
void CBC_DEC(Byte* key, Byte* ct, Byte* prect, Byte* pt, int keySize);
void OFB_ENC(Byte* key, Byte* pt, Byte* ot, Byte* ct, int keySize);
void OFB_DEC(Byte* key, Byte* ct, Byte* ot, Byte* pt, int keySize);
void fileEnc(std::string ptPath, std::string key, int keySize);
void fileDec(std::string ctPath, std::string key, int keySize);