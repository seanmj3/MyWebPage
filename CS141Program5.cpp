#include <iostream>   // For Input and Output
#include <vector>     // For vector functionalities
#include <fstream>    // For reading in .txt files or CSV files 
#include <cctype>     // Allows use of tolower() & toupper()
#include <cassert>    // For the assert statement used to validate file open
#include <sstream>
#include <string>     // For access to String functions
using namespace std;

// First display and prompt to user when program is run
void firstDisplay() {
cout << "Program 5: March Madness Frenzy"
     << "CS 141, Spring 2022, UIC"
     << "This program reads in data from NCAA Basketball Tournaments (aka March" 
     << "Madness). It provides overall information regarding the data, allows you to "
     << "see the path taken to the championship, uses rankings of teams to determine "
     << "which region is expected to win at a given round and to find the best underdog "
     << "team, and calculates point differences within the games. You can also compare "
     << "the actual brackets to your own predictions!\n" << endl; 
}

// Displays menu options to the user after they enter the name of a file
void menuDisplay() {
    cout << "\nSelect a menu option: \n"  
    << "  1. Display overall information about the data\n"
    << "  2. Display the path of the winning team to the championship\n"
    << "  3. Determine which region is expected to win the championship based on a given round\n"
    << "  4. Identify the best underdog within a given round\n"
    << "  5. Find the shoo-in and nail-biting games within a given round, or overall\n"
    << "  6. Compare the actual brackets to your predicted brackets\n"
    << "  7. Exit\n"
    << "Your choice --> "; 
}

// Class for each game in respective CSV files
// This includes Getters and Setters  
class Game {
    public:
    //Fully qualified constructors
    void setRegion(string region) { this->region = region; }
    void setRank1(int rank1) { this->rank1 = rank1; }
    void setTeam1(string team1) { this->team1 = team1; }
    void setScore1(int score1) { this->score1 = score1; } 
    void setRank2(int rank2) { this->rank2 = rank2; }
    void setTeam2(string team2) { this->team2 = team2; }
    void setScore2(int score2) { this->score2 = score2; }
    void setWinner(string winner) { this->winner = winner; }
    void setRoundNum(int roundNum) { this->roundNum = roundNum; }
    void setGameNum(int gameNum) { this->gameNum = gameNum; }

    //Default Constructor for scores that had canceled games
    Game() { score1 = 0; score2 = 0; } 

    //Getters 
    string getRegion() { return region; }
    int getRank1() { return rank1; }
    string getTeam1() { return team1; }
    int getScore1() { return score1; }
    int getRank2() { return rank2; }
    string getTeam2() { return team2; }
    int getScore2() { return score2; }
    string getWinner() { return winner; }
    int getRoundNum() { return roundNum; }
    int getGameNum() { return gameNum; }

    private:
        string region;
        int rank1;
        string team1;
        int score1;
        int rank2; 
        string team2; 
        int score2; 
        string winner; 
        int roundNum;
        int gameNum;     
};

// This is a helper function to provide a string for each function call 
int fileOption(string fileChoice) {
    int fileNum = 0; 
    if (fileChoice == "mens_bracket_2021.csv") {
        fileNum = 1;
    } else if (fileChoice == "womens_bracket_2022.csv") {
        fileNum = 2;
    } else if (fileChoice == "mens_bracket_2022.csv") {
        fileNum = 3;
    } else if (fileChoice == "mens_bracket_2021_predictions1.csv") {
        fileNum = 4; 
    } else if (fileChoice == "mens_bracket_2021_predictions2.csv") {
        fileNum = 5; 
    } else if (fileChoice == "mens_bracket_2022_predictions1.csv") {
        fileNum = 6; 
    } else if (fileChoice == "womens_bracket_2022_predictions1.csv") {
        fileNum = 7; 
    } else {
        cout << "try again dude" << endl; 
    }
    return fileNum; 
}

