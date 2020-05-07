#pragma once

#include "structures.h"

void WriteBytes(DWORD addr, const char *bytes, size_t len);
void ReadBytes(DWORD addr, char *buf, size_t len);
