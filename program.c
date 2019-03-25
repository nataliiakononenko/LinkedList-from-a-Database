#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

struct Node* head;

struct Node {

  char* brukernavn;
  char* passord;
  char* uid;
  char* gid;
  char* navn;
  char* hjemmekatalog;
  char* kommandotolker;

  struct Node *next;
};

void append(struct Node *head, char* a, char* b, char* c, char* d, char* e, char  * f, char* g)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = head;

      new_node->brukernavn  = malloc(strlen(a));
      new_node->passord = malloc(strlen(b));
      new_node->uid = malloc(strlen(c));
      new_node->gid = malloc(strlen(d));
      new_node->navn = malloc(strlen(e));
      new_node->hjemmekatalog = malloc(strlen(f));
      new_node->kommandotolker = malloc(strlen(g));

      new_node->next = NULL;

      strcpy(new_node->brukernavn, a);
      strcpy(new_node->passord, b);
      strcpy(new_node->uid, c);
      strcpy(new_node->gid, d);
      strcpy(new_node->navn, e);
      strcpy(new_node->hjemmekatalog, f);
      strcpy(new_node->kommandotolker, g);

    if (head == NULL)
    {
       head = new_node;
       return;
    }

      while (last->next != NULL)
        last = last->next;

    last->next = new_node;

    return;
}

void printList(struct Node *node)
{
  while (node != NULL)
  {
     printf("\n Studentkonto: \n BRUKERNAVN: %s\n PASSORD: %s\n UID: %s\n GID: %  s\n NAVN: %s\n KATALOG: %s\n TOLKER: %s\n ",
         node->brukernavn,
         node->passord,
         node->uid,
         node->gid,
         node->navn,
         node->hjemmekatalog,
         node->kommandotolker
        ) ;
     node = node->next;
  }
}

static int callback(void *list, int argc, char **argv, char **azColName){

   struct Node *head = list;

   append(head, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6] );

   return 0;
}


int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   rc = sqlite3_open("passwd.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   head = (struct Node*) malloc(sizeof(struct Node));

   sql = "SELECT * from Bruker";

   rc = sqlite3_exec(db, sql, callback, head, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }

  printList(head);

  sqlite3_close(db);

  return 0;
}
