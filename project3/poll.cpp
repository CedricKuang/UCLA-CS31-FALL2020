
#include <iostream>
#include <string>
using namespace std;

bool isSyntacticallyCorrect(string pollData);  /*three function prototypes*/
bool isStateCodeCorrect(string pollData, int& k);
int tallyVotes(string pollData, char party, int& voteTally);


int main()
{
    string pollData;           /*setting up basic variables, including poll data, party code, and tallied vote.*/
    char party;
    int voteTally = 0;

    cout << "Please enter a poll data:\n";   /*ask user to enter poll data and party code*/
    getline(cin, pollData);
    cout << "Please enter a party code:\n";
    cin.get(party);

    int n = tallyVotes(pollData, party, voteTally);                 /*get the return value from the function. output the answer or special situation.*/
    if (n == 1)
        cout << "You did not enter a correct poll data string.\n";   
    else if (n == 2)
        cout << "Your party code is not a letter.\n";
    else if (n == 3)
        cout << "At least one state forecast predicts zero electoral votes for that state in your poll data.\n";
    else
        cout << "The number of electoral votes that the poll data string predicts the candidate of party " << party << " will be " << voteTally << endl;
    return 0;
}

bool isSyntacticallyCorrect(string pollData)  /*this function is used to test whether the poll data is in the correct format*/
{
    int k = 0;
    if (pollData.size() == 0) /*empty string is valid*/
        return true;
    if (pollData.size() < 4)  /*test whether poll data contains at least 4 elements*/
        return false;
    while (k < pollData.size())      /*this while loop divide the string into sevral set. each set has 4 or 5 elements, which is one poll estimation.*/
    {
        if (isdigit(pollData[k]))  /*the first element must be a digit*/
            k++;
        else
            return false;

        if (isdigit(pollData[k]))  /*the second element could be wither a digit or character */
        {
            k++;
            if (isStateCodeCorrect(pollData, k)) /*check if these two character are valid state code*/
                k = k + 2;
            else
                return false;
        }
        else if (isStateCodeCorrect(pollData, k))
            k = k + 2;
        else
            return false;

        if (isalpha(pollData[k])) /*the forth or fifth element must be a character*/
            k++;
        else
            return false;
    }
    return true;
}

bool isStateCodeCorrect(string pollData, int& k) /*this function is used to check whether the two characters are valid state code*/
{
    string state[204] = { "al", "Al", "aL", "AL", "ak", "Ak", "aK", "AK", "az", "Az", "aZ", "AZ", "ar", "Ar", "aR", "AR", "ca", "Ca", "cA", "CA", "co", "cO", "Co", "CO","ct", "cT", "Ct", "CT", "de",
    "dE", "De", "DE", "dc", "dC", "Dc", "DC", "fl", "fL", "Fl", "FL", "ga", "gA", "Ga", "GA", "hi", "hI", "Hi", "HI", "id", "iD", "Id", "ID", "il", "iL", "Il", "IL", "in", "iN", "In", "IN", "ia", "iA", "Ia", "IA",
    "ks", "kS", "Ks", "KS", "ky", "kY", "Ky", "KY", "la", "lA", "La", "LA", "me", "mE", "Me", "ME", "md", "mD", "Md", "MD", "ma", "mA", "Ma", "MA", "mi", "mI", "Mi", "MI", "mn", "mN", "Mn", "MN", "ms", "mS", "Ms", "MS",
    "mo", "mO", "Mo", "MO", "mt", "mT", "Mt", "MT", "ne", "nE", "Ne", "NE", "nv", "nV", "Nv", "NV", "nh", "nH", "Nh", "NH", "nj", "nJ", "Nj", "NJ", "nm", "nM", "Nm", "NM", "ny", "nY", "Ny", "NY", "nc", "nC", "Nc", "NC",
    "nd", "nD", "Nd", "ND", "oh", "oH", "Oh", "OH", "ok", "oK", "Ok", "OK", "or", "oR", "Or", "OR", "pa", "pA", "Pa", "PA", "ri", "rI", "Ri", "RI", "sc", "sC", "Sc", "SC", "sd", "sD", "Sd", "SD", "tn", "tN", "Tn", "TN",
    "tx", "tX", "Tx", "TX", "ut", "uT", "Ut", "UT", "vt", "vT", "Vt", "VT", "va", "vA", "Va", "VA", "wa", "wA", "Wa", "WA", "wv", "wV", "Wv", "WV", "wi", "wI", "Wi", "WI", "wy", "wY", "Wy", "WY" };
    /*an array of strings that contains all possibilities of state codes*/
    string test = pollData.substr(k, 2);  /*cut two characters off the original string*/
    if (!(isalpha(test[0])) || !(isalpha(test[1])))  /*two charcters both must be character*/
        return false;
    int i = 0;
    while (test != state[i] && i < 204)  /*test whether it is in state code array*/
        i++;
    if (i == 204)
        return false;
    else
        return true;
}

