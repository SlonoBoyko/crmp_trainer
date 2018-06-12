/*
		Funclions from m0d_s0beit sa
*/


#include "main.h"
  

char hex_to_dec(signed char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	if (ch >= 'a' && ch <= 'f')
		return ch - 'A' + 10;

	return -1;
}

char *hex_to_bin(const char *hex)
{
	size_t len = strlen(hex);
	if (hex == nullptr || len % 2 != 0) 
		return nullptr;

	char *out = (char *)malloc(len /= 2);
	strnset(out, 0, len + 1);

	for (size_t i = 0; i < len; i++) {
		char bh = hex_to_dec(hex[i + 0]);
		char bl = hex_to_dec(hex[i + 1]);

		if (bl == -1 || bh == -1) {
			free(out); return nullptr;
		} out[i / 2] = (char)(bl | (bh << 4));
	}
	return out;
}

char *bin_to_hex(const char *bin)
{
	size_t len = strlen(bin);
	if (bin == nullptr || len == 0) 
		return nullptr;
	
	char *out = (char *)malloc(len * 2), buf[4];
	strnset(out, 0, len / 2);

	for (size_t i = 0; i < len; i++) {
		sprintf(buf, "%02X", bin[i]);
		strcat(out, buf);
	}
	return out;
}

string hex_to_string(const string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	if (len & 1) throw std::invalid_argument("odd length");

	string output;
	output.reserve(len / 2);
	for (size_t i = 0; i < len; i += 2)
	{
		char a = input[i];
		const char* p = std::lower_bound(lut, lut + 16, a);
		if (*p != a) throw std::invalid_argument("not a hex digit");

		char b = input[i + 1];
		const char* q = std::lower_bound(lut, lut + 16, b);
		if (*q != b) throw std::invalid_argument("not a hex digit");

		output.push_back(((p - lut) << 4) | (q - lut));
	}
	return output;
}

D3DCOLOR hex_to_color(const char *str, int len)
{
	char buf[12];
	strncpy_s(buf, str, len);
	D3DCOLOR color = 0x00;
	uint8_t *colorByteSet = (uint8_t *)&color;
	int stri = 0;
	for (int i = sizeof(color) - 1; i >= 0; i--)
	{
		if (i == 3 && len == 6)
		{
			colorByteSet[3] = 0xFF;
		} else
		{
			signed char bh = hex_to_dec(buf[stri++]);
			signed char bl = hex_to_dec(buf[stri++]);
			if (bh != -1 && bl != -1)
			{
				colorByteSet[i] = bl | (bh << 4);
			}
		}
	}
	return color;
}

string cp1251_to_utf8(const string str)
{
	int len_u = MultiByteToWideChar(1251, 0, str.data(), -1, 0, 0);
	if (len_u == NULL) return NULL;

	wchar_t *ures = new wchar_t[len_u];
	if (!MultiByteToWideChar(1251, 0, str.data(), -1, ures, len_u)) {
		delete[] ures; return NULL;
	}
	int len_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
	if (len_c == NULL) {
		delete[] ures;
		return NULL;
	}
	char *cres = new char[len_c];
	if (!WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, len_c, 0, 0)) {
		delete[] cres;
		return NULL;
	}
	string result = cres;

	delete[] ures; delete[] cres;
	return result;
}

string utf8_to_cp1251(const string str)
{
	int len_u = MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, 0, 0);
	if (len_u == NULL) return NULL;

	wchar_t *ures = new wchar_t[len_u];
	if (!MultiByteToWideChar(CP_UTF8, 0, str.data(), -1, ures, len_u)) {
		delete[] ures;
		return 0;
	}
	int len_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
	if (len_c == NULL) {
		delete[] ures;
		return NULL;
	}
	char *cres = new char[len_c];
	if (!WideCharToMultiByte(1251, 0, ures, -1, cres, len_c, 0, 0)) {
		delete[] cres; delete[] ures; return NULL;
	}
	string result = cres;

	delete[] ures; delete[] cres;
	return result;
}

/*				MATH				*/

int near_zero(float v)
{
	if (!isfinite(v)) return 1;
	return fabs(v) < FLOAT_EPSILON;
}

void vect3_zero(float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = 0.0f;
}

void vect3_invert(const float in[3], float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = -in[i];
}

