#pragma once
class Computer {
protected:
    int ship[5] = { 0,4,3,2,1 };
    char matrixFieldComp[10][10];

public:

    int random() {
        return 0 + rand() % 9;
    }
    void createShip() {
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < i;) {
                int position_A = 0 + rand() % 2;
                int position_B = 0 + rand() % 2;
                int x = random();
                int y = random();
                int size = ship[i];
                bool checkIsTrue = checkLocation(x, y, position_A, position_B, size);
                if (checkIsTrue) {
                    j++; 
                }
            }
        }
    }
    int checkLocation(int x, int y, int position_A, int position_B, int size) {
        if (matrixFieldComp[y][x] != '1') {
            if (position_A == 0) {
                if (position_B == 1 && x + size <= 10) {
                    int conditionY = (y + 1 < 10) ? y + 1 : y;
                    int conditionX = (x + size < 10) ? x + size : x + size - 1;
                    for (int i = (y - 1 >= 0) ? y - 1 : y; i <= conditionY; i++) {
                        for (int j = (x - 1 >= 0) ? x - 1 : x; j <= conditionX; j++) {
                            if (matrixFieldComp[i][j] == '1') {
                                return false;
                            }
                        }
                    }
                    for (int i = x; i < x + size; i++) {
                        matrixFieldComp[y][i] = '1';
                    }
                    return true;
                }
                else if (position_B == 0 && x - size - 1 >= 0) {
                    int conditionY = (y + 1 < 10) ? y + 1 : y;
                    int conditionX = (x + 1 < 10) ? x + 1 : x;
                    for (int i = (y - 1 >= 0) ? y - 1 : y; i <= conditionY; i++) {
                        for (int j = (x - size >= 0) ? x - size : x - size + 1; j <= conditionX; j++) {
                            if (matrixFieldComp[i][j] == '1') {
                                return false;
                            }
                        }
                    }
                    for (int i = x; i > x - size; i--) {
                        matrixFieldComp[y][i] = '1';
                    }
                    return true;
                }
            }
            else if (position_A == 1) {
                if (position_B == 1 && y - size + 1 >= 0) {
                    int conditionY = (y + 1 < 10) ? y + 1 : y;
                    int conditionX = (x + 1 < 10) ? x + 1 : x;
                    for (int i = (y - size >= 0) ? y - size : y - size + 1; i <= conditionY; i++) {
                        for (int j = (x - 1 >= 0) ? x - 1 : x; j <= conditionX; j++) {
                            if (matrixFieldComp[i][j] == '1') {
                                return false;
                            }
                        }
                    }
                    for (int i = y; i > y - size; i--) {
                        matrixFieldComp[i][x] = '1';
                    }
                    return true;
                }
                else if (position_B == 0 && y + size <= 10) {
                    int conditionY = (y + size < 10) ? y + size : y + size - 1;
                    int conditionX = (x + 1 < 10) ? x + 1 : x;
                    for (int i = (y - 1 >= 0) ? y - 1 : y; i <= conditionY; i++) {
                        for (int j = (x - 1 >= 0) ? x - 1 : x; j <= conditionX; j++) {
                            if (matrixFieldComp[i][j] == '1') {
                                return false;
                            }
                        }
                    }
                    for (int i = y; i < y + size; i++) {
                        matrixFieldComp[i][x] = '1';
                    }
                    return true;
                }
            }
        }
        return false;

    }
   

};
