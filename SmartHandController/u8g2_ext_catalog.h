#pragma once
#include "u8g2_ext.h"
#ifdef OLDCAT
#include <U8g2lib.h>
#include "u8g2_ext_event.h"
bool ext_UserInterfaceCatalog(u8g2_t *u8g2, Pad *extPad, const char *title);
#endif
