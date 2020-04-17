//DETERMINES NUMBER OF PACKS NEEDED TO COMPLETE REST OF COLLECTION

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>

//#define WhileLoopCondition (missingRares >= NumberOfRares * 0.5)			//for half of set's rares not using dust
//#define WhileLoopCondition (missingRares > 0)								//for all of set's rares not using dust
//#define WhileLoopCondition (missingCommons > 0)							//for all of set's commons not using dust
//#define WhileLoopCondition ((SetValue - (CollectionValue+dust)) > 0)		//for full set
//#define WhileLoopCondition ((missingCommons - (dust/40)) > 0)				//for getting all commons using dust and packs
//#define WhileLoopCondition ((missingRares - (dust/100)) > 0)				//for getting all rares using dust and packs
//#define WhileLoopCondition ((missingEpics - (dust/400)) > 0)				//for getting all epics using dust and packs
//#define WhileLoopCondition ((missingLegendaries - (dust/1600)) > 0)		//for getting all legendaries using dust and packs
#define WhileLoopCondition (PackNumber < (90+0))								//for opening ??? packs
//#define WhileLoopCondition 


#define NumberOfIterations 1000

using namespace std;

void PutIntoCollection(int CardSingle, int DustValueOfCard, int CardValue);
void PutIntoCollectionNew(int CardSingle, int DustValueOfCard, int CardValue);
void DustCard(int DustValueOfCard);
void initializeCollection();
void defineSetValues();
void printSetChoices();
void commonRareOrEpic(int CardSingle);
void printCommons();
float calculateSD();

float PackData[NumberOfIterations] = { 0 };

int RarityProbabilityNumber = 0;
int CardSingle = 0;
int DustValueOfCard = 0;
int CardValue = 0;
int setNum = -1;

int PackNumber = 0;
int MaxPackNumber = 0;
int MinPackNumber = 10000;
int TotalPackNumber = 0;

int NumberOfCommons = 0;
int NumberOfRares = 0;
int NumberOfEpics = 0;
int NumberOfLegendaries = 0;

int CardCollection[240] = { 0 };
int NumberOfCards = NumberOfCommons + NumberOfRares + NumberOfEpics + NumberOfLegendaries;

int RegularCommon = 6998;
int RegularRare = 2139;
int RegularEpic = 428;
int RegularLegendary = 108;
int RegularCards = RegularCommon + RegularRare + RegularEpic + RegularLegendary;

int GoldenCommon = 147;
int GoldenRare = 137;
int GoldenEpic = 31;
int GoldenLegendary = 11;

int OwnedCommons = 0;
int OwnedRares = 0;
int OwnedEpics = 0;
int OwnedLegendaries = 0;

int missingCommons = 0;
int missingRares = 0;
int missingEpics = 0;
int missingLegendaries = 0;

int SetValue = 0;
int CollectionValue = 0;
int dust = 0;
int totalDust = 0;

int totalCommons = 0;
int totalRares = 0;
int totalEpics = 0;
int totalLegendaries = 0;