// This function properly reads in the data from each csv file that is chosen 
void readInTournamentData(int fileNum, vector<Game>& tournamentGames) {
    ifstream inStream;
    if (fileNum == 1) {
        inStream.open("mens_bracket_2021.csv"); 
    } else if (fileNum == 2) {
        inStream.open("womens_bracket_2022.csv");
    } else if (fileNum == 3) {
        inStream.open("mens_bracket_2022.csv");
    } else if (fileNum == 4) { 
        inStream.open("mens_bracket_2021_predictions1.csv");
    } else if (fileNum == 5) {
        inStream.open("mens_bracket_2021_predictions2.csv");
    } else if (fileNum == 6) {
        inStream.open("mens_bracket_2022_predictions1.csv");
    } else if (fileNum == 7) {
        inStream.open("womens_bracket_2022_predictions1.csv");
    }
    

    assert(inStream.fail() == false);

    string recordLine;
    getline(inStream, recordLine); 

    while (getline(inStream, recordLine)) {
        stringstream s_stream(recordLine); 
        Game aGame; 

        int colNum = 0; 
        while (s_stream.good()) {
            string columnVal; 
            getline(s_stream, columnVal, ',');

            switch(colNum) {
                case 0:
                    aGame.setRegion(columnVal);
                    break; 
                case 1:
                    aGame.setRank1(stoi(columnVal));  
                    break;
                case 2:
                    aGame.setTeam1(columnVal); 
                    break;
                case 3:
                    if (columnVal == "") {
                        Game();  
                    } else {
                        aGame.setScore1(stoi(columnVal));
                    } 
                    break; 
                case 4: 
                    aGame.setRank2(stoi(columnVal)); 
                    break; 
                case 5: 
                    aGame.setTeam2(columnVal) ;
                    break; 
                case 6: 
                    if (columnVal == "") {
                        Game();
                    } else {
                        aGame.setScore2(stoi(columnVal));
                    } 
                    break; 
                case 7: 
                    aGame.setWinner(columnVal); 
                    break; 
                case 8:
                    aGame.setRoundNum(stoi(columnVal)); 
                    break; 
                case 9: 
                    aGame.setGameNum(stoi(columnVal)); 
                    break; 
            }
            colNum++; 
        }
        tournamentGames.push_back(aGame); 
    }
}

// Executes menu option 1 to display overall information about the data
void menuOption1(vector<Game>& tournamentRecords) {
    vector<Game> finalFour;
    vector<string> finalFourRegions;    

    for (int i = 0; i < tournamentRecords.size(); i++) {
        if (tournamentRecords.at(i).getRegion() == "Final Four") {
            finalFour.push_back(tournamentRecords.at(i)); 
        }
    } 
    cout << "Total number of games played in tournament: " << tournamentRecords.size() << endl;
    cout << "The Final Four contestants are:" << endl;
    for (int i = 0; i < tournamentRecords.size(); i++) {
        for (int j = 0; j < finalFour.size(); j++) {
            if (tournamentRecords.at(i).getRegion() != "Final Four" && tournamentRecords.at(i).getRegion() != "Championship") {
                if (tournamentRecords.at(i).getWinner() == finalFour.at(j).getTeam1()) {
                    finalFourRegions.push_back("\t" + tournamentRecords.at(i).getRegion() + " region: " + finalFour.at(j).getTeam1());
                    break;   
                } else if (tournamentRecords.at(i).getWinner() == finalFour.at(j).getTeam2()) {
                    finalFourRegions.push_back("\t" + tournamentRecords.at(i).getRegion() + " region: " + finalFour.at(j).getTeam2());
                    break; 
                } 
            }
        }
    }
    for (int i = 0; i < finalFourRegions.size(); i+=4) {
        cout << finalFourRegions.at(i) << endl; 
    }  
}

// Executes menu option 2 to display the path to the championship for a given winning team
void menuOption2(vector<Game>& tournamentRecords) {
    cout << "Path to the championship: " << endl;
    string champion = tournamentRecords.at(0).getWinner();
    string loser;   

    for (int i = tournamentRecords.size() - 1; i >= 0; i--) {
        if (tournamentRecords.at(i).getWinner() == champion) {
            cout << "Round " << tournamentRecords.at(i).getRoundNum() << ", Game " << tournamentRecords.at(i).getGameNum() <<  ": " << tournamentRecords.at(i).getTeam1() << " vs " << tournamentRecords.at(i).getTeam2() << ". Winner: " << champion << endl; 
        }
    }
}

