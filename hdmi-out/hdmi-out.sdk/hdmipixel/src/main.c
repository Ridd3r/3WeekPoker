/*
 * main.c
 Version 1.0
 *
 *  Created on: Jan 3, 2022
 *      Author: gurk
 */
#include "graphics.h"
#include "display_ctrl/display_ctrl.h"
#include "math.h"
#include "timer_ps/timer_ps.h"
#include <stdio.h>
#include "xuartps.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "xtime_l.h"

XTime time;



//#include <time.h>

/*DisplayCtrl dispCtrl;
XAxiVdma vdma;*/


/*
int main(){
		initialize();
		setAmountOfPlayers(8);
		initializePlayerEmblems();
		initChips();
		initBalanceSheets();
		createBackground();
		saveBackground();

		//for display can manually change later
		setPlayerCards(0, 1, 3, 1);
		setPlayerCards(0, 2, 3, 2);

		setPlayerCards(1, 3, 3, 1);
		setPlayerCards(1, 4, 3, 2);

		setPlayerCards(2, 5, 1, 1);
		setPlayerCards(2, 6, 1, 2);

		setPlayerCards(3, 2, 4, 1);
		setPlayerCards(3, 3, 4, 2);

		setPlayerCards(4, 4, 4, 1);
		setPlayerCards(4, 5, 4, 2);

		setPlayerCards(5, 11, 2, 1);
		setPlayerCards(5, 12, 2, 2);

		setPlayerCards(6, 13, 2, 1);
		setPlayerCards(6, 1, 2, 2);

		setPlayerCards(7, 2, 1, 1);
		setPlayerCards(7, 3, 1, 2);

		//placeBacksideOfCard(250, 250);


		//initial draw, rest is handled by interrupts
		updateBackground();
		drawLayer();
		setFrameFlag(1);
		startOrStopScreenUpdate(1);//enable interrupts

		while(1){


			getInput();
			if(getFrameFlag() == 0){
				//printf("\n\r newframe");
				updateBackground();
				drawLayer();
				setFrameFlag(1);
			}


			//startOrStopScreenUpdate(1);
		}
	return 0;
}

*/
struct Card {
	int cardVal;
	int cardType;
};

struct Card table[5];
struct Card tmp1;
struct Card tmpCard[7]; // sorted hand plus Card on table
struct Card curBestHand[5]; // current best hand (max. 5 Card) for player xs

struct Deck {

	struct Deck* last;
	struct Deck* next;

	struct Card cardInfo;
	int deckPlacement;
	int cardDrawn;
};

struct Deck* head = NULL;
struct Deck* shuffledHead = NULL;
struct Deck* newCard = NULL;
struct Deck* tmp = NULL;
struct Deck* tmpDeckShuffle = NULL;

struct Deck* ERRORCHECKER = NULL;


struct Player {
	int inPlay;

	int playerNumber;
	struct Deck card1;
	struct Deck card2;
	struct Card bestHand[5];
	int balance;
	int stake;
	int dealer;
	int kicker;
	int fold;
	int currentBet;
	int totalBet;
	int handVal;
	int allIn;
};
struct Player allPlayers[8];
struct Player EvalHandVariable;

int evaluateHand();
int evalKind();
void sortHand();
void makeBestHand(int offset, int isRoyal, int isSeq, int pairKind, int doublePaired, int offset2, int isFlush, int kind);
void printBestHand();
void printSortedCard();
int checkSeq(); // checks whether Card are in sequense or not - i.e. straight, straight flush or royal flush
int checkPaired(); //  checks whether we have concurrent paired Card - 4 Of A Kind, Set, or Pair
int checkDoublePaired(); // check for full house or double pair
int checkFlush(); //Check for 5 of same type (kind)
int kicker(int isDouble, int highCard); // Finds kicker if there is one (Pair and Two Pair)
void printHandVal(int value);
void reInitCurrentHand();
void initializeComb(); //initialize tmpCard
void initTable();
int checkKicker(int kicker1, int kicker2);
int compareHands();
int compareTwoHands(struct Player playerOne, struct Player playerTwo);
int isStraight = 0;
void printHandsInPlay(struct Player *players);

void generateDeck();
void shuffleDeck();
int selectPlayers(int inputBalance);
int selectStartingPool();
int generateBlinds(int newTurn);
void turnStructure(int turn, int playerAmount);
int findDealer();
void setNewDealer();
void dealCard(int dealer);
void turn();
void flop();
void river();
int playerTurn(int highestBet, int currentTurn, int playerAmount, int dealer);
int playerTurnStop(int highestBet, int playerAmount);
void endTurnRemovals();
void distributePool(int pool);
void winCondition();


int STATE = 1;
int turnNumber = 1;
int pool = 0;
int foldCounter = 0;
int maxPlayerAmount = 8;
int currentPlayerAmount = 0;
int winners[8];
int globalTablePosition = 0;


/*
#######################################################################################################
GAME LOGIC CODE
#######################################################################################################
*/

// STRUCTURE FUNCTIONS
int main(void) {
	initialize();
	startOrStopScreenUpdate(1);//enable interrupts
	createBackground();
	saveBackground();

	while(getFrameFlag() == 1){};//wait until screen can be updated
	updateBackground();
	drawLayer();
	setFrameFlag(1);

	while (1) {
		switch (STATE) {
		case 1: // GAME SETUP

			printf("-- GAME SETUP --\n\n");

			currentPlayerAmount = selectPlayers(selectStartingPool());

			setAmountOfPlayers(currentPlayerAmount);
			initializePlayerEmblems();

			STATE = 2;
			break;

		case 2: // GAME ACTIVE
			XTime_GetTime(&time);
			srand((unsigned)time);
			turnStructure(turnNumber, currentPlayerAmount);
			break;

		case 3:
			return 0;
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;


		};
	}
}

void turnStructure(int newTurn, int playerAmount) {

	int dealer = 0;

	switch (newTurn) {
	case 1: // DEAL Card (TURN 1)
//////////////////////////graphic
		clearFoldstatus();
		removeChips();
		clearDealerCards();
		initBalanceSheets();

		updateBackground();
		while(getFrameFlag() == 1){};//wait until screen can be updated
		drawLayer();
		setFrameFlag(1);

//////////////////////////////
		generateDeck();
		shuffleDeck();
		dealer = findDealer();
		dealCard(dealer);

		// initialize table and player hands before flop
		initializeComb();
		reInitCurrentHand();
		printSortedCard();
		initTable();

		printf("\n\n\t --------   NEW TURN   --------\n");
		printf("\t --------   NEW TURN   --------\n");
		printf("\t --------   NEW TURN   --------\n\n");

		pool = playerTurn(generateBlinds(dealer), newTurn, playerAmount, dealer);

		setPool(pool);
		poolChip();


		printf("\nTurn 1 current pool: %d\n", pool);
		if (turnNumber != 5) {
			turnNumber = 2;
		}
		break;
	case 2: // FLOP (TURN 2)
		flop();

		pool = playerTurn(0, newTurn, playerAmount, dealer) + pool;


		setPool(pool);
		poolChip();


		printf("\nTurn 2 current pool: %d\n", pool);
		if (turnNumber != 5) {
				turnNumber = 3;
			}
		break;
	case 3: // TURN (TURN 3)
		turn();



		pool = playerTurn(0, newTurn, playerAmount, dealer) + pool;

		setPool(pool);
		poolChip();

		printf("\nTurn 3 current pool: %d\n", pool);
		if (turnNumber != 5) {
				turnNumber = 4;
			}
		break;
	case 4: // RIVER (TURN 4)
		river();



		pool = playerTurn(0, newTurn, playerAmount, dealer) + pool;

		setPool(pool);
		poolChip();

		printf("\nTurn 4 current pool: %d\n", pool);
		turnNumber = 5;
		break;

	case 5: // END TURN

		// DISTRIBUTE POOL TO WINNER(S)

		printf("\n\n\t -------- ENDING TURN ------- \n\n");

		printf("Total current pool: %d\n", pool);
		distributePool(pool);
		endTurnRemovals();
		winCondition();

		setPool(pool);
		removePoolChip();
		break;
	}

}

