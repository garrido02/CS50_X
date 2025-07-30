#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letter(string input);
int count_words(string input);
int count_sentences(string input);
float grade_count(int count_letter, int count_words, int count_sentences);

//round - code to round to nearest integer
//output 16+ for index 16 or higher ;  output before grade 1 if less than 1;


int main(void)
{

    string s = get_string("Text: "); //prompt input

    int letters = count_letter(s); //count letters, sentences and words



    int words = count_words(s);


    int sentences = count_sentences(s);


    float index = grade_count(letters, words, sentences); //count grade
    if (index >= 16) //prepare printing
    {
        printf("Grade 16+\n");
        return 0;
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else
    {
        printf("Grade %.0f\n", index);
        return 0;
    }

}




int count_letter(string input) //count the number of letters
{
    int total_letters = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (isalpha(input[i])) //only if is alphabetical
        {
            total_letters += 1;
        }
    }
    return total_letters;
}



int count_words(string input) //count the nr of words
{
    int total_words = 1;
    for (int j = 0; j < strlen(input); j++)
    {
        if (isblank(input[j])) //only if the char is a space
        {
            total_words += 1;
        }
    }
    return total_words;
}



int count_sentences(string input) //count sentences
{
    int total_sentences = 0;
    for (int k = 0; k < strlen(input); k++)
    {
        if ((input[k] == '!' || input[k] == '?' || input[k] == '.')) //only if char is punct like . or ! or ?
        {
            total_sentences += 1;
        }
    }
    return total_sentences;
}


float grade_count(int letters, int words, int sentences)
{
    float L = ((float) letters / (float) words * 100);
    float S = ((float) sentences / (float) words * 100);

    float grade = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f\n", grade);

    return round(grade);
}