#include "pch.h"
#include "ariaMode.h"


#include <fstream>

using namespace std;

void byteXOR(Byte* a, Byte* b, Byte* t, int size) {
	for (int i = 0; i < size; i++) {
		t[i] = a[i] ^ b[i];
	}
}

void ECB_ENC(Byte* key, Byte* pt, Byte* ct, int dataSize, int keySize) {
	Byte rk[16 * 17];
	int paddingNum = 16 - dataSize % 16;
	for (int i = dataSize; i < ((dataSize - 1) / 16 + 1) * 16; i++) { //패딩 부분, PKCS 패딩 구현
		pt[i] = paddingNum;
	}
	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		Crypt(pt + 16 * i, EncKeySetup(key, rk, keySize), rk, ct + 16 * i);
	}

}
void ECB_DEC(Byte* key, Byte* ct, Byte* pt, int dataSize, int keySize) {
	Byte rk[16 * 17];
	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		Crypt(ct + 16 * i, DecKeySetup(key, rk, keySize), rk, pt + 16 * i);
	}
}

void CBC_ENC(Byte* key, Byte* pt, Byte* prect, Byte* ct, int keySize) { //prect는 이전 암호문
	Byte rk[16 * 17], pxor[16];
	byteXOR(pt, prect, pxor, 16);
	Crypt(pxor, EncKeySetup(key, rk, keySize), rk, ct);
}
void CBC_DEC(Byte* key, Byte* ct, Byte* prect, Byte* pt, int keySize) {
	Byte rk[16 * 17], tmp[16];
	Crypt(ct, DecKeySetup(key, rk, keySize), rk, tmp);
	byteXOR(tmp, prect, pt, 16);
}

void OFB_ENC(Byte* key, Byte* pt, Byte* ot, Byte* ct, int keySize) {
	Byte rk[16 * 17];
	Crypt(ot, EncKeySetup(key, rk, keySize), rk, ot);
	byteXOR(pt, ot, ct, 16);
}
void OFB_DEC(Byte* key, Byte* ct, Byte* ot, Byte* pt, int keySize) {
	Byte rk[16 * 17];
	Crypt(ot, EncKeySetup(key, rk, keySize), rk, ot);
	byteXOR(ct, ot, pt, 16);
}


void fileEnc(string ptPath, string keyin, int keySize) {
	ifstream readFile;
	ofstream writeFile;

	Byte key[16] = {};
	Byte* pt = NULL; //평문
	Byte* ct = NULL; //암호문
	int dataSize = 0;

	string ctPath = ptPath + ".enc";

	for (int i = 0; i < keyin.size(); i++) {
		key[i] = keyin[i];
	}

	readFile.open(ptPath, ios_base::binary);
	writeFile.open(ctPath, ios_base::binary);

	if (readFile.is_open()) {
		readFile.seekg(0, ios::end);
		dataSize = readFile.tellg();

		pt = (Byte*)malloc(((dataSize - 1) / 16 + 1) * 16);
		ct = (Byte*)malloc(((dataSize - 1) / 16 + 1) * 16);

		readFile.seekg(0, ios::beg);
		readFile.read((char*)pt, dataSize);

		printf("dataSize : %d\n", dataSize);
	}

	ECB_ENC(key, pt, ct, dataSize, keySize);

	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		printBlock(pt + i * 16); printf("\n");
	}
	printf("\n");
	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		printBlock(ct + i * 16); printf("\n");
	}

	if (writeFile.is_open()) {
		writeFile.write((char*)ct, ((dataSize - 1) / 16 + 1) * 16);
	}

	free(pt);
	free(ct);
}

void fileDec(string ctPath, string keyin, int keySize) {
	ifstream readFile;
	ofstream writeFile;

	Byte key[16] = {};
	Byte* ct = NULL; //암호문
	Byte* dec = NULL; //해독문
	int dataSize = 0;
	string type = "";
	string decPath = "";

	for (int i = 0; i < keyin.size(); i++) {
		key[i] = keyin[i];
	}

	decPath = ctPath.substr(0, ctPath.size() - 4);
	int dotFind = decPath.find_last_of('.');
	type = decPath.substr(dotFind, decPath.size() - dotFind);
	decPath = decPath.substr(0, dotFind);
	decPath = decPath + "_dec" + type;

	/*
	int dotFind = ctPath.find('.');
	int dotFind2 = ctPath.find_last_of('.');

	if (dotFind == std::string::npos) type = ""; //확장자를 못찾았을때
	else type = ctPath.substr(dotFind, dotFind2-dotFind);

	decPath = ctPath.substr(0, dotFind);
	decPath = decPath + "_dec" + type;
	*/


	readFile.open(ctPath, ios_base::binary);
	writeFile.open(decPath, ios_base::binary);

	if (readFile.is_open()) {
		readFile.seekg(0, ios::end);
		dataSize = readFile.tellg();

		ct = (Byte*)malloc(((dataSize - 1) / 16 + 1) * 16);
		dec = (Byte*)malloc(((dataSize - 1) / 16 + 1) * 16);

		readFile.seekg(0, ios::beg);
		readFile.read((char*)ct, dataSize);

		printf("dataSize : %d\n", dataSize);
	}

	ECB_DEC(key, ct, dec, dataSize, keySize);

	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		printBlock(ct + i * 16); printf("\n");
	}
	printf("\n");
	for (int i = 0; i < ((dataSize - 1) / 16 + 1); i++) {
		printBlock(dec + i * 16); printf("\n");
	}

	
	int paddingNum = dec[dataSize - 1];

	if (paddingNum > 0 && paddingNum < 16) {
		bool paddinged = true;

		for (int i = 1; i <= paddingNum; i++) { //뒤에서부터 비교하며 패딩 검사
			if (dec[dataSize - i] != paddingNum) paddinged = false;
		}

		if (paddinged) {
			dataSize -= paddingNum;
		}
	}

	if (writeFile.is_open()) {
		writeFile.write((char*)dec, dataSize);
	}

	free(ct);
	free(dec);
}
