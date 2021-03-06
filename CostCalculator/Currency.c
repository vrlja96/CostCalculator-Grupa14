#define _CRT_SECURE_NO_WARNINGS
#include "Currency.h"

Currency * readAllCurrencies(int * numOfCurrencies)
{
	FILE *currencyFile = fopen("currency.txt", "r");
	if (!currencyFile)
	{
		printf("Can not open \"currency.txt\" .");
		Sleep(2000);
		return NULL;
	}
	int numberOfCurrencies = 0, temp = 1;
	Currency *currencies = (Currency *)calloc(temp, sizeof(Currency));
	while (fscanf(currencyFile, "%s %lf\n", currencies[numberOfCurrencies].currency, &currencies[numberOfCurrencies].currencyRate) != EOF)
	{
		if (++numberOfCurrencies == temp)
			currencies = (Currency *)realloc(currencies, sizeof(Currency) * (temp *= 2));
	}
	if (numberOfCurrencies == 0)
	{
		*numOfCurrencies = 0;
		return NULL;
	}
	currencies = (Currency *)realloc(currencies, sizeof(Currency) * numberOfCurrencies);
	*numOfCurrencies = numberOfCurrencies;
	fclose(currencyFile);
	return currencies;
}

void addNewCurrency()
{
	int numberOfCurrencies;
	Currency newCurrency, *currencies = readAllCurrencies(&numberOfCurrencies);
	FILE *currencyFile = fopen("currency.txt", "a+");
	if (!currencyFile)
	{
		printf("Error. Can not open \"currency.txt\" ");
		Sleep(2000);
		return;
	}
	printf("Adding new Currency.\nName (3 characters): ");
	scanf("%s", newCurrency.currency);
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		if (!strcmp(currencies[i].currency, newCurrency.currency))
		{
			printf("Currency Rate: ");
			scanf("%lf", &newCurrency.currencyRate);
			if (newCurrency.currencyRate == currencies[i].currencyRate)
			{
				printf("Error! Currency with same rate already exist.");
				Sleep(2000);
				fclose(currencyFile);
				return;
			}
			printf("Currency already exists. Updating currency rate.");
			Sleep(2000);
			fclose(currencyFile);
			updateCurrencyRate(&newCurrency);
			return;
		}
	}
	printf("Currency Rate: ");
	scanf("%lf", &newCurrency.currencyRate);
	printf("Currency added.\n");
	Sleep(2000);
	fprintf(currencyFile, "%-4s %-5.2lf\n", newCurrency.currency, newCurrency.currencyRate);
	fclose(currencyFile);
}


void updateCurrencyRate(Currency *currency)
{
	int numberOfCurrencies;
	Currency *currencies = readAllCurrencies(&numberOfCurrencies), toUpdateCurrency;
	if (currency)
	{
		for (int i = 0; i < numberOfCurrencies; ++i)
		{
			if (!strcmp(currencies[i].currency, currency->currency))
			{
				currencies[i].currencyRate = currency->currencyRate;
				break;
			}
		}
		printCurrenciesInFile(currencies, numberOfCurrencies);
		return;
	}
	printf("Enter Currency you want to update: ");
	scanf("%s", toUpdateCurrency.currency);
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		if (!strcmp(toUpdateCurrency.currency, currencies[i].currency))
		{
			printf("Enter new Rate for %s: ", currencies[i].currency);
			scanf("%lf", &toUpdateCurrency.currencyRate);
			if (toUpdateCurrency.currencyRate == currencies[i].currencyRate)
			{
				printf("Error! Same Rate! Exiting");
				Sleep(2000);
				return;
			}
			currencies[i].currencyRate = toUpdateCurrency.currencyRate;
			printf("Updating successful");
			printCurrenciesInFile(currencies, numberOfCurrencies);
			Sleep(2000);
			return;
		}
	}
	char answer;
	getchar();
	printf("%s does not exist. Do you want to add it[Y/N]", toUpdateCurrency.currency);
	scanf("%c", &answer);
	if (answer == 'Y' || answer == 'y')
	{
		addNewCurrency();
		return;
	}
	return;
}

void printCurrenciesInFile(Currency *currencies, int numberOfCurrencies)
{
	FILE *file = fopen("currency.txt", "w");
	if (!file)
	{
		printf("Error! Can not open currency file");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		fprintf(file, "%-4s %-5.2lf\n", currencies[i].currency, currencies[i].currencyRate);
	}
	fclose(file);
}


int changeCurrency()
{
	int numberOfCurrencies;
	char currency[10] = { 0 };
	Currency *currencies = readAllCurrencies(&numberOfCurrencies);
	printAllCurrencies();
	printf("Input Currency Name (3 characters): ");
	scanf("%s", &currency);
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		if (!strcmp(currency, currencies[i].currency))
		{
			strcpy(currentCurrency.currency, currency);
			currentCurrency.currencyRate = currencies[i].currencyRate;
			printf("Currency changed.\n");
			Sleep(2000);
			return 1;
		}
	}
	printf("No such Currency in currency list.");
	Sleep(2000);
	return 0;
}

int removeCurrency()
{
	char name[10] = { 0 };
	int numberOfCurrencies;
	printf("Enter Currency Name you want to remove: ");
	scanf("%s", name);
	if (!strcmp(name, "BAM"))
	{
		printf("You can not remove BAM. It is default currency.");
		return 0;
	}
	Currency *currencies = readAllCurrencies(&numberOfCurrencies);
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		if (!strcmp(currencies[i].currency, name))
		{
			for (int j = i; j < numberOfCurrencies - 1; ++j)
			{
				currencies[j] = currencies[j + 1];
			}
			printCurrenciesInFile(currencies, numberOfCurrencies - 1);
			printf("Currency removed.");
			Sleep(2000);
			return 1;
		}
	}
	printf("No such currency in file.");
	Sleep(2000);
	return 0;
}

void printAllCurrencies()
{
	int numberOfCurrencies;
	Currency *currencies = readAllCurrencies(&numberOfCurrencies);
	printf("Avalivable Currencies (%d):\n", numberOfCurrencies);
	for (int i = 0; i < numberOfCurrencies; ++i)
	{
		printf("%-3s %5.2lf\n", currencies[i].currency, currencies[i].currencyRate);
	}
}
