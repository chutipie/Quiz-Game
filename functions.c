#include "functions.h"

void manageData(struct quizRecord questions[], int *nQuestionNumber){
    char password[21];
    int nChoice;
    int nAction;

    do {
        printf("\nEnter admin password: ");
        scanf("%s", password);

        if (strcmp(ADMIN_PASSWORD, password) == 0){
            printf("\nAccess Granted!\n");
        
        do {
            printf("\n=== Admin Menu ===\n");
            printf("[1] Add a Record\n");
            printf("[2] Edit a Record\n");
            printf("[3] Delete a Record\n");
            printf("[4] Import Record\n");
            printf("[5] Export Data\n");
            printf("[6] Returning to Main Menu\n");
            printf("\nChoose Action: ");
            scanf("%d", &nAction);

            switch(nAction){
                case 1: 
                    addRecord(questions, nQuestionNumber);
                    break;
                
                case 2:
                    editRecord(questions, nQuestionNumber);
                    break;
                
                case 3:
                    deleteRecord(questions, nQuestionNumber);
                    break;
                
                case 4:
                    // importData() function implementation here
                    break;
                
                case 5:
                    // exportData() function implementation here
                    break;
                
                case 6:
                    printf("\nReturning to Main Menu...\n");
                    break;

                default:
                    printf("\nInvalid Action. Please enter numbers 1-3.\n");
                }
            } while (nAction != 6);
            
        } else {
            printf("\nIncorrect password.\n");
            printf("\n[1] Re-enter password\n");
            printf("[2] Go back to the Main Menu\n");
            printf("\nChoose Action: ");
            scanf("%d", &nChoice);
        }
    } while (nChoice != 2 && nAction != 4);
}

int checkPair(struct quizRecord questions[], int nQuestionNumber, char *question){
    int i, j = -1;

    for (i = 0; i < nQuestionNumber; i++){
        if (strcmp(questions[i].cQuestion, question) == 0){
            j = i;
        }
    }
    return j;
}

void addRecord(struct quizRecord questions[], int *nQuestionNumber){
    char cTopic[21];
    char cQuestion[151];
    char cChoices[3][31];
    char cAnswer[31];
    int nInvalid = 0;
    int nCheck = 0;

    // Ask for question 
    printf("\nEnter question: ");
    getchar();
    fgets(cQuestion, sizeof(cQuestion), stdin);
    cQuestion[strcspn(cQuestion, "\n")] = '\0';

    // Checks if inputted question already exists
    int idx = checkPair(questions, *nQuestionNumber, cQuestion);
    // If said question is found
    if (idx != -1){
        printf("\nQuestion already exists!\n");
        printf("\nTopic: %s\n", questions[idx].cTopic);
        printf("Question: %s\n", questions[idx].cQuestion);
        printf("Choice 1: %s\n", questions[idx].cChoices[0]);
        printf("Choice 2: %s\n", questions[idx].cChoices[1]);
        printf("Choice 3: %s\n", questions[idx].cChoices[2]);
        printf("Answer: %s\n", questions[idx].cAnswer);
        nCheck = 1;
    }

    if (!nCheck){
        // Prompt user for topic and choices
        printf("Enter topic: ");
        scanf("%s", cTopic);
        printf("Enter 3 choices:\n");
        printf("Choice 1: ");
        scanf("%s", cChoices[0]);
        printf("Choice 2: ");
        scanf("%s", cChoices[1]);
        printf("Choice 3: ");
        scanf("%s", cChoices[2]);

        // Prompt user for correct answer to the said question
        while (!nInvalid){
            printf("Enter Answer: ");
            scanf("%s", cAnswer);
            if (*cAnswer < '1' || *cAnswer > '3'){
                printf("\nInvalid input!\n");
            } else {
                nInvalid = 1;
            }
        }

        // Create new quizRecord struct with input data and add to array
        struct quizRecord newQuestion;
        strcpy(newQuestion.cTopic, cTopic);
        strcpy(newQuestion.cQuestion, cQuestion);
        strcpy(newQuestion.cChoices[0], cChoices[0]);
        strcpy(newQuestion.cChoices[1], cChoices[1]);
        strcpy(newQuestion.cChoices[2], cChoices[2]);
        strcpy(newQuestion.cAnswer, cAnswer);

        questions[*nQuestionNumber] = newQuestion;
        (*nQuestionNumber)++;

        printf("\nQuestion added succesfully!\n");
    }
}