int playerTurn(int highestBet, int currentTurn,  int playerAmount, int dealer) {

	int tablePosition = 0;
	int turnSTATE = 1;
	int userInput;
	int firstTurnCounter = 0;
	int newPool = 0;
	int prevent = 0;

	while(getFrameFlag() == 1){};//wait until screen can be updated
	updateBackground();
	drawLayer();
	setFrameFlag(1);
	//TimerDelay(500);
	//updateBackground();


	while (turnSTATE == 1) {

		if (currentTurn == 1 && prevent == 0) {
			tablePosition = dealer + 3;
			printf("\n\tERRORCHECKER: TablePosition: set to %d\n", tablePosition);
			prevent++;
		}
		else if (currentTurn > 1 && prevent == 0) {
			if (globalTablePosition < maxPlayerAmount) {
				tablePosition = globalTablePosition + 1;
				printf("\n\tERRORCHECKER: TablePosition: set to %d\n", tablePosition);
				prevent++;
			}

			else if (currentTurn > 1 && globalTablePosition == maxPlayerAmount && prevent == 0){
				globalTablePosition = 0;
				tablePosition = globalTablePosition;
				printf("\n\tERRORCHECKER: TablePosition: set to %d\n", tablePosition);
				prevent++;
			}
		}
		else {
			printf("\n\tERRORCHECKER: TablePosition: 0\n");
			tablePosition = 0;
		}

		for (int i = tablePosition; i < maxPlayerAmount; i++) {

			globalTablePosition = i;

			if (allPlayers[i].inPlay == 1) {



				printf("\n\tERRORCHECKER: Foldercounter: %d | %d\n", foldCounter, playerAmount - 1);
				printf("\n\tERRORCHECKER: FirstTurnCounter: %d | %d\n", firstTurnCounter, currentPlayerAmount);

				if (foldCounter == playerAmount - 1) {
					printf("\n\tERRORCHECKER: Foldercounter: %d | %d FULL - ENDING TURN\n", foldCounter, playerAmount - 1);
					turnSTATE = 0;
					foldCounter = 0;
					turnNumber = 5;
					break;
				}

				if (firstTurnCounter < currentPlayerAmount) {
					firstTurnCounter++;
				}

				if (allPlayers[i].fold != 1) {

					EvalHandVariable = allPlayers[i]; // EvalHandVariable used in evaluation of hand algorithm
					allPlayers[i].handVal = evaluateHand();
					allPlayers[i].kicker = EvalHandVariable.kicker;
					memcpy(allPlayers[i].bestHand, curBestHand, sizeof(curBestHand));
					printSortedCard();
					printBestHand();
					printHandVal(allPlayers[i].handVal);
					reInitCurrentHand();

					if (firstTurnCounter == currentPlayerAmount) {

						printf("\n\tERRORCHECKER: FirstTurnCounter: %d | %d FULL - ENDING TURN\n\n", firstTurnCounter, currentPlayerAmount);

						turnSTATE = playerTurnStop(highestBet, playerAmount);
						if (turnSTATE == 0) {
							break;
						}
					}

					if (allPlayers[i].balance > 0) {

						currentPlayerICON(i); // GRAPHIC

						while(getFrameFlag() == 1){};//wait until screen can be updated
						drawLayer();
						setFrameFlag(1);

						printf("\n\n\t - PLAYER %d TURN -\n\n", allPlayers[i].playerNumber);
						printf("Current player: %d / %d \t total pool: % d \t current balance: %d \t current highest bet: %d \n current total bet: %d \t current bet: %d \t fold value: %d \t dealer value: %d\n", allPlayers[i].playerNumber, playerAmount, pool, allPlayers[i].balance, highestBet, allPlayers[i].totalBet, allPlayers[i].currentBet, allPlayers[i].fold, allPlayers[i].dealer);
						printf("\nPlease choose the following option:\n");

						if (allPlayers[i].currentBet < highestBet) {
							printf("1: Fold\n2: Call\n3:Raise\n\n");
						}
						else if (allPlayers[i].currentBet == highestBet) {
							printf("1: Fold\n2: Check\n3:Raise\n\n");
						}

						printf("Input: ");
						fflush(stdout);
						while(!XUartPs_IsReceiveData(XPAR_PS7_UART_1_BASEADDR)){//update while waiting for input
							while(getFrameFlag() == 1){}
							updateBackground();
							drawLayer();
							setFrameFlag(1);

						}
						scanf("%d", &userInput);


						switch (userInput) {
						case 1: // FOLD
							allPlayers[i].fold = 1;
							foldCounter++;
							break;

						case 2: // CALL OR CHECK


							while (1) {
								if (allPlayers[i].currentBet == highestBet) {//check
									printf("\n\tPlayer %d performed a CHECK\n\n", allPlayers[i].playerNumber);
									break;
								}
								else if (allPlayers[i].balance + allPlayers[i].currentBet >= highestBet) {//call
									allPlayers[i].currentBet = highestBet - allPlayers[i].currentBet;
									allPlayers[i].balance = allPlayers[i].balance - highestBet;
									allPlayers[i].totalBet = highestBet;
									initChips(i);
									setPlayerBet(i, allPlayers[i].totalBet);
									setPlayerBalance(i, allPlayers[i].balance);

									printf("\n\tPlayer %d performed a CALL of %d\n\n", allPlayers[i].playerNumber, allPlayers[i].totalBet);

									break;
								}
								else if (allPlayers[i].balance + allPlayers[i].currentBet < highestBet) {
									printf("You do not have enough to perform a CALL this turn.");

								}
								else {
									printf("\n\n\tERRORCHECKER - error with CHECK / CALL input\n\n");
								}
							}

							break;

						case 3: // RAISE

							while (1) {
								printf("Input bet: ");
								fflush(stdout);
								while(!XUartPs_IsReceiveData(XPAR_PS7_UART_1_BASEADDR)){//update while waiting for input
									while(getFrameFlag() == 1){}
									updateBackground();
									drawLayer();
									setFrameFlag(1);

								}
								scanf("%d", &userInput);

								if (userInput + allPlayers[i].currentBet < highestBet) {
									printf("\nYour bet is too LOW - please make your bet at least [ %d ]\n", highestBet);
								}
								else if (userInput > allPlayers[i].balance) {
									printf("\nYour bet is too HIGH - please make your bet less than [ %d ]\n", allPlayers[i].balance);
								}
								else if (userInput + allPlayers[i].currentBet >= highestBet && userInput < allPlayers[i].balance) {
									printf("\nYour bet was valid - proceeding\n");

									highestBet = userInput;
									allPlayers[i].balance = allPlayers[i].balance - userInput;
									allPlayers[i].currentBet = userInput;
									allPlayers[i].totalBet += userInput;
									initChips(i);
									setPlayerBet(i, allPlayers[i].totalBet);
									setPlayerBalance(i, allPlayers[i].balance);


									printf("\nYou raised to: %d\n", userInput);

									break;
								}
								else {
									printf("\n\n\tERRORCHECKER - error with BET input\n\n");
								}

							}
							break;
						}
							updateFoldstatus(i, allPlayers[i].fold);

							while(getFrameFlag() == 1){};//update screen
							updateBackground();
							drawLayer();
							setFrameFlag(1);
					}
					else {
						printf("\n\tERRORCHECKER: SKIP - Skipping player %d due to 0 balance.\n", allPlayers[i].playerNumber);
					}
				}
				else {
				printf("\n\tERRORCHECKER: SKIP - Skipping player %d due to fold.\n", allPlayers[i].playerNumber);
				}


				/*for (int i = 0; i < maxPlayerAmount; i++) {
					if (allPlayers[i].inPlay == 1) {
						printf("\nCurrent player: %d / %d \t total pool: % d \t current balance: %d \t current highest bet: %d \t current total bet: %d \t current bet: %d \t fold value: %d \t dealer value: %d\n", allPlayers[i].playerNumber, playerAmount, pool, allPlayers[i].balance, highestBet, allPlayers[i].totalBet, allPlayers[i].currentBet, allPlayers[i].fold, allPlayers[i].dealer);
					}
				}*/
			}


		}
	}

	printf("Calculating total pool\n");
	for (int i = 0; i < maxPlayerAmount; i++) {

		if (allPlayers[i].inPlay == 1) {

			newPool = allPlayers[i].totalBet + newPool;
			printf("Current new pool: %d - Player %d added %d to the pool!\n", newPool, allPlayers[i].playerNumber, allPlayers[i].totalBet);
			allPlayers[i].currentBet = 0;
			allPlayers[i].totalBet = 0;

		}
	}

	removeChips();

	return newPool;
}