int tallyVotes(string pollData, char party, int& voteTally) /*this function is used to tally the vote for a particular party.*/
{
    
    if (!(isSyntacticallyCorrect(pollData))) /*poll data must be in correct format*/  /*for returning 1 2 3, the function left the parameter unchanged*/
        return 1;
    
    if (!(isalpha(party))) /*party code must be valid*/
        return 2;
  
    if ((pollData[0] == '0' && pollData[1] == '0') || (pollData[0] == '0' && isalpha(pollData[1]))) /*there must not be zero vote for one party*/
        return 3;

    int n = pollData.find('0', 1);
    while (n != string::npos && n <= pollData.size())
    {
        if ((isalpha(pollData[n - 1]) && isalpha(pollData[n + 1])) || pollData[n+1] == '0')
            return 3;
        else
            n = pollData.find('0', n + 1);
    }

    voteTally = 0;
    if (pollData.size() == 0) /*if the poll data is empty, let voteTally = 0 and skip all the rest process*/
        return 0;

    char party2;    /*"party" will have both upper and lower case format*/
    if (islower(party))
        party2 = toupper(party);
    else if (isupper(party))
        party2 = tolower(party);

    char ch = '0';       /*tallying the votes for the particular party*/
    const int base = ch;         /*to convert the string to integer, we must subtract the "base" from the ASCII code of the specific character*/
    if ((pollData[3] == party || pollData[3] == party2) && isalpha(pollData[2]) && isalpha(pollData[1]))
        voteTally += (int(pollData[0]) - base);
    else if ((pollData[4] == party || pollData[4] == party2) && isalpha(pollData[3]) && isalpha(pollData[2]))
        voteTally += (10 * (int(pollData[0]) - base) + (int(pollData[1]) - base));
    int j = 5;
    int x = pollData.find(party, j);
    int y = pollData.find(party2, j);
    while (x != string::npos && x <= pollData.size())       /*finding the first case of the party code (upper/lower)*/
    {
        if (isalpha(pollData[x - 1]) && isalpha(pollData[x - 2]))      /*two characters before the party code must both be characters*/
        {
            if (isdigit(pollData[x - 3]) && isdigit(pollData[x - 4]))   /*vote has two digits*/
            {
                voteTally += (10 * (int(pollData[x - 4]) - base)) + (int(pollData[x - 3]) - base);
                x = pollData.find(party, x + 1);
            }
            else    /*vote has two digits*/
            {
                voteTally += (int(pollData[x - 3]) - base);
                x = pollData.find(party, x + 1);
            }
        }
    }
    while (y != string :: npos && y <= pollData.size())  /*finding the other case of the party code. the rest is the same*/
    {
        if (isalpha(pollData[y - 1]) && isalpha(pollData[y - 2]))
        {
            if (isdigit(pollData[y - 3]) && isdigit(pollData[y - 4]))
            {
                voteTally += (10 * (int(pollData[y - 4]) - base)) + (int(pollData[y - 3]) - base);
                y = pollData.find(party, y + 1);
            }
            else
            {
                voteTally += (int(pollData[y - 3]) - base);
                y = pollData.find(party, y + 1);
            }
        }
    }
    return 0;
}