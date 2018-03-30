
#pragma once

#pragma  pack (push,1)
typedef struct _xlogHead{
	byte start;
	UINT16 seq;
	byte beginHour;
	byte endHour;
	UINT32 length;
	byte crypt[64];

}xlogHead;
#pragma pack(pop)


uint32_t GetHeaderLen() {
    return sizeof(char) * 3 + sizeof(uint16_t) + sizeof(uint32_t) + sizeof(char) * 64;
}

uint32_t GetTailerLen() {
    return sizeof(kMagicEnd);
}