int vect3_near_zero(const float in[3])
{
	return near_zero(in[0]) && near_zero(in[1]) && near_zero(in[2]);
}

void vect3_copy(const float in[3], float out[3])
{
	memcpy(out, in, sizeof(float) * 3);
}

void vect3_vect3_sub(const float in1[3], const float in2[3], float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = in1[i] - in2[i];
}

float vect3_length(const float in[3])
{
	return sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
}

float vect3_dist(const float in1[3], const float in2[3])
{
	float dist[3];
	vect3_vect3_sub(in1, in2, dist);
	return vect3_length(dist);
}

float vect3_angle(const float in1[3], const float in2[3])
{
	float diff[3];
	vect3_vect3_sub(in1, in2, diff);
	return -atan2(diff[1], -diff[0]);
}

void vect3_normalize(const float in[3], float out[3])
{
	float	m = vect3_length(in);
	for (int i = 0; i < 3; i++)
		out[i] = in[i] / m;
}

void vect3_div(const float in[3], float m, float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = in[i] / m;
}

void vect3_mult(const float in[3], float m, float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = in[i] * m;
}

void vect3_vect3_add(const float in1[3], const float in2[3], float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = in1[i] + in2[i];
}

void vect3_vect3_mult(const float in1[3], const float in2[3], float out[3])
{
	for (int i = 0; i < 3; i++)
		out[i] = in1[i] * in2[i];
}

float vect3_dot_product(const float in1[3], const float in2[3])
{
	return in1[0] * in2[0] + in1[1] * in2[1] + in1[2] * in2[2];
}

void vect3_cross_product(const float in1[3], const float in2[3], float out[3])
{
	out[0] = (in1[1] * in2[2]) - (in2[1] * in1[2]);
	out[1] = (in1[2] * in2[0]) - (in2[2] * in1[0]);
	out[2] = (in1[0] * in2[1]) - (in2[0] * in1[1]);
}

void vect4_copy(const float in[4], float out[4])
{
	memcpy(out, in, sizeof(float) * 4);
}

void matrix_copy(const float in[16], float out[16])
{
	memcpy(out, in, sizeof(float) * 16);
}

void matrix_vect3_mult(const float matrix[16], const float in[3], float out[3])
{
	const float in4[4] = { in[0], in[1], in[2], 1.0f };
	float		out4[4];

	matrix_vect4_mult(matrix, in4, out4);
	vect3_copy(out4, out);
}

void matrix_vect4_mult(const float matrix[16], const float in[4], float out[4])
{
	float	res[4];
	for (int i = 0; i < 4; i++) {
		res[i] = in[0] * matrix[0 + i] + in[1] * matrix[4 + i] + in[2] * matrix[8 + i] + in[3] * matrix[12 + i];
	}

	vect4_copy(res, out);
}

void matrix_matrix_mult(const float in1[16], const float in2[16], float out[16])
{
	float	res[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[i * 4 + j] = in1[i * 4 + 0] * in2[0 + j] +
				in1[i * 4 + 1] * in2[4 + j] +
				in1[i * 4 + 2] * in2[8 + j] +
				in1[i * 4 + 3] * in2[12 + j];
		}
	}
	matrix_copy(res, out);
}

