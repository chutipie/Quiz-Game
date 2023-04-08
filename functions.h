#define ADMIN_PASSWORD "mysecretpassword"   
#define MAX_SCORES 50

struct quizRecord{
    char cTopic[21];            // Topic string
    int nQuestion;              // Question number
    char cQuestion[151];        // Question string
    char cChoices[3][31];       // Array of choices
    char cAnswer[31];           // Answer string
};

struct playerRecord{
    char cUsername[21];         // Player username string
    int nScore;                 // Quiz Score
};

void displayMainMenu();
void displayGameMenu(struct quizRecord *questions, struct playerRecord *data, int nQuestionNumber, int *nScores);
void startQuiz(struct quizRecord *questions, struct playerRecord *data, int nQuestionNumber, int *nScores);
void manageData(struct quizRecord questions[], int *nQuestionNumber);
void addRecord(struct quizRecord questions[], int *nQuestionNumber);
int displayEditRecordMenu();
void editRecord(struct quizRecord *questions, int *nQuestionNumber);
void deleteRecord(struct quizRecord *questions, int *nQuestionNumber);
void saveScores(struct playerRecord *data, int nScores);
void accumulateScores(struct playerRecord *data, int nScores, char *cUsername, int nPlayerScore);
void viewScores(struct playerRecord *data, int nScores);
int checkPair(struct quizRecord questions[], int nQuestionNumber, char *question);