// GAME SETUP FUNCTIONS
int selectPlayers(int inputBalance) {

	int userInput;

	printf("\nChoose the amount of players for the Poker Game. \nThe amount must be between 2-8 players.\n");
	printf("Input: ");
	scanf("%d", &userInput);printf("%d\n", userInput);



	for (int i = 0; i < userInput; i++) {
		allPlayers[i].playerNumber = i + 1;
		allPlayers[i].balance = inputBalance;
		allPlayers[i].inPlay = 1;
		setPlayerBalance(i,inputBalance);
		printf("Player %d generated!\n", allPlayers[i].playerNumber);
		if (i == 0) {
			allPlayers[i].dealer = 1;
			printf("Player %d set as Dealer!\n", allPlayers[i].playerNumber);
		}
	}
	printf("\n%d\n", userInput);




	return userInput;
}

int selectStartingPool() {

	int userInput;

	printf("\nPlease set the starting pool for each player:\n");
	printf("Input: ");
	scanf("%d", &userInput);printf("%d\n", userInput);

	return userInput;
}


// TURN FUNCTIONS
void generateDeck() {

    int valueOfCard = 1;
    int typeOfCard = 1;
    int order = 1;

    printf("\nGenerating new deck!\n\n");

    head = (struct Deck*)malloc(sizeof(struct Deck)); // GENERATE HEAD FOR DOUBLELINKED LIST
    head->last = NULL;
    head->next = NULL;
    head->cardInfo.cardVal = valueOfCard;
    head->cardInfo.cardType = typeOfCard;
    head->deckPlacement = order;

    order++;
    valueOfCard++;
    tmp = head;
    printf("Cardtype: %d Cardvalue: %d\n", tmp->cardInfo.cardType, tmp->cardInfo.cardVal);

    for (int i = 0; i < 51; i++) { // GENERATE THE REST OF THE DECK

        newCard = (struct Deck*)malloc(sizeof(struct Deck));

        newCard->last = tmp;
        newCard->next = NULL;
        newCard->cardInfo.cardVal = valueOfCard;
        newCard->cardInfo.cardType = typeOfCard;
        newCard->cardDrawn = 0;
        newCard->deckPlacement = order;
        valueOfCard++;
        order++;

        newCard->last->next = newCard;

        tmp = newCard;
        printf("Placement: %d Cardtype: %d Cardvalue: %d\n", tmp->deckPlacement, tmp->cardInfo.cardType, tmp->cardInfo.cardVal);


        if (valueOfCard == 14) {
            valueOfCard = 1;
            typeOfCard++;
        }
    }

    printf("\nDeck complete!\n\n");
}

void shuffleDeck() {

	int counter = 1;
	int shufflesLeft = 52;
	int randomNumber;
	time_t t;

	printf("\n\r ERROR CHECKER: random num:%d ", (int)time);
	//srand((unsigned)time(&t));
	//srand((unsigned)time);

	randomNumber = rand() % shufflesLeft;
	shufflesLeft = shufflesLeft - 1;

	printf("Shuffling the new Deck!\n\n");

	tmp = head;

	if (randomNumber == 0) {
		head = head->next;
		shuffledHead = tmp;

		tmp->next->last = NULL;
		tmp->next = NULL;

	}
	else {
		for (int i = 1; i <= randomNumber; i++) {
			tmp = tmp->next;
		}

		if (tmp->next != NULL) {
			tmp->next->last = tmp->last;
			tmp->last->next = tmp->next;
		}
		else {
			tmp->last->next = tmp->next;
		}

		tmp->next = NULL;
		tmp->last = NULL;
		shuffledHead = tmp;

	}

	shuffledHead->deckPlacement = counter;
	counter++;

	tmp = head;
	tmpDeckShuffle = shuffledHead;

	while (shufflesLeft != 0) {

		randomNumber = rand() % shufflesLeft;
		shufflesLeft = shufflesLeft - 1;

		if (randomNumber == 0 && shufflesLeft == 0) {

			tmp->next = NULL;
			tmp->last = tmpDeckShuffle;
			tmp->last->next = tmp;
			tmp->deckPlacement = counter;
		}

		if (randomNumber == 0 && shufflesLeft != 0) {
			head = head->next;

			tmp->next->last = NULL;
			tmp->next = NULL;

			tmpDeckShuffle->next = tmp;
			tmp->last = tmpDeckShuffle;

			tmp->deckPlacement = counter;

		}
		else if (shufflesLeft != 0) {
			for (int i = 1; i <= randomNumber; i++) {
				tmp = tmp->next;
			}

			if (tmp->next != NULL) {
				tmp->next->last = tmp->last;
				tmp->last->next = tmp->next;
			}
			else {
				tmp->last->next = tmp->next;
			}

			tmpDeckShuffle->next = tmp;
			tmp->last = tmpDeckShuffle;
			tmp->next = NULL;
		}
		tmp->deckPlacement = counter;

		tmpDeckShuffle = tmpDeckShuffle->next;
		tmp = head;
		counter++;
	}

	ERRORCHECKER = shuffledHead;
	printf("SHUFFLED DECK - Placement: %d Cardtype: %d Cardvalue: %d nextPTR: %p\n", ERRORCHECKER->deckPlacement, ERRORCHECKER->cardInfo.cardType, ERRORCHECKER->cardInfo.cardVal, ERRORCHECKER->next);
	while (ERRORCHECKER->next != NULL) {

		ERRORCHECKER = ERRORCHECKER->next;
		printf("SHUFFLED DECK - Placement: %d Cardtype: %d Cardvalue: %d nextPTR: %p\n", ERRORCHECKER->deckPlacement, ERRORCHECKER->cardInfo.cardType, ERRORCHECKER->cardInfo.cardVal, ERRORCHECKER->next);

	}

	printf("\nShuffling deck complete!\n\n");

}

int findDealer() {

	int dealerPosition = 0;
	for (int i = 0; i <= maxPlayerAmount; i++) {
		if (allPlayers[i].dealer == 1) {
			break;
		}
		dealerPosition++;
	}
	printf("New Dealer: Player %d\n", allPlayers[dealerPosition].playerNumber);
	return dealerPosition;
}

int generateBlinds(int dealerPosition) {

	int tablePosition = dealerPosition;

	int blind = 50;
	int smallBlind = 0;

	while (1) {
		for (int i = tablePosition; i <= maxPlayerAmount; i++) {

			if (i == maxPlayerAmount) {
				tablePosition = 0;
				i = 0;
				printf("ERRORCHECKER - Blind pattern reset\n");
			}

			if (allPlayers[i].inPlay == 1 && smallBlind == 0 && allPlayers[i].dealer == 0) {
				allPlayers[i].currentBet = blind / 2;
				allPlayers[i].totalBet += blind / 2;
				allPlayers[i].balance = allPlayers[i].balance - blind / 2;
				printf("\nSmall blind given to player: %d\n", allPlayers[i].playerNumber);

				setPlayerBalance(i, allPlayers[i].balance);
				initChips(i);
				setPlayerBet(i, allPlayers[i].currentBet);

				smallBlind++;
			}
			else if (allPlayers[i].inPlay == 1 && smallBlind == 1 && allPlayers[i].dealer == 0) {
				allPlayers[i].currentBet = blind;
				allPlayers[i].totalBet += blind;
				allPlayers[i].balance = allPlayers[i].balance - blind;
				printf("Big blind given to player: %d\n", allPlayers[i].playerNumber);

				setPlayerBalance(i, allPlayers[i].balance);
				initChips(i);
				setPlayerBet(i, allPlayers[i].currentBet);

				break;
			}
			else {
				printf("ERRORCHECKER - Blind skip player: %d\n", allPlayers[i].playerNumber);
			}
		}
		break;
	}
	return blind;
}