// This predicts the region that is expected to win given each round
void menuOption3(vector<Game>& tournamentRecords) {        
    int roundChoice = 0; 

    cout << "Enter a round to be evaluated:\n"
    << "Select 2 for round 2\n"
    << "Select 3 for round 3 'Sweet 16'\n"
    << "Select 4 for round 4 'Elite 8'\n"
    << "Select 5 for round 5 'Final 4'\n"
    << "Your choice --> ";
    cin >> roundChoice;  
    cout << "Analyzing round " << roundChoice << "..." << endl; 
    if (roundChoice == 2) {
        int min = 0;
        string highestRank;  
        vector<int> ranks; 
        vector<Game> gamesInRound;
        int regionOneRank = 0, regionTwoRank = 0, regionThreeRank = 0, regionFourRank = 0;
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 2 ) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        } 
        for (int i = 0; i < 4; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionOneRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionOneRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 4; i < 8; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionTwoRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionTwoRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 8; i < 12; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionThreeRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionThreeRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 12; i < 16; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionFourRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionFourRank += gamesInRound.at(i).getRank2();
            }
        }

        ranks.push_back(regionOneRank); 
        ranks.push_back(regionTwoRank); 
        ranks.push_back(regionThreeRank); 
        ranks.push_back(regionFourRank); 

        for (int i = 0; i < ranks.size(); i++) {
            min = ranks.at(0); 
            if (ranks.at(i) < min) {
                min = ranks.at(i); 
            }
        }
        for (int i = 0; i < ranks.size(); i++) {
            if (regionOneRank == min) {
                highestRank = gamesInRound.at(0).getRegion(); 
            } else if (regionTwoRank == min) {
                highestRank = gamesInRound.at(4).getRegion();
            } else if (regionThreeRank == min) {
                highestRank = gamesInRound.at(8).getRegion();
            } else if (regionFourRank == min) {
                highestRank = gamesInRound.at(12).getRegion();
            }
        }
        cout << "\nThe region expected to win is: " << highestRank << endl;
    } else if (roundChoice == 3) {
        int min = 0;
        string highestRank;  
        vector<int> ranks; 
        vector<Game> gamesInRound;
        int regionOneRank = 0, regionTwoRank = 0, regionThreeRank = 0, regionFourRank = 0; 

        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 3 ) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        } 
        for (int i = 0; i < 2; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionOneRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionOneRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 2; i < 4; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionTwoRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionTwoRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 4; i < 6; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionThreeRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionThreeRank += gamesInRound.at(i).getRank2();
            }
        }
        for (int i = 6; i < 8; i++) {
            if (gamesInRound.at(i).getTeam1() == gamesInRound.at(i).getWinner()) {
                regionFourRank += gamesInRound.at(i).getRank1();
            } else if (gamesInRound.at(i).getTeam2() == gamesInRound.at(i).getWinner()) {
                regionFourRank += gamesInRound.at(i).getRank2();
            }
        }
            

        ranks.push_back(regionOneRank); 
        ranks.push_back(regionTwoRank); 
        ranks.push_back(regionThreeRank); 
        ranks.push_back(regionFourRank); 

        min = ranks.at(0);
        for (int i = 0; i < ranks.size(); i++) { 
            if (ranks.at(i) < min) {
                min = ranks.at(i); 
            }
        }   

        for (int i = 0; i < ranks.size(); i++) {
            if (regionOneRank == min) {
                highestRank = gamesInRound.at(0).getRegion(); 
            } else if (regionTwoRank == min) {
                highestRank = gamesInRound.at(2).getRegion();
            } else if (regionThreeRank == min) {
                highestRank = gamesInRound.at(4).getRegion();
            } else if (regionFourRank == min) {
                highestRank = gamesInRound.at(6).getRegion();
            } 
        } 
        cout << "\nThe region expected to win is: " << highestRank << endl;
    } else if (roundChoice == 4) {
        int min = 0;
        string highestRank;  
        vector<int> ranks; 
        vector<Game> gamesInRound;
        int regionOneRank = 0, regionTwoRank = 0, regionThreeRank = 0, regionFourRank = 0; 

        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 4) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        } 
        if (gamesInRound.at(0).getTeam1() == gamesInRound.at(0).getWinner()) {
            regionOneRank += gamesInRound.at(0).getRank1();
        } else if (gamesInRound.at(0).getTeam2() == gamesInRound.at(0).getWinner()) {
            regionOneRank += gamesInRound.at(0).getRank2();
        }
        if (gamesInRound.at(1).getTeam1() == gamesInRound.at(1).getWinner()) {
            regionTwoRank += gamesInRound.at(1).getRank1();
        } else if (gamesInRound.at(1).getTeam2() == gamesInRound.at(1).getWinner()) {
            regionTwoRank += gamesInRound.at(1).getRank2();
        }
        if (gamesInRound.at(2).getTeam1() == gamesInRound.at(2).getWinner()) {
            regionThreeRank += gamesInRound.at(2).getRank1();
        } else if (gamesInRound.at(2).getTeam2() == gamesInRound.at(2).getWinner()) {
            regionThreeRank += gamesInRound.at(2).getRank2();
        }
        if (gamesInRound.at(3).getTeam1() == gamesInRound.at(3).getWinner()) {
            regionFourRank += gamesInRound.at(3).getRank1();
        } else if (gamesInRound.at(3).getTeam2() == gamesInRound.at(3).getWinner()) {
            regionFourRank += gamesInRound.at(3).getRank2();
        }
            
        ranks.push_back(regionOneRank); 
        ranks.push_back(regionTwoRank); 
        ranks.push_back(regionThreeRank); 
        ranks.push_back(regionFourRank); 

        min = ranks.at(0);
        for (int i = 0; i < ranks.size(); i++) { 
            if (ranks.at(i) < min) {
                min = ranks.at(i); 
            }
        }   
        for (int i = 0; i < ranks.size(); i++) {
            if (regionOneRank == min) {
                highestRank = gamesInRound.at(0).getRegion(); 
            } else if (regionTwoRank == min) {
                highestRank = gamesInRound.at(1).getRegion();
            } else if (regionThreeRank == min) {
                highestRank = gamesInRound.at(2).getRegion();
            } else if (regionFourRank == min) {
                highestRank = gamesInRound.at(3).getRegion();
            } 
        } 
        cout << "\nThe region expected to win is: " << highestRank << endl;
    } else if (roundChoice == 5) {
        int min = 0;
        string highestRank;   
        vector<Game> gamesInRound;
        vector<Game> gamesInRound2;

        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 5) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 4) {
                gamesInRound2.push_back(tournamentRecords.at(i)); 
            }
        }
        min = gamesInRound.at(0).getRank1(); 
        for (int i = 0; i < gamesInRound.size(); i++) { 
            if (gamesInRound.at(i).getRank1() < min) { 
                highestRank = gamesInRound.at(i).getTeam1(); 
            } else if (gamesInRound.at(i).getRank2() < min) { 
                highestRank = gamesInRound.at(i).getTeam2(); 
            } else {
                highestRank = gamesInRound.at(0).getTeam1(); 
            }
        }
        for (int i = 0; i < gamesInRound2.size(); i++) {
            if (gamesInRound2.at(i).getTeam1() == highestRank) {
                cout << "The region expected to win is: " << gamesInRound2.at(i).getRegion() << endl;
                break;  
            } else if (gamesInRound2.at(i).getTeam2() == highestRank) {
                cout << "The region expected to win is: " << gamesInRound2.at(i).getRegion() << endl; 
            }
        }   
    } 
}

