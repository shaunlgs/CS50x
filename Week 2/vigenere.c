
int main (int argc, char* argv[])
{
    bool isWord;
    string k;
    string p;
    int j = 0;
    int key;

    /* check if user inputs 2 command line arguments
       and the second command line argument (the keyword) is a word */
    if (argc != 2)
    {
        printf("Usage: /home/cs50/pset2/vigenere <keyword>\n");
        return 1;
    }
    else
    {
        for (int i = 0, j = strlen(argv[1]); i < j; i++)
        {
            isWord = isalpha(argv[1][i]);
        }
        if (isWord == false)
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        }
    }

    // store user keyword
    k = argv[1];

    // get user plaintext
    p = GetString();

    // loop over each character in the plaintext
    for (int i = 0, m = strlen(p); i < m; i++)
    {
        if (isalpha(p[i]))
        {
            // turn vigenere keyword's character into alphabetical index 0 to 26
            j = j % strlen(k);
            if (isupper(k[j]))
            {
                key = k[j] - 'A';
            }
            else
            {
                key = k[j] - 'a';
            }
            if (isupper(p[i]))
            {
                // turn alphabet from ascii to alphabetical index 0 to 26, then execute vigenere cipher
                p[i] = (p[i] - 'A' + key) % 26;
                // turn alpabet from alphabetical index back to ascii
                p[i] = p[i] + 'A';
                j++;
            }
            else
            {
                // turn alphabet from ascii to alphabetical index 0 to 26, then execute vigenere cipher
                p[i] = (p[i] - 'a' + key) % 26;
                // turn alpabet from alphabetical index back to ascii
                p[i] = p[i] + 'a';
                j++;
            }
        }
    }
    // print enciphered plaintext
    for (int i = 0, m = strlen(p); i < m; i++)
    {
        printf("%c", p[i]);
    }
    printf("\n");

}
