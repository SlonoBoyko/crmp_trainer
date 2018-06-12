/*
		Funclions from m0d_s0beit sa
*/

#pragma once

#define M_PI						3.14159265358979323844
#define HALF_PI						1.57079632679489661923
#define DEGRESS						0.01745329251994329576
#define DEGTORAD					( deg ) ( (deg * M_PI) / 180.f )
#define RADTODEG					( rad ) ( (rad * 180.f) / M_PI )

/*				CODE				*/

char								hex_to_dec(signed char ch);
char								*hex_to_bin(const char *str);
char								*bin_to_hex(const char *bin);
string								hex_to_string(const string& input);
D3DCOLOR							hex_to_color(const char *str, int len);

string								cp1251_to_utf8(const string str);
string								utf8_to_cp1251(const string str);

/*				MATH				*/
int									near_zero(float v);
void								vect3_copy(const float in[3], float out[3]);
int									vect3_near_zero(const float in[3]);
void								vect3_invert(const float in[3], float out[3]);
void								vect3_zero(float out[3]);

void								vect3_vect3_add(const float in1[3], const float in2[3], float out[3]);
void								vect3_vect3_sub(const float in1[3], const float in2[3], float out[3]);
void								vect3_vect3_mult(const float in1[3], const float in2[3], float out[3]);
void								vect3_mult(const float in[3], float m, float out[3]);
void								vect3_div(const float in[3], float m, float out[3]);

float								vect3_length(const float in[3]);
float								vect3_dist(const float in1[3], const float in2[3]);
float								vect3_angle(const float in1[3], const float in2[3]);
void								vect3_normalize(const float in[3], float out[3]);

float								vect3_dot_product(const float in1[3], const float in2[3]);
void								vect3_cross_product(const float in1[3], const float in2[3], float out[3]);

void								vect4_copy(const float in[4], float out[4]);

void								matrix_vect3_mult(const float matrix[16], const float in[3], float out[3]);
void								matrix_vect4_mult(const float matrix[16], const float in[4], float out[4]);
void								matrix_matrix_mult(const float in1[16], const float in2[16], float out[16]);
void								matrix_vect3_rotate(const float in[16], const float vect[3], float t, float out[16]);
void								matrix_copy(const float in[16], float out[16]);

/*				OTHER					*/
void								Log(const char *text, ...);
bool								FileExists(const char *fname);
bool								DirExists(const char *dirname);

void								CalcScreenCoors(CVector * vecWorld, CVector * vecScreen);
void								CalcWorldCoors(CVector * vecScreen, CVector * vecWorld);

/*				RANDOM				*/

namespace random
{
	static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								"abcdefghijklmnopqrstuvwxyz"
								"0123456789";

	inline float _float(float min, float max)
	{
		return min + float(rand() / float(RAND_MAX)) * (max - min);
	}

	inline float _float(float max)
	{
		return float(rand() / float(RAND_MAX)) * max;
	}

	inline int _int(int min, int max)
	{
		return min + rand() % (max - min);
	}

	inline int _int(int max)
	{
		return rand() % max;
	}

	inline string _string(size_t min, size_t max)		// symbols count
	{
		size_t len = min + rand() % (max - min);
		if (len < min) len = min;	
		string ret; ret.reserve(len + 1);
		for (size_t i = 0; i <= len; i++)
			ret.push_back(alpha[rand() % sizeof(alpha) - 1]);
		return ret;
	}

	inline string _string(size_t len)		// symbols count
	{
		string ret; ret.reserve(len + 1);
		for (size_t i = 0; i < len; i++)
			ret.push_back(alpha[rand() % sizeof(alpha) - 1]);
		return ret;
	}

	inline char *_charstr(char *str, size_t len)
	{
		for (size_t i = 0; i < len; ++i) 
			str[i] = alpha[rand() % (sizeof(alpha) - 1)];
		str[len] = 0;
		return str;
	}

	template<typename T>
	inline T get(T min, T max)
	{
		if (std::is_integral<T>())			return min + rand() % int(max - min);
		if (std::is_floating_point<T>())	return min + (T(rand() / T(RAND_MAX)) * T(max - min));
		return min;
	}
	
}

