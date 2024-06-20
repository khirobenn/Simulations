#include "main_functions.h"

int main(){

    srand(time(NULL));

    while(true){

        int choice;
        do{
            printf("\e[1;1H\e[2J");
            cout << "****** Menu ******"  << endl;
            cout << "1. Balls simulation." << endl;
            cout << "2. Particles simulation. (Blue : No collision || Red : Collision)" << endl;
            cout << "3. Rotation simulation." << endl;
            cout << "4. Quit." << endl;
            cout << "--> ";
            cin >> choice;
        }while(choice <= 0 || choice >= 5);

        if(choice == 4) break;

        int mode;
        
        do{
            printf("\e[1;1H\e[2J");
            cout << "Choose mode" << endl;
            switch(choice){
                case 1:
                case 2:
                    cout << "1. Without quad-tree grid." << endl;
                    cout << "2. With quad-tree grid." << endl;
                    cout << "--> ";
                    cin >> mode;
                    printf("\e[1;1H\e[2J");
                    cout << "Use left click of the mouse to add a ball in the screen." << endl;
                    break;
                case 3:
                    cout << "1. Rotation simple ( x² + y² = radius² )." << endl;
                    cout << "2. Infinity symbol rotation. " << endl;
                    cout << "--> ";
                    cin >> mode;
                    break;
            }
        } while(mode != 1 && mode != 2);

        RenderWindow window(VideoMode(WIDTH, HEIGHT), "Ball Test");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        switch(choice){
            case 1:
                Balls_Physic_Simulation<Ball>(window, mode);
                break;
            case 2:
                Balls_Physic_Simulation<Particle>(window, mode);
                break;
            case 3:
                Rotation(window, mode-1);
                break;
        }
        
    }

    printf("\e[1;1H\e[2J");
    cout << "Thank you for trying my simulation and have a good day!" << endl;

    return 0;
}