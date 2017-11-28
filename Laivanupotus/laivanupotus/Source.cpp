#include <iostream>
using namespace std;

const int MAX_TAULU = 4;

int main()
{
	int taulu[MAX_TAULU] = { 2,7,1,3 };
	int i = 0;
	int j = 0;

	cout << "Alkuperainen" << endl;
	for (i = 0; i < MAX_TAULU; i++)
		cout << taulu[i] << " ";
	cout << endl;


	for (i = 0; i < (MAX_TAULU - 1); i++)
		for (j = i + 1; j < MAX_TAULU; j++)
			if (taulu[j]<taulu[i])
			{
				int apu = taulu[i];
				taulu[i] = taulu[j];
				taulu[j] = apu;
			}

	cout << "Jarjestetty" << endl;
	for (i = 0; i < MAX_TAULU; i++)
		cout << taulu[i] << " ";
	cout << endl;
	//juupeli
	return 0;
}