// Executes code to find the underdog of a given round
void menuOption4(vector<Game>& tournamentRecords) {
    int roundChoice = 0;  
    cout << "Enter a round to be evaluated:\n" 
         << "Select 2 for round 2\n"
         << "Select 3 for round 3 'Sweet 16'\n"
         << "Select 4 for round 4 'Elite 8'\n"
         << "Select 5 for round 5 'Final 4'\n"
         << "Select 6 for round 6 'Championship'\n"
         << "Your choice --> ";
    cin >> roundChoice; 
    
    if (roundChoice == 2) {
        vector<Game> gamesInRound;
        int lowestRank = 0;
        string underDog;  
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 2) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < gamesInRound.size(); i++) {
            if (gamesInRound.at(i).getRank1() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam1(); 
                lowestRank = gamesInRound.at(i).getRank1(); 
            }
            if (gamesInRound.at(i).getRank2() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam2(); 
                lowestRank = gamesInRound.at(i).getRank2(); 
            }
        }
        cout << "The best underdog team is " << underDog << " which has rank " << lowestRank << "." << endl; 
    } else if (roundChoice == 3) {
        vector<Game> gamesInRound;
        int lowestRank = 0;
        string underDog;  
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 3) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < gamesInRound.size(); i++) {
            if (gamesInRound.at(i).getRank1() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam1(); 
                lowestRank = gamesInRound.at(i).getRank1(); 
            }
            if (gamesInRound.at(i).getRank2() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam2(); 
                lowestRank = gamesInRound.at(i).getRank2(); 
            }
        }
        cout << "The best underdog team is " << underDog << " which has rank " << lowestRank << "." << endl;
    } else if (roundChoice == 4) {
        vector<Game> gamesInRound;
        int lowestRank = 0;
        string underDog;  
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 4) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < gamesInRound.size(); i++) {
            if (gamesInRound.at(i).getRank1() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam1(); 
                lowestRank = gamesInRound.at(i).getRank1(); 
            }
            if (gamesInRound.at(i).getRank2() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam2(); 
                lowestRank = gamesInRound.at(i).getRank2(); 
            }
        }
        cout << "The best underdog team is " << underDog << " which has rank " << lowestRank << "." << endl;
    } else if (roundChoice == 5) {
        vector<Game> gamesInRound;
        int lowestRank = 0;
        string underDog;  
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 5) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < gamesInRound.size(); i++) {
            if (gamesInRound.at(i).getRank1() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam1(); 
                lowestRank = gamesInRound.at(i).getRank1(); 
            }
            if (gamesInRound.at(i).getRank2() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam2(); 
                lowestRank = gamesInRound.at(i).getRank2(); 
            }
        }
        cout << "The best underdog team is " << underDog << " which has rank " << lowestRank << "." << endl;
    } else if (roundChoice == 6) {
        vector<Game> gamesInRound;
        int lowestRank = 0;
        string underDog;  
        for (int i = 0; i < tournamentRecords.size(); i++) {
            if (tournamentRecords.at(i).getRoundNum() == 6) {
                gamesInRound.push_back(tournamentRecords.at(i)); 
            }
        }
        for (int i = 0; i < gamesInRound.size(); i++) {
            if (gamesInRound.at(i).getRank1() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam1(); 
                lowestRank = gamesInRound.at(i).getRank1(); 
            } 
            if (gamesInRound.at(i).getRank2() > lowestRank) {
                underDog = gamesInRound.at(i).getTeam2(); 
                lowestRank = gamesInRound.at(i).getRank2(); 
            }
        }
        cout << "The best underdog team is " << underDog << " which has rank " << lowestRank << "." << endl;
    }
}

