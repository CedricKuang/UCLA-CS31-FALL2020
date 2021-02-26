#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include <cassert>
using namespace std;
const int MAX_WORD_LENGTH = 20;
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules);
int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1], const char wordout[][MAX_WORD_LENGTH+1], int nRules);

int main()
{
	const int TEST1_NRULES = 3;
	char test1win[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"family", "unhappy", "horse",
	};
	char test1wout[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"",       "horse",   "",
	};
	assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
		test1win, test1wout, TEST1_NRULES) == 2);
	assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
		test1win, test1wout, TEST1_NRULES - 1) == 0);
	assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
		test1win, test1wout, TEST1_NRULES) == 1);
	assert(determineScore("A horse!  A horse!  My kingdom for a horse!",
		test1win, test1wout, TEST1_NRULES) == 1);
	assert(determineScore("horse:stable ratio is 10:1",
		test1win, test1wout, TEST1_NRULES) == 0);
	assert(determineScore("**** 2020 ****",
		test1win, test1wout, TEST1_NRULES) == 0);
	assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
		test1win, test1wout, -1) == 0);
	const int nRules = 12;
	char wordin[12][21] = { "conf@@sion", "FAMILY", "charm", "hearty", "house", "worn-out", "family", "charm", "ties", "", "charm", "FaMiLy" };
	char wordout[12][21] = { "", "TIES", "confusion", "hearty", "intrigue", "younger", "first", "", "family", "frightened", "", "tIeS" };
	assert(cleanupRules(wordin, wordout, nRules) == 5);
	assert(cleanupRules(wordin, wordout, -3) == 0);
	cout << "All tests succeeded" << endl;
}

int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
	if (nRules < 0)		/*treat negative nRules as zero*/
		nRules = 0;

	for (int i = 0; i < nRules; i++)    /*a for loop which visits all the string in both wordin and wordout (same as follows)*/
	{
		for (int m = 0; m < strlen(wordin[i]); m++)     /*a for loop which visits charcters in a particular string in wordin*/
		{
			if (!(isalpha(wordin[i][m])))               /*if this string conatins character that is not alphabetic, eleminate it and the string in wordout with corresponding position*/
			{
				strcpy(wordin[i], "");
				strcpy(wordout[i], "");
			}
		}
		for (int m = 0; m < strlen(wordout[i]); m++)   /*a for loop which visits charcters in a particular string in wordout*/
		{
			if (!(isalpha(wordout[i][m])))             /*if this string conatins character that is not alphabetic, eleminate it and the string in wordin with corresponding position*/
			{
				strcpy(wordin[i], "");
				strcpy(wordout[i], "");
			}
		}
	}

	for (int i = 0; i < nRules; i++)
	{
		for (int m = 0; m < strlen(wordin[i]); m++)   /*convert all the characters of strings in wordin into lower case*/
		{
			if (isupper(wordin[i][m]))
				wordin[i][m] = tolower(wordin[i][m]);
		}
	    for (int m = 0; m < strlen(wordout[i]); m++)  /*convert all the characters of strings in wordout into lower case*/
		{
			if (isupper(wordout[i][m]))
				wordout[i][m] = tolower(wordout[i][m]);
		}
	}

	for (int i = 0; i < nRules; i++)
	{
		if (strcmp(wordin[i], wordout[i]) == 0 && strcmp(wordin[i], "") != 0 && strcmp(wordout[i], "") != 0)   /*if strings at the same position in wordin and wordout are the same, eliminate both of them*/
		{
			strcpy(wordin[i], "");
			strcpy(wordout[i], "");
		}

		if (strcmp(wordin[i], "") == 0 && strcmp(wordout[i], "") != 0)   /*if the string in wordout has no corresponding string in wordin at the same position, eliminate it*/
			strcpy(wordout[i], "");
	}

	for (int i = 0; i < nRules; i++)
	{
		if (strcmp(wordin[i], "") != 0 && strcmp(wordout[i], "") == 0)    /*if one-word rule has the same win as other rules, leaving just one instance of one-word rule*/
		{
			for (int m = 0; m < nRules; m++)
			{
				if (strcmp(wordin[i], wordin[m]) == 0 && m != i)
				{
					strcpy(wordin[m], "");
					strcpy(wordout[m], "");
				}
			}
		}
	}

	for (int i = 0; i < nRules; i++)
	{
		for (int m = 0; m < nRules; m++)     /*if two or moe than two two-word rules are indentical, leaving just one of them*/
		{
			if (strcmp(wordin[i], wordin[m]) == 0 && strcmp(wordout[i], wordout[m]) == 0 && i != m)
			{
				strcpy(wordin[m], "");
				strcpy(wordout[m], "");
			}
		}
	}
	/*all the processes above are to adjust the array into "clean form"*/

	for (int i = 0; i < nRules; i++)        /*this loop is to push all the strings in an array that are not empty to the front, and all those empty strings to the back*/
	{
		if (strcmp(wordin[i], "") == 0 && strcmp(wordout[i], "") == 0)     /*find a position in which the string in both wordin and wordout are empty*/
		{
			int m = i;
			while (m < nRules && strcmp(wordin[m], "") == 0 && strcmp(wordout[m], "") == 0)    /*keep finding the string that is not empty*/
				m++;
			if (m < nRules)
			{
				strcpy(wordin[i], wordin[m]);     /*assign the empty string at i with the non empty string at m*/
				strcpy(wordout[i], wordout[m]);
				strcpy(wordin[m], "");           /*eliminating the string at m*/
				strcpy(wordout[m], "");
			}
		}
	}

	for (int i = 0; i < nRules; i++)
	{
		if (strcmp(wordin[i], "") == 0 && strcmp(wordout[i], "") == 0)    /*find a position in which the string in both wordin and wordout are empty*/
			return i;	/*return the position i, which indicates the final number of elements in both wordin and wordout after the adjustment*/
	}

	return nRules;
}

