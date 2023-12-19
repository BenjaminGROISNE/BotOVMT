#include "OVMT.h"

OVMT::OVMT() {
    ALCHEMY=AD= CULTIVATION= GARDEN= LAWS= WORLDRIFT= ARENA= ASSISTANT= DIVINITIES= GATE= HEIRLOOM= MAIL= OTHERWORLD= PACK= PERKS= RANKING= ABYSS= DREAMYAD= RESSOURCES= MONSTERHUNT = false;
    dimX = 1080;
    dimY = 1920;
    fillPopup();
    sys.createpaths();
    package = "com.ltgames.android.m71.sea";
    activity = "com.ltgames.android.m71.sea/com.gbits.hook.HookUnityPlayerActivity";
    mac = macroConfig(package,activity);
    C = Coords();
    sys = sysCommands();
    adb = fadb();
    op = fopencv();
    endmacro = false;
    restartMacro = true;
    waitMacro = false;
    
}

void OVMT::setAdb(fadb adb) {
    this->adb = adb;
}
void OVMT::setSys(sysCommands sys) {
    this->sys = sys;
}

void OVMT::selectActivity() {
    int duration = 30;
    int timeleft;
    std::string choix;
    bool choseFavPreset = false;
    bool chosePreset = false;
    std::string textseconds = "Seconds left: ";
    std::cout <<std::endl<< "Type which activity you wanna do:" << std::endl;
    std::cout << "ALL : 0" << std::endl;
    std::cout << "ALCHEMY:A GARDEN:C LAWS:D WORLDRIFT:E ARENA:F ASSISTANT:G DIVINITIES:H GATE:I HEIRLOOM:J MAIL:K OTHERWORLD:L PACK:M PERKS:N RANKING:O ABYSS:P DREAMYAD:Q RESSOURCES:R MONSTERHUNT:S ;" << std::endl;
    std::cout << "for example: abjdlm or ABJghDd or 0" << std::endl << std::endl;
    std::cout << "Type P to choose preset" << std::endl;
    std::cout << "Type F to choose favorite Preset" << std::endl;
    std::cout << "Type S to Skip" << std::endl;
    std::cout << "Validate your input with Enter" << std::endl;
    std::cout << std::endl << "Seconds left: ";
    auto start = std::chrono::steady_clock::now();
    long long int elapsed = 0;
    long long int lastelapsed = elapsed;
    int maxchar = 0;
    int nbchar = 0;
    int lastnbchar = 0;
    int i = duration;
    while (i > 0) {
        i /= 10;
        maxchar++;
    }
    std::cout << duration;
    mac.readMcfilefavouritePreset();

    do {
        auto now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        timeleft = duration - elapsed;
        if (lastelapsed != elapsed) {
            nbchar = 0;
            i = timeleft;
            while (i != 0) {
                i /= 10;
                nbchar++;
            }
            for (int j = 0; j < maxchar + textseconds.length(); ++j) {
                std::cout << "\b";
            }
            std::cout << textseconds;
            for (int j = 0; j < 2 * maxchar - nbchar; ++j) {
                std::cout << " ";
            }
            for (int j = 0; j < maxchar; ++j) {
                std::cout << "\b";
            }
            std::cout << timeleft;
            lastelapsed = elapsed;
        }
        if (ml.isKeyPressed(sf::Keyboard::P)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout <<std::endl<< "Type Preset: ";
            std::cin.clear();
            std::cin >> choix;
            chosePreset = true;
        }

        if (ml.isKeyPressed(sf::Keyboard::F)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "Type favorite Preset: ";
            std::cin.clear();
            std::cin >> choix;
            mac.favouritePreset = choix;
            mac.updateFavouritePreset(mac.favouritePreset);
        }

        if (ml.isKeyPressed(sf::Keyboard::S)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        }

    } while (timeleft > 0 && !chosePreset);

    if (!chosePreset) {
        choix = mac.favouritePreset;
    }
    std::cout << std::endl;
    for (int i = 0; i < choix.size(); i++) {
        switch (tolower(choix[i])) {
        case 'a':
            ALCHEMY = true;
            std::cout << "ALCHEMY ";
            break;
        case 'c':
            GARDEN = true;
            std::cout << "GARDEN ";
            break;
        case 'd':
            LAWS = true;
            std::cout << "LAWS ";
            break;
        case 'e':
            WORLDRIFT = true;
            std::cout << "WORLDRIFT ";
            break;
        case 'f':
            ARENA = true;
            std::cout << "ARENA ";
            break;
        case 'g':
            ASSISTANT = true;
            std::cout << "ASSISTANT ";
            break;
        case 'h':
            DIVINITIES = true;
            std::cout << "DIVINITIES ";
            break;
        case 'i':
            GATE = true;
            std::cout << "GATE ";
            break;
        case 'j':
            HEIRLOOM = true;
            std::cout << "HEIRLOOM ";
            break;
        case 'k':
            MAIL = true;
            std::cout << "MAIL ";
            break;
        case 'l':
            OTHERWORLD = true;
            std::cout << "OTHERWORLD ";
            break;
        case 'm':
            PACK = true;
            std::cout << "PACK ";
            break;
        case 'n':
            PERKS = true;
            std::cout << "PERKS ";
            break;
        case 'o':
            RANKING = true;
            std::cout << "RANKING ";
            break;
        case 'p':
            ABYSS = true;
            std::cout << "ABYSS ";
            break;
        case 'q':
            DREAMYAD = true;
            std::cout << "DREAMYAD ";
            break;
        case 'r':
            RESSOURCES = true;
            std::cout << "RESSOURCES ";
            break;
        case 's':
            MONSTERHUNT = true;
            std::cout << "MONSTERHUNT ";
            break;
        case '0':
            ALCHEMY = GARDEN = LAWS = WORLDRIFT = ARENA = ASSISTANT = DIVINITIES = GATE = HEIRLOOM = MAIL = OTHERWORLD = PACK = PERKS = RANKING = ABYSS = DREAMYAD = RESSOURCES = MONSTERHUNT = true;
            std::cout << "ALCHEMY ; GARDEN ; LAWS ; WORLDRIFT ; ARENA ; ASSISTANT ; DIVINITIES ; GATE ; HEIRLOOM ; MAIL ; OTHERWORLD ; PACK ; PERKS ; RANKING ; ABYSS ; DREAMYAD ; RESSOURCES ; MONSTERHUNT";
            break;
        }
        std::cout << " will be done." << std::endl;
    }
}



bool OVMT::macroEnd() {
    if(ALCHEMY == false && CULTIVATION == false && GARDEN == false && LAWS == false && WORLDRIFT == false && ARENA == false && ASSISTANT == false && DIVINITIES == false && GATE == false && HEIRLOOM == false && MAIL == false && OTHERWORLD == false && PACK == false && PERKS == false && RANKING == false && ABYSS == false && DREAMYAD == false && RESSOURCES == false && MONSTERHUNT == false){
        endmacro = true;
        return true;
    }
    else return false;
}

void OVMT::macroLoop() {
  
    while (true) {
        switch (restartMacro) {
        case true:
            startGame();
            break;
        case false:
            if (RESSOURCES) {
                doRessources();
                RESSOURCES = false;
                break;
            }
            if (ALCHEMY) {
                doAlchemy();
                ALCHEMY = false;
                break;
            }
            if (ASSISTANT) {
                doAssistant();
                ASSISTANT = false;
                break;
            }
            if(GARDEN){
                doGarden();
                GARDEN = false;
                break;
            }
            if (LAWS) {
                doLaws();
                LAWS = false;
                break;
            }
            if (WORLDRIFT) {
                doWorldrift();
                WORLDRIFT = false;
                break;
            }
            if (ARENA) {
            doArena();
            ARENA = false;
            break;
            }
            if (DIVINITIES) {
            doDivinities();
            DIVINITIES = false;
            break;
            }
            if (GATE) {
            doGate();
            GATE = false;
            break;
            }
            if (HEIRLOOM) {
            doHeirloom();
            HEIRLOOM = false;
            break;
            }
            if (OTHERWORLD) {
            doOtherworld();
            OTHERWORLD = false;
            break;
            }
            if (PACK) {
            doPack();
            PACK = false;
            break;
            }
            if (RANKING) {
            doRanking();
            RANKING = false;
            break;
            }
            if (ABYSS) {
            doAbyss();
            ABYSS = false;
            break;
            }
            if (DREAMYAD) {
            doDreamad();
            DREAMYAD =false;
            break;
            }
            if (MONSTERHUNT) {
                doMonsterhunt();
                MONSTERHUNT = false;
                break;
            }
            if (MAIL) {
                doMail();
                MAIL = false;
                break;
            }
            if (PERKS) {
                doPerks();
                PERKS = false;
                break;
            }
            break;
        } 
        if (macroEnd()) {
            std::cout << "End of Macro" << std::endl;
            break;
        }
    }
}

