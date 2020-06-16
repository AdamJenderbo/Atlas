
namespace Atlas
{
	__declspec(dllimport) void Print();
}

void main()
{
	Atlas::Print();
	while (true);
}