void dealCard(int dealer) {

	int STATUS = dealer + 1;

	tmp = shuffledHead;


	//update to next and clear previous
	while(getFrameFlag() == 1){};//wait until screen can be updated
	updateBackground();
	drawLayer();
	setFrameFlag(1);
	updateBackground();


	while (allPlayers[STATUS].card2.cardDrawn == 0) {

		if (allPlayers[STATUS].inPlay == 1) {

			if (allPlayers[STATUS].card1.cardDrawn == 0) {

				allPlayers[STATUS].card1.cardInfo = tmp->cardInfo;
				allPlayers[STATUS].card1.cardDrawn = 1;

				printf("Player: %d has drawn his first card! Cardtype: %d CardVal: %d\n", allPlayers[STATUS].playerNumber, allPlayers[STATUS].card1.cardInfo.cardType, allPlayers[STATUS].card1.cardInfo.cardVal);
				setPlayerCards(STATUS, allPlayers[STATUS].card1.cardInfo.cardVal, allPlayers[STATUS].card1.cardInfo.cardType, 1);


			}
			else if (allPlayers[STATUS].card2.cardDrawn == 0) {

				allPlayers[STATUS].card2.cardInfo = tmp->cardInfo;
				allPlayers[STATUS].card2.cardDrawn = 1;
				printf("Player: %d has drawn his second card! Cardtype: %d CardVal: %d\n", allPlayers[STATUS].playerNumber, allPlayers[STATUS].card2.cardInfo.cardType, allPlayers[STATUS].card2.cardInfo.cardVal);
				setPlayerCards(STATUS, allPlayers[STATUS].card2.cardInfo.cardVal, allPlayers[STATUS].card2.cardInfo.cardType, 2);

			}
			tmp = tmp->next;

			drawLayer();
			while(getFrameFlag() == 1){};
			setFrameFlag(1);
		}

		STATUS++;
		if (STATUS == maxPlayerAmount) {
			STATUS = 0;
		}





	}

}

void flop() {

	printf("\n\n\t##FLOP##\n\n");

	for (int i = 0; i < 3; i++) {
		table[i].cardVal = tmp->cardInfo.cardVal;
		table[i].cardType = tmp->cardInfo.cardType;
		tmp->cardDrawn = 1;

		placeDealerCard(table[i].cardVal , table[i].cardType);
		tmp = tmp->next;
		printf("Cardnumber %d: \t Card Type: %d \t Card Value: %d\n", i+1, table[i].cardType, table[i].cardVal);
	}
}

void turn() {
	table[3].cardVal = tmp->cardInfo.cardVal;
	table[3].cardType = tmp->cardInfo.cardType;
	tmp->cardDrawn = 1;
	placeDealerCard(table[3].cardVal , table[3].cardType);
	tmp = tmp->next;

	printf("##TURN##\n");
	printf("Card 4:\tCard Type: %d\tCard Value: %d\n", table[3].cardType, table[3].cardVal);
}

void river() {
	table[4].cardVal = tmp->cardInfo.cardVal;
	table[4].cardType = tmp->cardInfo.cardType;
	tmp->cardDrawn = 1;
	placeDealerCard(table[4].cardVal , table[4].cardType);
	tmp = tmp->next;

	printf("##RIVER##\n");
	printf("Card 5:\tCard Type: %d\tCard Value: %d\n", table[4].cardType, table[4].cardVal);

}

int playerTurnStop(int highestBet, int playerAmount) {

	int counter = 0;
	int finalCounter = 0;

	for (int i = 0; i < maxPlayerAmount; i++) {

		if (allPlayers[i].inPlay == 1 && allPlayers[i].fold != 1) {
			printf("ERRORCHECKER - Checking Player: %d\n", allPlayers[i].playerNumber);
			if (allPlayers[i].totalBet == highestBet) {
				counter++;
				printf(" - Bet of %d matches highest bet of %d\n", allPlayers[i].totalBet, highestBet);
			}
			else if (allPlayers[i].totalBet != highestBet) {
				finalCounter++;
				printf("- Bet of %d does NOT match highest bet of %d\n", allPlayers[i].totalBet, highestBet);
			}
		}
	}

	if (finalCounter == 0) {

		printf("\n\t ! All players in play match the highest bet [ %d | %d ] ending turn !\n", counter, finalCounter);

		return 0;
	}
	else {
		return 1;
	}
}


// END TURN FUNCTIONS
void endTurnRemovals() {

	for (int i = 0; i < maxPlayerAmount; i++) {
		if (allPlayers[i].balance <= 0 && allPlayers[i].inPlay == 1) {
			allPlayers[i].inPlay = 0;
			allPlayers[i].fold = 0;
			allPlayers[i].card1.cardDrawn = 0;
			allPlayers[i].card2.cardDrawn = 0;
			currentPlayerAmount = currentPlayerAmount - 1;
			removePlayerFromGame(i);



			printf("\n\tPlayer %d was REMOVED from play due to Balance = 0\n", allPlayers[i].playerNumber);
		}
		else if (allPlayers[i].inPlay == 1) {

			printf("\n\tRemoved Cards from player %d hand\n", allPlayers[i].playerNumber);

			allPlayers[i].fold = 0;
			allPlayers[i].card1.cardDrawn = 0;
			allPlayers[i].card2.cardDrawn = 0;
			allPlayers[i].currentBet = 0;

		}
	}

	foldCounter = 0;
	pool = 0;
	setNewDealer();
	turnNumber = 1;

	printf("\n\tReset values\n\n");

}

void setNewDealer() {

	printf("\nSetting new dealer\n");

	for (int i = 0; i < maxPlayerAmount; i++) {
		if (allPlayers[i].dealer == 1) {

			printf("Old dealer found: Player %d\n", allPlayers[i].playerNumber);

			for (int j = i + 1; j < maxPlayerAmount; j++) {

				if (allPlayers[j].inPlay == 1) {

					printf("New dealer found: Player %d\n", allPlayers[j].playerNumber);

					allPlayers[i].dealer = 0;
					allPlayers[j].dealer = 1;
					break;
				}

				if (j == maxPlayerAmount) {
					j = 0;
				}

			}
			break;
		}
	}
}

void distributePool(int pool) {

	int tmpWinnerValue = 0;
	int winnerAmountCounter = 0;

	tmpWinnerValue = compareHands();

	if (tmpWinnerValue != -1) {
		printf("\n\tTurn Winner: %d - Total pool value: %d\n", allPlayers[tmpWinnerValue].playerNumber, pool);
		allPlayers[tmpWinnerValue].balance += pool;
		setPlayerBalance(tmpWinnerValue, allPlayers[tmpWinnerValue].balance);

	}
	else if (tmpWinnerValue == -1) {
		printf("Several turn winners: ");
		for (int i = 0; i < maxPlayerAmount; i++) {
			if (winners[i] != -1) {
				winnerAmountCounter++;
			}
		}
		pool = pool / winnerAmountCounter;

		for (int i = 0; i < maxPlayerAmount; i++) {
			if (winners[i] != -1) {
				printf(" %d", allPlayers[winners[i]].playerNumber);
				allPlayers[winners[i]].balance += pool;
				setPlayerBalance(i, allPlayers[i].balance);
			}
		}
		printf(" Pool split: %d\n", pool);
	}
	else {
		printf("\n\n\tERRORCHECKER - Error with distribution of pool\n\n");
	}
}

void winCondition() {

	int winCounter = 0;
	int playerTmp = 0;

	for (int i = 0; i < maxPlayerAmount; i++) {
		if (allPlayers[i].inPlay == 1) {
			winCounter++;
			playerTmp = allPlayers[i].playerNumber;
		}
	}
	if (winCounter == 1) {
		printf("Player %d has won the game!!!", allPlayers[playerTmp].playerNumber);
		STATE = 3;
	}
}



/*
#######################################################################################################
EVALUATION OF HAND ALGORITHM
Version 1.10
#######################################################################################################
*/
void printHandVal(int value){
	switch(value){
		case 1:
			printf("## High card! ##\n");
			break;
		case 2:
			printf("## Pair! ##\n");
			break;
		case 3:
			printf("## Two Pair! ##\n");
			break;
		case 4:
			printf("## Set! ##\n");
			break;
		case 5:
			printf("## Straight! ##\n");
			break;
		case 6:
			printf("## Flush ##\n");
			break;
		case 7:
			printf("## Full House! ##\n");
			break;
		case 8:
			printf("## Four Of A Kind! ##\n");
			break;
		case 9:
			printf("## Straight Flush! ##\n");
			break;
		case 10:
			printf("## Royal Flush! ##\n");
			break;
	}
}

