#include <stdio.h>
int p[5], ch[5];    //p means philosopher and ch means chopstics
void signal(int i)
{
    int j = (i + 1) % 5;
    p[i] = 0;
    ch[i] = 0;
    ch[j] = 0;
}
void wait(int i)
{
    int right = (i + 1) % 5;
    if (ch[i] == 0 && ch[right] == 0)
    {
        p[i] = 1;
        ch[i] = 1;
        ch[right] = 1;
    }
    else if (p[i] == 1)
    {
        int w;
        printf("Do you want philosopher %d to stop eating: ", i);
        scanf("%d", &w);
        if (w == 1)
            signal(i);
    }
    else
    {
        printf("Chopsticks %d %d are busy\nPhilosopher %d waits\n", i, right, i);
    }
}
int main()
{
    int user, philo;
    for (int i = 0; i < 5; i++)
        p[i] = 0, ch[i] = 0;
    do
    {
        for (int i = 0; i < 5; i++)
        {
            printf("%d %s\n", i, p[i] == 0 ? "Thinking" : "Eating");
        }
        printf("Who wants to eat: ");
        scanf("%d", &philo);
        wait(philo);
        printf("Want to continue? Press 1: ");
        scanf("%d", &user);
    } while (user == 1);
    return 0;
}