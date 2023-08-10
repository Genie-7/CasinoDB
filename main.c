#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

static int callback(void* data, int argc, char** argv, char** ColName){
    for(int i=0;i<argc;i++){
        printf("%s\n", argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    int c;
    c = sqlite3_open("Casino.db", &db);
    if(c != SQLITE_OK) {
        printf("Can’t open database! %s\n", sqlite3_errmsg(db)); return(0);
    } else {
        printf("Connected to database successfully.\n"
               "Welcome to Casino\n");
    }
    int s = -1;
    char *sql;
    char *ErrMsg=0;
    char id[1];
    char UGTI[20];

    while(s!=0){
        printf("\n0) Exit\n"
               "1) What games a member plays\n"
               "2) Which game a member plays the most\n"
               "3) What game a member gains the most money from\n"
               "4) What game a member loses the most money from\n"
               "5) Which game is making the most money\n"
               "6) Which game is losing the most money\n"
               "7) How many units there are of a game type\n"
               "8) How many tables there are\n"
               "9) Which game a dealer is in control of\n"
               "10) How many members there are\n"
               "11) How many games there are total\n"
               "12) How many dealers there are total\n"
               "13) Active Dealers\n"
               "14) How much money the casino has lost or made\n"
               "15) How much a member has spent\n"
               "16) Members playtime\n"
               "17) How many games a member has played\n"
               "18) How long a member has played each game\n"
               "Selection: ");
        scanf("%d", &s);
        switch(s) {
            case 0:
                printf("Goodbye\n");
                return 0;
            case 1:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql = (char*)malloc(sizeof("SELECT DISTINCT(Type) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s;"));
                sprintf(sql,"SELECT DISTINCT(Type) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s;\n",id);
                printf("Games: \n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 2:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql = (char*)malloc(sizeof("SELECT Type, SUM(TimePlayed) FROM Plays as P, Game as G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(TimePlayed) DESC LIMIT 1;"));
                sprintf(sql, "SELECT Type, SUM(TimePlayed) FROM Plays as P, Game as G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(TimePlayed) DESC LIMIT 1;\n", id);
                printf("Most played with time in minutes:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 3:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql = (char*)malloc(sizeof("SELECT Type, SUM(CashOutAmount - CashInAmount) FROM Plays AS P, Game AS G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(CashOutAmount - CashInAmount) DESC LIMIT 1;"));
                sprintf(sql, "SELECT Type, SUM(CashOutAmount - CashInAmount) FROM Plays AS P, Game AS G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(CashOutAmount - CashInAmount) DESC LIMIT 1;\n", id);
                printf("Most profitable game with amount won:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 4:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(CashOutAmount - CashInAmount) ASC LIMIT 1;"));
                sprintf(sql, "SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.MemberId=%s AND P.GameName=G.Name GROUP BY GameName ORDER BY SUM(CashOutAmount - CashInAmount) ASC LIMIT 1;", id);
                printf("Least profitable game with amount lost:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 5:
                sql=(char*)malloc(sizeof("SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.GameName=G.Name GROUP BY Type ORDER BY SUM(CashInAmount - CashOutAmount) DESC LIMIT 1;"));
                sprintf(sql, "SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.GameName=G.Name GROUP BY Type ORDER BY SUM(CashInAmount - CashOutAmount) DESC LIMIT 1;");
                printf("\nMost profitable game:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 6:
                sql=(char*)malloc(sizeof("SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.GameName=G.Name GROUP BY Type ORDER BY SUM(CashInAmount - CashOutAmount) ASC LIMIT 1;"));
                sprintf(sql, "SELECT Type, SUM(CashInAmount - CashOutAmount) FROM Plays AS P, Game AS G WHERE P.GameName=G.Name GROUP BY Type ORDER BY SUM(CashInAmount - CashOutAmount) ASC LIMIT 1;");
                printf("\nLeast profitable game:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 7:
                printf("\nEnter Game Type to look up: ");
                scanf("%s", UGTI);
                sql=(char*)malloc(sizeof("SELECT COUNT(*) FROM Game WHERE Type LIKE '%%';")+sizeof(UGTI));
                sprintf(sql, "SELECT COUNT(*) FROM Game WHERE Type LIKE '%c%s%c';", 37,UGTI,37);
                printf("%s units:\n"
                       "----------------------------\n",UGTI);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 8:
                sql=(char*)malloc(sizeof("SELECT COUNT(*) FROM Game WHERE Type NOT LIKE '%slot machine%';"));
                sprintf(sql, "SELECT COUNT(*) FROM Game WHERE Type NOT LIKE '%cslot machine%c';",37,37);
                printf("\nTotal Tables:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 9:
                printf("\nEnter DealerId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT Type, GameName FROM Runs as R, Game as G WHERE R.DealerId=%s AND R.IsActive=TRUE AND G.Name=R.GameName;"));
                sprintf(sql, "SELECT Type, GameName FROM Runs as R, Game as G WHERE R.DealerId=%s AND R.IsActive=TRUE AND G.Name=R.GameName;", id);
                printf("Dealer with id %s is in control of:\n"
                       "----------------------------\n", id);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 10:
                sql=(char*)malloc(sizeof("SELECT COUNT(*) FROM Member;"));
                sprintf(sql, "SELECT COUNT(*) FROM Member;");
                printf("\nNumber of Members:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 11:
                sql=(char*)malloc(sizeof("SELECT COUNT(*) FROM Game;"));
                sprintf(sql, "SELECT COUNT(*) FROM Game;");
                printf("\nNumber of Games:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 12:
                sql=(char*)malloc(sizeof("SELECT COUNT(*) FROM Dealer;"));
                sprintf(sql, "SELECT COUNT(*) FROM Dealer;");
                printf("\nNumber of Dealers:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 13:
                sql=(char*)malloc(sizeof("SELECT D.Name, Type FROM Runs AS R, Dealer AS D, Game as G WHERE R.IsActive=1 AND D.Id=R.DealerId AND G.Name=R.GameName;"));
                sprintf(sql, "SELECT D.Name, Type FROM Runs AS R, Dealer AS D, Game as G WHERE R.IsActive=1 AND D.Id=R.DealerId AND G.Name=R.GameName;");
                printf("\nActive Dealers:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 14:
                sql=(char*)malloc(sizeof("SELECT SUM(CashInAmount)-SUM(CashOutAmount) FROM Plays;"));
                sprintf(sql, "SELECT SUM(CashInAmount)-SUM(CashOutAmount) FROM Plays;");
                printf("\nNet profit of casino:\n"
                       "----------------------------\n");
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 15:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT SUM(CashInAmount)-SUM(CashOutAmount) FROM Plays WHERE MemberId=%s;"));
                sprintf(sql, "SELECT SUM(CashInAmount)-SUM(CashOutAmount) FROM Plays WHERE MemberId=%s;", id);
                printf("Member with id %s money spent:\n"
                       "----------------------------\n", id);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 16:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT SUM(TimePlayed) FROM Plays WHERE MemberId=%s;"));
                sprintf(sql, "SELECT SUM(TimePlayed) FROM Plays WHERE MemberId=%s;", id);
                printf("Member with id %s playtime in minutes:\n"
                       "----------------------------\n", id);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 17:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT COUNT(DISTINCT(Type)) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s;"));
                sprintf(sql, "SELECT COUNT(DISTINCT(Type)) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s;", id);
                printf("Number of games Member with id %s has played:\n"
                       "----------------------------\n", id);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            case 18:
                printf("\nEnter MemberId to look up: ");
                scanf("%s", id);
                sql=(char*)malloc(sizeof("SELECT Type, SUM(TimePlayed) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s GROUP BY GameName;"));
                sprintf(sql, "SELECT Type, SUM(TimePlayed) FROM Game AS G, Plays AS P WHERE P.GameName=G.Name AND P.MemberId=%s GROUP BY GameName;", id);
                printf("Member with id %s game time playing table in minutes:\n"
                       "----------------------------\n", id);
                c= sqlite3_exec(db, sql, callback, 0, &ErrMsg);
                if(c!=SQLITE_OK){
                    printf("SQL Error: %s\n", ErrMsg);
                    sqlite3_free(ErrMsg);
                }
                else{
                    printf("----------------------------\n"
                           "Operation done successfully\n");
                }
                break;
            default:
                printf("\nInvalid selection please try again.\n"
                       "Enter 0 to exit.\n");
        }
    }
    sqlite3_close(db);
}
