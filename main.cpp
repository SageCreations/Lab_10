#include <iostream>
#include <iomanip>

using namespace std;

void insertion(int frame, int data, int x[10])
{
    x[frame-1] = data;
}

void scoreCard(const int r1[], const int r2[], int sc[])
{
    //************************** logic ****************************
    for (int i = 0; i < 10; i++)
    {
        if (i > 0) {
            if (r1[i] == 10) {
                if (r1[i + 1] == 10)
                    sc[i] = sc[i - 1] + 10 + r1[i + 1] + r1[i + 2];
                else sc[i] = sc[i - 1] + 10 + r1[i + 1] + r2[i + 1];
            } else if (r1[i] + r2[i] == 10) {
                sc[i] = sc[i - 1] + 10 + r1[i + 1];
            } else sc[i] = sc[i - 1] + r1[i] + r2[i];
        }
        else {
            if (r1[i] == 10) {
                if (r1[i + 1] == 10)
                    sc[i] =  10 + r1[i + 1] + r1[i + 2];
                else sc[i] = 10 + r1[i + 1] + r2[i + 1];
            } else if (r1[i] + r2[i] == 10) {
                sc[i] = 10 + r1[i + 1];
            } else sc[i] = r1[i] + r2[i];
        }
    }
    //****************************** display ************************************
    cout << "\n\n  Frame  -";
    for (int i = 0; i < 10; i++)
        cout << setw(5) << i+1;

    cout << setw(4) << " Xtr-1 Xtr-2";

    cout << "\nBall - 1 :";
    if (r1[10] != 0 && r1[11] != 0) {
        for (int i = 0; i < 12; i++)
            cout << setw(5) << r1[i];
    }
    else if (r1[10] != 0 && r1[11] == 0) {
        for (int i = 0; i < 11; i++)
            cout << setw(5) << r1[i];
    }
    else {
        for (int i = 0; i < 10; i++)
            cout << setw(5) << r1[i];
    }

    cout << "\nBall - 2 :";
    for (int i = 0; i < 10; i++)
        cout << setw(5) << r2[i];

    cout << "\n  Score : ";
    for (int i = 0; i < 10; i++)
        cout << setw(5) << sc[i];
}

int main() {
    char more;
    int pinsHit, pinsLeft;
//*************************Frame Looping******************************************
    do {
        int row1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int row2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int score[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        cout << "\n\tWelcome to Blinn Bowling Center";
        for (int i = 1; i <= 10; i++)
        {
            cout << "\nFrame - " << i;
            pinsLeft = 10;
            for (int j = 1; j <= 2; j++) {
                cout << "\n\tBall - " << j << " : ";
                cin >> pinsHit;

                if (pinsHit < 0 || pinsHit > 10) {
                    cout << "\t\t\tIllegal score, do one more time...(1)";
                    --j;
                } else if (pinsHit == 10) {
                    cout << "\t\tCongratulation!  It is STRIKE...";
                    insertion(i, 10, row1);
                    insertion(i, 0, row2);
                    break;
                } else {
                    int original = pinsLeft;
                    pinsLeft -= pinsHit;

                    if (pinsLeft < 0) {
                        cout << "\t\t\tIllegal score, do one more time...";
                        pinsLeft = original;
                        --j;
                    } else {
                        if (pinsLeft == 0) {
                            cout << "\t\tNot bad, it is SPARE...";
                            insertion(i, pinsHit, row2);
                            break;
                        } else if (j == 2) {
                            cout << "\t\tNeed work harder, Dude!";
                            insertion(i, pinsHit, row2);
                        }
                    }
                    if (j == 1)
                        insertion(i, pinsHit, row1);
                }
            }
            //*********************************EXTRA HANDLING*************************
            if (i == 10) {
                if (row1[i-1] == 10) {
                    for (int j = 11; j <= 12; j++) {
                        cout << "\n\tExtra - " << j << " : ";
                        cin  >> pinsHit;

                        if (pinsHit < 0 || pinsHit > 10) {
                            cout << "\t\t\tIllegal score, do one more time...";
                            --j;
                        }
                        else {
                            row1[j-1] = pinsHit;
                        }
                    }
                }
                else if (pinsLeft == 0) {
                    bool repeat;
                    do {
                        cout << "\n\tExtra - 1 : ";
                        cin >> pinsHit;
                        if (pinsHit < 0 || pinsHit > 10) {
                            cout << "\t\t\tIllegal score, do one more time...";
                            repeat = true;
                        }
                        else {
                            row1[0] = pinsHit;
                            row1[1] = 0;
                            repeat = false;
                        }
                    } while (repeat);
                }
                else {
                    for (int j = 11; j <= 12; j++) {
                        row1[j-1] = 0;
                    }
                }
            }
        }
        //************************************DISPLAY SCORE****************************
        scoreCard(row1, row2, score);

        cout << "\n\n\t\t\tDo more (Y/N) ? ";
        cin  >> more;
    } while (more == 'y' || more == 'Y');

    return 0;
}