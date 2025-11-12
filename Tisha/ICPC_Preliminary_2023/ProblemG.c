/*
Given a string that represents the outcome of each ball bowled by a bowler.
Each character in the string is either:

'W' → the bowler takes a wicket, or

'0'–'6' → the number of runs conceded on that ball.

Task is to calculate and print the bowler’s bowling figures in the format
*/


#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T); 

    for (int cas = 1; cas <= T; cas++) {
        char S[100];
        scanf("%s", S);

        int balls = strlen(S);
        int runs = 0, wickets = 0;

        // count runs and wickets
        for (int i = 0; i < balls; i++) {
            if (S[i] == 'W')
                wickets++;
            else
                runs += (S[i] - '0');
        }

        int overs = balls / 6;
        int extra_balls = balls % 6;

        // print result
        printf("%d.%d over", overs, extra_balls);
        if (balls > 6 || overs > 1 || (overs == 1 && extra_balls == 0)) printf("s");

        printf(" %d run", runs);
        if (runs != 1) printf("s");

        printf(" %d wicket", wickets);
        if (wickets != 1) printf("s");

        printf("\n");
    }

    return 0;
}
