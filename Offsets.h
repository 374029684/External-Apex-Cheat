#pragma once
#define TOFFSET(d1) d1 //((d1)+offset_ran_var)
extern unsigned long long offset_ran_var;



#define OFFSET_ENTITYLIST			0x1a75038		//cl_entitylist
#define OFFSET_NAME					0x589			//m_iName
#define OFFSET_ITEM_GLOW            0x2c0          //m_highlightFunctionBits
#define OFFSET_GLOW_ENABLE          0x3c8          //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS   0x3d0          //2 = enabled, 5 = disabled