void OVMT::startMacro()
{
    mac.setDim(dimX, dimY);
    mac.initMacroConfig();
    selectActivity();
    mac.blue.startInstance(mac.playingInstance);
    mac.updateBlueStacksConfAdbPort(mac.playingInstance);
    adb.setPort(mac.playingInstance.port);
    adb.devices();
    adb.disconnectLocalhost(adb.intport);
    adb.connectLocalhost(adb.intport);
    sys.setPort(adb.intport);
    sys.createpaths();
}

void OVMT::startGame() {
    try {
        std::cout << "RESTART"<<std::endl;
        restartMacro = false;
        rebootCount = 0;
        adb.quitPackage(package);
        adb.launchPackage(activity);
        while (!fA(loadingpage));
        while (fA(loadingpage));
        while (!fcA(start)) {
            fcA(notice);
        }
        while (fcA(start));
        goHome();

    }
    catch (int e) {
        
        return;
    }
}

void OVMT::goHome() {
    while (!fcA(ctown)) {
        while (fcA(back));
        Coords menu{0.5 * dimX,0.99 * dimY};
        adb.touch(menu.x, menu.y);
    }
}



void OVMT::doExample() {
    try {
        goHome();
        goHome();
       
    }
    catch (int e) {       
        return;
    }
}

void OVMT::doAlchemy()
{
    try {
        goHome();
        while (!fcA(cabode));
        std::vector<std::string>abodecult = { corporiacave,magickacave };
        while (!fA(peticon))adb.swipe(0.3 * dimX, 0.5 * dimY, 0.8 * dimX, 0.5 * dimY, 500);
        while (!fcOneTemplateA(abodecult))adb.swipe(0.6 * dimX, 0.5 * dimY, 0.4 * dimX, 0.5 * dimY, 1000);
        while (fcOneTemplateA(abodecult));
        while (!fA(pickelixir));
        bool corporia = false;
        bool magicka = false;
        if (fA(magickacultivator))magicka = true;
        else if (fA(corporiacultivator))corporia = true;
        while (!fOneTemplateA(abodecult)) {
            fcA(back);
        }
        while (!fcA(alchemyicon))adb.swipe(0.4 * dimX, 0.5 * dimY, 0.6 * dimX, 0.5 * dimY, 1000);
        while (fcA(alchemyicon));
        std::vector<std::string>alchemychoice = { selectcauldron ,cancelpills,claimpills };
        while (!fOneTemplateA(alchemychoice));
        while (!fA(onselectpillpage)) {
            if (fcA(selectcauldron));
            else if (fcA(claimpills)) {
                while (fcA(changepills));
            }
            else if (fA(cauldron)) {
                while (fcA(changepills));
            }
            else if (fA(cancelpills)) {
                while (fA(cancelpills));
            }
        }
        bool cancraftpill = false;
        std::vector<std::string>corpPowder = { dracophantpowder,caelumpowder,utilitypowder,foursymbolspowder };
        std::vector<std::string>magickaPill = { choosejadeitypill,choosecosmospill,goldendragonpill,etiquettepill };
        if (corporia || magicka) {
            if (corporia) {
                if (fcOneTemplateA(corpPowder)) {
                    if (!fcA(norecipe))cancraftpill = true;
                }
            }
            else if (magicka) {
                if (fcOneTemplateA(magickaPill)) {
                    if (!fcA(norecipe))cancraftpill = true;
                }
            }
        }

        if (cancraftpill) {
            while (fcA(selectpill));


            std::vector<std::string>limitpill = { zerolimit,onelimit,twolimit,threelimit,fourlimit,fivelimit,sixlimit,sevenlimit,eightlimit,ninelimit };
            std::vector<std::string>craftpills = { zerocraft,onecraft,twocraft,threecraft,fourcraft,fivecraft,sixcraft,sevencraft,eightcraft,ninecraft };
            std::vector<std::string>coremat = { graycore,greencore,bluecore,purplecore,yellowcore };
            std::vector<std::string>outcomecraft = { nopillmat,tapblank,claimpills };
            std::vector<std::string>goodoutcome = { tapblank,claimpills };

            Coords Cmaterial(0.37 * dimX, 0.78 * dimY);

            Coords C1mat(0.271 * dimX, 0.24 * dimY);
            Coords C2mat(0.355 * dimX, 0.636 * dimY);
            Zone matquality(C1mat, C2mat);

            Coords C1TextZone((double)0, 0.833 * dimY);
            Coords C2TextZone((double)dimX, 0.877 * dimY);
            Zone text(C1TextZone, C2TextZone);


            Coords C1pillLimit, C2pillLimit;
            Zone zonepillLimit;

            Zone ZoneCraftPill;
            Coords C1craftpill, C2craftpill;

            bool firstcraftepic = false;
            bool epicpill = false;
            bool legpill = false;
            bool initpilldim = true;
            bool cancraftgreen = true;
            bool cancraftgray = true;
            bool cancraftblue = true;
            bool cancraftepic = true;
            bool cancraftleg = true;
            bool cancraftbetterpill = false;
            int pillbeforeepic = 0;

            bool cancraftanymat = true;
            //Zone craftmats
            while (!fA(quantitypill)) {
                fcA(craftpill);
            }
            while (!fA(lowerpill));
            C1craftpill.x = C.x + getMatWidth(lowerpill) / 2;
            C1craftpill.y = C.y - getMatHeight(lowerpill) * 2;
            while (!fA(augmentpill));
            C2craftpill.x = C.x - getMatWidth(augmentpill) / 2;
            C2craftpill.y = C.y - getMatHeight(augmentpill) / 2;
            ZoneCraftPill.C1 = C1craftpill;
            ZoneCraftPill.C2 = C2craftpill;
            while (!fA(cauldron))adb.touch(0.5 * dimX, 0.999 * dimY);



            while (cancraftgreen || cancraftgray || cancraftblue) {
                if (!cancraftanymat)break;
                //Find HOW MANY CRAFTS TILL THRESHOLD
                if (fZoneA(alwaystext, text)) {
                    epicpill = true;
                    cancraftbetterpill = true;
                }
                else if (fZoneA(gettext, text)) {
                    cancraftbetterpill = true;
                    legpill = true;
                }
                if (initpilldim && !cancraftbetterpill) {
                    while (!fZoneA(crafttext, text));
                    C1pillLimit.x = C.x + (getMatWidth(crafttext) / 2);
                    C1pillLimit.y = C.y - (getMatHeight(crafttext) / 2);
                    while (!fZoneA(moretext, text));
                    C2pillLimit.x = C.x - (getMatWidth(moretext) / 2);
                    C2pillLimit.y = C.y + (getMatHeight(moretext) / 2);
                    initpilldim = false;
                    zonepillLimit.C1 = C1pillLimit;
                    zonepillLimit.C2 = C2pillLimit;
                    zonepillLimit.showZone();
                    initpilldim = false;
                }
                if (!cancraftbetterpill) {
                    Number nbpillLimit = fNumberIntegerA(limitpill, zonepillLimit);
                    std::cout << nbpillLimit.nb << " pills before legendary pill" << std::endl;
                    std::cout << (int)nbpillLimit.nb % 100 << " pills before legendary or epic pill" << std::endl;
                    pillbeforeepic = (int)nbpillLimit.nb % 100;
                }

                //CRAFT BETTER PILL
                if (cancraftbetterpill) {
                    while (cancraftbetterpill) {
                        if (epicpill) {
                            if (cancraftleg) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftleg, Cmaterial, yellowcore, cancraftbetterpill, cancraftanymat);
                            }
                            else if (cancraftepic) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftepic, Cmaterial, purplecore, cancraftbetterpill, cancraftanymat);
                            }
                            else if (cancraftblue) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftblue, Cmaterial, bluecore, cancraftbetterpill, cancraftanymat);
                            }

                            else {
                                cancraftbetterpill = false;
                                epicpill = false;
                            }

                        }
                        else if (legpill) {
                            if (cancraftgray) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftgray, Cmaterial, graycore, cancraftbetterpill, cancraftanymat);
                            }
                            else if (cancraftgreen) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftgreen, Cmaterial, greencore, cancraftbetterpill, cancraftanymat);
                            }
                            else if (cancraftblue) {
                                craftBetterPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, cancraftblue, Cmaterial, bluecore, cancraftbetterpill, cancraftanymat);
                            }
                            else {
                                cancraftbetterpill = false;
                                legpill = false;
                            }
                        }
                    }
                }

                //CRAFT NORMAL PILL
                else if (cancraftblue) {
                    craftNormalPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, pillbeforeepic, cancraftblue, Cmaterial, bluecore, cancraftanymat);

                }
                else if (cancraftgreen) {
                    craftNormalPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, pillbeforeepic, cancraftgreen, Cmaterial, greencore, cancraftanymat);

                }
                else if (cancraftgray) {
                    craftNormalPill(craftpills, coremat, outcomecraft, goodoutcome, ZoneCraftPill, matquality, pillbeforeepic, cancraftgray, Cmaterial, graycore, cancraftanymat);
                }
            }
        }
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doPet(bool &eatpills)
{
    while (!fcA(peticon))adb.swipe(0.3 * dimX, 0.5 * dimY, 0.8 * dimX, 0.5 * dimY, 500);
    while (fcA(peticon));
    std::vector<std::string>colorpet = { yellowpet,graypet,greenpet };
    std::vector<std::string>foodpet = { foodpet1,foodpet2,foodpet3,foodpet4 };
    while (fcOneTemplateA(foodpet));
    while (!fA(menagerie)) {
        fcA(back);
    }
    while (!fA(petformation)) {
        fcA(cpetarray);
    }
    std::string highestpet = "";

    if (fCompareMultipleTemplateA(yellowpet, colorpet))highestpet = yellowpet;
    else if (fCompareMultipleTemplateA(greenpet, colorpet))highestpet = greenpet;
    else if (fCompareMultipleTemplateA(graypet, colorpet))highestpet = graypet;
    else highestpet = graypet;
    while (!fcCompareMultipleTemplateA(highestpet, colorpet));
    while (!fcA(infopet));
    while (fcA(infopet));
    int noautofeed = 0;
    while (!fcA(autofeed)) {
        fcA(feedpet);
    }
    while (!fcA(confirmfeed)) {
        if(fcA(autofeed))noautofeed++;
        if (noautofeed > 3) {
            break;
        }
    }
    eatpills = true;
    while (!fA(peticon)) {
        fcA(back);
    }
}