void matrix_vect3_rotate(const float in[16], const float vect[3], float t, float out[16])
{
	const float x = vect[0], y = vect[1], z = vect[2];
	const float sin_t = sinf(t), cos_t = cosf(t);
	float		res[16];
	const float matrix[16] =
	{
		cos_t + (1.0f - cos_t) * x * x,
		(1.0f - cos_t) * x * y - sin_t * z,
		(1.0f - cos_t) * x * z + sin_t * y,
		0.0f,
		(1.0f - cos_t) * y * x + sin_t * z,
		cos_t + (1.0f - cos_t) * y * y,
		(1.0f - cos_t) * y * z - sin_t * x,
		0.0f,
		(1.0f - cos_t) * z * x - sin_t * y,
		(1.0f - cos_t) * z * y + sin_t * x,
		cos_t + (1.0f - cos_t) * z * z,
		0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	matrix_matrix_mult(in, matrix, res);
	vect4_copy(&in[4 * 3], &res[4 * 3]);
	matrix_copy(res, out);
}

inline void D3DXMatrixInverse_safe(D3DMATRIX *pOut, FLOAT *pDet, D3DMATRIX *pM)
{
	HMODULE hD3Dx9 = nullptr;
	char buf[MAX_PATH], path[MAX_PATH];
	GetSystemDirectory(buf, MAX_PATH);
	strcat_s(buf, "\\d3dx9");

	for (size_t i = 24; i <= 43; i++) {
		sprintf_s(path, "%s_%d.dll", buf, i);
		hD3Dx9 = GetModuleHandle(path);
		if (hD3Dx9 != nullptr) break;
	}
	DWORD dwFunc = (DWORD)GetProcAddress(hD3Dx9, "D3DXMatrixInverse");
	func::stdcall(dwFunc, pOut, pDet, pM);
}

void CalcWorldCoors(CVector * vecScreen, CVector * vecWorld)
{
	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIXA16 m((float*)(0xB6FA2C));

	// Invert the view matrix
	D3DXMATRIXA16 minv;
	memset(&minv, 0, sizeof(D3DXMATRIXA16));
	m._44 = 1.0f;
	
	D3DXMatrixInverse_safe(&minv, NULL, &m);

	DWORD *dwLenX = (DWORD*)(0xC17044);
	DWORD *dwLenY = (DWORD*)(0xC17048);

	// Reverse screen coordinates
	float fRecip = 1.0f / vecScreen->fZ;
	vecScreen->fX /= fRecip * (*dwLenX);
	vecScreen->fY /= fRecip * (*dwLenY);

	// Do an (inverse) transformation
	vecWorld->fX = vecScreen->fZ * minv._31 + vecScreen->fY * minv._21 + vecScreen->fX * minv._11 + minv._41;
	vecWorld->fY = vecScreen->fZ * minv._32 + vecScreen->fY * minv._22 + vecScreen->fX * minv._12 + minv._42;
	vecWorld->fZ = vecScreen->fZ * minv._33 + vecScreen->fY * minv._23 + vecScreen->fX * minv._13 + minv._43;
}

void CalcScreenCoors(CVector * vecWorld, CVector * vecScreen)
{
	/** C++-ifyed function 0x71DA00, formerly called by CHudSA::CalcScreenCoors **/

	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIX m((float*)(0xB6FA2C));

	// Get the static virtual screen (x,y)-sizes
	DWORD *dwLenX = (DWORD*)(0xC17044);
	DWORD *dwLenY = (DWORD*)(0xC17048);

	// Do a transformation
	vecScreen->fX = vecWorld->fZ * m._31 + vecWorld->fY * m._21 + vecWorld->fX * m._11 + m._41;
	vecScreen->fY = vecWorld->fZ * m._32 + vecWorld->fY * m._22 + vecWorld->fX * m._12 + m._42;
	vecScreen->fZ = vecWorld->fZ * m._33 + vecWorld->fY * m._23 + vecWorld->fX * m._13 + m._43;

	// Get the correct screen coordinates
	float fRecip = 1.0f / vecScreen->fZ;
	vecScreen->fX *= fRecip * (*dwLenX);
	vecScreen->fY *= fRecip * (*dwLenY);
}


////////////////////////////////////////////////////////

bool FileExists(const char *fname)
{
	return access(fname, 0) != -1;
}

bool DirExists(const char *dirname)
{
	if (dirname == NULL) return false;

	DWORD dwAttr = GetFileAttributes(dirname);
	if (dwAttr == INVALID_FILE_ATTRIBUTES)
		return false;

	return (dwAttr & FILE_ATTRIBUTE_DIRECTORY);
}

void Log(const char *text, ...)
{
	if (text == NULL || !strlen(text)) return;

	SYSTEMTIME t; GetLocalTime(&t);
	string fname = szWorkingDirectory;
	fname += "CRMP_Trainer.log";
	
	va_list ap; va_start(ap, text);
	FILE *flog = fopen(fname.c_str(), "ab");
	fprintf(flog, "[%.2d:%.2d:%.2d:%.2d]: ", t.wHour, 
		t.wMinute, t.wSecond, t.wMilliseconds / 10);
	vfprintf(flog, text, ap); 
	va_end(ap);

	fprintf(flog, "\r\n"); 
	fclose(flog);
}