int displayEditRecordMenu(){
    int choice;
    printf("\n=== Edit Record Menu ===\n");
    printf("[1] Edit Question\n");
    printf("[2] Edit Topic\n");
    printf("[3] Edit Choice 1\n");
    printf("[4] Edit Choice 2\n");
    printf("[5] Edit Choice 3\n");
    printf("[6] Edit Answer\n");
    printf("[7] Return to Admin Menu\n");
    printf("\nInput Action: ");
    scanf("%d", &choice);
    getchar(); // consume trailing newline character
    return choice;
}

void editRecord(struct quizRecord *questions, int *nQuestionNumber){
    // Display all unique topics
    char cUniqueTopics[*nQuestionNumber][21];
    int nUniqueTopics = 0;
    int idx, i, j, nChoice = 0;

    for (i = 0; i < *nQuestionNumber; i++){
        for (j = 0; j < nUniqueTopics; j++){
            if (strcmp(questions[i].cTopic, cUniqueTopics[j]) == 0){
                printf("\nTopic already in records\n");
                break;
            }
        }
        if (j == nUniqueTopics){
            strcpy(cUniqueTopics[j], questions[i].cTopic);
            nUniqueTopics++;
        }
    }

    printf("\nAvailable Topics:\n");
    for (int i = 0; i < nUniqueTopics; i++){
        printf("[%d] %s\n", i + 1, cUniqueTopics[i]);
    }

    // Prompt admin to choose a topic to edit
    int nSelectedTopic;
    printf("\nEnter number of the topic to edit: ");
    scanf("%d", &nSelectedTopic);
    if (nSelectedTopic < 1 || nSelectedTopic > nUniqueTopics) {
        printf("\nInvalid topic selection\n");
        return;
    }

    char cSelectedTopic[21];
    strcpy(cSelectedTopic, cUniqueTopics[nSelectedTopic - 1]);

    // Display questions in selected topic
    printf("\nQuestions in topic: %s\n", cSelectedTopic);
    int nQuestionInTopic = 0;
    for (i = 0; i < *nQuestionNumber; i++){
        if (strcmp(questions[i].cTopic, cSelectedTopic) == 0){
            printf("%d. %s\n", nQuestionInTopic + 1, questions[i].cQuestion);
            nQuestionInTopic++;
        }
    }
    if (nQuestionInTopic == 0) {
        printf("\nNo questions in selected topic\n");
        return;
    }

    // Prompt user to select a question to edit
    printf("\nEnter number of the question to edit: ");
    scanf("%d", &idx);
    if (idx < 1 || idx > nQuestionInTopic) {
        printf("\nInvalid question selection\n");
        return;
    }

    // Find index of selected question in question array
    int nQuestionIndex = 0;
    for (i = 0; i < *nQuestionNumber; i++){
        if (strcmp(questions[i].cTopic, cSelectedTopic) == 0){
            nQuestionIndex++;
        }
        if (nQuestionIndex == idx){
            idx = i;
            break;
        }
    }

    char cNewQuestion[151];
    char cNewChoices[4][31];
    char cNewTopic[21];
    char cNewAnswer[31];

    while (nChoice != 7){
        nChoice = displayEditRecordMenu();

        switch (nChoice){
            case 1:
                printf("Input new question: ");
                getchar(); // Consume the newline character
                fgets(cNewQuestion, sizeof(cNewQuestion), stdin);
                cNewQuestion[strcspn(cNewQuestion, "\n")] = '\0';
                strcpy(questions[idx].cQuestion, cNewQuestion);
                printf("\nQuestion updated successfully!\n");
                break;

            case 2:
                printf("Input new topic: ");
                getchar(); // Consume the newline character
                fgets(cNewTopic, sizeof(cNewTopic), stdin);
                cNewTopic[strcspn(cNewTopic, "\n")] = '\0';
                strcpy(questions[idx].cTopic, cNewTopic);
                printf("\nTopic updated succesfully!\n");
                break;

            case 3:
                printf("Input New Choice 1: ");
                getchar();
                fgets(cNewChoices[0], sizeof(cNewChoices[0]), stdin);
                cNewChoices[0][strcspn(cNewChoices[0], "\n")] = '\0';
                strcpy(questions[idx].cChoices[0], cNewChoices[0]);
                printf("\nChoice 1 updated succesfully!\n");
                break;
            
            case 4:
                printf("Input New Choice 2: ");
                getchar();
                fgets(cNewChoices[1], sizeof(cNewChoices[1]), stdin);
                cNewChoices[1][strcspn(cNewChoices[1], "\n")] = '\0';
                strcpy(questions[idx].cChoices[1], cNewChoices[1]);
                printf("\nChoice 2 updated succesfully!\n");
                break;
                
            case 5:
                printf("Input New Choice 3: ");
                getchar();
                fgets(cNewChoices[2], sizeof(cNewChoices[2]), stdin);
                cNewChoices[2][strcspn(cNewChoices[2], "\n")] = '\0';
                strcpy(questions[idx].cChoices[2], cNewChoices[2]);
                printf("\nChoice 3 updated succesfully!\n");
                break;

            case 6: 
                printf("Input New Answer: ");
                getchar();
                fgets(cNewAnswer, sizeof(cNewAnswer), stdin);
                cNewAnswer[strcspn(cNewAnswer, "\n")] = '\0';
                strcpy(questions[idx].cAnswer, cNewAnswer);
                printf("\nAnswer updated succesfully\n");
                break;

            case 7:
                printf("\nReturning to Admin Menu...\n");
                break;
            
            default:
                printf("\nInvalid action. Please enter a valid input.\n");
        }
    }
}

