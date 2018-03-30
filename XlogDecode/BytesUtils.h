#pragma once

CString dump(byte *buf, int len){
	TCHAR hex[8];
	CString out = L"";
	for(int ii=0;ii<len;ii++){
		wsprintf(hex, L"%02X", buf[ii]);
		out += hex;
	}
	return out;
}