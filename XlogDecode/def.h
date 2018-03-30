#pragma once

typedef UINT32 uint32_t;
typedef UINT16 uint16_t;
#ifndef byte
typedef unsigned char byte;
#endif

static const char kMagicSyncStart = '\x06';
static const char kMagicSyncNoCryptStart ='\x08';
static const char kMagicAsyncStart ='\x07';
static const char kMagicAsyncNoCryptStart ='\x09';

static const char kMagicEnd  = '\0';