void deleteRecord(struct quizRecord *questions, int *nQuestionNumber){
    int idx;
    int nAction = 0;
    int nCheck = 0;

    // Display questions in topic
    do {
        printf("Questions in topic:\n");
        for (int i = 0; i < *nQuestionNumber; i++){
            printf("[%d] %s\n", i + 1, questions[i].cQuestion);
        }
        printf("[0] Return to Admin Menu\n");

        printf("\nEnter number of the question to delete: ");
        scanf("%d", &idx);

        if (idx < 0 || idx > *nQuestionNumber){
            printf("\nInvalid Input!\n");
        } else if (idx == 0){
            nAction = 1;
            nCheck = 1;
        } else {
            nCheck = 1;
        }
    } while (!nCheck);
    
    if (!nAction){
        for (int i = idx - 1; i < *nQuestionNumber; i++){
            questions[i] = questions[i + 1];
        }
        (*nQuestionNumber)--;
        printf("Question deleted successfully\n");
    }
}

void importData(){
    FILE *fp;

    char cFilename[21];
    char cTopic[21];
    int nQuestionNumber;
    char cQuestion[151];
    char cChoices[3][31];
    char cAnswer[31];
    char cLine[151];

    printf("Enter filename: ");
    scanf("%s", cFilename);

    fp = fopen(cFilename, "r");
    while (fp == NULL){
        printf("\nFile not found. Try again or press '0' go back.\n");
        scanf("%s", cFilename);
        if (cFilename[0] == 0){
            return 0;
        }
        fp = fopen(cFilename, "r");
    }

    
}

void saveScores(struct playerRecord *data, int nScores){
    FILE *fp;
    int i;

    fp = fopen("scores.txt", "a");
    if (fp == NULL) {
        printf("Unable to open file to save scores!\n");
        return;
    }

    for (i = 0; i < nScores; i++) {
        fprintf(fp, "%s\n%d\n\n", data[i].cUsername, data[i].nScore);
    }

    fclose(fp);
}

void accumulateScores(struct playerRecord *data, int nScores, char cUsername[], int nPlayerScore){
    int i;
    for (i = 0; i < nScores; i++){
        if (strcmp(data[i].cUsername, cUsername) == 0){
            data[i].nScore += nPlayerScore;
            return;
        }
    }
    strcpy(data[i].cUsername, cUsername);
    data[i].nScore = nPlayerScore;
}

void viewScores(struct playerRecord *data, int nScores){
    printf("\n============================\n");
    printf("\tHigh Scores\n");
    int i; // Declare the loop counter before the loop
    for (i = 0; i < nScores; i++){ // Initialize the loop counter to zero
        printf("[%d] %s: %d\n", i + 1, data[i].cUsername, data[i].nScore);
    }
    printf("\n============================\n");
}