int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH + 1], const char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
	char document2[251] = "";     /*create a new cstring named "document2"*/
	int m = 0;
	for (int i = 0; document[i] != '\0'; i++)       /*make document2 a copy of document, only including the alphabetic characters and spaces*/
	{
		if (isalpha(document[i]) || isspace(document[i]))
		{
			document2[m] = tolower(document[i]);
			m++;
		}
	}

	int countScore = 0;
	for (int i = 0; i < nRules; i++)     /*this for loop is to count the score that document can get*/
	{
		if (strcmp(wordout[i], "") == 0 && strcmp(wordin[i], "") != 0)      /*count score for one-word rule*/
		{
			int m = 0;
			while (document2[m] != '\0')        /*keep making copy of each word in the sentence in document2*/
			{
				char temp[251];
				int n = 0;
				while (document2[m] != ' ' && document2[m] != '\0')     /*making copy chracter by character until encounter a sapce or '/0'*/
				{
					temp[n] = document2[m];
					m++;
					n++;
				}
				temp[n] = '\0';
				if (strcmp(wordin[i], temp) == 0)     /*compare the copy with wordin. If they are identical, increase the score by one*/
				{
					countScore++;
					break;
				}
				while (document2[m] == ' ')
					m++;
			}
		}
		else if (strcmp(wordout[i], "") != 0 && strcmp(wordin[i], "") != 0)		/*count score for two-word rule*/
		{
			bool in = false;
			bool out = true;
			int m = 0;
			while (document2[m] != '\0')	/*same as one-word rule. keep making copy*/
			{
				char temp[251];
				int n = 0;
				while (document2[m] != ' ' && document2[m] != '\0')
				{
					temp[n] = document2[m];
					m++;
					n++;
				}
				temp[n] = '\0';
				if (strcmp(wordin[i], temp) == 0)    /*if the copy and wordin are identical, set in to true*/
					in = true;
				else if (strcmp(wordout[i], temp) == 0)    /*if the copy and wordout are identical, set out to false*/
					out = false;
				while (document2[m] == ' ')
					m++;
			}
			if (in && out)       /*only when in and out are both true and score increases by one*/
				countScore++;
		}
	}
	return countScore;
}
