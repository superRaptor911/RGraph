#include <RG/File.h>


int main()
{
	rg::File f;
	f.close();
	f.open("test.txt");
	f.append("This works");
	return 0;
}