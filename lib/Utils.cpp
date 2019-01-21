#include "String.h"

namespace Utils
{
	bool isSimpleSpace(char c)
	{
		return c==' ' || c=='\t';
	}

	bool isSpace(char c)
	{
		return c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\v' || c=='\f';
	}

	bool isascii(int c)
	{
		return !(c & (~127));
	}

	int atoi(const String str)
	{
		int i = 0;
		int res = 0;
		bool isNegative = false;

		while (isSpace(str[i]))
			i++;

		isNegative = (str[i] == '-');
		if (isNegative || str[i] == '+')
			i++;

		while (str[i] && str[i] >= '0' && str[i] <= '9')
			res = str[i++] - '0' + res * 10;
		if (isNegative)
			res = -res;

		return (res);
	}

	int strlen(const char *s)
	{
		int	i = 0;

		while (s[i] != '\0')
			i++;
		return (i);
	}
}