void OVMT::doPack()
{
    try {
        goHome();
        while (!fcA(pack));
        while (fcA(pack));
        std::vector<std::string>rcmd = { crcmd,ncrcmd };
        while (!fA(dailyspecial)) {
            while (!fcOneTemplateA(rcmd));
        }
        while (!fcOneTemplateMultipleTemplateA(viewrcmd, E, 0));
        while (fcOneTemplateMultipleTemplateA(viewrcmd, E, 0));
        std::vector<std::string>freespecialtile = { freedailyspecial,soldoutdailyspecial };
        while (!fcOneTemplateA(freespecialtile))
            while (!fA(dailyspecial)) {
                adb.touch(0.5 * dimX, 0.99 * dimY);
            }
        std::vector<std::string>flashsales = { cflashsales,ncflashsales };
        while (!fA(specialoffers)) {
            adb.touch(0.5 * dimX, 0.99 * dimY);
            while (!fcOneTemplateA(flashsales));
        }
        fcA(specialoffers);
        while (fcA(freepack)) {
            while (!fcA(tapblank));
            while (fcA(tapblank));
        }
        fcA(weeklypack);
        while (fcA(freepack)) {
            while (!fcA(tapblank));
            while (fcA(tapblank));
        }
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doCultivation()
{
    try {
        goHome();
        while (!fcA(cabode));
        bool eatpills = false;
        doPet(eatpills);
        std::vector<std::string>abodecult = { corporiacave,magickacave };
        while (!fA(peticon))adb.swipe(0.3 * dimX, 0.5 * dimY, 0.8 * dimX, 0.5 * dimY, 500);
        while (!fcOneTemplateA(abodecult))adb.swipe(0.6 * dimX, 0.5 * dimY, 0.4 * dimX, 0.5 * dimY, 1000);
        while (fcOneTemplateA(abodecult));
        while (!fA(choosepath));
        while (!fcA(pickelixir));
        while (fcA(pickelixir));
        while (!fcA(useallelixirs));
        while (!fcA(useallelixirs));
        while (!fcA(useallelixirs));
        while (!fA(choosepath)) {
            fcA(back);
        }
        while (fcA(quickrespira));
        std::vector<std::string>allrespiraeffects = { respiraeffect1,respiraeffect2,respiraeffect3 };
        if (eatpills == true&&fcA(pickpill)) {
            int maxpills = 28;
            while (!fcA(cancelpills) && maxpills > 0 && fA(symbolpill)) {
                adb.touch(0.120 * dimX, 0.835 * dimY);
                maxpills--;
                std::cout << maxpills << " pills left to take at most" << std::endl;
            }
            while (fcA(leavepills));
        }
        while (fcOneTemplateA(allrespiraeffects));
        goHome();

    }
    catch (int e) {
        return;
    }
}

void OVMT::doGarden()
{
    try {
        goHome();

        while (!fcA(cabode));
        while (!fcA(gardenicon)) {
            adb.swipe(0.9 * dimX, 0.5 * dimY, 0.3 * dimX, 0.5 * dimY, 500);
        }
        while (fcA(gardenicon));
        while (fcA(claimgarden));
        while (!fA(waterattempts)) {
            fcA(water);
        }
        Coords attemptsC1 = { C.x - getMatWidth(waterattempts) / 2,C.y - getMatHeight(waterattempts) / 2 };
        Coords attemptsC2 = { attemptsC1.x + getMatWidth(waterattempts),attemptsC1.y + getMatHeight(waterattempts) };
        Coords rightnbattemptsC1 = { attemptsC2.x,attemptsC1.y };
        Coords rightnbattemptsC2 = { attemptsC2.x + getMatWidth(waterattempts) / 2,attemptsC2.y };
        Coords downattemptsC1 = { attemptsC1.x,attemptsC2.y };
        Coords downattemptsC2 = { attemptsC2.x,attemptsC2.y + getMatHeight(waterattempts) };
        Zone GoodZone;
        bool foundnbattempts = false;
        while (!foundnbattempts) {
            Zone rightnbattemptsZone(rightnbattemptsC1, rightnbattemptsC2);
            if (fZoneA(slash, rightnbattemptsZone)) {
                foundnbattempts = true;
                GoodZone = rightnbattemptsZone;
            }
            Zone downnbattempts(downattemptsC1, downattemptsC2);
            if (fZoneA(slash, downnbattempts)) {
                foundnbattempts = true;
                GoodZone = downnbattempts;
            }
        }
        GoodZone.showZone();
        std::vector<std::string>digits = { zerowater,onewater,twowater,threewater,fourwater,fivewater,sixwater,sevenwater,eightwater,ninewater };
        Number nb = fNumberIntegerA(digits, GoodZone);
        bool foundfate = false;
        if (nb.digits.size() <= 3 && nb.digits.size() >= 2) {
            if (nb.digits.at(0).nb == 1) {
                while (!foundfate) {
                    if (fA(fatewater)) {
                        foundfate = true;
                        Coords C1fate(C.x - getMatWidth(fatewater) / 2, C.y - getMatHeight(fatewater) / 2);
                        Coords C2fate(C1fate.x + getMatWidth(fatewater), C1fate.y + getMatHeight(fatewater));
                        Coords C1freefate(C2fate.x, C1fate.y);
                        Coords C2freefate(C2fate.x + 2 * getMatWidth(fatewater), C2fate.y);
                        Zone freezone(C1freefate, C2freefate);
                        freezone.showZone();
                        if (!fZoneA(freegarden, freezone)) {
                            std::cout << "Garden already done, SET IT MANUALLY NEXT TIME IF NOT" << std::endl;
                            while (!fcA(cancelwater));
                            while (fcA(cancelwater));
                        }
                        else {
                            std::cout << "Only one free garden selected AUGMENT IT MANUALLY";
                            while (!fcA(confirmwater));
                            while (fcA(confirmwater));
                        }
                    }
                }
            }
            else if (nb.digits.at(0).nb < 6) {
                std::cout << "First garden of the day";
                while (!fcA(confirmwater));
                while (fcA(confirmwater));
            }
        }
        while (fcA(claimgarden));
        goHome();

    }
    catch (int e) {
        return;
    }
}

void OVMT::doLaws()
{
}

void OVMT::doWorldrift()
{
    try {
        goHome();
        bool noattempts = false;
        bool domanualreincarnation=true;
        bool doautoreincarnation = false;
        while (!fcA(cabode));
        while (!fcA(worldrifticon)) {
            adb.swipe(0.3 * dimX, 0.5 * dimY, 0.9 * dimX, 0.5 * dimY, 500);
        }
        while (!fA(startreincarnation)) {
               fcA(worldrifticon);
        }
        if (fA(autoworldrift)) {
            doautoreincarnation = true;
            domanualreincarnation = false;
        }

        if (doautoreincarnation) {
            while (!fcA(autoworldrift));
            Coords C1mid(0, 0);
            Coords C2mid(dimX, 0.65 * dimY);
            Zone mid(C1mid, C2mid);
            while (!fZoneA(autoreincarnationtile, mid)) {
                if (fA(noreincarnationattempts)) {
                    noattempts = true;
                    break;
                }
                fcA(autoworldrift);
            }
            if (!noattempts) {
                while (!fSwipeA(changenbreincarnation, rightx, samey));
                while (!fcA(tapblank))fcZoneA(autoreincarnationtile, mid);
                while (fcA(tapblank));
            }
        }
        else if (domanualreincarnation) {
        anothertry:
            while (!fcA(randomstart)) {
                if (fA(noreincarnationattempts)) {
                    noattempts = true;
                    break;
                }
                fcA(startreincarnation);
            }
            if (!noattempts) {
                while (!fcA(startreincarnation));
                while (fcA(startreincarnation));
                while (!fcA(skipreincarnation));
                while (fcA(skipreincarnation));
                while (!fcA(confirmreincarnation));
                while (fcA(confirmreincarnation));
                while (!fcA(endreincarnation));
                while (fcA(endreincarnation));
                goto anothertry;
            }
        }
        goHome();

    }
    catch (int e) {
        return;
    }
}

void OVMT::doArena()
{
    try {
        goHome();
        while (!fA(sectlibrary)) {
              fcA(csect);
        }
        while (!fcA(arena)) {
              fcA(ctown);
        }
        while (!fcA(challengearena)){
            fcA(arena);
        }
        while (!fA(challengetilearena)) {
            fcA(challengearena);
        }
        int nb = 0;
        fnbTemplateA(yinyangarena, nb);
        if (nb <= 1) {
            fcA(refresharena);
            fnbTemplateA(yinyangarena, nb);
        } 
        if (nb>1) {
            Coords C1enemytofight, C2enemytofight;
            std::vector<std::string> figures = { zeroarena,onearena,twoarena,threearena,fourarena,fivearena,sixarena,sevenarena,eightarena,ninearena };
            Unit Ubillionarena(billionarena, B);
            std::vector<Unit> Units = { Ubillionarena };
            double mybr, enemybr;
            Coords topbr, bottombr;
            int nbrefresh=0;

            fOneTemplateMultipleTemplateA(yinyangarena, S, 0);
            topbr = { C.x - getMatWidth(yinyangarena) / 2,C.y - getMatHeight(yinyangarena) / 2 };
            bottombr = { (int)(topbr.x + 0.182 * dimX),(int)(topbr.y + getMatHeight(yinyangarena)) };
            Zone Tofight = { topbr,bottombr };
            Tofight.showZone();
            Number br = fNumberDecimalA(figures, Units, dotarena, Tofight);
            mybr = br.nb;
            while (nbrefresh < 3) {
                fOneTemplateMultipleTemplateA(yinyangarena, S, 1);
                topbr = { C.x - getMatWidth(yinyangarena) / 2,C.y - getMatHeight(yinyangarena) / 2 };
                bottombr = { (int)(topbr.x + 0.182 * dimX),(int)(topbr.y + getMatHeight(yinyangarena)) };
                Tofight = { topbr,bottombr };
                Tofight.showZone();
                br = fNumberDecimalA(figures, Units, dotarena, Tofight);
                enemybr = br.nb;
                if (mybr*1.025 > enemybr) {
                    while (fcOneTemplateMultipleTemplateA(challengetilearena, S, 0)&&!fA(heroinvitationarena));
                    if (fA(heroinvitationarena)) { 
                        while (!fcA(back))adb.touch(0.5 * dimX, 0.99 * dimY);
                        break;
                    }
                    std::vector<std::string>outcome = { victorytower,defeattower };
                    std::vector<std::string>speed = { speedone,speedtwo,speedthree };
                    std::vector<std::string>infspeed = { speedone,speedtwo };
                    while (fOneTemplateA(speed)) {
                        while (!fA(speedthree)) {
                            if (!fcOneTemplateA(infspeed))break;
                        }
                    }
                    while (!fA(challengearena)) {
                        fcOneTemplateA(outcome);
                    }
                }           
                nbrefresh++;       
                while (!fA(challengetilearena)) {
                    fcA(challengearena);
                }
                fcA(refresharena);
            }
        }
        goHome();
    }
    catch(int e){
        return;
    }
}

void OVMT::doAssistant()
{
    try {
        std::vector<Coords>savecoord;
        std::vector<std::string>tasks = {atask,btask,ctask,dtask,etask};
        std::vector<std::string>collections = {yellowcollection,purplecollection,bluecollection,greencollection,graycollection};
        std::vector<std::string>wanted = {yellowwanted,purplewanted,bluewanted,greenwanted,graywanted};
        goHome();
        while (!fcA(assistant));
        while (fcA(assistant));
        while (!fcA(assistantmarket));
        while (fcA(assistantmarket));
        while (!fA(back));
        while (fcA(implement));
        while (!fcA(back));
        while (!fcA(assistantfatevillion));
        while (fcA(assistantfatevillion));
        while (!fSwipeA(refreshfatevillion, leftx, samey));
        while (!fcA(implement));
        while (!fcA(back));
        while (fcA(back));
        while (!fcA(assistantalchemy));
        while (fcA(assistantalchemy));
        while (!fA(back));
        if (!fA(stopassistant)) {
            fcA(claimalchemyassistant);
            while (!fcA(implementalchemyassistant));
        }
        while (!fcA(back));
        while (fcA(back));
        while (!fcA(assistantbounty));
        while (!fA(back))fcA(assistantbounty);
        while (fcCompareMultipleTemplateA(yellowcollection, collections) || fcCompareMultipleTemplateA(yellowwanted, wanted)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if(!fcZoneA(completebounty,Z))break;
        }
        while (fcCompareMultipleTemplateA(purplecollection, collections)||fcCompareMultipleTemplateA(purplewanted, wanted)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if (!fcZoneA(completebounty, Z))break;
        }
        while (fcCompareMultipleTemplateA(bluecollection, collections)|| fcCompareMultipleTemplateA(bluewanted, wanted)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if (!fcZoneA(completebounty, Z))break;
        }
        while (!fcA(back));
        while(!fcA(assistantdailytask))fcA(back);
        while (!fA(back))fcA(assistantdailytask);
        fcA(quickimplement);
        while (fA(quickimplement))fcA(secttaskassistant);
        while (fcCompareMultipleTemplateA(atask, tasks)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if(!fcZoneA(starttask,Z))break;
        }
        while (fcCompareMultipleTemplateA(btask, tasks)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if (!fcZoneA(starttask, Z))break;
        }
        while (fcCompareMultipleTemplateA(ctask, tasks)) {
            Coords other = { C.x + dimX * 0.72,C.y + 0.13 * dimY };
            Zone Z = { C,other };
            if (!fcZoneA(starttask, Z))break;
        }
        while (fcA(back));
        while (!fA(ctown))adb.touch(0.5 * dimX, 0.95 * dimY);
        goHome();

    }
    catch (int e) {
        return;
    }
}

void OVMT::doDivinities()
{
    try {
        goHome();
        adb.swipe(0.4 * dimX, 0.5 * dimY, 0.6 * dimX, 0.5 * dimY, 1000);
        while (!fA(divinities)) {
            adb.swipe(0.3 * dimX, 0.5 * dimY, 0.7 * dimX, 0.5 * dimY, 1000);
        }
        while (!fA(mail)) {
            adb.swipe(0.3 * dimX, 0.5 * dimY, 0.7 * dimX, 0.5 * dimY, 1000);
        }
        while(!fcA(divinities))
        while (!fcA(immortalbanquet)) {
            fcA(divinities);
        }
        while (fcA(immortalbanquet));
        std::vector<std::string>choice;
        choice = { invitebanquet,partyover };
        while (!fOneTemplateA(choice));
        if (fcA(invitebanquet)) {
            while (fcA(invitebanquet));
            while (!fcA(bagbanquet));
            while (fcA(bagbanquet));
        }
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doGate()
{
}

void OVMT::doHeirloom()
{
    try {
        goHome();
        while (!fA(divinities)) {
            adb.swipe(0.4 * dimX, 0.5 * dimY, 0.6 * dimX, 0.5 * dimY, 500);
        }
        while (!fcA(heirloom)) {
            adb.swipe(0.6 * dimX, 0.5 * dimY, 0.4 * dimX, 0.5 * dimY, 500);
        }
        while (fcA(heirloom));
        while (!fcA(cexotic));
        if (fA(freeexplore)) {
            if (fcCompareA(exploreonce, explore10)) {
                while(fcA(tapblank));
            }
        }
        while (!fcA(cspiritland));
        if (fA(freeexplore)) {
            if (fcCompareA(exploreonce, explore10)) {
                while (fcA(tapblank));
            }
        }
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doMail()
{
    try {
        goHome();
        while (!fA(divinities)) {
            adb.swipe(0.4*dimX,0.5 * dimY,0.6*dimX , 0.5 * dimY, 1000);
        }
        while (fA(divinities)&&!fcA(mail)) {
            adb.swipe(0.6 * dimX, 0.5 * dimY, 0.4 * dimX, 0.5 * dimY, 1000);
        }
        while(!fcA(claimallmail))fcA(mail);
        while (fcA(tapblank));
        goHome();


    }
    catch (int e) {
        return;
    }
}

void OVMT::doOtherworld()
{
    try {
        goHome();
        if (((getUTCDay() == Thursday && getUTCHour() > 16 && getUTCHour() < 23) || (getUTCDay() == Friday && getUTCHour() < 1))) {
            goHome();
            return;
        }

        while (!fcA(ctown));
        while (!fcA(otherworld)) {
            adb.swipe(0.8 * dimX, 0.5 * dimY, 0.3 * dimX, 0.5 * dimY, 500);
        }
        while (!fcA(xserverduel)) {
            fcA(otherworld);
        }
        while (!fA(refreshxserver)) {
            fcA(xserverduel);
        }
        std::vector<std::string>mybr = { myzeroxserver,myonexserver ,mytwoxserver ,mythreexserver ,myfourxserver ,myfivexserver ,mysixxserver ,mysevenxserver ,myeightxserver ,myninexserver };
        Unit mybillion(mybillionxserver, B);
        std::vector<Unit>myunits = { mybillion };
        std::vector<std::string>enemybr = { zeroxserver,onexserver,twoxserver,threexserver,fourxserver,fivexserver,sixxserver,sevenxserver,eightxserver,ninexserver };
        Unit enemybillion(billionxserver, B);
        Unit enemythousand(thousandxserver, K);
        Unit enemymillion(millionxserver, M);
        std::vector<Unit>enemyunits = { enemybillion,enemymillion,enemythousand };
        int nbrefresh = 0;
        int nbbattle = 0;
        bool nobattleleft = false;
        while (!fA(bottomxserver)) {
            adb.swipe(0.5 * dimX, 0.6 * dimY, 0.5 * dimX, 0.3 * dimY, 500);
        }
        int mypos;
        if (fA(battleotherworld)) {
            mypos = 1;
        }
        else mypos = 0;

        fOneTemplateMultipleTemplateA(yinyangxserver, S, mypos);
        Coords C1br = { C.x + getMatWidth(yinyangxserver) / 2,C.y - getMatWidth(yinyangxserver) / 2 };
        Coords C2br = { C1br.x + getMatWidth(yinyangxserver) * 4,C1br.y + getMatHeight(yinyangxserver) };
        Zone mybrZone = { C1br,C2br };
        mybrZone.showZone();
        Number myPower = fNumberDecimalA(mybr, myunits, mydotxserver, mybrZone);
        std::cout << myPower.nb;


        while (true) {
            bool onlysweep = false;
            fOneTemplateMultipleTemplateA(yinyangxserver, S, mypos + 1);
            Coords C1br = { C.x + getMatWidth(yinyangxserver) / 2,C.y - getMatWidth(yinyangxserver) / 2 };
            Coords C2br = { C1br.x + getMatWidth(yinyangxserver) * 4,C1br.y + getMatHeight(yinyangxserver) };
            Zone enemybrZone = { C1br,C2br };
            enemybrZone.showZone();
            Number enemyPower = fNumberDecimalA(enemybr, enemyunits, dotxserver, enemybrZone);
            std::cout << enemyPower.nb;
            bool retry = true;
            if (enemyPower.nb < myPower.nb / 50) {
                std::cout << "Rank Reset will fight weak ennemies" << std::endl;
                while (!fcA(xserverduel)) {
                    fcA(back);
                }
                while (!fA(refreshxserver)) {
                    fcA(xserverduel);
                }

                while (retry) {
                    fcOneTemplateMultipleTemplateA(challengexserver, N, 0);
                    std::vector<std::string> outcome = { victorytower,defeattower };
                    while (!fOneTemplateA(outcome)) {
                        std::vector<std::string>speed = { speedone,speedtwo,speedthree };
                        std::vector<std::string>infspeed = { speedone,speedtwo };
                        while (fOneTemplateA(speed)) {
                            while (!fA(speedthree)) {
                                if (!fcOneTemplateA(infspeed))break;
                            }
                        }
                        if (fA(duelinvitationxserver)) {
                            goto end;
                        }
                    }
                    if (fA(duelinvitationxserver)) {
                        goto end;
                    }
                    if (fA(victorytower)) {
                        while (fcA(victorytower));
                        while (fcA(tapblank));
                    }
                    if (fA(defeattower)) {
                        while (fcA(defeattower));
                        retry = false;
                    }

                }

            }
            if (enemyPower.nb < myPower.nb && !onlysweep && retry == true) {
                std::cout << "Same power enemies" << std::endl;
                fcOneTemplateMultipleTemplateA(challengexserver, S, 0);
                std::vector<std::string> outcome = { victorytower,defeattower };
                while (!fOneTemplateA(outcome)) {
                    std::vector<std::string>speed = { speedone,speedtwo,speedthree };
                    std::vector<std::string>infspeed = { speedone,speedtwo };
                    while (fOneTemplateA(speed)) {
                        while (!fA(speedthree)) {
                            if (!fcOneTemplateA(infspeed))break;
                        }
                    }
                    if (fA(duelinvitationxserver)) {
                        goto end;
                    }
                }
                if (fA(duelinvitationxserver)) {
                    goto end;
                }
                if (fA(victorytower)) {
                    while (fcA(victorytower));
                    while (fcA(tapblank));
                }
                if (fA(defeattower)) {
                    while (fcA(defeattower));
                    onlysweep = true;
                }
            }
            else {
                while (!fA(bottomxserver)) {
                    adb.swipe(0.5 * dimX, 0.6 * dimY, 0.5 * dimX, 0.3 * dimY, 500);
                }
                if (!fcA(battlexotherworld)) {
                    fcA(battleotherworld);
                    while (fcA(tapblank));
                    goto end;
                }
                else {
                    while (fcA(tapblank));
                }
            }

        }
        end:
    


        goHome();


    }

    catch (int e) {
        return;
    }
}

void OVMT::doPerks()
{
    try {
        goHome();
        while (!fcA(perks));
        while (fcA(perks));
        while (!fA(cdailyperks));
        while (fcA(claimperks));
        while (fcA(rewardtreasureperks));
        while (fcA(tapblank));        

        while (!fcA(cweeklyperks));
        while (fcA(claimperks));
        while (fcA(rewardtreasureperks));
        while (fcA(tapblank));
        
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doRanking()
{
    try {
        goHome();
        while (!fA(ranking)) {
            adb.swipe(0.8 * dimX, 0.5 * dimY, 0.3 * dimX, 0.5 * dimY, 1000);
        }
        while (!fcA(brranking)) {
            fcA(ranking);
        }
        wait(1000);
        while (fcCompareA(likeranking,clikeranking)); 
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doAbyss()
{
}

void OVMT::doDreamad()
{
}

void OVMT::doRessources()
{
    try {
        goHome();
        while (fcA(cultivationicon))while (fcA(confirmcultivation));;
        while (fcA(ressourcesicon)) {
            while (!fcA(claimedressources)) {
                fcA(claimexploration);
            }
        }
        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::doMonsterhunt()
{
}

void OVMT::doTower()
{
    try {
        goHome();

        goHome();
    }
    catch (int e) {
        return;
    }
}

void OVMT::craftNormalPill(std::vector<std::string>craftsdigits, std::vector<std::string>coremat, std::vector<std::string>outcomecraft, std::vector<std::string>goodoutcome, Zone craft, Zone matquality, int pillbeforeepic, bool& cancraftmat, Coords cmaterial, std::string core, bool& cancraftanymat) {
    while (!fA(craftingmaterial)) {
        adb.touch(cmaterial.x, cmaterial.y);
        if (fA(nopillmat)) {
            cancraftanymat = false;
            return;
        }
    }
    int multiplier = 1;
    if (core == bluecore)multiplier = 4;
    else if (core == greencore)multiplier = 1;
    else if (core == graycore)multiplier = 0;

    if (fcCompareMultipleTemplateZoneA(core, coremat, matquality)) {
        while (fcCompareMultipleTemplateZoneA(core, coremat, matquality));
        while (!fA(quantitypill)) {
            fcA(craftpill);
        }
        Number nbpillCraft = fNumberIntegerA(craftsdigits, craft);
        int compteur = 0;
        while (nbpillCraft.nb * multiplier - pillbeforeepic >= multiplier && nbpillCraft.nb > 0) {
            nbpillCraft.nb--;
            compteur++;
            fcdA(lowerpill);
            std::cout << "Minus one" << std::endl;
        }
        while (fcA(confirmpillquantity));
        while (!fOneTemplateA(outcomecraft))fA(activecauldron);
        while (fcOneTemplateA(goodoutcome));
        if (fA(nopillmat)) {
            while (!fA(cauldron))adb.touch(0.5 * dimX, 0.999 * dimY);
        }
        if (compteur == 0) cancraftmat = false;
    }
    else {
        while (!fA(cauldron))adb.touch(0.5 * dimX, 0.999 * dimY);
        cancraftmat = false;
    }
}

void OVMT::craftBetterPill(std::vector<std::string>craftsdigits, std::vector<std::string>coremat, std::vector<std::string>outcomecraft, std::vector<std::string>goodoutcome, Zone craft, Zone matquality, bool& cancraftmat, Coords cmaterial, std::string core, bool& cancraftbetterpill, bool& cancraftanymat) {
    while (!fA(craftingmaterial)) {
        adb.touch(cmaterial.x, cmaterial.y);
        if (fA(nopillmat)) {
            cancraftanymat = false;
            return;
        }
    }
    if (fcCompareMultipleTemplateZoneA(core, coremat, matquality)) {
        while (fcCompareMultipleTemplateZoneA(core, coremat, matquality));
        while (!fA(quantitypill)) {
            fcA(craftpill);
        }
        Number nbpillCraft = fNumberIntegerA(craftsdigits, craft);
        if (nbpillCraft.nb == 1) {
            fcA(confirmpillquantity);
            while (!fOneTemplateA(outcomecraft))fA(activecauldron);
            if (fcOneTemplateA(goodoutcome)) {
                cancraftmat = false;
            }
            else if (fA(nopillmat)) {
                while (!fA(cauldron))adb.touch(0.5 * dimX, 0.999 * dimY);
            }
            cancraftmat = false;
        }
        else {
            fSwipeA(buttonchoosequantity, leftx, samey);
            fcA(confirmpillquantity);
            while (!fcOneTemplateA(goodoutcome));
            cancraftbetterpill = false;
        }
    }
    else {
        while (!fA(cauldron))adb.touch(0.5 * dimX, 0.999 * dimY);
        cancraftmat = false;
    }
}




void OVMT::showlistCoords() {
    for (int i = 0; i < listcoords.size(); i++) {
        std::cout << "C" << i << ": ";
        std::cout << "x: " << listcoords.at(i).x << " y: " << listcoords.at(i).y;
    }
    std::cout << std::endl;
}
int OVMT::getMatWidth(const std::string& namemat)
{
    return op.CreateMat(namemat).cols;
}
int OVMT::getMatHeight(const std::string& namemat)
{
    return op.CreateMat(namemat).rows;
}
void OVMT::setPort(int port) {
    adb.setPort(port);
}
int OVMT::getDimX() {
    return dimX;
}
int OVMT::getDimY() {
    return dimY;
}
int OVMT::getYear() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_year + 1900;
}
int OVMT::getMonth() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_mon + 1;
}
int OVMT::getDay() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    int dayOfWeek = now.tm_wday;
    if (dayOfWeek == 0) {
        dayOfWeek = 7;
    }
    return dayOfWeek;
}

int OVMT::getUTCDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    struct tm utc_time;
    gmtime_s(&utc_time, &current_time);

    int day = utc_time.tm_wday;
    if (day == 0)
        day = 7;

    return day;
}
int OVMT::getUTCHour() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    struct tm utc_time;
    gmtime_s(&utc_time, &current_time);
    return utc_time.tm_hour;

}
int OVMT::getHour() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_hour;
}
int OVMT::getMinute() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_min;
}
int OVMT::getSecond() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    return now.tm_sec;
}

void OVMT::swipeleftmenu() {
    for (int i = 0; i < 5; i++) {
        adb.swipe(0.1 * dimX, 500, 0.9 * dimX, 500, 500);
    }
}
void OVMT::swipemiddlemenu() {
    swipeleftmenu();
    for (int i = 0; i < 2; i++) {
        adb.swipe(dimX - dimX / 4, 500, 100, 500, 500);
    }
}
void OVMT::swiperightmenu() {
    for (int i = 0; i < 5; i++) {
        adb.swipe(dimX * 0.9, dimY / 2, 0.1 * dimX, dimY / 2, 500);
    }
}


int OVMT::getCx()const {
    return C.x;
}
int OVMT::getCy()const {
    return C.y;
}

void OVMT::setRebootCount(int nb) {
    rebootCount = nb;
}

int OVMT::getRebootCount() {
    return rebootCount;
}

void OVMT::setDimX(int x) {
    dimX = x;
}
void OVMT::setDimY(int y) {
    dimY = y;
}





bool OVMT::fcA(std::string imgtemplate) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    Template mat(imgtemplate, op.CreateGrayMat(imgtemplate));
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fcpopupA(const Template& bmat)
{
    for (int i = 0; i < listPopup.size(); ++i) {
        if (op.cvmtfTemplate(listPopup.at(i).T, bmat, C)) {
            state cond = listPopup.at(i).cond;
            switch (cond) {
            case state::block:
                adb.touch(C.x, C.y);
                wait(2500);
                return true;
                break;

            case state::disconnect:
                restartMacro = true;
                throw 20;
                break;
            }
        }

    }
    return false;
}

void OVMT::fillPopup()
{
    std::vector<std::string> discpopup = {};
    std::vector<std::string> blockpopup = {};
    for (std::string discstr : discpopup) {
        Popup P(discstr, state::disconnect);
        listPopup.push_back(P);
    }
    for (std::string blockstr : blockpopup) {
        Popup P(blockstr, state::block);
        listPopup.push_back(P);
    }
}

bool OVMT::fcOneTemplateMultipleTemplateA(std::string imgtemplate, pos direction, int order) {
    std::vector<Coords>list;
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template mat(imgtemplate, op.CreateGrayMat(imgtemplate));
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplate(mat, bmat, list)) {
        rebootCount = 0;
        restartMacro = false;
        list = orderCoords(list, direction);
        if (order < 0)order = 0;
        if (order >= list.size())order = list.size() - 1;
        C = list.at(order);
        adb.touch(C.x, C.y);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}


bool OVMT::fOneTemplateMultipleTemplateA(std::string imgtemplate, pos direction, int order) {
    std::vector<Coords>list;
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template mat(imgtemplate, op.CreateGrayMat(imgtemplate));
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplate(mat, bmat, list)) {
        rebootCount = 0;
        restartMacro = false;
        list = orderCoords(list, direction);
        if (order < 0)order = 0;
        if (order >= list.size())order = list.size() - 1;
        C = list.at(order);
        return true;
    }
    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fnbTemplateA(std::string imgtemplate, int& nb)
{
    std::vector<Coords>list;
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        nb = 0;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template mat(imgtemplate, op.CreateGrayMat(imgtemplate));
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplate(mat, bmat, list)) {
        rebootCount = 0;
        restartMacro = false;
        nb = list.size();
        return true;
    }

    else {
        nb = 0;
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fnbTemplateZoneA(std::string imgtemplate, int& nb, Zone Z)
{
    std::vector<Coords>list;
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        nb = 0;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template mat(imgtemplate, op.CreateGrayMat(imgtemplate));
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplateZone(mat, bmat, list, Z)) {
        rebootCount = 0;
        restartMacro = false;
        nb = list.size();
        return true;
    }

    else {
        nb = 0;
        wait(1000);
        rebootCount++;
        return false;
    }
}


bool OVMT::fcCompareA(std::string goodTemplate, std::string similartemplate)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, typeMat::Color);
    Template smat(similartemplate, typeMat::Color);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (goodTemplate != similartemplate && op.cvmtfCompareTemplate(goodmat, bmat, smat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fCompareA(std::string goodTemplate, std::string similartemplate)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, Color);
    Template smat(similartemplate, Color);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (goodTemplate != similartemplate && op.cvmtfCompareTemplate(goodmat, bmat, smat, C)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fcCompareMultipleTemplateA(std::string goodTemplate, std::vector<std::string> similartemplates)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, op.CreateMat(goodTemplate));

    std::vector<Template>simMats;
    for (std::string smat : similartemplates) {
        Template simMat(smat, Color);
        simMats.push_back(simMat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfCompareMultipleTemplate(goodmat, bmat, simMats, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fCompareMultipleTemplateA(std::string goodTemplate, std::vector<std::string> similartemplates)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, Color);
    std::vector<Template>simMats;

    for (std::string smat : similartemplates) {
        Template simMat(smat, Color);
        simMats.push_back(simMat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfCompareMultipleTemplate(goodmat, bmat, simMats, C)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fCompareMultipleTemplateZoneA(std::string goodTemplate, std::vector<std::string> similartemplates, Zone Z)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, Color);
    std::vector<Template>simMats;

    for (std::string& smat : similartemplates) {
        Template simMat(smat, Color);
        simMats.push_back(simMat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfCompareMultipleTemplateZone(goodmat, bmat, simMats, C, Z)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fcCompareMultipleTemplateZoneA(std::string goodTemplate, std::vector<std::string> similartemplates, Zone Z)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, Color);
    std::vector<Template>simMats;

    for (std::string& smat : similartemplates) {
        Template simMat(smat, Color);
        simMats.push_back(simMat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfCompareMultipleTemplateZone(goodmat, bmat, simMats, C, Z)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fMultipleCompareMultipleTemplateA(std::string goodTemplate, std::vector<std::string> similartemplates)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template goodmat(goodTemplate, Color);
    std::vector<Template>simMats;

    for (std::string& smat : similartemplates) {
        Template simMat(smat, Color);
        simMats.push_back(simMat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplateCompareMultipleTemplate(goodmat, bmat, simMats, listcoords)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fcOneTemplateA(std::vector<std::string> allTempl)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::vector<Template>allMats;

    for (std::string& mat : allTempl) {
        Template Mat(mat, Gray);
        allMats.push_back(Mat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.type = Gray;
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfOneTemplate(allMats, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fOneTemplateA(std::vector<std::string> allTempl)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::vector<Template>allMats;
    for (std::string& mat : allTempl) {
        Template Mat(mat, op.CreateGrayMat(mat));
        allMats.push_back(Mat);
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfOneTemplate(allMats, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}
bool OVMT::fOneMultipleTemplateA(std::vector<std::vector<std::string>> allTempl)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::vector<Template>listMat;
    std::vector<std::vector<Template>>allMats;
    for (int i = 0; i < allTempl.size(); ++i) {
        for (int j = 0; j < allTempl.at(i).size(); ++j) {
            Template Mat(allTempl.at(i).at(j), Gray);
            listMat.push_back(Mat);
        }
        allMats.push_back(listMat);
        listMat.clear();
    }
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfOneMultipleTemplate(allMats, bmat, listcoords)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fSwipeA(std::string imgtemplate, Coords Cresult)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(Mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.swipe(C.x, C.y, Cresult.x, Cresult.y, 1000);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}
bool OVMT::fSwipeA(std::string imgtemplate, poswipe endx, poswipe endy)
{
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
        throw 20;
        return false;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(Mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        int Cendx, Cendy;
        switch (endx) {
        case samex:
            Cendx = C.x;
            break;
        case rightx:
            Cendx = dimX;
            break;
        case leftx:
            Cendx = 0;
            break;
        default:
            Cendx = 0;
            break;
        }
        switch (endy) {
        case samey:
            Cendy = C.y;
            break;
        case upy:
            Cendy = 0;
            break;
        case downy:
            Cendy = dimY;
            break;
        default:
            Cendy = 0;
            break;
        }
        adb.swipe(C.x, C.y, Cendx, Cendy, 1000);
        wait(3000);
        return true;
    }

    else {
        wait(1000);
        rebootCount++;
        return false;
    }
}

bool OVMT::fcZoneA(std::string imgtemplate, Zone Z) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (restartMacro) {
        throw 20;
        return false;
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfZone(Mat, bmat, C, Z)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(3000);
        return true;
    }

    else {
        rebootCount++;
        return false;
    }
}
bool OVMT::fZoneA(std::string imgtemplate, Zone Z) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (restartMacro) {
        throw 20;
        return false;
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfZone(Mat, bmat, C, Z)) {
        rebootCount = 0;
        restartMacro = false;
        wait(3000);
        return true;
    }

    else {
        rebootCount++;
        return false;
    }
}

bool OVMT::fcdA(std::string imgtemplate) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (restartMacro) {
        throw 20;
        return false;
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(Mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        return true;
    }

    else {
        rebootCount++;
        return false;
    }
}

bool OVMT::fcMoreDelayA(std::string imgtemplate) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    if (restartMacro) {
        throw 20;
        return false;
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(Mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        adb.touch(C.x, C.y);
        wait(6000);
        return true;
    }

    else {
        rebootCount++;
        return false;
    }
}




void OVMT::test()
{
    restartMacro = false;
    rebootCount = 0;
    try {

    }
    catch (int e) {
        return;
    }
}


bool OVMT::fMultipleTemplateA(std::string img) {
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template Mat(img, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfMultipleTemplate(Mat, bmat, listcoords)) {
        rebootCount = 0;
        restartMacro = false;
        return true;
    }

    if (restartMacro) {
        throw 20;
        return false;
    }
    else {
        rebootCount++;
        return false;
    }
}

bool OVMT::fA(std::string imgtemplate) {
    if (rebootCount >= 25) {
        std::cout << "Relance du jeu\n" << std::endl;
        restartMacro = true;
    }
    while (waitMacro) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    Template Mat(imgtemplate, Gray);
    Template bmat;
    do {
        adb.screenshot();
        bmat.mat = op.CreateGrayMat(backg);
        bmat.id = backg;
    } while (fcpopupA(bmat));

    if (op.cvmtfTemplate(Mat, bmat, C)) {
        rebootCount = 0;
        restartMacro = false;
        wait(500);
        return true;
    }
    if (restartMacro) {
        throw 20;
        return false;
    }
    else {
        rebootCount++;
        wait(300);
        return false;
    }
}

void OVMT::wait(int milliSeconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
}

bool OVMT::fMultipleDigitsA(int nb, std::vector<std::string>figures, Zone Z) {
    std::string imagetofind;
    switch (nb) {
    case 0:
        imagetofind = figures.at(0);
        break;
    case 1:
        imagetofind = figures.at(1);
        break;
    case 2:
        imagetofind = figures.at(2);
        break;
    case 3:
        imagetofind = figures.at(3);
        break;
    case 4:
        imagetofind = figures.at(4);
        break;
    case 5:
        imagetofind = figures.at(5);
        break;
    case 6:
        imagetofind = figures.at(6);
        break;
    case 7:
        imagetofind = figures.at(7);
        break;
    case 8:
        imagetofind = figures.at(8);
        break;
    case 9:
        imagetofind = figures.at(9);
        break;
    }
    Template Tdigit(imagetofind, op.CreateMat(imagetofind));
    Template Tbackg(backg, op.CreateMat(backg));
    std::vector<Template>Tdigits;
    for (std::string dig : figures) {
        Template t(dig, op.CreateMat(dig));
        Tdigits.push_back(t);
    }
    return op.cvmtfMultipleTemplateCompareMultipleTemplateZone(Tdigit, Tbackg, Tdigits, listcoords, Z);
}

Number OVMT::fNumberIntegerA(std::vector<std::string>figures, std::vector<Unit>Units, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    for (int i = 0; i < 10; ++i) {
        listcoords.clear();
        if (fMultipleDigitsA(i, figures, Z)) {
            for (int j = 0; j < listcoords.size(); ++j) {
                Dtemp.Cnb = listcoords.at(j);
                Dtemp.nb = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }
    std::vector<std::string>allsameImages;
    for (std::string image : figures) {
        allsameImages.push_back(image);
    }
    for (Unit image : Units) {
        allsameImages.push_back(image.nameunit);
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).nb * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    for (Unit u : Units) {
        switch (u.Ord) {

        case Orders::noOrd:
            break;
        case Orders::K:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.K = true;
                Ntemp.nb *= pow(10, 3);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::M:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.M = true;
                Ntemp.nb *= pow(10, 6);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::B:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.B = true;
                Ntemp.nb *= pow(10, 9);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::T:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.T = true;
                Ntemp.nb *= pow(10, 12);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        }

    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number OVMT::fNumberIntegerA(std::vector<std::string>figures, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    for (int i = 0; i < 10; ++i) {
        listcoords.clear();
        if (fMultipleDigitsA(i, figures, Z)) {
            for (int j = 0; j < listcoords.size(); ++j) {
                Dtemp.Cnb = listcoords.at(j);
                Dtemp.nb = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }
    std::vector<std::string>allsameImages;
    for (std::string image : figures) {
        allsameImages.push_back(image);
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).nb * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number OVMT::fNumberDecimalA(std::vector<std::string>figures, std::vector<Unit>Units, std::string dot, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    for (int i = 0; i < 10; ++i) {
        listcoords.clear();
        if (fMultipleDigitsA(i, figures, Z)) {
            for (int j = 0; j < listcoords.size(); ++j) {
                Dtemp.Cnb = listcoords.at(j);
                Dtemp.nb = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }

    std::vector<std::string>allsameImages;
    for (std::string image : figures) {
        allsameImages.push_back(image);
    }
    for (Unit image : Units) {
        allsameImages.push_back(image.nameunit);
    }
    Coords Cdot;
    if (fCompareMultipleTemplateZoneA(dot, allsameImages, Z)) {
        Ntemp.decimal = true;
        Cdot = C;
        std::cout << "DECIMAL NUMBER" << std::endl;
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).nb * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    if (Ntemp.decimal == true) {
        for (int i = 0; i < Ntemp.digits.size(); i++) {
            if (Cdot.x < Ntemp.digits.at(i).Cnb.x) {
                Ntemp.dotposition = i;
                Ntemp.nb /= pow(10, Ntemp.digits.size() - i);
                std::cout << "Dot position:" << i << std::endl;
                break;
            }
        }
    }
    std::cout << Ntemp.nb << std::endl;
    for (Unit u : Units) {
        switch (u.Ord) {

        case Orders::noOrd:

            break;
        case Orders::K:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.K = true;
                Ntemp.nb *= pow(10, 3);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::M:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.M = true;
                Ntemp.nb *= pow(10, 6);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::B:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.B = true;
                Ntemp.nb *= pow(10, 9);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        case Orders::T:
            if (fCompareMultipleTemplateZoneA(u.nameunit, allsameImages, Z)) {
                Ntemp.T = true;
                Ntemp.nb *= pow(10, 12);
                std::cout << Ntemp.nb << std::endl;
                return Ntemp;
            }
            break;
        }
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}

Number OVMT::fNumberDecimalA(std::vector<std::string>figures, std::string dot, Zone Z) {
    adb.screenshot();
    Number Ntemp;
    Digit Dtemp;
    for (int i = 0; i < 10; ++i) {
        listcoords.clear();
        if (fMultipleDigitsA(i, figures, Z)) {
            for (int j = 0; j < listcoords.size(); ++j) {
                Dtemp.Cnb = listcoords.at(j);
                Dtemp.nb = i;
                Ntemp.digits.push_back(Dtemp);
            }
        }
    }

    std::vector<std::string>allsameImages;
    for (std::string image : figures) {
        allsameImages.push_back(image);
    }
    Coords Cdot;
    if (fCompareMultipleTemplateZoneA(dot, allsameImages, Z)) {
        Ntemp.decimal = true;
        Cdot = C;
        std::cout << "DECIMAL NUMBER" << std::endl;
    }
    orderDigits(Ntemp.digits);
    for (int l = 0; l < Ntemp.digits.size(); ++l) {
        Ntemp.nb += Ntemp.digits.at(l).nb * pow(10, Ntemp.digits.size() - l - 1);
    }
    std::cout << Ntemp.nb << std::endl;
    if (Ntemp.decimal == true) {
        for (int i = 0; i < Ntemp.digits.size(); i++) {
            if (Cdot.x < Ntemp.digits.at(i).Cnb.x) {
                Ntemp.dotposition = i;
                Ntemp.nb /= pow(10, Ntemp.digits.size() - i);
                std::cout << "Dot position:" << i << std::endl;
                break;
            }
        }
    }
    std::cout << Ntemp.nb << std::endl;
    return Ntemp;
}




void OVMT::orderDigits(std::vector<Digit>& digits) {
    std::sort(digits.begin(), digits.end(), [&](const Digit& a, const Digit& b) {
        return a.Cnb.x < b.Cnb.x;
        });
}

int OVMT::distancePoint(const Coords& fixpt, const Coords& pt)
{
    return (int)sqrt(pow(fixpt.x - pt.x, 2) + pow(fixpt.y - pt.y, 2));
}


std::vector<Coords> OVMT::orderCoords(const std::vector<Coords>& coordes, pos range) {
    std::vector<Coords> coords = coordes;

    switch (range) {
    case N:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y < b.y;
            });
        break;

    case S:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y > b.y;
            });
        break;

    case W:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x < b.x;
            });
        break;

    case E:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x > b.x;
            });
        break;

    case NW:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x + a.y < b.x + b.y;
            });
        break;

    case NE:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x - a.y > b.x - b.y;
            });
        break;

    case SW:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.y - a.x > b.y - b.x;
            });
        break;

    case SE:
        std::sort(coords.begin(), coords.end(), [](const Coords& a, const Coords& b) {
            return a.x + a.y > b.x + b.y;
            });
        break;
    }


    return coords;
}

std::vector<Coords> OVMT::orderPoint(const std::vector<Coords>& coords, const Coords& Cf)
{
    std::vector<Coords> newcoords = coords;
    std::sort(newcoords.begin(), newcoords.end(), [&](const Coords& a, const Coords& b) {
        int distanceA = distancePoint(a, Cf);
        int distanceB = distancePoint(b, Cf);
        return distanceA < distanceB;
        });
    return newcoords;
}