int evaluateHand(){
	isStraight = 0;
	int isSet = 0;
	int isPair = 0;
	int isTwoPair = 0;
	int tmpHandValue = 0;



	tmpHandValue = checkSeq();
	if (tmpHandValue == 10 || tmpHandValue == 9){ // in case of straight flush or royal flush - return
		return tmpHandValue;
	}
	else if (tmpHandValue == 5){
		isStraight = 1;
	}

	tmpHandValue = checkPaired();
	if (tmpHandValue == 8){
		return tmpHandValue;
	}
	else if (tmpHandValue == 4){
		isSet = 1;
	}
	else if (tmpHandValue == 2){
		isPair = 1;
	}

	tmpHandValue = checkDoublePaired();
	if (tmpHandValue == 7){
		return tmpHandValue;
	}
	else if (tmpHandValue == 3){
		isTwoPair = 1;
	}

	if(checkFlush() == 6){
		return 6;
	}

	if (isStraight){
		return 5;
	}
	else if (isSet){
		return 4;
	}
	else if (isTwoPair){
		return 3;
	}
	else if (isPair){
		return 2;
	}
	else{
		int j = 0;
		int check = 0;
		for (int i = 6; i >= 0; i--){
			if (tmpCard[0].cardVal == 1 && !check){
				curBestHand[0].cardVal = 1;
				curBestHand[0].cardType = tmpCard[0].cardType;
				j++;
				i++;
				check = 1;
			}
			else{
				curBestHand[j].cardVal = tmpCard[i].cardVal;
				curBestHand[j].cardType = tmpCard[i].cardType;
				j++;
				if (j == 5){
					break;
				}
			}
		}
		EvalHandVariable.kicker = kicker(0, 1);
		return 1;
	}

}

int checkFlush(){
	int kind = 0;
	int offSet = 0;
	int hearts = 0;
	int clubs = 0;
	int diamonds = 0;
	int spades = 0;

	for (int i = 0; i < 7; i++){
		if (tmpCard[i].cardType == 1){
			hearts++;
		}
		else if (tmpCard[i].cardType == 2){
			clubs++;
		}
		else if (tmpCard[i].cardType == 3){
			diamonds++;
		}
		else if (tmpCard[i].cardType == 4){
			spades++;
		}
		if (hearts >= 5 || clubs >= 5 || diamonds >= 5 || spades >= 5){
			offSet = i;
		}
	}

	if (hearts >= 5){
		kind = 1;
	}
	else if (clubs >= 5){
		kind = 2;
	}
	else if (diamonds >= 5){
		kind = 3;
	}
	else if (spades >= 5){
		kind = 4;
	}

	if (offSet != 0){
		makeBestHand(offSet, 0, 0, 0, 0, 0, 1, kind);
		return 6;
	}
	return 0;
}

int checkDoublePaired(){
	int pair1 = 0;
	int pair2 = 0;
	int pair3 = 0;
	int set = 0;
	int offsetPair1 = 0;
	int offsetPair2 = 0;
	int offsetPair3 = 0;
	int offsetHouse = 0;
	int fullHouse = 0;
	int twoPair = 0;

	int houseVal = 0;

	for (int i = 0; i < 7; i++){
		if (tmpCard[i].cardVal == tmpCard[i + 1].cardVal){
			if (tmpCard[i].cardVal == tmpCard[i + 2].cardVal){
				houseVal = tmpCard[i].cardVal;
				offsetHouse = i;
				set = 1;
				if (i == 4){
					break;
				}
				continue;
			}
			if (pair1 == 1 && pair2 == 1 && pair3 == 0 && tmpCard[i].cardVal != houseVal){
				offsetPair3 = i;
				pair3 = 1;
			}
			else if (pair1 == 1 && pair2 == 0 && pair3 == 0 && tmpCard[i].cardVal != houseVal){
				offsetPair2 = i;
				pair2 = 1;
			}
			else if (pair1 == 0 && pair2 == 0 && pair3 == 0 && tmpCard[i].cardVal != houseVal){
				offsetPair1 = i;
				pair1 = 1;
			}
		}
	}



	if (set && pair3){
		makeBestHand(offsetPair3, 0, 0, 0, 1, offsetHouse, 0, 0);
		return 7;
	}
	else if (set && pair2){
		makeBestHand(offsetPair2, 0, 0, 0, 1, offsetHouse, 0, 0);
		return 7;
	}
	else if (set && pair1){
		makeBestHand(offsetPair1, 0, 0, 0, 1, offsetHouse, 0, 0);
		return 7;
	}
	else if (pair2 && pair3 && !isStraight){
		makeBestHand(offsetPair2, 0, 0, 0, 1, offsetPair3, 0, 0);
		return 3;
	}
	else if (pair1 && pair3 && !isStraight){
		makeBestHand(offsetPair1, 0, 0, 0, 1, offsetPair3, 0, 0);
		return 3;
	}
	else if (pair1 && pair2 && !isStraight){
		makeBestHand(offsetPair1, 0, 0, 0, 1, offsetPair2, 0, 0);
		return 3;
	}

	return 0;

}

int checkPaired(){
	int offSet1 = 0;
	int offSet2 = 0;
	int offSet3 = 0;
	int four = 0;
	int set = 0;
	int pair = 0;

	for (int i = 0; i < 7; i++){
		if (tmpCard[i].cardVal == tmpCard[i + 1].cardVal &&
		tmpCard[i].cardVal == tmpCard[i+2].cardVal &&
		tmpCard[i].cardVal == tmpCard[i+3].cardVal){
			offSet3 = i;
			four = 1;
		}
		else if (tmpCard[i].cardVal == tmpCard[i + 1].cardVal &&
		tmpCard[i].cardVal == tmpCard[i+2].cardVal){
			offSet2 = i;
			set = 1;
		}
		else if (tmpCard[i].cardVal == tmpCard[i + 1].cardVal){
			offSet1 = i;
			pair = 1;
		}
	}
	if (four == 1){
		makeBestHand(offSet3, 0, 0, 4, 0, 0, 0, 0);
		return 8;
	}
	else if (set == 1 && !isStraight){
		makeBestHand(offSet2, 0, 0, 3, 0, 0, 0, 0);
		return 4;
	}
	else if (pair == 1 && !isStraight){
		makeBestHand(offSet1, 0, 0, 2, 0, 0, 0, 0);
		return 2;
	}

	return 0;
}

int checkSeq(){
	int tmpHandValue = 0;

	sortHand();

	int offset = 0;
	int start = 0;
	int isRoyal = 0;
	int seq = 0;
	int isSeq = 0;
	// first check for royal flush or straight flush
	// if not of the same kind - straight
	for (int i = 0; i < 7; i++){
		if ((tmpCard[i].cardVal == (tmpCard[i + 1].cardVal - 1))
		 || (tmpCard[i].cardVal == (tmpCard[i + 2].cardVal - 1))
		 || (tmpCard[i].cardVal == (tmpCard[i + 3].cardVal - 1))){
		 	if ((tmpCard[i].cardVal != tmpCard[i - 1].cardVal)){
		 		if (!start){
		 			offset = i;
		 			start = 1;
		 		}
				seq++;
				if (seq > 4 && tmpCard[i].cardVal == (tmpCard[i-1].cardVal + 1)){
					printf("Incremented off-set\n");
					offset++;
				}
			}
		}
		else if (i != 6 && !(seq >= 4)){
			if (tmpCard[i].cardVal != 13){
				start = 0;
				seq = 0;
			}
		}
	}
	printf("seq: %d\n", seq);
	if (seq >= 3 && tmpCard[0].cardVal == 1 && tmpCard[6].cardVal == 13 && !(tmpCard[5].cardVal < 12)
		&& !(tmpCard[4].cardVal < 11) && !(tmpCard[3].cardVal < 10)){
		for (int i = 0; i < 7; i++){
			if (tmpCard[offset].cardVal != 10 && tmpCard[offset + 1].cardVal != 11){
				printf("Incremented ace-high off-set\n");
				offset++;
			}
			else{
				break;
			}
		}
		isStraight = 1;
		isSeq = 1;
		isRoyal = 1;
		makeBestHand(offset, isRoyal, isSeq, 0, 0, 0, 0, 0);
		if (evalKind() == 1){
			return 10;
		}
		else{
			printf("Ace high straight\n");
			tmpHandValue = 5;
			//break;
		}
	}
	else if (seq >= 4){
		isStraight = 1;
		isSeq = 1;
		makeBestHand(offset, isRoyal, isSeq, 0, 0, 0, 0, 0);
		if (evalKind() == 1){
			return 9;
		}
		else{
			printf("Normal straight\n");
			tmpHandValue = 5;
			//break;
		}
	}
	if (tmpHandValue != 0){
		return tmpHandValue;
	}


	return 0;
	//check for four of a kind
}