// Finds the shoo-in and nail-biter games of a given round or of the overall data
void menuOption5(vector<Game>& tournamentRecords) {
    int roundChoice = 0; 
    cout << "Enter a round to be evaluated:\n" 
         << "Select 1 for round 1\n"
         << "Select 2 for round 2\n"
         << "Select 3 for round 3 'Sweet 16'\n"
         << "Select 4 for round 4 'Elite 8'\n"
         <<  "Select 5 for round 5 'Final 4'\n"
         << "Select 6 for round 6 'Championship'\n"
         << "Select 7 for the overall tournament\n"
         << "Your choice --> ";
    cin >> roundChoice;
    if (roundChoice < 7) {
        cout << "Analyzing round " << roundChoice << "..." << endl;
    } else {
        cout << "Analyzing the overall tournament..." << endl; 
    }

    if (roundChoice == 1) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 1) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter  << " points." << endl;
    } else if (roundChoice == 2) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 2) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter  << " points." << endl;
    } else if (roundChoice == 3) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 3) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter << " points." << endl;
    } else if (roundChoice == 4) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 4) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter << " points." << endl;
    } else if (roundChoice == 5) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 5) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter << " points." << endl;
    } else if (roundChoice == 6) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
           if (tournamentRecords.at(i).getRoundNum() == 6) {
               gamesInRound.push_back(tournamentRecords.at(i)); 
           }  
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter << " points." << endl;
    } else if (roundChoice == 7) {
        int shooIn = 0;
        int nailBiter = 200; 
        int round = 0; 
        int gameNum = 0; 
        string team1; 
        string team2; 
        string winner;  
        vector<Game> gamesInRound;

       for (int i = 0; i < tournamentRecords.size(); i++) {
            gamesInRound.push_back(tournamentRecords.at(i));   
       }
       for (int i = 0; i < gamesInRound.size(); i++) {
           if ((gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2()) > shooIn) {
               shooIn = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() > shooIn) {
               shooIn = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();  
           } 
       } 
       cout << "\nThe shoo-in game was :" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << shooIn << " points." << endl;

       for (int i = 0; i < gamesInRound.size(); i++) {
           if (gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() < nailBiter && gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2() >= 0) {
               nailBiter = gamesInRound.at(i).getScore1() - gamesInRound.at(i).getScore2();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner(); 
           }
           if (gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() < nailBiter && gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1() >= 0) {
               nailBiter = gamesInRound.at(i).getScore2() - gamesInRound.at(i).getScore1();
               round = gamesInRound.at(i).getRoundNum(); 
               gameNum = gamesInRound.at(i).getGameNum(); 
               team1 = gamesInRound.at(i).getTeam1(); 
               team2 = gamesInRound.at(i).getTeam2(); 
               winner = gamesInRound.at(i).getWinner();
           }
       }
       cout << "\nThe nail-biting game was:" << endl; 
       cout << "Round " << round << ", Game " << gameNum << ": " << team1 << " vs " << team2 << ". Winner: " << winner << endl;
       cout << "The difference was " << nailBiter << " points." << endl;
    }
}

