#pragma once
#include <windows.h>
#include "comp.h"

using namespace sf;
std::string Convert(int number) {
    std::ostringstream buff;
    buff << number;
    return buff.str();
}
class Field : public Computer{
protected:
    int height = 10;
    int width = 10;
    char matrixFieldUser[10][10];
    int countUser = 0;
    int countComp = 0;
    int firstHitX = 0;
    int firstHitY = 0;
    int mode = 0;
    int xForBot = 0;
    int yForBot = 0;
    int fourShip = 1;
    int threeShip = 2;
    int twoShip = 3;
    int oneShip = 4;
    int countDeck = 0;
    bool botHit = true;
    int dir = 0;
    int userShips = 20;
    Texture imgShip;
    Texture imgMiss;
    bool playerCanGo = true;
    bool flagSleep = true;
public:
    void fillField() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                matrixFieldComp[i][j] = '0';
                matrixFieldUser[i][j] = '0';
            }
        }
    }

    void Play() {
        RenderWindow window(VideoMode(1100, 900), "SFML Works!");
        Vector2f mouse(Mouse::getPosition(window));
        Event event;
        Texture texture;
        Texture texture_2;
        Font font;
        Texture backgroundPic;
        backgroundPic.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\imgonline-com-ua-Resize-0o9t3whDTe.jpg");
        Sprite bgRect;
        String strUserScore;
        String strCompScore;
        bool checkStart = false;
        bool checkUserReady = true;
        bool flagWarning = true;
        bool restartCheck = false;
        bool checkAudio = true;
        bgRect.setTexture(backgroundPic);
        bgRect.setTextureRect(IntRect(0, 0, 1100, 900));
        bgRect.setPosition(0, 0);
        font.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\20451.ttf");
        imgShip.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\icons8-взрыв-27.png");
        imgMiss.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\icons8-cross-mark-27.png");
        texture_2.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\water-texture.jpg");
        texture.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\icons8-исторический-корабль-27.png");

        CircleShape start(60);
        start.setPosition(490, 770);
        start.setFillColor(Color(179, 235, 255));
        start.setOutlineThickness(3.f);
        start.setOutlineColor(Color(20, 20, 20));
        Text textStart(L"Старт", font, 40);
        textStart.setPosition(500, 800);
        textStart.setStyle(Text::Bold);
        textStart.setFillColor(Color(0, 0, 0));
        Sprite sprite_user[10][10];
        Sprite sprite_comp[10][10];

        CircleShape restart(60);
        restart.setPosition(-490, 770);
        restart.setFillColor(Color(179, 235, 255));
        restart.setOutlineThickness(3.f);
        restart.setOutlineColor(Color(20, 20, 20));
        Text restartText(L"Заново", font, 36);
        restartText.setPosition(-490, 800);
        restartText.setStyle(Text::Bold);
        restartText.setFillColor(Color(0, 0, 0));

        CircleShape exit(60);
        exit.setPosition(90, 770);
        exit.setFillColor(Color(179, 235, 255));
        exit.setOutlineThickness(3.f);
        exit.setOutlineColor(Color(20, 20, 20));
        Text exitText(L"Выход", font, 40);
        exitText.setPosition(100, 800);
        exitText.setStyle(Text::Bold);
        exitText.setFillColor(Color(0, 0, 0));

        CircleShape audioOnOff(60);
        audioOnOff.setPosition(890, 770);
        audioOnOff.setFillColor(Color(179, 235, 255));
        audioOnOff.setOutlineThickness(3.f);
        audioOnOff.setOutlineColor(Color(20, 20, 20));
        Text audioOnOffText(L"Муз вкл/выкл", font, 19);
        audioOnOffText.setPosition(895, 815);
        audioOnOffText.setStyle(Text::Bold);
        audioOnOffText.setFillColor(Color(0, 0, 0));

        

        RectangleShape rectFieldComp(Vector2f(307.f, 307.f));
        rectFieldComp.setPosition(109, 105); // 109 268 108
        rectFieldComp.setFillColor(Color(0, 0, 0));
        RectangleShape rectFieldUser(Vector2f(307.f, 307.f));
        rectFieldUser.setPosition(686, 105);
        rectFieldUser.setFillColor(Color(0, 0, 0));

        RectangleShape rectFieldCompWhite(Vector2f(297.f, 297.f));
        rectFieldCompWhite.setPosition(114, 110);
        rectFieldCompWhite.setFillColor(Color(64, 64, 64));
        RectangleShape rectFieldUserWhite(Vector2f(297.f, 297.f));
        rectFieldUserWhite.setPosition(691, 110);
        rectFieldUserWhite.setFillColor(Color(64, 64, 64));


        Text compFieldText;
        compFieldText.setString(L"Поле соперника");
        compFieldText.setPosition(120, 40);
        compFieldText.setFillColor(Color(0, 0, 0));
        compFieldText.setCharacterSize(45);
        compFieldText.setStyle(Text::Bold);
        compFieldText.setFont(font);

        Text userFieldText;
        userFieldText.setString(L"Ваше поле");
        userFieldText.setPosition(743, 40);
        userFieldText.setFillColor(Color(0, 0, 0));
        userFieldText.setCharacterSize(45);
        userFieldText.setStyle(Text::Bold);
        userFieldText.setFont(font);

        Text currentScoreText(L"Текущий счет", font, 50);
        currentScoreText.setPosition(-415, 450);
        currentScoreText.setFillColor(Color(0, 0, 0));
        currentScoreText.setStyle(Text::Bold);

        Text currentScore;
        currentScore.setPosition(-535, 510);
        currentScore.setFillColor(Color(0, 0, 0));
        currentScore.setStyle(Text::Bold);
        currentScore.setFont(font);
        currentScore.setCharacterSize(45);

        Text instruction(L" Перед тем как нажать старт \n расставьте корабли на своей \n базе в таком количестве \n Один 4-х палубный корабль \n Два 3-х палубных корабля \n Три 2-х палубных корабля \n Четыре 1 палубных кораблей \n Между кораблями должен \n быть отступ в одну клеточку.\n Корабли строятся только по \n вертикали и горизонтали", font, 20);
        instruction.setPosition(415, 90);
        instruction.setFillColor(Color(189, 12, 0));
        instruction.setStyle(Text::Bold);

        Text playerWinText(L"Поздравляю, вы победили!!!", font, 70);
        playerWinText.setPosition(-900, 300);
        playerWinText.setFillColor(Color(0, 0, 0));
        playerWinText.setStyle(Text::Bold);

        Text compWinText(L"Эх, соперник одержал победу(", font, 70);
        compWinText.setPosition(-900, 300);
        compWinText.setFillColor(Color(0, 0, 0));
        compWinText.setStyle(Text::Bold);
       
        Text warningFirst(L"Расставьте все корабли на своем поле", font, 30);
        warningFirst.setPosition(600, 410);
        warningFirst.setFillColor(Color(255, 0, 0));
        warningFirst.setStyle(Text::Bold);

        SoundBuffer buffer;
        buffer.loadFromFile("C:\\Users\\user\\Desktop\\курсовая\\saundtrek_k_filmu_pirati_karibskogo_morja_-_original_(zf.fm).ogg");// тут загружаем в буфер что то
        Sound sound;
        sound.setBuffer(buffer);
        sound.setLoop(true);
        sound.play();

      
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {

                sprite_user[i][j].setPosition(691 + (j * 30), 110 + (i * 30));
                sprite_user[i][j].setTextureRect(IntRect(0, 0, 27.f, 27.f));
                sprite_user[i][j].setTexture(texture_2);

            }

        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {

                sprite_comp[i][j].setPosition(114 + (j * 30), 110 + (i * 30));
                sprite_comp[i][j].setTextureRect(IntRect(0, 0, 27.f, 27.f));
                sprite_comp[i][j].setTexture(texture_2);

            }
        }

    
   
        while (window.isOpen())
        {
            window.clear(Color(179, 179, 179));
            window.draw(bgRect);
            window.draw(rectFieldComp);
            window.draw(rectFieldUser);
            window.draw(compFieldText);
            window.draw(userFieldText);
            window.draw(currentScoreText);
            window.draw(rectFieldCompWhite);
            window.draw(rectFieldUserWhite);
            strCompScore = Convert(countComp);
            strUserScore = Convert(countUser);
            currentScore.setString(strCompScore + ":" + strUserScore);
            window.draw(start);
            window.draw(textStart);
            window.draw(restart);
            window.draw(restartText);
            window.draw(exit);
            window.draw(exitText);
            window.draw(audioOnOff);
            window.draw(audioOnOffText);
            window.draw(currentScore);
            window.draw(instruction);
            window.draw(playerWinText);
            window.draw(compWinText);
           
       

          
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    window.draw(sprite_comp[i][j]);
                    window.draw(sprite_user[i][j]);
                }

            }
           

            if (flagWarning == false){
                window.draw(warningFirst);
            }

            if (restartCheck) {
                textStart.setPosition(500, 800);
                start.setPosition(490, 770);
                restart.setPosition(-490, 770);
                restartText.setPosition(-500, 800);
                currentScoreText.setPosition(-415, 450);
                currentScore.setPosition(-535, 510);
                instruction.setPosition(415, 90);     
                rectFieldComp.setPosition(109, 105);
                rectFieldUser.setPosition(686, 105);
                rectFieldCompWhite.setPosition(114, 110);
                rectFieldUserWhite.setPosition(691, 110);
                playerWinText.setPosition(-900, 300);
                compWinText.setPosition(-900, 300);
                compFieldText.setPosition(120, 40);
                userFieldText.setPosition(743, 40);
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        sprite_comp[i][j].setPosition(114 + (j * 30), 110 + (i * 30));
                        sprite_user[i][j].setPosition(691 + (j * 30), 110 + (i * 30));
                    }
                }

                restartCheck = false;
                checkStart = false;
                checkUserReady = true;
                flagWarning = true;
                playerCanGo = true;
                flagSleep = true;

                 countUser = 0;
                 countComp = 0;
                 firstHitX = 0;
                 firstHitY = 0;
                 mode = 0;
                 xForBot = 0;
                 yForBot = 0;
                 fourShip = 1;
                 threeShip = 2;
                 twoShip = 3;
                 oneShip = 4;
                 countDeck = 0;
                 botHit = true;
                 dir = 0;
                 userShips = 20;

                fillField();
                createShip();
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        sprite_user[i][j].setTexture(texture_2);
                        sprite_comp[i][j].setTexture(texture_2);
                    }
                }
              
            }

            while (window.pollEvent(event))
            {
                // Пользователь нажал на «крестик» и хочет закрыть окно?
                if (event.type == Event::Closed)
                    window.close();
                
                if (checkUserReady) {
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && (userShips > 0 || matrixFieldUser[i][j] == '1')){
                                if (sprite_user[i][j].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                                    
                                    if (matrixFieldUser[i][j] != '1') {
                                        matrixFieldUser[i][j] = '1';
                                        userShips--;
                                        sprite_user[i][j].setTexture(texture);
                                    }else if (matrixFieldUser[i][j] == '1') {
                                        matrixFieldUser[i][j] = '0';
                                        userShips++;
                                        sprite_user[i][j].setTexture(texture_2);
                                    }
                                    


                                }
                            }
                            window.draw(sprite_user[i][j]);
                        }
                    }
                }


                /* Fight(window,event,start,sprite_comp);*/

                if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left ) {
                    if (start.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        if (userShips == 0) {
                            checkStart = true;
                            checkUserReady = false;
                            flagWarning = true;
                        }
                        else {
                            flagWarning = false;
                        }
                       
                    }
                  

                }
                if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
                    if (audioOnOff.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        if (checkAudio) {
                            sound.pause();
                            checkAudio = false;
                        }
                        else {
                            sound.play();
                            checkAudio = true;
                        }

                    }


                }
                if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
                    if (restart.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        restartCheck = true;
                    }
                }
                if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
                    if (exit.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        window.close();
                    }
                }
                if (event.type == sf::Event::MouseMoved) {
                    if (start.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        start.setFillColor(Color(0, 55, 65));
                    }
                    else {
                        start.setFillColor(Color(179, 235, 255));
                    }
                    if (restart.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        restart.setFillColor(Color(0, 55, 65));
                    }
                    else {
                        restart.setFillColor(Color(179, 235, 255));
                    }
                    if (exit.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        exit.setFillColor(Color(0, 55, 65));
                    }
                    else {
                        exit.setFillColor(Color(179, 235, 255));
                    }
                    if (audioOnOff.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        audioOnOff.setFillColor(Color(0, 55, 65));
                    }
                    else {
                        audioOnOff.setFillColor(Color(179, 235, 255));
                    }

                }
                if (checkStart) {
                    textStart.setPosition(-500, 770);
                    start.setPosition(-490, 770);
                    restart.setPosition(490, 770);
                    restartText.setPosition(500, 800);
                    currentScoreText.setPosition(415, 450);
                    currentScore.setPosition(535, 510);
                    instruction.setPosition(-415, 90);
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && playerCanGo) {
                                if (sprite_comp[i][j].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) ) {
                                    if (matrixFieldComp[i][j] == '1') {
                                        sprite_comp[i][j].setTexture(texture);
                                        window.draw(sprite_comp[i][j]);
                                        window.display();
                                        matrixFieldComp[i][j] = 's';
                                        countUser++;
                                        if (countUser == 20) {
                                            rectFieldComp.setPosition(-500,105);
                                            rectFieldUser.setPosition(-686, 105);
                                            rectFieldCompWhite.setPosition(-500, 105);
                                            rectFieldUserWhite.setPosition(-686, 105);
                                            compFieldText.setPosition(-500, 40);
                                            userFieldText.setPosition(-500, 40);
                                            for (int i = 0; i < 10; i++) {
                                                for (int j = 0; j < 10; j++) {
                                                    sprite_user[i][j].setPosition(-691 + (j * 30), 110 + (i * 30));
                                                    sprite_comp[i][j].setPosition(-691 + (j * 30), 110 + (i * 30));
                                                }

                                            }
                                            playerWinText.setPosition(200, 300);
                                        }
                                    }

                                    if(matrixFieldComp[i][j] == '0'){
                                        sprite_comp[i][j].setTexture(imgMiss);
                                        window.draw(sprite_comp[i][j]);
                                        window.display();
                                        compShoot(window, event, sprite_user);
                                        if (countComp == 20) {
                                            rectFieldComp.setPosition(-500, 105);
                                            rectFieldUser.setPosition(-686, 105);
                                            rectFieldCompWhite.setPosition(-500, 105);
                                            rectFieldUserWhite.setPosition(-686, 105);
                                            compFieldText.setPosition(-700, 40);
                                            userFieldText.setPosition(-700, 40);
                                            for (int i = 0; i < 10; i++) {
                                                for (int j = 0; j < 10; j++) {
                                                    sprite_user[i][j].setPosition(-691 + (j * 30), 110 + (i * 30));
                                                    sprite_comp[i][j].setPosition(-691 + (j * 30), 110 + (i * 30));
                                                }

                                            }
                                            compWinText.setPosition(150, 300);
                                        }
                                    }

                                }
                            }  

                        }
                    }
                }

            }
            window.display();
        }


    }
 
    void compShoot(RenderWindow& window, Event& event, Sprite sprite_user[][10]) {
        playerCanGo = false;
        jump:
        botHit = true;
        do
        {
            if (flagSleep) {
                Sleep(1500);
                window.display();
            }
           
            if (mode == 0) {
                xForBot = rand() % 10;
                yForBot = rand() % 10;
                if (matrixFieldUser[yForBot][xForBot] == '2' || matrixFieldUser[yForBot][xForBot] == 's') {
                    flagSleep = false;
                }
                else {
                    flagSleep = true;
                }
                if (matrixFieldUser[yForBot][xForBot] == '1') {
                    mode = 1;
               
                    sprite_user[yForBot][xForBot].setTexture(imgShip);
                    window.draw(sprite_user[yForBot][xForBot]);
                    countComp++;
                    matrixFieldUser[yForBot][xForBot] = '2';
                    firstHitX = xForBot;
                    firstHitY = yForBot;
                    countDeck++;
                }
                else if (matrixFieldUser[yForBot][xForBot] == '0') {
                    
                    sprite_user[yForBot][xForBot].setTexture(imgMiss);
                    window.draw(sprite_user[yForBot][xForBot]);
                    matrixFieldUser[yForBot][xForBot] = 's';
                    botHit = false;
                }

            }
            else if (mode == 1) {
                if (countDeck == 1 && (twoShip > 0 || threeShip > 0 || fourShip > 0)) { // 1
                    if (dir == 0) {
                        if (xForBot > 0) {
                            xForBot--;
                        }
                        else {
                            dir = 1;
                            xForBot = firstHitX + 1;
                        }
                       
                    }else if(dir == 1){
                        if (xForBot < 9) {
                            xForBot++;
                        }
                        else {
                            dir = 2;
                            yForBot = firstHitY - 1;
                        }
                        
                    }else if(dir == 2){
                        if (yForBot > 0) {
                            yForBot--;
                        }
                        else {
                            dir = 3;
                            yForBot = firstHitY + 1;
                        }
                    }
                    else if (dir == 3) {
                        if (yForBot < 9) {
                            yForBot++;
                        }
                        else {
                            countDeck = 0;
                            oneShip--;
                            dir = 0;
                            mode = 0;
                            goto jump;
                        }
                    }
                    if (matrixFieldUser[yForBot][xForBot] == '1') {
                       
                        sprite_user[yForBot][xForBot].setTexture(imgShip);
                        window.draw(sprite_user[yForBot][xForBot]);

                        
                       
                        countComp++;
                        countDeck++;
                        matrixFieldUser[yForBot][xForBot] = '2';
               

                    }
                    else if(matrixFieldUser[yForBot][xForBot] == '0' || matrixFieldUser[yForBot][xForBot] == 's'){
                        if (matrixFieldUser[yForBot][xForBot] == '0') {
                           
                            sprite_user[yForBot][xForBot].setTexture(imgMiss);
                            window.draw(sprite_user[yForBot][xForBot]);
                            
                            
                            
                            matrixFieldUser[yForBot][xForBot] = 's';
                            botHit = false;
                        }
                     
                        
                         if (dir == 3) {
                            countDeck = 0;
                            oneShip--;
                            dir = 0;
                            mode = 0;
                         }
                         else {
                            dir++;
                            
                                xForBot = firstHitX;
                            
                                yForBot = firstHitY;
                            
                         }
                       
                       
                    }
                    
                }else if(countDeck == 2 && (threeShip > 0 || fourShip > 0)){ // 2
                    if (dir == 0) {
                        if (xForBot > 0) {
                            xForBot--;
                        }
                        else {
                            dir = 1;
                            xForBot = firstHitX + 1;
                        }

                    }
                    else if (dir == 1) {
                        if (xForBot < 9) {
                            xForBot++;
                        }
                        else {
                            countDeck = 0;
                            twoShip--;
                            dir = 0;
                            mode = 0;
                            goto jump;
                        }

                    }
                    else if (dir == 2) {
                        if (yForBot > 0) {
                            yForBot--;
                        }
                        else {
                            dir = 3;
                            yForBot = firstHitY + 1;
                        }
                    }
                    else if (dir == 3) {
                        if (yForBot < 9) {
                            yForBot++;
                        }
                        else {
                            countDeck = 0;
                            twoShip--;
                            dir = 0;
                            mode = 0;
                            goto jump;
                        }
                    }
                    if (matrixFieldUser[yForBot][xForBot] == '1') {
                        
                        sprite_user[yForBot][xForBot].setTexture(imgShip);
                        window.draw(sprite_user[yForBot][xForBot]);
                       
                       
                       
                        countComp++;
                        countDeck++;
                        matrixFieldUser[yForBot][xForBot] = '2';

                    }
                    else if (matrixFieldUser[yForBot][xForBot] == '0' || matrixFieldUser[yForBot][xForBot] == 's') {
                        if (matrixFieldUser[yForBot][xForBot] == '0') {
                           
                            sprite_user[yForBot][xForBot].setTexture(imgMiss);
                            window.draw(sprite_user[yForBot][xForBot]);
                           
                            
                            
                            matrixFieldUser[yForBot][xForBot] = 's';
                            botHit = false;
                        }
                        if (dir == 1 || dir == 3) {
                            countDeck = 0;
                            twoShip--;
                            dir = 0;
                            mode = 0;
                        }else if (dir == 0 || dir == 2) {
                            dir++;
                         
                                xForBot = firstHitX;
                           
                                yForBot = firstHitY;
                            
                        }
                       
                      
                       

                    }
                }
                else if(countDeck == 3 && fourShip > 0) { // 3
                    if(dir == 0) {
                        if (xForBot > 0) {
                            xForBot--;
                        }
                        else {
                            dir = 1;
                            xForBot = firstHitX + 1;
                        }

                    }else if (dir == 1) {
                        if (xForBot < 9) {
                            xForBot++;
                        }
                        else {
                            countDeck = 0;
                            threeShip--;
                            dir = 0;
                            mode = 0;
                            goto jump;
                        }
                    }
                    else if (dir == 2) {
                    if (yForBot > 0) {
                        yForBot--;
                    }
                    else {
                        dir = 3;
                        yForBot = firstHitY + 1;
                    }
                    }
                    else if (dir == 3) {
                    if (yForBot < 9) {
                        yForBot++;
                    }
                    else {
                        countDeck = 0;
                        threeShip--;
                        dir = 0;
                        mode = 0;
                        goto jump;
                    }
                    }
                    if (matrixFieldUser[yForBot][xForBot] == '1') {
                        

                        sprite_user[yForBot][xForBot].setTexture(imgShip);
                        window.draw(sprite_user[yForBot][xForBot]);
                       
                       
                        countComp++;
                        countDeck=0;
                        dir = 0;
                        fourShip = 0;
                        mode = 0;
                        matrixFieldUser[yForBot][xForBot] = '2';

                    }
                    else if (matrixFieldUser[yForBot][xForBot] == '0' || matrixFieldUser[yForBot][xForBot] == 's') {
                        if (matrixFieldUser[yForBot][xForBot] == '0') {
                          
                            sprite_user[yForBot][xForBot].setTexture(imgMiss);
                            window.draw(sprite_user[yForBot][xForBot]);
                            
                           
                           
                            matrixFieldUser[yForBot][xForBot] = 's';
                            botHit = false;
                        }
                        if (dir == 1 || dir == 3) {
                            countDeck = 0;
                            threeShip--;
                            dir = 0;
                            mode = 0;
                        }
                        else if (dir == 0 || dir == 2) {
                            dir++;
                          
                                xForBot = firstHitX;
                          
                                yForBot = firstHitY;
                           
                        }
                    }
                }
                else {
                    if (countDeck == 1) {
                        oneShip--;
                    }
                    if (countDeck == 2) {
                        twoShip--;
                    }
                    if (countDeck == 3) {
                        threeShip--;
                    }
                    countDeck = 0;
                    mode = 0;
                    dir = 0;
                }
              
            }
          if (countComp == 20) {
              botHit = false;
          }
          window.display();
        } while (botHit);
        playerCanGo = true;

    }
};