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
}
