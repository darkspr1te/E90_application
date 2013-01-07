#ifndef __T9_ENGLISH_H__
#define __T9_ENGLISH_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

struct Key_index
{
    const char* KC;
    int Sy_num;
    const char** KC_Symb;
};

const char* KE_SYmb_a[]={"A","a"};
const char* KE_SYmb_b[]={"B","b"};
const char* KE_SYmb_c[]={"C","c"};
const char* KE_SYmb_d[]={"D","d"};
const char* KE_SYmb_e[]={"E","e"};
const char* KE_SYmb_f[]={"F","f"};
const char* KE_SYmb_g[]={"G","g"};
const char* KE_SYmb_h[]={"H","h"};
const char* KE_SYmb_i[]={"I","i"};
const char* KE_SYmb_j[]={"J","j"};
const char* KE_SYmb_k[]={"K","k"};
const char* KE_SYmb_l[]={"L","l"};
const char* KE_SYmb_m[]={"M","m"};
const char* KE_SYmb_n[]={"N","n"};
const char* KE_SYmb_o[]={"O","o"};
const char* KE_SYmb_p[]={"P","p"};
const char* KE_SYmb_q[]={"Q","q"};
const char* KE_SYmb_r[]={"R","r"};
const char* KE_SYmb_s[]={"S","s"};
const char* KE_SYmb_t[]={"T","t"};
const char* KE_SYmb_u[]={"U","u"};
const char* KE_SYmb_v[]={"V","v"};
const char* KE_SYmb_w[]={"W","w"};
const char* KE_SYmb_x[]={"X","x"};
const char* KE_SYmb_y[]={"Y","y"};
const char* KE_SYmb_z[]={"Z","z"};

struct Key_index Key_index_en[]=
{
    {"q",2,KE_SYmb_q},
    {"w",2,KE_SYmb_w},
	{"e",2,KE_SYmb_e},
	{"r",2,KE_SYmb_r},
	{"t",2,KE_SYmb_t},
	{"y",2,KE_SYmb_y},
	{"u",2,KE_SYmb_u},
	{"i",2,KE_SYmb_i},
    {"o",2,KE_SYmb_o},
    {"p",2,KE_SYmb_p},
	{"a",2,KE_SYmb_a},
    {"s",2,KE_SYmb_s},
    {"d",2,KE_SYmb_d},
    {"f",2,KE_SYmb_f},
    {"g",2,KE_SYmb_g},
	{"h",2,KE_SYmb_h},
    {"j",2,KE_SYmb_j},
	{"k",2,KE_SYmb_k},
	{"l",2,KE_SYmb_l},
	{"z",2,KE_SYmb_z},
	{"x",2,KE_SYmb_x},
	{"c",2,KE_SYmb_c},
	{"v",2,KE_SYmb_v},
	{"b",2,KE_SYmb_b},
	{"n",2,KE_SYmb_n},
	{"m",2,KE_SYmb_m},	
	{"end",1,NULL}
};

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__T9_ENGLISH_H__*/