void makeBestHand(int offset, int isRoyal, int isSeq, int pairKind, int doublePaired, int offset2, int isFlush, int kind){
	//printf("makeBestHand() called\n");
	if (isSeq){
		int j = 0;
		if (isRoyal){
			curBestHand[j].cardVal = tmpCard[0].cardVal;
			curBestHand[j].cardType = tmpCard[0].cardType;
			j++;
			for (int i = offset; i < (offset + 4); i++){
			if ((tmpCard[i].cardVal == tmpCard[i+1].cardVal)
				&& (tmpCard[i].cardVal == tmpCard[i+2].cardVal)){
				if (tmpCard[i].cardType == tmpCard[i + 3].cardType){ //if we have 3 of a kind, adjust offset
					//in case of sequense
					curBestHand[j].cardVal = tmpCard[i].cardVal;
					curBestHand[j].cardType = tmpCard[i].cardType;
					offset += 2;
					i += 2;
					j++;
					continue;
				}
				else if (tmpCard[i + 1].cardType == tmpCard[i + 3].cardType){
					curBestHand[j].cardVal = tmpCard[i + 1].cardVal;
					curBestHand[j].cardType = tmpCard[i + 1].cardType;
					offset += 2;
					i += 2;
					j++;
					continue;
				}
				else{
					curBestHand[j].cardVal = tmpCard[i + 2].cardVal;
					curBestHand[j].cardType = tmpCard[i + 2].cardType;
					offset += 2;
					i += 2;
					j++;
					continue;
				}
			}

			else if (tmpCard[i].cardVal == tmpCard[i+1].cardVal){ // if we have pair, adjust offset
				//in case of sequense
				if (tmpCard[i].cardType == tmpCard[i + 2].cardType){
					curBestHand[j].cardVal = tmpCard[i].cardVal;
					curBestHand[j].cardType = tmpCard[i].cardType;
					offset++;
					i++;
					j++;
					continue;
				}
				else{
					curBestHand[j].cardVal = tmpCard[i + 1].cardVal;
					curBestHand[j].cardType = tmpCard[i + 1].cardType;
					offset++;
					i++;
					j++;
					continue;
				}
			}
				curBestHand[j].cardVal = tmpCard[i].cardVal;
				curBestHand[j].cardType = tmpCard[i].cardType;
				j++;
			}
			return;

		}

		for (int i = offset; i < (offset + 5); i++){
			if ((tmpCard[i].cardVal == tmpCard[i+1].cardVal)
				&& (tmpCard[i].cardVal == tmpCard[i+2].cardVal)){
				if (tmpCard[i].cardType == tmpCard[i + 3].cardType){ //if we have 3 of a kind, adjust offset
					//in case of sequense
					curBestHand[j].cardVal = tmpCard[i].cardVal;
					curBestHand[j].cardType = tmpCard[i].cardType;
					offset += 2;
					i  += 2;
					j++;
					continue;
				}
				else if (tmpCard[i + 1].cardType == tmpCard[i + 3].cardType){
					curBestHand[j].cardVal = tmpCard[i + 1].cardVal;
					curBestHand[j].cardType = tmpCard[i + 1].cardType;
					offset += 2;
					i += 2;
					j++;
					continue;
				}
				else{
					curBestHand[j].cardVal = tmpCard[i + 2].cardVal;
					curBestHand[j].cardType = tmpCard[i + 2].cardType;
					offset += 2;
					i += 2;
					j++;
					continue;
				}
			}

			else if (tmpCard[i].cardVal == tmpCard[i+1].cardVal){ // if we have pair, adjust offset
				//in case of sequense
				if (tmpCard[i].cardType == tmpCard[i + 2].cardType){
					curBestHand[j].cardVal = tmpCard[i].cardVal;
					curBestHand[j].cardType = tmpCard[i].cardType;
					offset++;
					i++;
					j++;
					continue;
				}
				else{
					curBestHand[j].cardVal = tmpCard[i + 1].cardVal;
					curBestHand[j].cardType = tmpCard[i + 1].cardType;
					offset++;
					i++;
					j++;
					continue;
				}
			}

			curBestHand[j].cardVal = tmpCard[i].cardVal;
			curBestHand[j].cardType = tmpCard[i].cardType;
			j++;
		}
	}

	// check for 4OfAKind or Set or Pair
	else if (pairKind != 0){
		switch(pairKind){
			case 4:
				curBestHand[0].cardVal = tmpCard[offset].cardVal;
				curBestHand[0].cardType = tmpCard[offset].cardType;

				curBestHand[1].cardVal = tmpCard[offset + 1].cardVal;
				curBestHand[1].cardType = tmpCard[offset + 1].cardType;

				curBestHand[2].cardVal = tmpCard[offset + 2].cardVal;
				curBestHand[2].cardType = tmpCard[offset + 2].cardType;

				curBestHand[3].cardVal = tmpCard[offset + 3].cardVal;
				curBestHand[3].cardType = tmpCard[offset + 3].cardType;

				EvalHandVariable.kicker = kicker(0, 0);

				break;
			case 3:
				curBestHand[0].cardVal = tmpCard[offset].cardVal;
				curBestHand[0].cardType = tmpCard[offset].cardType;

				curBestHand[1].cardVal = tmpCard[offset + 1].cardVal;
				curBestHand[1].cardType = tmpCard[offset + 1].cardType;

				curBestHand[2].cardVal = tmpCard[offset + 2].cardVal;
				curBestHand[2].cardType = tmpCard[offset + 2].cardType;

				EvalHandVariable.kicker = kicker(0, 0);

				break;
			case 2:
				curBestHand[0].cardVal = tmpCard[offset].cardVal;
				curBestHand[0].cardType = tmpCard[offset].cardType;

				curBestHand[1].cardVal = tmpCard[offset + 1].cardVal;
				curBestHand[1].cardType = tmpCard[offset + 1].cardType;

				EvalHandVariable.kicker = kicker(0, 0);

				break;
			default:
				break;
		}
	}
	else if (doublePaired){
		if (tmpCard[offset].cardVal == tmpCard[offset + 1].cardVal){
			curBestHand[0].cardVal = tmpCard[offset].cardVal;
			curBestHand[0].cardType = tmpCard[offset].cardType;

			curBestHand[1].cardVal = tmpCard[offset + 1].cardVal;
			curBestHand[1].cardType = tmpCard[offset + 1].cardType;
		}

		if (tmpCard[offset2].cardVal == tmpCard[offset2 + 1].cardVal){
			if (tmpCard[offset2].cardVal == tmpCard[offset2 + 2].cardVal){
				curBestHand[2].cardVal = tmpCard[offset2].cardVal;
				curBestHand[2].cardType = tmpCard[offset2].cardType;

				curBestHand[3].cardVal = tmpCard[offset2 + 1].cardVal;
				curBestHand[3].cardType = tmpCard[offset2 + 1].cardType;

				curBestHand[4].cardVal = tmpCard[offset2 + 2].cardVal;
				curBestHand[4].cardType = tmpCard[offset2 + 2].cardType;

				//break;
			}
				curBestHand[2].cardVal = tmpCard[offset2].cardVal;
				curBestHand[2].cardType = tmpCard[offset2].cardType;

				curBestHand[3].cardVal = tmpCard[offset2 + 1].cardVal;
				curBestHand[3].cardType = tmpCard[offset2 + 1].cardType;

				EvalHandVariable.kicker = kicker(1, 0);
				//break;
		}
	}
	else if (isFlush){
		int check = 0;
		int j = 0;
		int counter = 0;
		for (int i = offset; i >= 0; i--){
			if (tmpCard[0].cardType == kind && tmpCard[0].cardVal == 1 && !check){
				curBestHand[4].cardVal = tmpCard[0].cardVal;
				curBestHand[4].cardType = tmpCard[0].cardType;
				counter++;
				i++;
				check = 1;
				continue;
			}
			if (tmpCard[1].cardType == kind && tmpCard[1].cardVal == 1 && !check){
				curBestHand[4].cardVal = tmpCard[1].cardVal;
				curBestHand[4].cardType = tmpCard[1].cardType;
				counter++;
				i++;
				check = 1;
				continue;
			}
			if (tmpCard[2].cardType == kind && tmpCard[2].cardVal == 1 && !check){
				curBestHand[4].cardVal = tmpCard[2].cardVal;
				curBestHand[4].cardType = tmpCard[2].cardType;
				counter++;
				i++;
				check = 1;
				continue;
			}
			if (tmpCard[i].cardType == kind){
				curBestHand[j].cardVal = tmpCard[i].cardVal;
				curBestHand[j].cardType = tmpCard[i].cardType;
				counter++;
				if (counter == 5){
					break;
				}
				j++;
			}
		}
	}
}