// Executes code to compare the actual data of the selected bracket to the data of a predicted bracket
void menuOption6(vector<Game>& tournamentRecords) {
    vector<Game> predictions; 
    string fileChoice;
    int score = 0, numCorrect = 0;
    ifstream inStream;   
    cout << "Enter the name of the file with your predicted brackets: ";
    cin >> fileChoice;
    
    readInTournamentData(fileOption(fileChoice), predictions);  

    for (int i = 0; i < predictions.size(); i++) {
        if ((predictions.at(i).getWinner() == tournamentRecords.at(i).getWinner())) { 
            numCorrect++;
            score += (predictions.at(i).getRoundNum() * 5); 
        }
    }
    cout << "You correctly predicted the winner for " << numCorrect << " games." << endl;
    cout << "This means that you have a score of " << score << "." << endl; 
    if (score >= 250) {
        cout << "Great job! You could consider entering your predictions to win money!" << endl; 
    } else {
        cout << "You may want to learn more about basketball to improve your predictions next year." << endl; 
    }
}

// Main function that executed the selected menu option
int main() {
    string fileChoice; 
    firstDisplay(); 
    cout << "Enter the name of the file with the data for the NCAA tournament:"; 
    cin >> fileChoice;

    vector<Game> tournamentRecords; 
    readInTournamentData(fileOption(fileChoice), tournamentRecords);
    int menuSelection = 0;
    
    while (true) {
        menuDisplay(); 
        cin >> menuSelection; 

        if (menuSelection == 7) {
            cout << "Exiting program...";
            break;
        } else if (menuSelection == 1) {
            menuOption1(tournamentRecords);
        } else if (menuSelection == 2) {
            menuOption2(tournamentRecords); 
        } else if (menuSelection == 3) {
            menuOption3(tournamentRecords);
        } else if (menuSelection == 4) {
            menuOption4(tournamentRecords); 
        } else if (menuSelection == 5) {
            menuOption5(tournamentRecords); 
        } else if (menuSelection == 6) {
            menuOption6(tournamentRecords);
        } else {
            cout << "Invalid value.  Please re-enter a value from the menu options below." << endl; 
        }
    } 
    return 0; 
}