int main(int argc, char** argv) {

	ofstream myfile;

	srand(time(0));

	while (setNum != 0)
	{
		printSetChoices();
		defineSetValues();

		cout << "\nEnter Number of Owned Commons: ";
		cin >> OwnedCommons;
		cout << "Enter Number of Owned Rares: ";
		cin >> OwnedRares;
		cout << "Enter Number of Owned Epics: ";
		cin >> OwnedEpics;
		cout << "Enter Number of Owned Legendaries: ";
		cin >> OwnedLegendaries;

		initializeCollection();

		cout << "\nSet Value = " << SetValue << endl;
		cout << "Collection Value = " << CollectionValue << endl;
		cout << "Raw Dust Needed = " << SetValue - CollectionValue << endl;

		//OLD SYSTEM
		for (int k = 0; k < NumberOfIterations; k++)
		{
			while (WhileLoopCondition)
			{
				//cout << "Current Dust: " << dust << endl;
				//cout << "Current Collection Value: " << CollectionValue << endl;
				//cout << "Still need: " << (SetValue - (CollectionValue + dust)) << endl;

				for (int i = 0; i < 5; i++)
				{
					CardSingle = 0;
					DustValueOfCard = 0;
					CardValue = 0;
					RarityProbabilityNumber = rand() % 10000 + 1;

					//IF IS REGULAR COMMON
					if (RarityProbabilityNumber <= RegularCommon)
					{
						CardSingle = rand() % NumberOfCommons;
						DustValueOfCard = 5;
						CardValue = 40;
						PutIntoCollection(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR RARE
					if (RarityProbabilityNumber > RegularCommon&& RarityProbabilityNumber <= RegularRare + RegularCommon)
					{
						CardSingle = rand() % NumberOfRares + NumberOfCommons;
						DustValueOfCard = 20;
						CardValue = 100;
						PutIntoCollection(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR EPIC
					if (RarityProbabilityNumber > RegularRare + RegularCommon && RarityProbabilityNumber <= RegularEpic + RegularRare + RegularCommon)
					{
						CardSingle = rand() % NumberOfEpics + (NumberOfRares + NumberOfCommons);
						DustValueOfCard = 100;
						CardValue = 400;
						PutIntoCollection(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR LEGENDARY
					if (RarityProbabilityNumber > RegularEpic + RegularRare + RegularCommon && RarityProbabilityNumber <= RegularCards)
					{
						CardSingle = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
						DustValueOfCard = 400;
						CardValue = 1600;
						PutIntoCollection(CardSingle, DustValueOfCard, CardValue);
					}



					//IF IS GOLDEN COMMON
					if (RarityProbabilityNumber > RegularCards&& RarityProbabilityNumber <= RegularCards + GoldenCommon)
					{
						DustValueOfCard = 50;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN RARE
					if (RarityProbabilityNumber > RegularCards + GoldenCommon && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare)
					{
						DustValueOfCard = 100;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN EPIC
					if (RarityProbabilityNumber > RegularCards + GoldenCommon + GoldenRare && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare + GoldenEpic)
					{
						DustValueOfCard = 400;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN LEGENDARY
					if (RarityProbabilityNumber > RegularCards + GoldenCommon + GoldenRare + GoldenEpic && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare + GoldenEpic + GoldenLegendary)
					{
						DustValueOfCard = 1600;
						DustCard(DustValueOfCard);
					}
				}
				PackNumber++;
			}

			PackData[k] = PackNumber;
			if (PackNumber > MaxPackNumber)
			{
				MaxPackNumber = PackNumber;
			}
			if (PackNumber < MinPackNumber)
			{
				MinPackNumber = PackNumber;
			}

			totalCommons = totalCommons + (NumberOfCommons * 2 - missingCommons);
			totalRares = totalRares + (NumberOfRares * 2 - missingRares);
			totalEpics = totalEpics + (NumberOfEpics * 2 - missingEpics);
			totalLegendaries = totalLegendaries + (NumberOfLegendaries - missingLegendaries);

			TotalPackNumber = TotalPackNumber + PackNumber;
			PackNumber = 0;
			totalDust = totalDust + dust;
			dust = 0;
			initializeCollection();
		}

		cout << "\n======OLD SYSTEM======" << endl;
		cout << "Average Pack Count: " << TotalPackNumber / NumberOfIterations << endl;
		cout << "Max pack count: " << MaxPackNumber << endl;
		cout << "Min pack count: " << MinPackNumber << endl;
		cout << "Standard Deviation: " << calculateSD() << endl;
		cout << "Average # of Commons: " << totalCommons / NumberOfIterations << "/" << NumberOfCommons * 2 << endl;
		cout << "Average # of Rares: " << totalRares / NumberOfIterations << "/" << NumberOfRares * 2 << endl;
		cout << "Average # of Epics: " << totalEpics / NumberOfIterations << "/" << NumberOfEpics * 2 << endl;
		cout << "Average # of Legendaries: " << totalLegendaries / NumberOfIterations << "/" << NumberOfLegendaries << endl;
		cout << "Average Dust: " << totalDust / NumberOfIterations;

		myfile.open("PackDataOld.csv");
		for (int i = 0; i < NumberOfIterations; i++)
		{
			myfile << PackData[i];
			myfile << "\n";
		}
		myfile.close();

		totalDust = 0;
		TotalPackNumber = 0;
		MaxPackNumber = 0;
		MinPackNumber = 10000;
		totalCommons = 0;
		totalRares = 0;
		totalEpics = 0;
		totalLegendaries = 0;
		for (int i = 0; i < NumberOfIterations; i++)
		{
			PackData[i] = 0;
		}
		dust = 0;
		PackNumber = 0;
		initializeCollection();

		//NEW SYSTEM
		for (int k = 0; k < NumberOfIterations; k++)
		{
			while (WhileLoopCondition)
			{
				//cout << "openning pack" << endl;
				for (int j = 0; j < 5; j++)
				{
					CardSingle = 0;
					DustValueOfCard = 0;
					CardValue = 0;
					RarityProbabilityNumber = rand() % 10000 + 1;

					//IF IS REGULAR COMMON
					if (RarityProbabilityNumber <= RegularCommon)
					{
						//cout << "regular common..." << endl;
						CardSingle = rand() % NumberOfCommons;
						DustValueOfCard = 5;
						CardValue = 40;
						PutIntoCollectionNew(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR RARE
					if (RarityProbabilityNumber > RegularCommon&& RarityProbabilityNumber <= RegularRare + RegularCommon)
					{
						//cout << "regular rare..." << endl;
						CardSingle = rand() % NumberOfRares + NumberOfCommons;
						DustValueOfCard = 20;
						CardValue = 100;
						PutIntoCollectionNew(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR EPIC
					if (RarityProbabilityNumber > RegularRare + RegularCommon && RarityProbabilityNumber <= RegularEpic + RegularRare + RegularCommon)
					{
						//cout << "regular epic..." << endl;
						CardSingle = rand() % NumberOfEpics + (NumberOfRares + NumberOfCommons);
						DustValueOfCard = 100;
						CardValue = 400;
						PutIntoCollectionNew(CardSingle, DustValueOfCard, CardValue);
					}
					//IF IS REGULAR LEGENDARY
					if (RarityProbabilityNumber > RegularEpic + RegularRare + RegularCommon && RarityProbabilityNumber <= RegularCards)
					{
						//cout << "regular legendary..." << endl;
						CardSingle = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
						DustValueOfCard = 400;
						CardValue = 1600;
						PutIntoCollectionNew(CardSingle, DustValueOfCard, CardValue);
					}



					//IF IS GOLDEN COMMON
					if (RarityProbabilityNumber > RegularCards&& RarityProbabilityNumber <= RegularCards + GoldenCommon)
					{
						//cout << "golden common..." << endl;
						DustValueOfCard = 50;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN RARE
					if (RarityProbabilityNumber > RegularCards + GoldenCommon && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare)
					{
						//cout << "golden rare..." << endl;
						DustValueOfCard = 100;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN EPIC
					if (RarityProbabilityNumber > RegularCards + GoldenCommon + GoldenRare && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare + GoldenEpic)
					{
						//cout << "golden epic..." << endl;
						DustValueOfCard = 400;
						DustCard(DustValueOfCard);
					}
					//IF IS GOLDEN LEGENDARY
					if (RarityProbabilityNumber > RegularCards + GoldenCommon + GoldenRare + GoldenEpic && RarityProbabilityNumber <= RegularCards + GoldenCommon + GoldenRare + GoldenEpic + GoldenLegendary)
					{
						//cout << "golden legendary..." << endl;
						DustValueOfCard = 1600;
						DustCard(DustValueOfCard);
					}
				}
				PackNumber++;
			}

			PackData[k] = PackNumber;
			if (PackNumber > MaxPackNumber)
			{
				MaxPackNumber = PackNumber;
			}
			if (PackNumber < MinPackNumber)
			{
				MinPackNumber = PackNumber;
			}

			totalCommons = totalCommons + (NumberOfCommons * 2 - missingCommons);
			totalRares = totalRares + (NumberOfRares * 2 - missingRares);
			totalEpics = totalEpics + (NumberOfEpics * 2 - missingEpics);
			totalLegendaries = totalLegendaries + (NumberOfLegendaries - missingLegendaries);

			TotalPackNumber = TotalPackNumber + PackNumber;
			PackNumber = 0;
			totalDust = totalDust + dust;
			dust = 0;
			initializeCollection();
		}

		cout << "\n\n======NEW SYSTEM======" << endl;
		cout << "Average Pack Count: " << TotalPackNumber / NumberOfIterations << endl;
		cout << "Max pack count: " << MaxPackNumber << endl;
		cout << "Min pack count: " << MinPackNumber << endl;
		cout << "Standard Deviation: " << calculateSD() << endl;
		cout << "Average # of Commons: " << totalCommons / NumberOfIterations << "/" << NumberOfCommons * 2 << endl;
		cout << "Average # of Rares: " << totalRares / NumberOfIterations << "/" << NumberOfRares * 2 << endl;
		cout << "Average # of Epics: " << totalEpics / NumberOfIterations << "/" << NumberOfEpics * 2 << endl;
		cout << "Average # of Legendaries: " << totalLegendaries / NumberOfIterations << "/" << NumberOfLegendaries << endl;
		cout << "Average Dust: " << totalDust / NumberOfIterations;

		myfile.open("PackDataNew.csv");
		for (int i = 0; i < NumberOfIterations; i++)
		{
			myfile << PackData[i];
			myfile << "\n";
		}
		myfile.close();

		totalDust = 0;
		TotalPackNumber = 0;
		MaxPackNumber = 0;
		MinPackNumber = 10000;
		totalCommons = 0;
		totalRares = 0;
		totalEpics = 0;
		totalLegendaries = 0;

		for (int i = 0; i < NumberOfIterations; i++)
		{
			PackData[i] = 0;
		}

		dust = 0;
		PackNumber = 0;
		initializeCollection();
	}
	return 0;
}





void PutIntoCollection(int CardSingle, int DustValueOfCard, int CardValue)
{
	if (CardSingle < (NumberOfEpics + NumberOfRares + NumberOfCommons))
	{
		if (CardCollection[CardSingle] < 2)
		{
			CardCollection[CardSingle]++;
			CollectionValue = CollectionValue + CardValue;
			commonRareOrEpic(CardSingle);
		}
		else
		{
			DustCard(DustValueOfCard);
		}
	}
	else
	{
		if (CardCollection[CardSingle] < 1)
		{
			CardCollection[CardSingle]++;
			CollectionValue = CollectionValue + CardValue;
			missingLegendaries--;
		}
		else
		{
			bool RoomForLegendary = false;
			for (int i = (NumberOfEpics + NumberOfRares + NumberOfCommons); i < (NumberOfLegendaries + NumberOfEpics + NumberOfRares + NumberOfCommons); i++)
			{
				if (CardCollection[i] == 0)
				{
					RoomForLegendary = true;
				}
			}
			if (RoomForLegendary == true)
			{
				int Num = 0;
				Num = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
				while (CardCollection[Num] == 1)
				{
					Num = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
				}
				CardCollection[Num]++;
				CollectionValue = CollectionValue + CardValue;
				missingLegendaries--;
			}
			else
			{
				DustCard(DustValueOfCard);
			}
		}
	}
}

void PutIntoCollectionNew(int CardSingle, int DustValueOfCard, int CardValue)
{
	//cout << "single: " << CardSingle << endl;
	if (CardSingle < (NumberOfCommons))
	{
		if (CardCollection[CardSingle] < 2)
		{
			CardCollection[CardSingle]++;
			//printCommons();
			CollectionValue = CollectionValue + CardValue;
			missingCommons--;
			//cout << missingCommons << endl;
		}
		else
		{
			bool RoomForCommon = false;
			int sum = 0;
			for (int i = 0; i < NumberOfCommons; i++)
			{
				if (CardCollection[i] != 2)
				{
					RoomForCommon = true;
				}
				//sum = sum + CardCollection[i];
				//cout << CardCollection[i] << " ";
			}
			//cout << endl << "SUM: " << sum << endl;
			if (RoomForCommon == true)
			{
				int Num = 0;
				Num = rand() % NumberOfCommons;
				while (CardCollection[Num] == 2)
				{
					Num = rand() % NumberOfCommons;
				}
				CardCollection[Num]++;
				//printCommons();
				CollectionValue = CollectionValue + CardValue;
				missingCommons--;
				//cout << missingCommons << endl;

			}
			else
			{
				//dustedCommon = true;
				//cout << "dusting common" << endl;
				DustCard(DustValueOfCard);
			}
		}
	}
	else if (CardSingle < (NumberOfRares + NumberOfCommons))
	{
		if (CardCollection[CardSingle] < 2)
		{
			CardCollection[CardSingle]++;
			CollectionValue = CollectionValue + CardValue;
			missingRares--;
		}
		else
		{
			bool RoomForRare = false;
			for (int i = (NumberOfCommons); i < (NumberOfRares + NumberOfCommons); i++)
			{
				if (CardCollection[i] != 2)
				{
					RoomForRare = true;
				}
			}
			if (RoomForRare == true)
			{
				int Num = 0;
				Num = rand() % NumberOfRares + (NumberOfCommons);
				while (CardCollection[Num] == 2)
				{
					Num = rand() % NumberOfRares + (NumberOfCommons);
				}
				CardCollection[Num]++;
				CollectionValue = CollectionValue + CardValue;
				missingRares--;
			}
			else
			{
				DustCard(DustValueOfCard);
			}
		}
	}
	else if (CardSingle < (NumberOfEpics + NumberOfRares + NumberOfCommons))
	{
		if (CardCollection[CardSingle] < 2)
		{
			CardCollection[CardSingle]++;
			CollectionValue = CollectionValue + CardValue;
			missingEpics--;
		}
		else
		{
			bool RoomForEpic = false;
			for (int i = (NumberOfRares + NumberOfCommons); i < (NumberOfEpics + NumberOfRares + NumberOfCommons); i++)
			{
				if (CardCollection[i] != 2)
				{
					RoomForEpic = true;
				}
			}
			if (RoomForEpic == true)
			{
				int Num = 0;
				Num = rand() % NumberOfEpics + (NumberOfRares + NumberOfCommons);
				while (CardCollection[Num] == 2)
				{
					Num = rand() % NumberOfEpics + (NumberOfRares + NumberOfCommons);
				}
				CardCollection[Num]++;
				CollectionValue = CollectionValue + CardValue;
				missingEpics--;
			}
			else
			{
				DustCard(DustValueOfCard);
			}
		}
	}
	else
	{
		if (CardCollection[CardSingle] < 1)
		{
			CardCollection[CardSingle]++;
			CollectionValue = CollectionValue + CardValue;
			missingLegendaries--;
		}
		else
		{
			bool RoomForLegendary = false;
			for (int i = (NumberOfEpics + NumberOfRares + NumberOfCommons); i < (NumberOfLegendaries + NumberOfEpics + NumberOfRares + NumberOfCommons); i++)
			{
				if (CardCollection[i] != 1)
				{
					RoomForLegendary = true;
				}
			}
			if (RoomForLegendary == true)
			{
				int Num = 0;
				Num = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
				while (CardCollection[Num] == 1)
				{
					Num = rand() % NumberOfLegendaries + (NumberOfEpics + NumberOfRares + NumberOfCommons);
				}
				CardCollection[Num]++;
				CollectionValue = CollectionValue + CardValue;
				missingLegendaries--;
			}
			else
			{
				DustCard(DustValueOfCard);
			}
		}
	}
}

void DustCard(int DustValueOfCard)
{
	dust = dust + DustValueOfCard;
}

void initializeCollection()
{
	CollectionValue = OwnedCommons * 40 + OwnedRares * 100 + OwnedEpics * 400 + OwnedLegendaries * 1600;

	for (int i = 0; i < (NumberOfCommons + NumberOfRares + NumberOfEpics + NumberOfLegendaries); i++)
	{
		CardCollection[i] = 0;
	}

	int x = OwnedCommons / 2;
	for (int i = 0; i < x; i++)
	{
		CardCollection[i] = 2;
	}
	if (x * 2 != OwnedCommons)
	{
		CardCollection[NumberOfCommons - 1] = 1;
	}

	int y = OwnedRares / 2;
	for (int i = NumberOfCommons; i < y + NumberOfCommons; i++)
	{
		CardCollection[i] = 2;
	}
	if (y * 2 != OwnedRares)
	{
		CardCollection[NumberOfRares + NumberOfCommons - 1] = 1;
	}

	int z = OwnedEpics / 2;
	for (int i = (NumberOfRares + NumberOfCommons); i < z + (NumberOfRares + NumberOfCommons); i++)
	{
		CardCollection[i] = 2;
	}
	if (z * 2 != OwnedEpics)
	{
		CardCollection[NumberOfEpics + NumberOfRares + NumberOfCommons - 1] = 1;
	}

	for (int i = (NumberOfEpics + NumberOfRares + NumberOfCommons); i < (OwnedLegendaries + NumberOfEpics + NumberOfRares + NumberOfCommons); i++)
	{
		CardCollection[i] = 1;
	}

	missingCommons = NumberOfCommons * 2 - OwnedCommons;
	//cout << "missing commons: " << missingCommons << endl;
	missingRares = NumberOfRares * 2 - OwnedRares;
	missingEpics = NumberOfEpics * 2 - OwnedEpics;
	missingLegendaries = NumberOfLegendaries - OwnedLegendaries;

}

void defineSetValues()
{
	switch (setNum)
	{
	case 0:
		exit(1);
	case 1: //classic
		NumberOfCommons = 92;
		NumberOfRares = 80;
		NumberOfEpics = 36;
		NumberOfLegendaries = 32;
		break;
	case 2: //gvg
		NumberOfCommons = 40;
		NumberOfRares = 37;
		NumberOfEpics = 26;
		NumberOfLegendaries = 20;
		break;
	case 3: //grand tourny
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 20;
		break;
	case 4: //old gods
		NumberOfCommons = 50;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 21;
		break;
	case 5: //gadgetzan
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 20;
		break;
	case 6: //un'goro
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 23;
		break;
	case 7: //frozen throne
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 23;
		break;
	case 8: //kobolds
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 23;
		break;
	case 9: //witchwood
		NumberOfCommons = 48;
		NumberOfRares = 35;
		NumberOfEpics = 25;
		NumberOfLegendaries = 21;
		break;
	case 10: //boomsday
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 24;
		break;
	case 11: //rumble
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 23;
		break;
	case 12: //rise of shadows
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 24;
		break;
	case 13: //uldum
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 23;
		break;
	case 14: //dragons
		NumberOfCommons = 49;
		NumberOfRares = 36;
		NumberOfEpics = 27;
		NumberOfLegendaries = 28;
		break;
	case 15: //outland
		NumberOfCommons = 52;
		NumberOfRares = 35;
		NumberOfEpics = 23;
		NumberOfLegendaries = 25;
		break;
	}
	SetValue = NumberOfCommons * 2 * 40 + NumberOfRares * 2 * 100 + NumberOfEpics * 2 * 400 + NumberOfLegendaries * 1600;
}

void printSetChoices()
{
	cout << "\n\n========Sets==========" << endl;
	cout << "======Classic[1]======" << endl;
	cout << "=Goblins vs Gnomes[2]=" << endl;
	cout << "==Grand Tournament[3]=" << endl;
	cout << "======Old Gods[4]=====" << endl;
	cout << "=====Gadgetzan[5]=====" << endl;
	cout << "======Un'Goro[6]======" << endl;
	cout << "===Frozen Throne[7]===" << endl;
	cout << "======Kobolds[8]======" << endl;
	cout << "=====Witchwood[9]=====" << endl;
	cout << "=====Boomsday[10]=====" << endl;
	cout << "======Rumble[11]======" << endl;
	cout << "==Rise of Shadows[12]=" << endl;
	cout << "=======Uldum[13]======" << endl;
	cout << "======Dragons[14]=====" << endl;
	cout << "======Outland[15]=====" << endl;
	cout << "========EXIT[0]=======" << endl;
	cout << "Enter a set(Number): ";

	cin >> setNum;

	while (setNum < 0 || setNum > 15)
	{
		cout << "Not a set" << endl << "Enter a set(Number): ";
		cin >> setNum;
	}
}

void commonRareOrEpic(int CardSingle)
{
	if (CardSingle < NumberOfCommons)
	{
		missingCommons--;
	}
	else if (CardSingle < (NumberOfCommons + NumberOfRares))
	{
		missingRares--;
	}
	else
	{
		missingEpics--;
	}
}

void printCommons()
{
	int sum = 0;
	for (int i = 0; i < NumberOfCommons; i++)
	{
		cout << CardCollection[i] << " ";
		sum = CardCollection[i] + sum;
	}
	cout << endl << "SUM: " << sum << endl << "TOTAL: " << sum + missingCommons << endl;
}

float calculateSD()
{
	float sum = 0.0, mean, standardDeviation = 0.0;

	int i;

	for (i = 0; i < 10; ++i)
	{
		sum += PackData[i];
	}

	mean = sum / 10;

	for (i = 0; i < 10; ++i)
		standardDeviation += pow(PackData[i] - mean, 2);

	return sqrt(standardDeviation / 10);
}