//we only need to identify a unique kicker hand in case of Pair og Two Pair
int kicker(int isDouble, int highCard){
	int check = 0;

	if (highCard){
		if (EvalHandVariable.card1.cardInfo.cardVal == 1){
			return EvalHandVariable.card1.cardInfo.cardVal;
		}
		else if (EvalHandVariable.card2.cardInfo.cardVal == 1){
			return EvalHandVariable.card2.cardInfo.cardVal;
		}
		else if (EvalHandVariable.card1.cardInfo.cardVal > EvalHandVariable.card2.cardInfo.cardVal){
			return EvalHandVariable.card1.cardInfo.cardVal;
		}
		else if (EvalHandVariable.card1.cardInfo.cardVal < EvalHandVariable.card2.cardInfo.cardVal){
			return EvalHandVariable.card2.cardInfo.cardVal;
		}
	}
	else if (!isDouble){
		if (EvalHandVariable.card1.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card2.cardInfo.cardVal != curBestHand[0].cardVal){
			if (EvalHandVariable.card1.cardInfo.cardVal == 1){
				return 1;
			}
			else if (EvalHandVariable.card2.cardInfo.cardVal == 1){
				return 1;
			}
			else if (EvalHandVariable.card1.cardInfo.cardVal > EvalHandVariable.card2.cardInfo.cardVal){
				return EvalHandVariable.card1.cardInfo.cardVal;
			}
			else{
				return EvalHandVariable.card2.cardInfo.cardVal;
			}
		}
		if (EvalHandVariable.card1.cardInfo.cardVal == curBestHand[0].cardVal && EvalHandVariable.card2.cardInfo.cardVal != curBestHand[0].cardVal){
			return EvalHandVariable.card2.cardInfo.cardVal;
		}
		if (EvalHandVariable.card1.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card2.cardInfo.cardVal == curBestHand[0].cardVal){
			return EvalHandVariable.card1.cardInfo.cardVal;
		}
	}
	else if (isDouble){
		if ((EvalHandVariable.card1.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card1.cardInfo.cardVal != curBestHand[2].cardVal)
			&& (EvalHandVariable.card2.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card2.cardInfo.cardVal != curBestHand[2].cardVal)){
			if (EvalHandVariable.card1.cardInfo.cardVal == 1){
				return 1;
			}
			else if (EvalHandVariable.card2.cardInfo.cardVal == 1){
				return 1;
			}
			else if (EvalHandVariable.card1.cardInfo.cardVal > EvalHandVariable.card2.cardInfo.cardVal){
				return EvalHandVariable.card1.cardInfo.cardVal;
			}
			else{
				return EvalHandVariable.card2.cardInfo.cardVal;
			}
		}
		if ((EvalHandVariable.card1.cardInfo.cardVal == curBestHand[0].cardVal || EvalHandVariable.card1.cardInfo.cardVal == curBestHand[2].cardVal)
			&& (EvalHandVariable.card2.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card2.cardInfo.cardVal != curBestHand[2].cardVal)){
			return EvalHandVariable.card2.cardInfo.cardVal;
		}
		if ((EvalHandVariable.card1.cardInfo.cardVal != curBestHand[0].cardVal && EvalHandVariable.card1.cardInfo.cardVal != curBestHand[2].cardVal)
			&& (EvalHandVariable.card2.cardInfo.cardVal == curBestHand[0].cardVal || EvalHandVariable.card2.cardInfo.cardVal == curBestHand[2].cardVal)){
			return EvalHandVariable.card1.cardInfo.cardVal;
		}
	}

	return 0;
}

int evalKind(){
	int counter = 0;
	for (int i = 0; i < 5; i++){
		if (curBestHand[i].cardType == curBestHand[i + 1].cardType){
			counter++;
		}
	}
	if (counter == 4){
		return 1;
	}
	return 0;
}

void sortHand(){
	int size = 7; // hand plus all Card on board after flop, turn and river

	tmpCard[0].cardVal = EvalHandVariable.card1.cardInfo.cardVal;
	tmpCard[0].cardType = EvalHandVariable.card1.cardInfo.cardType;

	tmpCard[1].cardVal = EvalHandVariable.card2.cardInfo.cardVal;
	tmpCard[1].cardType = EvalHandVariable.card2.cardInfo.cardType;

	for (int i = 0; i < 5; i++){
		tmpCard[i + 2].cardVal = table[i].cardVal;
		tmpCard[i + 2].cardType = table[i].cardType;
		if (tmpCard[i + 2].cardVal == 0){
			size--;
		}
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size - i - 1; j++){
			if ((tmpCard[j].cardVal > tmpCard[j + 1].cardVal) && ((tmpCard[j].cardVal > 0)
				|| (tmpCard[j + 1].cardVal > 0))){
				tmp1 = tmpCard[j + 1];
				tmpCard[j + 1] = tmpCard[j];
				tmpCard[j] = tmp1;
			}
		}
	}
}

void printBestHand(){
	printf("Final best hand:\n");
	for (int i = 0; i < 5; i++){
		printf("Card %d: ##VALUE: %d\t ##TYPE: %d\n", i + 1, curBestHand[i].cardVal, curBestHand[i].cardType);
	}
}

void printSortedCard(){
	printf("Sorted Card:\n");
	for (int i = 0; i < 7; i++){
		printf("Card %d: ##VALUE: %d\t ##TYPE: %d\n", i + 1,  tmpCard[i].cardVal, tmpCard[i].cardType);
	}
}

void reInitCurrentBestHand(){
	for (int i = 0; i < 5; i++){
		curBestHand[i].cardVal = 0;
		curBestHand[i].cardType = 0;
	}
}


/*
#######################################################################################################
COMPARISON OF HANDS
Version 1.4
#######################################################################################################
*/
int compareHands() {
	int bestHandIndex;
	int inPlay[8];
	int contestors[8];
	int maxHandVal = 0;
	int j = 0;

	printHandsInPlay(allPlayers);

	for (int i = 0; i < 8; i++)
	{
		inPlay[i] = -1;
		contestors[i] = -1;
		winners[i] = -1;
	}

	// First find all players still in play and find maximum hand value
	for (int i = 0; i < maxPlayerAmount; i++) {
		if (allPlayers[i].fold != 1 && allPlayers[i].inPlay == 1) {
			printf("Player: %d - Fold value: %d - inPlay value: %d\n", allPlayers[i].playerNumber, allPlayers[i].fold, allPlayers[i].inPlay);
			if (maxHandVal == 0) {
				maxHandVal = allPlayers[i].handVal;
			}
			if (allPlayers[i].handVal > maxHandVal) {
				maxHandVal = allPlayers[i].handVal;
			}
			inPlay[j] = i;
			j++;
		}
	}

	// Find player(s) who have same max. hand values
	int g = 0;
	for (int i = 0; i < j; i++) {
		if (allPlayers[inPlay[i]].handVal == maxHandVal) {
			contestors[g] = inPlay[i];
			g++;
		}
	}


	printf("Number of contestors: %d\n", g);

	//if Only one max. hand - we already have the winner
	if (g == 1) {
		printf("Wins on:\t");
		printHandVal(allPlayers[contestors[0]].handVal);
		return contestors[0];
	}

	//Other wise, we have to compare hands
	j = 0;
	int retValue = 0;
	int winnerIndex = -2;
	for (int i = 0; i < g - 1; i++) {
		if (contestors[i] != -1 && contestors[i + 1] != -1) {
			if (winnerIndex < 0) {
				retValue = compareTwoHands(allPlayers[contestors[i]], allPlayers[contestors[i + 1]]);
			}
			if (winnerIndex >= 0) {
				retValue = compareTwoHands(allPlayers[winnerIndex], allPlayers[contestors[i + 1]]);
			}
			if (retValue == 1 && (winnerIndex == -2)) {
				winnerIndex = contestors[i];
			}
			else if (retValue == 1 && (winnerIndex >= -1)) {
				continue;
			}
			else if (retValue == 2) {
				winnerIndex = contestors[i + 1];
			}

			else {
				if (i == 0) {
					winners[j++] = contestors[i];
				}
				if (winnerIndex < 0) {
					if (contestors[i] != winners[j - 1]) {
						winners[j++] = contestors[i];
					}
					winners[j++] = contestors[i + 1];
				}
				else if (winnerIndex >= 0) {
					winners[j++] = winnerIndex;
					winners[j++] = contestors[i + 1];
				}
				winnerIndex = -1;
			}
		}
	}

	printf("Wins on:\t");
	printf("winners[0]: %d\n", winners[1]);
	printHandVal(allPlayers[winnerIndex].handVal);
	return winnerIndex; // return index of winning player
}

