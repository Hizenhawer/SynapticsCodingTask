#include <iostream>
#include <inttypes.h>
#include "Display.h"
#include "RGB.h"
#include "Gradient.h"

static bool str_to_uint16(const char*, uint16_t*);
static bool myConvert(char*, uint16_t*);
int inputErrorHandler(int);

int main(int argc, char* argv[]) {
	Display dis(argv[1]);
	uint16_t tl = 0x0, tr = 0x0, bl = 0x0, br = 0x0;

	if (argc < 4)
		return inputErrorHandler(-1);
	if (!myConvert(argv[2], &tl))
		return inputErrorHandler(-2);
	if (!myConvert(argv[3], &tr))
		return inputErrorHandler(-2);
	if (argc < 5)
		bl = tl;
	else
		if (!myConvert(argv[4], &bl))
			return inputErrorHandler(-2);
	if (argc < 6)
		br = tr;
	else
		if (!myConvert(argv[5], &br))
			return inputErrorHandler(-2);

	RGB otl(tl), otr(tr), obl(bl), obr(br);
	RGB rgbs[4] = { otl,otr,obl,obr };
	//cout << otl.to_string() << endl << otr.to_string() << endl << obl.to_string() << endl << obr.to_string() << endl;
	Gradient gradient(rgbs, dis.size());
	dis.draw({ 0,0 }, gradient.getPixels(), dis.size().height * dis.size().width);
	dis.present();
	return 0;
}

static bool str_to_uint16(const char* str, uint16_t* res)
{
	char* end;
	errno = 0;
	intmax_t val = strtoimax(str, &end, 10);
	if (errno == ERANGE || val < 0 || val > UINT16_MAX || end == str || *end != '\0')
		return false;
	*res = (uint16_t)val;
	return true;
}

static bool myConvert(char* str, uint16_t* res) {
	if (str[0] == '0' && str[1] == 'x')
	{
		char* stopstring;
		*res = (uint16_t)strtoul(str, &stopstring, 16);
	}
	else if (!str_to_uint16(str, res))
	{
		return false;
	}
	return true;
}

int inputErrorHandler(int errNum)
{
	using std::cout;
	switch (errNum)
	{
	case -1:
	{
		cout << "Minimum 2 colors needed\n";
		return 1;
	}
	case -2:
	{
		cout << "Color value is not correct hex or int value\n";
		return 1;
	}
	default:
		return 1;
	}
}