void startQuiz(struct quizRecord *questions, struct playerRecord *data, int nQuestionNumber, int *nScores){
    char cUsername[21];
    int nPlayerScore = 0;
    int i, j;

    printf("\nEnter username: ");
    scanf("%s", cUsername);
    strcpy(data->cUsername, cUsername);

    while (1) {
        char cTopics[nQuestionNumber][21];
        int nTopics = 0;
        int nCheck = 0;
        int n = 0;
        int nChoice;

        for (i = 0; i < nQuestionNumber; i++){
            for (j = 0; j < nTopics; j++){
                if (strcmp(cTopics[j], questions[i].cTopic) == 0){
                    nCheck = 1;
                }
            }
            if (!nCheck){
                strcpy(cTopics[nTopics], questions[i].cTopic);
                nTopics++;
            }
        }
        printf("\nTopics:\n");
        for (i = 0; i < nTopics; i++){
            printf("[%d] %s\n", i + 1, cTopics[i]);
            printf("\tQuestions:\n");
            for (j = 0; j < nQuestionNumber; j++){
                if (strcmp(questions[j].cTopic, cTopics[i]) == 0){
                    printf("\t%s\n", questions[j].cQuestion);
                }
            }
        }
        printf("[0] End quiz\n");

        
        printf("\nInput Action: ");
        scanf("%d", &nChoice);
        getchar();

        if (nChoice == 0){
            printf("\nPlayer: %s\n", cUsername);
            printf("Score: %d\n", nPlayerScore);
            accumulateScores(data, *nScores, cUsername, nPlayerScore);
            printf("\nReturning to Game Menu...\n");
            return;
        }

        if (nChoice < 1 || nChoice > nTopics){
            printf("\nInvalid Action. Input a valid action.\n");
            continue;
        }

        for (i = 0; i < nQuestionNumber; i++){
            if (strcmp(questions[i].cTopic, cTopics[nChoice - 1]) == 0){
                n++;
            }
        }

        if (n == 0){
            printf("\nNo available questions. Please pick a different topic.\n");
            continue;
        }

        int idx = rand() % n + 1;
        i = 0;
        while (idx > 0){
            if (strcmp(questions[i].cTopic, cTopics[nChoice - 1]) == 0){
                idx--;
            }
            i++;
        }
        i--;

        char cAnswer[31];
        printf("\nTopic: %s\n", questions[i].cTopic);
        printf("Question: %s\n", questions[i].cQuestion);
        printf("Choice 1: %s\n", questions[i].cChoices[0]);
        printf("Choice 2: %s\n", questions[i].cChoices[1]);
        printf("Choice 3: %s\n", questions[i].cChoices[2]);
        printf("\nInput your answer (1-3): ");
        fgets(cAnswer, sizeof(cAnswer), stdin);
        cAnswer[strcspn(cAnswer, "\n")] = '\0';

        if (strcmp(cAnswer, questions[i].cAnswer) == 0) {
            nPlayerScore++;
            printf("\nCorrect! Your Score: %d\n", nPlayerScore);
        } else {
            printf("Incorrect! The correct answer is: %s\n", questions[i].cAnswer);
            printf("Score: %d", nPlayerScore);
        }
    }
}

void displayMainMenu(){
    printf("\n=== Who wants to be a Millionaire? ===\n");
    printf("[1] Play Game\n");
    printf("[2] Manage Data (Admin)\n");
    printf("[3] Exit Game\n");
    printf("\nChoose Action: ");
}

void displayGameMenu(struct quizRecord *questions, struct playerRecord *data, int nQuestionNumber, int *nScores){
    int nChoice;
    
    do{
        printf("\n=== Game Menu ===\n");
        printf("[1] Start Quiz\n");
        printf("[2] View Scores\n");
        printf("[3] Exit to Main Menu\n");
        printf("\nChoose Action: ");

        scanf("%d", &nChoice);

        switch(nChoice){
            case 1: 
                startQuiz(questions, data, nQuestionNumber, nScores);
                break;
            
            case 2:
                viewScores(data, *nScores);
                break; 
            
            case 3:
                saveScores(data, *nScores);
                printf("\nExiting to Main Menu...\n");
                break;

            default: 
                printf("\nInvalid Choice. Please try again.\n");
        }
    } while (nChoice != 3);
}