int compareTwoHands(struct Player playerOne, struct Player playerTwo){
	//If players have different hands
	// This line may be redundant
	if (playerOne.handVal > playerTwo.handVal){
		return 1;
	}
	else if (playerOne.handVal < playerTwo.handVal){
		return 2;
	}

	//If players have same hand

	//## HIGH-CARD #################
	if (playerOne.handVal == 1){
		printf("Comparing high card\n");
		for (int i = 0; i < 5; i++){
			if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
				return 1;
			}
			else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
				return 2;
			}
			else if (playerOne.bestHand[i].cardVal > playerTwo.bestHand[i].cardVal){
				return 1;
			}
			else if(playerOne.bestHand[i].cardVal < playerTwo.bestHand[i].cardVal){
				return 2;
			}
		}
	}



	//## PAIR #######################
	if (playerOne.handVal == 2){
		printf("Comparing pair\n");
		if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
			return 2;
		}
		else if (playerOne.bestHand[0].cardVal > playerTwo.bestHand[0].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal < playerTwo.bestHand[0].cardVal){
			return 2;
		}
		else{
			printf("Comparing kicker\n");
			return checkKicker(playerOne.kicker, playerTwo.kicker);
		}
	}


	//## TWO PAIR #####################
	else if (playerOne.handVal == 3){
		printf("Comparing two pair\n");
		if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
			return 2;
		}
		else if (playerOne.bestHand[2].cardVal > playerTwo.bestHand[2].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[2].cardVal < playerTwo.bestHand[2].cardVal){
			//printf("hello\n");
			return 2;
		}
		else if (playerOne.bestHand[2].cardVal == playerTwo.bestHand[2].cardVal){
			if (playerOne.bestHand[0].cardVal > playerTwo.bestHand[0].cardVal){
				return 1;
			}
			else if (playerOne.bestHand[0].cardVal < playerTwo.bestHand[0].cardVal){
				return 2;
			}
			else {
				printf("Comparing kicker\n");
				return checkKicker(playerOne.kicker, playerTwo.kicker);
			}
		}
	}


	//## SET ################################
	else if (playerOne.handVal == 4){
		printf("Comparing set\n");
		if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
			return 2;
		}
		else if (playerOne.bestHand[0].cardVal > playerTwo.bestHand[0].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal < playerTwo.bestHand[0].cardVal){
			return 2;
		}
		else{
			printf("Comparing kicker\n");
			return checkKicker(playerOne.kicker, playerTwo.kicker);
		}
	}


	// ## STRAIGHT ############################
	else if (playerOne.handVal == 5){
		printf("Comparing Straight\n");
		if ((playerOne.bestHand[4].cardVal == 13 && playerOne.bestHand[0].cardVal == 1)
			&& !(playerTwo.bestHand[4].cardVal == 13 && playerTwo.bestHand[0].cardVal == 1)){
			printf("Comparing ace-high straight\n");
			return 1;
		}
		else if ((playerTwo.bestHand[4].cardVal == 13 && playerTwo.bestHand[0].cardVal == 1)
			&& !(playerOne.bestHand[4].cardVal == 13 && playerOne.bestHand[0].cardVal == 1)){
			printf("Comparing ace-high straight\n");
			return 0;
		}
		else if (playerOne.bestHand[4].cardVal > playerTwo.bestHand[4].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[4].cardVal < playerTwo.bestHand[4].cardVal){
			return 2;
		}
		else{
			return 0;
		}
	}

	// ## FLUSH #################################
	else if (playerOne.handVal == 6){
		int maxCard1 = 0;
		int maxCard2 = 0;

		printf("Comparing flush\n");
		if (playerOne.bestHand[4].cardVal == 1 && playerTwo.bestHand[4].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[4].cardVal != 1 && playerTwo.bestHand[4].cardVal == 1){
			return 2;
		}
		else{
			for (int i = 0; i < 5; i++){
				if (playerOne.bestHand[i].cardVal > playerTwo.bestHand[i].cardVal){
					return 1;
				}
				else if (playerOne.bestHand[i].cardVal < playerTwo.bestHand[i].cardVal){
					return 2;
				}
			}
		}
		return 0;
	}

	//## FULL-HOUSE #########################
	if (playerOne.handVal == 7){
		printf("Comparing full house\n");
		if (playerOne.bestHand[2].cardVal == 1 && playerTwo.bestHand[2].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[2].cardVal != 1 && playerTwo.bestHand[2].cardVal == 1){
			return 2;
		}
		else if (playerOne.bestHand[2].cardVal > playerTwo.bestHand[2].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[2].cardVal < playerTwo.bestHand[2].cardVal){
			return 2;
		}
		else{
			if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
				return 1;
			}
			else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
				return 2;
			}
			else if (playerOne.bestHand[0].cardVal > playerTwo.bestHand[0].cardVal){
				return 1;
			}
			else if (playerOne.bestHand[0].cardVal < playerTwo.bestHand[0].cardVal){
				return 2;
			}
			else{
				return 0;
			}
		}
	}

	// ## FOUR OF A KIND #########################
	else if (playerOne.handVal == 8){
		printf("Comparing four of a kind\n");
		if (playerOne.bestHand[0].cardVal == 1 && playerTwo.bestHand[0].cardVal != 1){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal != 1 && playerTwo.bestHand[0].cardVal == 1){
			return 2;
		}
		else if (playerOne.bestHand[0].cardVal > playerTwo.bestHand[0].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[0].cardVal < playerTwo.bestHand[0].cardVal){
			return 2;
		}
		else{
			return 0;
		}
	}

	// ## STRAIGH FLUSH ############################
	else if (playerOne.handVal == 9){
		printf("Comparing straight flush\n");
		if (playerOne.bestHand[4].cardVal > playerTwo.bestHand[4].cardVal){
			return 1;
		}
		else if (playerOne.bestHand[4].cardVal < playerTwo.bestHand[4].cardVal){
			return 2;
		}
		else{
			return 0;
		}
	}


	return 0;
}

int checkKicker(int kicker1, int kicker2){
	if (kicker1 == 1 && !(kicker2 == 1)){
		return 1;
	}
	else if (kicker2 == 1 && !(kicker1 == 1)){
		return 2;
	}
	if (kicker1 > kicker2){
		return 1;
	}
	else if (kicker2 > kicker1){
		return 2;
	}
	else{
		return 0;
	}
}


/*
#######################################################################################################
INITIALIZATION FUNCTIONS
#######################################################################################################
*/
void initializeComb(){
	int val = -2;
	for (int i = 0; i < 7; i++){
		tmpCard[i].cardVal = val;
		tmpCard[i].cardType = val;
		val -= 2;
	}
}

void reInitCurrentHand(){
	for (int i = 0; i < 5; i++){
		curBestHand[i].cardVal = 0;
		curBestHand[i].cardType = 0;
	}
}

void initTable(){
	int val = -2;
	for (int i = 0; i < 5; i++){
		table[i].cardVal = val;
		table[i].cardType = val;
		val -= 2;
	}
}

void printHandsInPlay(struct Player* players) {
	printf("Hands to compare:\n");
	for (int i = 0; i < 8; i++) {
		if (players[i].fold != 1 && players[i].inPlay == 1) {
			printf("Player %d\n", players[i].playerNumber);
			for (int j = 0; j < 5; j++) {
				printf("Card %d:\t##VALUE: %d\t##TYPE: %d\n", j + 1, players[i].bestHand[j].cardVal, players[i].bestHand[j].cardType);
			}
		}
	}
}
